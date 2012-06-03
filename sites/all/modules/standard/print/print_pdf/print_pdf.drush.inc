<?php

/**
 * @file
 * drush integration for print_pdf module PDF libraries download.
 */

/**
 * The PDF project download URL
 */

/**
 * Implements hook_drush_command().
 */
function print_pdf_drush_command() {
  $items = array();

  $pdf_libs = array();
  drush_command_invoke_all_ref('drush_pdf_libs_alter', $pdf_libs);

  $items['print-pdf-download'] = array(
    'description' => 'Download and extract a PDF library.',
    'arguments' => array(
      'library' => dt('The PDF library to download. Available choices: !libs.', array('!libs' => implode(', ', array_keys($pdf_libs)))),
    ),
    'options' => array(
      'path' => dt('A path to the download folder. If omitted Drush will use the default location (@path).', array('@path' => 'sites/all/libraries')),
    ),
    'aliases' => array('pdfdl'),
    'bootstrap' => DRUSH_BOOTSTRAP_DRUPAL_ROOT, // No site or config needed.
  );

  return $items;
}

/**
 * Implements of drush_hook_COMMAND_validate().
 */
function drush_print_pdf_download_validate($library = NULL) {
  if (is_null($library)) {
    $pdf_libs = array();
    drush_command_invoke_all_ref('drush_pdf_libs_alter', $pdf_libs);

    drush_set_error('DRUSH_PDFDL_MISSING_ARG', dt("Usage: drush !cmd <library>\nWhere <library> is one of the following: !libs\n\nTry 'drush !cmd --help' for more information.", array('!cmd' => 'print-pdf-download', '!libs' => implode(', ', array_keys($pdf_libs)))));
  }
}

/**
 * Download and extract PDF archive.
 *
 * @param string $library
 *   library to download
 */
function drush_print_pdf_download($library) {
  $pdf_libs = array();
  drush_command_invoke_all_ref('drush_pdf_libs_alter', $pdf_libs);

  if (isset($library) && isset($pdf_libs[drupal_strtolower($library)])) {
    $func = $pdf_libs[drupal_strtolower($library)]['callback'];

    $download_url = $func();
    if ($download_url) {
      $path = drush_get_option('path');
      if (empty($path)) {
        $path = drush_get_context('DRUSH_DRUPAL_ROOT') . '/sites/all/libraries';
      }

      // Create the path if it does not exist.
      if (!is_dir($path)) {
        drush_op('mkdir', $path);
        drush_log(dt('Directory @path was created', array('@path' => $path)), 'notice');
      }

      // Chdir to the download location.
      $olddir = getcwd();
      drush_op('chdir', $path);

      // Warn about an existing dir
      if (is_dir($library)) {
        // drush_op('rmdir', $library); // Directory must be empty for the php rmdir to work..
        drush_log(dt('An existing @library was overwritten at @path', array('@library' => $library, '@path' => $path . '/' . $library)), 'notice');
      }

      // Download the archive
      $filename = _print_pdf_drush_download_file($download_url);
      if ($filename) {
        $extract_ret = _print_pdf_drush_download_extract($filename);
        if ($extract_ret) {
          // Remove the archive
          drush_op('unlink', $filename);
          drush_log(dt('@file has been downloaded and extracted in @path', array('@file' => $filename, '@path' => $path)), 'success');
        }
        else {
          drush_log(dt('@file has been downloaded to @path, but extract failed. Check that you have the necessary program installed, and if necessary extract it manually.',
                    array('@file' => $filename, '@path' => $path)), 'warning');
        }
      }
      else {
        drush_log(dt('Drush was unable to download @library to @path', array('@library' => $library, '@path' => $path)), 'error');
      }

      // Set working directory back to the previous working directory.
      drush_op('chdir', $olddir);
    }
  }
  else {
    drush_log(dt('Please specify a PDF library. Available choices: !libs.', array('!libs' => implode(', ', array_keys($pdf_libs)))), 'error');
  }
}

/**
 * Download a file using wget or curl
 *
 * Adapted from a function in drush/includes/drush.inc to support 302 redirects.
 *
 * @param string $download_url
 *   The path to the file to download
 *
 * @return string
 *   The filename that was downloaded, or NULL if the file could not be
 *   downloaded.
 */
function _print_pdf_drush_download_file($download_url) {
  $wget_ret = drush_shell_exec("wget -nv --trust-server-names %s", $download_url);

  if (!drush_get_context('DRUSH_SIMULATE')) {
    if ($wget_ret) {
      // Get the filename of the saved file from the output
      $wget_out = explode('"', array_shift(drush_shell_exec_output()));
      $filename = $wget_out[1];
    }
    else {
      $tempnam = uniqid('print_pdf_drush_');

      $curl_ret = drush_shell_exec("curl -s -L -o %s %s -w '%%{url_effective}'", $tempnam, $download_url);
      if ($curl_ret) {
        // File was donwloaded with the tempname

        // Find the effective name
        $filename = explode('/', array_shift(drush_shell_exec_output()));
        $filename = array_pop($filename);

        // Rename file from tempname to effective name
        if (!drush_op('rename', $tempnam, './' . $filename)) {
          $filename = $tempnam;
        }
      }
      else {
        $filename = FALSE;
      }
    }
  }
  else {
    $filename = basename($download_url);
  }

  return $filename;
}

/**
 * Helper to extract the downloaded zip/tar archive.
 *
 * @param string $filename
 *   filename of the file to extract
 *
 * @return bool
 *   TRUE on success, FALSE on failure
 */
function _print_pdf_drush_download_extract($filename) {
  $arch_ret = FALSE;

  if (drush_op('is_file', $filename)) {
    switch (drush_op('mime_content_type', $filename)) {
      case 1:
        $arch_ret = TRUE;
        break;
      case 'application/zip':
        // Decompress the zip archive
        $arch_ret = drush_shell_exec('unzip -qq -o ' . $filename);
        // ZIP archives usually get the access rights wrong
        drush_log(dt('@filename is a Zip file. Check the access permissions of the extracted files.', array('@filename' => $filename)), 'warning');
        break;
      case 'application/x-gzip':
        // Decompress the tar gz archive
        $arch_ret = drush_shell_exec('tar xzf ' . $filename);
        break;
      case 'application/x-bzip2':
        // Decompress the tar bz2 archive
        $arch_ret = drush_shell_exec('tar xjf ' . $filename);
        break;
    }
  }
  else {
    drush_log(dt('@filename not found.', array('@filename' => $filename)), 'error');
  }

  return $arch_ret;
}
