<?php

/**
 * @file
 * Core Library manual mode specifics functions.
 * 
 * This code will be used only in manual inclusion mode. When the site admin
 * decides that his configuration is solid enough, he will set the bypass mode
 * and these functions won't ever be called anymore.
 * 
 * This code tends to disappear in the future, but this is still solid code and
 * a nice PoC.
 */

function core_library_manual_init() {
  // Include required file, we may be the first to get here.
  require_once DRUPAL_ROOT . '/includes/common.inc';

  // Fetch site admin manually set settings.
  $settings = variable_get('library_aggregation_settings', array());

  foreach ($settings as $name => $values) {
    if ($values['mode'] == LIBRARY_AGGREGATE_ALL) {
      core_library_manual_process($values['module'], $name);
    }
  }
}

/**
 * Process library depedencies.
 * 
 * This function will be used only in manual mode. If you are in learning mode
 * all library files will be found and overriden at hook_library_TYPE_alter()
 * time.
 * 
 * Gather all libraries override for all pages including. Pragmatically set
 * all of them using drupal_add_js(), but set the drupal_static() cache of
 * drupal_add_library() first to avoid any hook calls for theses.
 */
function core_library_manual_process($module, $name) {
  // Bypass drupal_static() anti-pattern. All javascript and CSS we are going
  // to add will exists for the full runtime.
  static $processed = array(), $added;

  if (!isset($added)) {
    // We will populate the drupal_add_library() static cache ourself by adding
    // javascript and CSS files with our own algorithm.
    $added = &drupal_static('drupal_add_library', array());
  }

  // Security check, sometimes, $module is an array (but why?).
  if (!is_string($module) || !is_string($name)) {
    return;
  }

  // This will trigger the drupal_alter() over libraries.
  $library = drupal_get_library($module, $name);

  // Process dependencies recursively. Because dependencies will always remains
  // harcoded, the result will always be the same resulting in the same files
  // being aggregated at each page hit.
  if (isset($library['dependencies'])) {
    foreach ($library['dependencies'] as $dependency) {
      list($_module, $_name) = $dependency;
      if (!isset($processed[$_module . '-' . $_name])) {
        core_library_manual_process($_module, $_name);
      }
    }
  }

  // Force settings for JS and CSS files to ensure the aggregation.
  if (isset($library['js'])) {
    foreach ($library['js'] as $file => $data) {
      core_library_defaults_js($data);
      drupal_add_js($file, $data);
    }
  }
  if (isset($library['css'])) {
    foreach ($library['css'] as $file => $data) {
      $data['data'] = $file;
      core_library_defaults_css($data);
      drupal_add_css($file, $data);
    }
  }

  // Register the library to the core.
  $added[$module][$name] = TRUE;
  // Circular dependency and infinite recursivity breaker.
  $processed[$module . '-' . $name] = TRUE;
}
