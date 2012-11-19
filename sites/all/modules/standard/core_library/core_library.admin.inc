<?php

/**
 * @file
 * Core Library module administration pages.
 */

/**
 * Main administration screen.
 */
function core_library_admin_settings($form, &$form_state) {

  $form['bypass'] = array(
    '#type' => 'fieldset',
    '#title' => t("Drupal aggregation mecanism bypass"),
    '#collapsible' => FALSE,
  );
  $form['bypass']['core_library_bypass'] = array(
    '#type' => 'radios',
    '#options' => array(
      NULL => t("Disabled") . '<br/><small>' . t("Let Drupal core do what it has to do. If you select this, you should then disable this module.") . '</small>',
      LIBRARY_MODE_MANUAL => t("Manual") . '<br/><small>' . t("Let the site admin choose which file should go through the aggregation process. This needs the Core Library Advanced UI module to be enabled at least to choose the files.") . '</small>',
      LIBRARY_MODE_LEARNING_ANONYMOUS => t("Anonymous only") . '<br/><small>' . t("Automatically learn files that are being used for anymous users only.") . '</small>',
      LIBRARY_MODE_LEARNING_NO_ADMIN => t("All, no admin") . '<br/><small>' . t("Automatically learn files to aggregate while users browse, excluding the administration pages.") . '</small>',
      LIBRARY_MODE_LEARNING_ALL => t("All <cite>Pinage!</cite>") . '<br/><small>' . t("Automatically learn files to aggregate while users browse, including administration pages.") . '</small>',
      LIBRARY_MODE_BYPASS => t("Full bypass <cite>I'm done playing!</cite>") . '<br/><small>' . t("As you select this option, you consider that auto learning did its job, and you don't want to let Drupal core mess up anymore with aggregated files. This means that it won't never ever see new CSS and JS files until you revert this option, but you will save a lot of I/O bypassing its aggregation mecanism, good for production sites, totally wrong for development or testing sites.") . '</small>',
    ),
    '#default_value' => variable_get('core_library_bypass', NULL),
  );

  $form['css'] = array(
    '#type' => 'fieldset',
    '#title' => t("CSS grouping mode"),
    '#collapsible' => FALSE,
  );
  $form['css']['core_library_css_group'] = array(
    '#type' => 'radios',
    '#options' => array(
      NULL => t("Disabled") . '<br/><small>' . t("Let Drupal core group CSS as it intend to. This means that you will always get (at least) 3 CSS files, one per group.") . '</small>',
      LIBRARY_CSS_GROUP_DUAL => t("Dual mode") . '<br/><small>' . t("System libraries, and arbitrary module files in one single file, followed by theme specifics into another file.") . '</small>',
    ),
    '#default_value' => variable_get('core_library_css_group', NULL),
  );

  $form['behavior'] = array(
    '#type' => 'fieldset',
    '#title' => t("Behavior options"),
    '#collapsible' => FALSE,
  );
  $form['behavior']['core_library_respectful_preprocess'] = array(
    '#type' => 'checkbox',
    '#title' => t("Respect modules preprocess settings"),
    '#default_value' => variable_get('core_library_respectful_preprocess', TRUE),
    '#description' => t("Modules can decide weither or not their JavaScript or CSS files should preprocessed or not. Some of them are complex video players, such as the Media Element script and need multiple files packaged with them. When a JavaScript is preprocessed, it is moved to another location which can prevent it from finding additional files, if you experience JavaScript problems try to enable this option."),
  );

  $form['advanced'] = array(
    '#type' => 'fieldset',
    '#title' => t("Advanced options"),
    '#collapsible' => FALSE,
  );
  $form['advanced']['core_library_js_minify'] = array(
    '#type' => 'checkbox',
    '#title' => t("Minify JS"),
    '#default_value' => variable_get('core_library_js_minify', FALSE),
    '#description' => t("If checked, the system will attempt to minify JS files. This can lead to some JS crashing since a lot of custom JS files may not have been well formatted. Browsers are tolerant while minifier is not on JS syntax."),
  );

  $form = system_settings_form($form);

  $form['actions']['submit']['#submit'] = $form['#submit'];
  unset($form['#submit']);
  $form['actions']['submit']['#submit'][] = 'core_library_admin_settings_submit_prepare_cache';

  $form['actions']['clear'] = array(
    '#type' => 'submit',
    '#value' => t("Reset learnt files"),
    '#submit' => array('core_library_admin_settings_submit_clear'),
  );
  $form['actions']['rebuild'] = array(
    '#type' => 'submit',
    '#value' => t("Rebuild files"),
    '#attributes' => array('title' => t("This will force the system to rebuild aggregated and minified files.")),
    '#submit' => array('core_library_admin_settings_submit_rebuild'),
  );

  return $form;
}

/**
 * Prepare cache submit handler.
 */
function core_library_admin_settings_submit_prepare_cache($form, &$form_state) {
  $error = NULL;
  $error_variables = array();
  $directory = 'public://static';

  // Check our final static folder is valid.
  if (!file_prepare_directory($directory, FILE_CREATE_DIRECTORY | FILE_MODIFY_PERMISSIONS)) {
    $error = "Failed to create 'static-aggregation' directory, reverting aggregation bypass mode to manual.";
  }

  if ($error) {
    // Error must not break the Drupal site. In case of any error, revert to
    // manual mode, so the module will continue to work, but Drupal will also
    // continue to built its own final html head rendering.
    watchdog('core_library', $error, $error_variables, WATCHDOG_ERROR);
    drupal_set_message(t($error, $error_variables), 'error');

    // Revert variable, and set the error message for the end user.
    variable_set('core_library_bypass', LIBRARY_MODE_MANUAL);
  }

  // Also check for the JSMin library to be present, if the option is checked.
  if (variable_get('core_library_js_minify', TRUE) && !file_exists(core_library_js_minify_library_path())) {
    drupal_set_message(t("JSMin library was not found, see README.txt"), 'error');
    variable_set('core_library_js_minify', FALSE);
  }
}

/**
 * Clear learnt files submit handler.
 */
function core_library_admin_settings_submit_clear($form, &$form_state) {
  variable_del('library_aggregation_settings');
  variable_del('library_aggregation_orphans');
  variable_del('core_library_css_status');
  variable_del('core_library_updated');
  drupal_set_message(t("Current aggregation settings have been removed."));
  
  $current_mode = variable_get('core_library_bypass', NULL);
  if ($current_mode == LIBRARY_MODE_BYPASS || $current_mode == LIBRARY_MODE_MANUAL) {
    variable_set('core_library_bypass', NULL);
    drupal_set_message(t("Aggregation mode was bypass or manual, set back to default."));
  }
}

/**
 * Rebuild aggregated files submit handler.
 */
function core_library_admin_settings_submit_rebuild($form, &$form_state) {
  variable_del('core_library_css_status');
  variable_del('core_library_js_minified');
  drupal_set_message(t("Aggregated files marked for rebuild."));
  drupal_set_message(t("Minified files cache destroyed."));
}
