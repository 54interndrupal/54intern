<?php

/**
 * @file
 * Generates the PDF version using mPDF
 *
 * This file is included by the print_pdf_mpdf module and includes the
 * functions that interface with the mPDF library
 *
 * @ingroup print
 */

/**
 * Implements hook_print_pdf_generate().
 */
function print_pdf_mpdf_print_pdf_generate($html, $meta, $filename = NULL) {
  $pdf_tool = explode('|', variable_get('print_pdf_pdf_tool', PRINT_PDF_PDF_TOOL_DEFAULT));
  $paper_size = variable_get('print_pdf_paper_size', PRINT_PDF_PAPER_SIZE_DEFAULT);
  $page_orientation = variable_get('print_pdf_page_orientation', PRINT_PDF_PAGE_ORIENTATION_DEFAULT);
  $content_disposition = variable_get('print_pdf_content_disposition', PRINT_PDF_CONTENT_DISPOSITION_DEFAULT);

  require_once(DRUPAL_ROOT . '/' . $pdf_tool[1]);

  $format = ($page_orientation == "landscape") ? $paper_size . "-L" : $paper_size;

  // Try to use local file access for image files
  $html = _print_pdf_file_access_images($html);

  // set document information
  $mpdf = new mPDF('UTF-8', $format);

  $mpdf->SetAuthor(strip_tags($meta['name']));
  $mpdf->SetCreator(variable_get('site_name', 'Drupal'));
  // Pulled from the HTML meta data
  // $mpdf->SetTitle(html_entity_decode($meta['title'], ENT_QUOTES, 'UTF-8'));

//  $keys = implode(' ', explode("\n", trim(strip_tags($print['taxonomy']))));
//  $mpdf->SetKeywords($keys);

  // Encrypt the file and grant permissions to the user to copy and print
  // No password is required to open the document
  // Owner has full rights using the password "MyPassword"
  // $mpdf->SetProtection(array('copy', 'print'), '', 'MyPassword');
  $mpdf->SetProtection(array('copy', 'print', 'print-highres'), '', '');

  $mpdf->WriteHTML($html);

  // try to recover from any warning/error
  ob_clean();

  if ($filename) {
    // Close and output PDF document
    $output_dest = ($content_disposition == 2) ? 'D' : 'I';
    $mpdf->Output($filename, $output_dest);
    return TRUE;
  }
  else {
    return $mpdf->Output('', 'S');
  }
}
