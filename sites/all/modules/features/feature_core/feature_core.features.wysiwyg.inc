<?php
/**
 * @file
 * feature_core.features.wysiwyg.inc
 */

/**
 * Implements hook_wysiwyg_default_profiles().
 */
function feature_core_wysiwyg_default_profiles() {
  $profiles = array();

  // Exported profile: fitered_html_with_editor
  $profiles['fitered_html_with_editor'] = array(
    'format' => 'fitered_html_with_editor',
    'editor' => 'ckeditor',
    'settings' => array(
      'default' => 1,
      'user_choose' => 0,
      'show_toggle' => 1,
      'theme' => 'advanced',
      'language' => 'en',
      'buttons' => array(
        'default' => array(
          'Bold' => 1,
          'Italic' => 1,
          'Underline' => 1,
          'JustifyLeft' => 1,
          'JustifyCenter' => 1,
          'JustifyRight' => 1,
          'BulletedList' => 1,
          'NumberedList' => 1,
          'Link' => 1,
          'Anchor' => 1,
          'TextColor' => 1,
          'BGColor' => 1,
          'Blockquote' => 1,
          'Cut' => 1,
          'Copy' => 1,
          'Paste' => 1,
          'PasteText' => 1,
          'RemoveFormat' => 1,
          'Font' => 1,
          'FontSize' => 1,
          'Styles' => 1,
          'Table' => 1,
          'Smiley' => 1,
        ),
      ),
      'toolbar_loc' => 'top',
      'toolbar_align' => 'left',
      'path_loc' => 'bottom',
      'resizing' => 1,
      'verify_html' => 1,
      'preformatted' => 0,
      'convert_fonts_to_spans' => 1,
      'remove_linebreaks' => 1,
      'apply_source_formatting' => 0,
      'paste_auto_cleanup_on_paste' => 0,
      'block_formats' => 'p,address,pre,h2,h3,h4,h5,h6,div',
      'css_setting' => 'theme',
      'css_path' => '',
      'css_classes' => '',
    ),
    'rdf_mapping' => array(),
  );

  return $profiles;
}
