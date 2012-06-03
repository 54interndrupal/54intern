<?php

/**
 * @file
 * Generates the PDF versions of the pages
 *
 * This file is included by the print_pdf module and includes the
 * functions that interface with the PDF generation packages.
 *
 * @ingroup print
 */

module_load_include('inc', 'print', 'print.pages');

/**
 * Generate a PDF version of the printer-friendly page
 *
 * @see print_controller()
 * @see _print_pdf_dompdf()
 * @see _print_pdf_tcpdf()
 */
function print_pdf_controller() {
  // Disable caching for generated PDFs, as Drupal doesn't ouput the proper headers from the cache
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

    $pdf_filename = variable_get('print_pdf_filename', PRINT_PDF_FILENAME_DEFAULT);
    if (!empty($pdf_filename) && !empty($node)) {
      $pdf_filename = token_replace($pdf_filename, array('node' => $node));
    }
    else {
      $pdf_filename = token_replace($pdf_filename, array('site'));
      if (empty($pdf_filename) || count(token_scan($pdf_filename))) {
        // If there are still tokens, use a fallback solution
        $pdf_filename = str_replace('/', '_', $path);
      }
    }
  }
  else {
    $pdf_filename = 'page';
  }

  if (function_exists('transliteration_clean_filename')) {
    $pdf_filename = transliteration_clean_filename($pdf_filename, language_default('language'));
  }

  drupal_alter('print_pdf_filename', $pdf_filename, $path);

  $pdf = print_pdf_generate_path($path, $cid, $pdf_filename . '.pdf');
  if ($pdf == NULL) {
    drupal_goto($path);
    exit;
  }

  $nodepath = (isset($node->path) && is_string($node->path)) ? drupal_get_normal_path($node->path) : 'node/' . $path;
  db_merge('print_pdf_page_counter')
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
 * Gennerate a PDF for a given Drupal path.
 *
 * @param string $path
 *   path of the page to convert to PDF
 * @param int $cid
 *   (optional) comment ID of the comment to render.
 * @param string $pdf_filename
 *   (optional) filename of the generated PDF
 *
 * @return
 *   generated PDF page, or NULL in case of error
 *
 * @see print_pdf_controller()
 */
function print_pdf_generate_path($path, $cid = NULL, $pdf_filename = NULL) {
  global $base_url;

  $link = print_pdf_print_link();
  $node = print_controller($path, $link['format'], $cid);
  if ($node) {
    $html = theme('print', array('node' => $node, 'expand_css' => TRUE, 'format' => $link['format']));

    // Img elements must be set to absolute
    $pattern = '!<(img\s[^>]*?)>!is';
    $html = preg_replace_callback($pattern, '_print_rewrite_urls', $html);

    // Convert the a href elements, to make sure no relative links remain
    $pattern = '!<(a\s[^>]*?)>!is';
    $html = preg_replace_callback($pattern, '_print_rewrite_urls', $html);
    // And make anchor links relative again, to permit in-PDF navigation
    $html = preg_replace("!${base_url}/" . $link['path'] . '/.*?#!', '#', $html);

    $meta = array(
      'node' => $node,
      'url' => url(drupal_get_path_alias(empty($node->nid) ? $node->path : "node/$node->nid"), array('absolute' => TRUE)),
    );
    if (isset($node->name)) $meta['name'] = $node->name;
    if (isset($node->title)) $meta['title'] = $node->title;

    return print_pdf_generate_html($html, $meta, $pdf_filename);
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
 * @see print_pdf_controller()
 */
function _print_pdf_file_access_images($html) {
  global $base_url, $language;
  $print_pdf_images_via_file = variable_get('print_pdf_images_via_file', PRINT_PDF_IMAGES_VIA_FILE_DEFAULT);

  $lang = (function_exists('language_negotiation_get_any') && language_negotiation_get_any('locale-url')) ? $language->language : '';

  // Always convert private to local paths
  $pattern = "!(<img\s[^>]*?src\s*?=\s*?['\"]?)${base_url}/(?:(?:index.php)?\?q=)?(?:${lang}/)?system/files/([^>]*?>)!is";
  $replacement = '$1file://' . realpath(variable_get('file_private_path', '')) . '/$2';
  $html = preg_replace($pattern, $replacement, $html);
  if ($print_pdf_images_via_file) {
    $pattern = "!(<img\s[^>]*?src\s*?=\s*?['\"]?)${base_url}/(?:(?:index.php)?\?q=)?(?:${lang}/)?([^>]*?>)!is";
    $replacement = '$1file://' . dirname($_SERVER['SCRIPT_FILENAME']) . '/$2';
    $html = preg_replace($pattern, $replacement, $html);
  }

  return $html;
}
