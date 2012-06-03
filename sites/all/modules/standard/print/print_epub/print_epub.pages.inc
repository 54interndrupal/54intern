<?php

/**
 * @file
 * Generates the EPUB versions of the pages
 *
 * This file is included by the print_epub module and includes the
 * functions that interface with the EPUB generation packages.
 *
 * @ingroup print
 */

module_load_include('inc', 'print', 'print.pages');

/**
 * Generate a EPUB version of the printer-friendly page
 *
 * @see print_controller()
 * @see _print_epub_domepub()
 * @see _print_epub_tcepub()
 */
function print_epub_controller() {
  // Disable caching for generated EPUBs, as Drupal doesn't ouput the proper headers from the cache
  $GLOBALS['conf']['cache'] = FALSE;

  $args = func_get_args();
  $path = filter_xss(implode('/', $args));
  $cid = isset($_GET['comment']) ? (int)$_GET['comment'] : NULL;

  if (!empty($path)) {
    if ($alias = drupal_lookup_path('source', $path)) {
      // Alias
      $path_arr = explode('/', $alias);
      $node = node_load($path_arr[1]);
    }
    elseif (ctype_digit($args[0])) {
      // normal nid
      $node = node_load($args[0]);
    }

    $epub_filename = variable_get('print_epub_filename', PRINT_EPUB_FILENAME_DEFAULT);
    if (!empty($epub_filename) && !empty($node)) {
      $epub_filename = token_replace($epub_filename, array('node' => $node));
    }
    else {
      $epub_filename = token_replace($epub_filename, array('site'));
      if (empty($epub_filename) || count(token_scan($epub_filename))) {
        // If there are still tokens, use a fallback solution
        $epub_filename = str_replace('/', '_', $path);
      }
    }
  }
  else {
    $epub_filename = 'page';
  }

  if (function_exists('transliteration_clean_filename')) {
    $epub_filename = transliteration_clean_filename($epub_filename, language_default('language'));
  }

  drupal_alter('print_epub_filename', $epub_filename, $path);

  $epub = print_epub_generate_path($path, $cid, $epub_filename . '.epub');
  if ($epub == NULL) {
    drupal_goto($path);
    exit;
  }

  $nodepath = (isset($node->path) && is_string($node->path)) ? drupal_get_normal_path($node->path) : 'node/' . $path;
  db_merge('print_epub_page_counter')
    ->key(array('path' => $nodepath))
    ->fields(array(
        'totalcount' => 1,
        'timestamp' => REQUEST_TIME,
    ))
    ->expression('totalcount', 'totalcount + 1')
    ->execute();

  drupal_exit();
}

/**
 * Gennerate a EPUB for a given Drupal path.
 *
 * @param string $path
 *   path of the page to convert to EPUB
 * @param int $cid
 *   (optional) comment ID of the comment to render.
 * @param string $epub_filename
 *   (optional) filename of the generated EPUB
 *
 * @return
 *   generated EPUB page, or NULL in case of error
 *
 * @see print_epub_controller()
 */
function print_epub_generate_path($path, $cid = NULL, $epub_filename = NULL) {
  global $base_url;

  $link = print_epub_print_link();
  $node = print_controller($path, $link['format'], $cid);
  if ($node) {
    $html = theme('print', array('node' => $node, 'expand_css' => TRUE, 'format' => $link['format']));

    $meta = array(
      'node' => $node,
      'url' => url(drupal_get_path_alias(empty($node->nid) ? $node->path : "node/$node->nid"), array('absolute' => TRUE)),
    );
    if (isset($node->name)) $meta['name'] = $node->name;
    if (isset($node->title)) $meta['title'] = $node->title;

    return print_epub_generate_html($html, $meta, $epub_filename);
  }
  else {
    return NULL;
  }
}

/**
 * Convert image paths to the file:// protocol
 *
 * In some Drupal setups, the use of the 'private' filesystem or Apache's
 * configuration prevent access to the images of the page. This function
 * tries to circumnvent those problems by accessing files in the local
 * filesystem.
 *
 * @param string $html
 *   contents of the post-processed template already with the node data
 *
 * @return string
 *   converted file names
 *
 * @see print_epub_controller()
 */
function _print_epub_file_access_images($html) {
  global $base_url, $language;
  $print_epub_images_via_file = variable_get('print_epub_images_via_file', PRINT_EPUB_IMAGES_VIA_FILE_DEFAULT);

  $lang = (function_exists('language_negotiation_get_any') && language_negotiation_get_any('locale-url')) ? $language->language : '';

  // Always convert private to local paths
  $pattern = "!(<img\s[^>]*?src\s*?=\s*?['\"]?)${base_url}/(?:(?:index.php)?\?q=)?(?:${lang}/)?system/files/([^>]*?>)!is";
  $replacement = '$1file://' . realpath(variable_get('file_private_path', '')) . '/$2';
  $html = preg_replace($pattern, $replacement, $html);
  if ($print_epub_images_via_file) {
    $pattern = "!(<img\s[^>]*?src\s*?=\s*?['\"]?)${base_url}/(?:(?:index.php)?\?q=)?(?:${lang}/)?([^>]*?>)!is";
    $replacement = '$1file://' . dirname($_SERVER['SCRIPT_FILENAME']) . '/$2';
    $html = preg_replace($pattern, $replacement, $html);
  }

  return $html;
}
