<?php

/**
 * @file
 * Core Library advanced UI module administration pages.
 */

/**
 * Get known orphans by removing the known library files.
 */
function _core_library_get_known_orphans() {
  // Gather all already known files for orphans exclusion.
  $known = array();
  $hook = 'library';
  foreach (module_implements('library') as $module) {
    foreach (module_invoke($module, $hook) as $name => $library) {
      if (isset($library['js'])) {
        foreach ($library['js'] as $file => $data) {
          $file = drupal_get_path('module', $module) . '/' . $file;
          $known[$file] = TRUE;
        }
      }
      if (isset($library['css'])) {
        foreach ($library['css'] as $file => $data) {
          $file = drupal_get_path('module', $module) . '/' . $file;
          $known[$file] = TRUE;
        }
      }
    }
  }

  $select = db_select('core_library_stat', 'l');
  $select->join('system', 's', 's.name = l.module');
  $select->addField('s', 'type', 'owner_type');
  return $select
    ->fields('l')
    ->condition('file', array_keys($known), 'NOT IN')
    ->orderBy('l.module', 'ASC')
    ->orderBy('l.type', 'ASC')
    ->orderBy('l.file', 'ASC')
    ->execute()
    ->fetchAll();
}

/**
 * Orphans administration screen.
 */
function core_library_admin_orphans($form, &$form_state) {
  $form['#tree'] = TRUE;

  // Abitrary do some packages. We will populate it then build a full array
  // for HTML build.
  $form['orphans'] = array();

  // Known orphans.
  $orphans = variable_get('library_aggregation_orphans', array());

  // Core fixed files that will exists on all pages whatever happens.
  $fixed = array('misc/drupal.js');

  foreach (_core_library_get_known_orphans() as $row) {
    $subform = array();

    // Rows that come back from database are module path agnostic, we need to
    // convert them to fit our real site here.
    if ($row->module != 'core') {
      $row->file = drupal_get_path($row->owner_type, $row->module) . '/' . $row->file;
    } 

    // Some metadata for display purpose only.
    $subform['row'] = array('#type' => 'value', '#value' => $row);

    // Other needed stuff.
    $subform['type'] = array('#type' => 'value', '#value' => $row->type);
    $subform['module'] = array('#type' => 'value', '#value' => $row->module);
    // The most important stuff: the mode selection.
    $subform['mode'] = array(
      '#type' => 'select',
      '#title' => t("Aggregation mode"),
      '#options' => array(
        LIBRARY_AGGREGATE_ALL => t("All"),
        // FIXME: Disabled, this was a (not so) good idea.
        // LIBRARY_AGGREGATE_PATH => t("Page"),
        LIBRARY_AGGREGATE_DEFAULT => t("Default"),
      ),
      '#default_value' => isset($orphans[$row->type][$row->file]['mode']) ? $orphans[$row->type][$row->file]['mode'] : LIBRARY_AGGREGATE_DEFAULT,
    );

    // Disable some fixed libraries (that core will append to aggregation
    // whatever happens).
    if (in_array($row->file, $fixed)) {
      $subform['mode']['#default_value'] = LIBRARY_AGGREGATE_ALL;
      $subform['mode']['#disabled'] = TRUE;
    }

    // All done.
    $form['orphans'][$row->module][$row->file] = $subform;
  }

  $form['buttons'] = array();
  $form['buttons']['submit'] = array(
    '#type' => 'submit',
    '#value' => t("Save"),
  );

  return $form;
}

function core_library_admin_orphans_submit($form, &$form_state) {
  $orphans = array();
  foreach ($form_state['values']['orphans'] as $module => $files) {
    foreach ($files as $file => $values) {
      // Add to our variable only if we need to.
      if ($values['mode'] != LIBRARY_AGGREGATE_DEFAULT) {
        $orphans[$values['type']][$file] = array(
          'mode' => $values['mode'],
          'module' => $module,
        );
      }
    }
  }
  variable_set('library_aggregation_orphans', $orphans);
  drupal_set_message(t("Libraries aggregation settings have been saved"));
}

/**
 * Libraries administration screen.
 */
function core_library_admin_libraries($form, &$form_state) {
  $form['#tree'] = TRUE;

  // Abitrary do some packages. We will populate it then build a full array
  // for HTML build.
  $form['libraries'] = array(
    'core' => array(),
    'effect' => array(),
    'ui' => array(),
    'contrib' => array(),
  );

  // Get current existing settings.
  $settings = variable_get('library_aggregation_settings', array());

  $hook = 'library';
  foreach (module_implements('library') as $module) {
    foreach (module_invoke($module, $hook) as $name => $library) {
      $subform = array();
      $subform['mode'] = array(
        '#type' => 'select',
        '#title' => t("Aggregation mode"),
        '#options' => array(
          LIBRARY_AGGREGATE_ALL => t("All"),
          LIBRARY_AGGREGATE_PATH => t("Page"),
          LIBRARY_AGGREGATE_DEFAULT => t("Default"),
        ),
        '#default_value' => isset($settings[$name]['mode']) ? $settings[$name]['mode'] : LIBRARY_AGGREGATE_DEFAULT,
      );
      $subform['description'] = array(
        '#type' => 'value',
        '#value' => $library,
      );
      $subform['module'] = array(
        '#type' => 'value',
        '#value' => $module,
      );
      // Find out type.
      if ($name == 'ui' || substr($name, 0, 3) == 'ui.') {
        $type = 'ui';
      }
      else if ($name == 'effects' || substr($name, 0, 8) == 'effects.') {
        $type = 'effect';
      }
      else if ($module == 'system') {
        $type = 'core';
      }
      else {
        $type = 'contrib';
      }
      // All done.
      $form['libraries'][$type][$name] = $subform;
    }
  }

  $form['buttons'] = array();
  $form['buttons']['submit'] = array(
    '#type' => 'submit',
    '#value' => t("Save"),
  );

  return $form;
}

function core_library_admin_libraries_submit($form, &$form_state) {
  $settings = array();
  foreach ($form_state['values']['libraries'] as $type => $libraries) {
    foreach ($libraries as $name => $values) {
      $settings[$name] = array(
        'mode'       => $values['mode'],
        'skip_alter' => isset($values['skip_alter']) ? $values['skip_alter'] : FALSE,
        'module'     => $values['module'],
      );
    }
  }
  variable_set('library_aggregation_settings', $settings);
  drupal_set_message(t("Libraries aggregation settings have been saved"));
}

/**
 * Export profile page.
 */
function core_library_admin_export_form($form, &$form_state, $callback) {
  $form['export'] = array(
    '#type' => 'markup',
    '#prefix' => '<pre id="export-text" style="background: white; color: black; padding: 0.5em 1em; border: 1px solid black;">',
    '#suffix' => '</pre>',
    '#markup' => is_callable($callback) ? $callback() : '',
  );
  if (module_exists('oox')) {
    $form['#attached'] = array('js' => array(
      drupal_get_path('module', 'oox') . '/js/jquery.copy.min.js',
      drupal_get_path('module', 'oox') . '/js/copy.js',
    ));
    $form['clip'] = array(
      '#type' => 'button',
      '#value' => t("Copy to clipboard"),
      '#attributes' => array('class' => array('copy-to-clipboard'), 'rel' => 'export-text'),
    );
  }
  return $form;
}

/**
 * Export all known files.
 */
function core_library_known_file_export() {
  $code = array();

  $code[] = "; This file was generated using the Core Library module.";
  $code[] = "; Built list of already known files for later use.";

  foreach (_core_library_get_known_orphans() as $row) {
    $code[] = $row->module . "[" . $row->type . "][] = " . $row->file;
  }

  return implode("\n", $code);
}

/**
 * Export current profile.
 */
function core_library_profile_export_current() {
  $code = array();

  $settings = variable_get('library_aggregation_settings', array());
  $orphans = variable_get('library_aggregation_orphans', array());

  $code[] = "; This file was generated using the Core Library module.";
  $code[] = "; Libraries.";
  uasort($settings, '_core_library_sort_by_module');

  foreach ($settings as $name => $options) {
    if ($options['mode'] == LIBRARY_AGGREGATE_ALL) {
      $code[] = "libraries[" . $options['module'] .  "][] = " . $name;
    }
  }

  foreach ($orphans as $type => $items) {
    $code[] = "; " . strtoupper($type) . " files.";
    foreach ($items as $file => $options) {
      if ($options['mode'] == LIBRARY_AGGREGATE_ALL) {
        $code[] = $type . "[] = " . $file;
      }
    }
  }

  return implode("\n", $code);
}

/**
 * Sort options array by module.
 */
function _core_library_sort_by_module($a, $b) {
  $a_module = is_array($a) && isset($a['module']) ? $a['module'] : '';
  $b_module = is_array($b) && isset($b['module']) ? $b['module'] : '';
  return strcasecmp($a_module, $b_module);
}

/**
 * Format a percent value for some tables.
 */
function _core_library_format_percent($max, $value) {
  return $value . " (" . round($value / $max * 100) . "%)";
}

/**
 * Orphan settings form theming function.
 */
function theme_core_library_admin_orphans(&$variables) {
  $elements = array('#type' => 'vertical_tabs');
  $form = &$variables['form'];

  // Headers will be the same for each table.
  $headers = array(t("File"), t("Module"), t("Type"), t("Mode"), t("Hits"), t("Admin hits"), t("Anonymous hits"));

  $tables = array();
  foreach (element_children($form['orphans']) as $module) {
    foreach (element_children($form['orphans'][$module]) as $file) {
      $frow = $form['orphans'][$module][$file]['row']['#value'];
      $row = array('data' => array());
      $row['data'][] = $file;
      $row['data'][] = $module;
      unset($form['orphans'][$module][$file]['mode']['#title']);
      $row['data'][] = $frow->type;
      $row['data'][] = drupal_render($form['orphans'][$module][$file]['mode']);
      $row['data'][] = $frow->hits;
      $row['data'][] = _core_library_format_percent($frow->hits, $frow->hits_admin);
      $row['data'][] = _core_library_format_percent($frow->hits, $frow->hits_anonymous);
      $tables[$frow->owner_type][] = $row;
    }
  }

  // New elements.
  foreach ($tables as $owner_type => $rows) {
    $elements[$owner_type] = array(
      '#type' => 'fieldset',
      '#title' => t(ucfirst($owner_type)),
      '#collapsible' => TRUE,
      '#collapsed' => TRUE,
      '#group' => 'owner_type',
      'content' => array(
        // F-ing theme system. Why wouldn't it use my theme function here? Because
        // it changes the variable to something other than the theme function will
        // understand, with absolutely no reasons!
        //'#type' => 'markup',
        // '#theme' => 'table',
        '#markup' => theme('table', array('header' => $headers, 'rows' => $rows))
        // 'header' => $headers,
        // 'rows' => $rows,
      ),
    );
  }

  return drupal_render($elements) . drupal_render_children($form);
}

/**
 * Libraries settings form theming function.
 */
function theme_core_library_admin_libraries(&$variables) {
  $elements = array('#type' => 'vertical_tabs');
  $form = &$variables['form'];

  // Headers will be the same for each table.
  $headers = array(t("Library"), t("Identifier"), t("Module"), t("Mode"));

  // Put different packages in different tables.
  foreach (element_children($form['libraries']) as $type) {
    $rows = array();
    foreach (element_children($form['libraries'][$type]) as $name) {
      $row = array('data' => array());
      $row['data'][] = $form['libraries'][$type][$name]['description']['#value']['title'];
      $row['data'][] = $name;
      $row['data'][] = $form['libraries'][$type][$name]['module']['#value'];
      unset($form['libraries'][$type][$name]['mode']['#title']);
      unset($form['libraries'][$type][$name]['skip_alter']['#title']);
      $row['data'][] = drupal_render($form['libraries'][$type][$name]['mode']);
      $rows[] = $row;
    }

    // New element.
    $elements[$type] = array(
      '#type' => 'fieldset',
      '#title' => $type,
      '#collapsible' => TRUE,
      '#collapsed' => TRUE,
      '#group' => 'library_types',
      'content' => array('#markup' => theme('table', array('header' => $headers, 'rows' => $rows))),
    );
  }

  return drupal_render($elements) . drupal_render_children($form);
}
