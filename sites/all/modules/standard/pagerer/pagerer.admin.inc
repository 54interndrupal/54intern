<?php
/**
 * @file
 * Pagerer administration
 *
 * Drupal core 7.x
 *
 * @package  User interface
 * @author   mondrake <mondrake@mondrake.org>
 */

/**
 * Main Pagerer settings admin form.
 */
function pagerer_settings_form($form, &$form_state) {
  // Initialize theme for safety.
  drupal_theme_initialize();
  // Add Pagerer's css.
  drupal_add_css(drupal_get_path('module', 'pagerer') . '/pagerer.css');
  // Get theme registry and pagerer variables.
  $theme_registry = theme_get_registry();
  $vars = _pagerer_get_variables();

  // Global option for pager override.
  $form['pagerer_override_pager'] = array(
    '#type' => 'checkbox',
    '#title' => t('Replace standard pager with Pagerer'),
    '#description' => t('Check to enable Pagerer features on any pager served by Drupal core.'),
    '#default_value' => $vars['pagerer_override_pager'],
    '#disabled' => !_pagerer_theme_override_safe($theme_registry, 'pager', 'theme_pager', 'system'),
  );

  // Global option to enable adaptive pager.
  $form['pagerer_enable_adaptive'] = array(
    '#type' => 'checkbox',
    '#title' => t('Enable adaptive pager'),
    '#description' => t('Check to enable Pagerer adaptive pager theme.'),
    '#default_value' => $vars['pagerer_enable_adaptive'],
    '#disabled' => !_pagerer_theme_override_safe($theme_registry, 'pager_link', 'theme_pager_link', 'system'),
  );

  // List of the themes available for panes.
  $options = array(
    'none',
    'pagerer_standard',
    'pagerer_mini',
    'pagerer_slider',
    'pagerer_progressive',
    'pagerer_adaptive',
  );
  $options = drupal_map_assoc($options);

  // Panes configuration.
  $form['panes_container'] = array(
    '#type' => 'fieldset',
    '#title' => t('Pagerer panes configuration'),
    '#description' => t('Select the themes to be rendered in each Pagerer pane. Click "Configure" to change each theme behaviour.'),
  );

  // Table container to render the 3 pane config boxes inline.
  $form['panes_container']['panes'] = array(
    '#tree'          => TRUE,
    '#title'         => t('Panes'),
    '#theme'         => 'table',
    '#header'        => array(),
    '#rows'          => array(),
    '#attributes'    => array('class' => array('pagerer_admin_panes_config')),
  );
  // Left pane.
  $left_pane = array(
    '#type' => 'fieldset',
    '#title' => t('Left pane'),
  );
  $left_pane['theme_name'] = array(
    '#type' => 'select',
    '#title' => t('Theme'),
    '#options' => $options,
    '#default_value' => $vars['left_pane']['theme_name'],
  );
  $left_pane['configure'] = array(
    '#type' => 'submit',
    '#name' => 'config_left',
    '#value' => t('Configure'),
  );
  // Center pane.
  $center_pane = array(
    '#type' => 'fieldset',
    '#title' => t('Center pane'),
  );
  $center_pane['theme_name'] = array(
    '#type' => 'select',
    '#title' => t('Theme'),
    '#options' => $options,
    '#default_value' => $vars['center_pane']['theme_name'],
  );
  $center_pane['configure'] = array(
    '#type' => 'submit',
    '#name' => 'config_center',
    '#value' => t('Configure'),
  );
  // Right pane.
  $right_pane = array(
    '#type' => 'fieldset',
    '#title' => t('Right pane'),
  );
  $right_pane['theme_name'] = array(
    '#type' => 'select',
    '#title' => t('Theme'),
    '#options' => $options,
    '#default_value' => $vars['right_pane']['theme_name'],
  );
  $right_pane['configure'] = array(
    '#type' => 'submit',
    '#name' => 'config_right',
    '#value' => t('Configure'),
  );
  // Container elements - FAPI accessible.
  $form['panes_container']['panes']['e'] = array(
    'left' => array('data' => &$left_pane),
    'center' => array('data' => &$center_pane),
    'right' => array('data' => &$right_pane),
  );
  // Container elements - to render the table.
  $form['panes_container']['panes']['#rows'][0] = array(
    array('data' => &$left_pane),
    array('data' => &$center_pane),
    array('data' => &$right_pane),
  );

  // Pagerer's preview.
  pager_default_initialize(47884, 50);
  $form['preview'] = array(
    '#type' => 'fieldset',
    '#title' => t('Pagerer preview'),
  );
  $form['preview']['pagerer'] = array(
    '#markup' => theme('pagerer', array(
                        'left_pane'   => $vars['left_pane'],
                        'center_pane' => $vars['center_pane'],
                        'right_pane' => $vars['right_pane'],
                      )),
  );

  // Save configuration.
  $form['save'] = array(
    '#type' => 'submit',
    '#name' => 'save',
    '#value' => t('Save configuration'),
  );

  return $form;
}

/**
 * Main Pagerer settings admin form - validation.
 */
function pagerer_settings_form_validate($form, &$form_state) {
  $v = &$form_state['values'];
  // Checks 'pagerer_adaptive' selected from panes if global option not enabled.
  if (!$v['pagerer_enable_adaptive']) {
    if ($v['panes']['e']['left']['data']['theme_name'] == 'pagerer_adaptive') {
      form_set_error(
        'panes][e][left][data',
        t('Turn on the "Enable adaptive pager" option to select the adaptive pager.', array())
      );
    }
    if ($v['panes']['e']['center']['data']['theme_name'] == 'pagerer_adaptive') {
      form_set_error(
        'panes][e][center][data',
        t('Turn on the "Enable adaptive pager" option to select the adaptive pager.', array())
      );
    }
    if ($v['panes']['e']['right']['data']['theme_name'] == 'pagerer_adaptive') {
      form_set_error(
        'panes][e][right][data',
        t('Turn on the "Enable adaptive pager" option to select the adaptive pager.', array())
      );
    }
  }
  // Check 'Config' was invoked without selecting a theme.
  if (strpos($form_state['triggering_element']['#name'], 'config', 0) === 0) {
    $e = explode('_', $form_state['triggering_element']['#name']);
    $pane = $e[1];
    if ($v['panes']['e'][$pane]['data']['theme_name'] == 'none') {
      form_set_error(
        'panes][e][' . $pane . '][data',
        t('Select a theme before clicking "Configure".', array())
      );
    }
  }
}

/**
 * Main Pagerer settings admin form - submission.
 */
function pagerer_settings_form_submit($form, &$form_state) {
  $vars = _pagerer_get_variables();
  $v = $form_state['values'];

  // Check if theme registry rebuild is needed.
  if ($vars['pagerer_override_pager'] <> $v['pagerer_override_pager']) {
    if ($v['pagerer_override_pager']) {
      drupal_set_message(t('Pagerer will replace Drupal core pager.'));
      watchdog(
        'pagerer',
        'Pagerer will replace Drupal core pager.',
        NULL,
        WATCHDOG_NOTICE
      );
    }
    else {
      drupal_set_message(t('Drupal core pager has been restored.'));
      watchdog(
        'pagerer',
        'Drupal core pager has been restored.',
        NULL,
        WATCHDOG_NOTICE
      );
    }
    $theme_rebuild = TRUE;
  }
  elseif ($vars['pagerer_enable_adaptive'] <> $v['pagerer_enable_adaptive']) {
    if ($v['pagerer_enable_adaptive']) {
      drupal_set_message(t('Pagerer adaptive pager is now enabled.'));
      watchdog(
        'pagerer',
        'Pagerer adaptive pager is now enabled.',
        NULL,
        WATCHDOG_NOTICE
      );
    }
    else {
      drupal_set_message(t('Pagerer adaptive pager has been disabled.'));
      watchdog(
        'pagerer',
        'Pagerer adaptive pager has been disabled.',
        NULL,
        WATCHDOG_NOTICE
      );
    }
    $theme_rebuild = TRUE;
  }
  else {
    $theme_rebuild = FALSE;
  }

  // Set variable.
  $vars['pagerer_override_pager'] = $v['pagerer_override_pager'];
  $vars['pagerer_enable_adaptive'] = $v['pagerer_enable_adaptive'];
  $vars['left_pane']['theme_name'] = $v['panes']['e']['left']['data']['theme_name'];
  $vars['center_pane']['theme_name'] = $v['panes']['e']['center']['data']['theme_name'];
  $vars['right_pane']['theme_name'] = $v['panes']['e']['right']['data']['theme_name'];
  variable_set('pagerer', $vars);
  drupal_set_message(t('The configuration options have been saved.'), 'status');

  // Theme registry rebuild.
  if ($theme_rebuild) {
    drupal_theme_rebuild();
  }

  // Hands over to pane configuration if a pane configuration button
  // was invoked.
  if (strpos($form_state['triggering_element']['#name'], 'config', 0) === 0) {
    $e = explode('_', $form_state['triggering_element']['#name']);
    $pane = $e[1];
    drupal_goto('admin/config/user-interface/pagerer/' . $pane);
  }
}

/**
 * Pagerer pane level settings admin form.
 */
function pagerer_pane_settings_form($form, &$form_state) {
  // Pane to be configured.
  $pane = $form_state['build_info']['args'][0];
  switch ($pane) {
    case 'left':
      $pane_t = t('Left');
      break;

    case 'center':
      $pane_t = t('Center');
      break;

    case 'right':
      $pane_t = t('Right');
      break;
  }

  // Merge configuration variables with those coming from default theme
  // variables.
  $vars = _pagerer_get_variables();
  $theme = $vars[$pane . '_pane']['theme_name'];
  if (isset($vars[$pane . '_pane']['theme_variables'])) {
    $theme_vars = $vars[$pane . '_pane']['theme_variables'];
  }
  else {
    $theme_vars = array();
  }
  $theme_registry = theme_get_registry();
  $default_theme_vars = $theme_registry[$theme]['variables'];
  $v = array_merge($default_theme_vars, $theme_vars);

  // Pane theme.
  $form['theme_name'] = array(
    '#type' => 'textfield',
    '#title' => t('@pane_t pane theme', array('@pane_t' => $pane_t)),
    '#default_value' => $theme,
    '#description' => t('To change the pane theme, go back to main Pagerer configuration.'),
    '#disabled' => TRUE,
  );
  $form['reset_theme'] = array(
    '#type' => 'submit',
    '#name' => 'reset_theme',
    '#value' => t('Reset theme defaults'),
  );

  $options = drupal_map_assoc(array('pages', 'items', 'item_ranges'));
  $form['display'] = array(
    '#type' => 'select',
    '#title' => t('Display'),
    '#options' => $options,
    '#default_value' => $v['display'],
    '#description' => t('Select whether to display pages, or items, or item ranges.'),
    '#required' => TRUE,
  );
  $form['quantity'] = array(
    '#type' => 'textfield',
    '#title' => t('Quantity'),
    '#default_value' => $v['quantity'],
    '#description' => t('The number of pages in the pager list.'),
    '#required' => TRUE,
    '#size' => 3,
    '#maxlength' => 3,
  );
  if ($theme == 'pagerer_progressive') {
    $form['factors'] = array(
      '#type' => 'textfield',
      '#title' => t('Scale factors'),
      '#default_value' => $v['factors'],
      '#description' => t('Comma delimited string of factors to use to determine progressive links.'),
      '#required' => TRUE,
    );
  }

  // Display configuration.
  $form['display_container'] = array(
    '#type' => 'fieldset',
    '#title' => t('Main elements'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
    '#description' => t('Configure main pager elements as "label", "current page" and "total".'),
  );
  $options = drupal_map_assoc(array('none', 'before_current', 'first', 'last'));
  $form['display_container']['label_display'] = array(
    '#type' => 'select',
    '#title' => t('Label'),
    '#options' => $options,
    '#default_value' => $v['label_display'],
    '#description' => t('Select whether and where to render a text "label" element (e.g. "Page:"). Options are "none" (not displayed), "before_current" (in front of current page), "first" (at the beginning), "last" (at the end).'),
    '#required' => TRUE,
  );
  $options = drupal_map_assoc(array('none', 'normal', 'widget', 'slider'));
  $form['display_container']['current_display'] = array(
    '#type' => 'select',
    '#title' => t('Current page'),
    '#options' => $options,
    '#default_value' => $v['current_display'],
    '#description' => t('Select how the current page is rendered in the pager. Options are "none" (not displayed), "normal" (as a text), "widget" (an active input box from where users can enter directly a page to go to), "slider" (as a slider).'),
    '#required' => TRUE,
  );
  $options = drupal_map_assoc(array('none', 'after_current', 'first', 'last'));
  $form['display_container']['total_display'] = array(
    '#type' => 'select',
    '#title' => t('Total pages/items'),
    '#options' => $options,
    '#default_value' => $v['total_display'],
    '#description' => t('Select whether and where to render a text element indicating the total pages (or items). Options are "none" (not displayed), "after_current" (just after current page), "first" (at the beginning), "last" (at the end).'),
    '#required' => TRUE,
  );

  // Links configuration.
  $form['links_container'] = array(
    '#type' => 'fieldset',
    '#title' => t('Links'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
    '#description' => t('Configure link elements like "<< first", "< previous", "next >" and "last >>".'),
  );
  $options = drupal_map_assoc(array('never', 'not_on_first', 'always'));
  $form['links_container']['first_link'] = array(
    '#type' => 'select',
    '#title' => t('First'),
    '#options' => $options,
    '#default_value' => $v['first_link'],
    '#description' => t('Select when to render a link to the first page (e.g. "<< first"). Options are "never" (not displayed), "not_on_first" (not displayed if current page is the first), "always" (always displayed).'),
    '#required' => TRUE,
  );
  $options = drupal_map_assoc(array('never', 'not_on_first', 'always'));
  $form['links_container']['previous_link'] = array(
    '#type' => 'select',
    '#title' => t('Previous'),
    '#options' => $options,
    '#default_value' => $v['previous_link'],
    '#description' => t('Select when to render a link to the previous page (e.g. "<< previous"). Options are "never" (not displayed), "not_on_first" (not displayed if current page is the first), "always" (always displayed).'),
    '#required' => TRUE,
  );
  $options = drupal_map_assoc(array('never', 'not_on_last', 'always'));
  $form['links_container']['next_link'] = array(
    '#type' => 'select',
    '#title' => t('Next'),
    '#options' => $options,
    '#default_value' => $v['next_link'],
    '#description' => t('Select when to render a link to the next page (e.g. "next >"). Options are "never" (not displayed), "not_on_last" (not displayed if current page is the last), "always" (always displayed).'),
    '#required' => TRUE,
  );
  $options = drupal_map_assoc(array('never', 'not_on_last', 'always'));
  $form['links_container']['last_link'] = array(
    '#type' => 'select',
    '#title' => t('Last'),
    '#options' => $options,
    '#default_value' => $v['last_link'],
    '#description' => t('Select when to render a link to the last page (e.g. "last >>"). Options are "never" (not displayed), "not_on_last" (not displayed if current page is the last), "always" (always displayed).'),
    '#required' => TRUE,
  );
  if ($theme == 'pagerer_adaptive' or $theme == 'pagerer_progressive') {
    $options = drupal_map_assoc(array('relative', 'absolute'));
    $form['links_container']['progr_links'] = array(
      '#type' => 'select',
      '#title' => t('Outer pages'),
      '#options' => $options,
      '#default_value' => $v['progr_links'],
      '#description' => t('Progressive and Adaptive pagers render links to pages far from the current. Select whether to render these links as "absolute" page numbers (or items/item ranges) or as "relative" offsets from current (e.g. "+10 +100 +1000").'),
      '#required' => TRUE,
    );
  }

  // Separators configuration.
  $form['separators_container'] = array(
    '#type' => 'fieldset',
    '#title' => t('Separators'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
    '#description' => t('Configure separators text.'),
  );
  $form['separators_container']['pager_breaker'] = array(
    '#type' => 'textfield',
    '#title' => t('Breaker'),
    '#default_value' => $v['pager_breaker'],
    '#description' => t('Text to render a break in the page sequence.'),
  );
  $form['separators_container']['pager_separator'] = array(
    '#type' => 'textfield',
    '#title' => t('Element separator'),
    '#default_value' => $v['pager_separator'],
    '#description' => t('Text to fill between contiguous pages. "none" will prevent creating any filler.'),
  );
  $form['separators_container']['range_separator'] = array(
    '#type' => 'textfield',
    '#title' => t('Range separator'),
    '#default_value' => $v['range_separator'],
    '#description' => t('Text to place between first and last item in a range.'),
  );

  // Advanced options configuration.
  $form['advanced_options_container'] = array(
    '#type' => 'fieldset',
    '#title' => t('Advanced options'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
    '#description' => t('Configure advanced options.'),
  );
  $form['advanced_options_container']['slider'] = array(
    '#type' => 'fieldset',
    '#title' => t('Slider'),
    '#collapsible' => FALSE,
    '#description' => t('jQuery slider options.'),
  );
  $options = drupal_map_assoc(array('tickmark', 'timelapse', 'auto'));
  $form['advanced_options_container']['slider']['slider_action'] = array(
    '#type' => 'select',
    '#title' => t('Action confirmation method'),
    '#options' => $options,
    '#default_value' => $v['slider_action'],
    '#description' => t('Select how the page relocation should be triggered after it has been selected through the slider. Options are: "tickmark" (page relocation only occurs after user clicks a tickmark on the slider handle), "timelapse" (page relocation occurs after a grace time has elapsed), "auto" (the timelapse method is automatically selected based on the accuracy of the slider).'),
    '#required' => TRUE,
  );
  $form['advanced_options_container']['slider']['slider_action_timelapse'] = array(
    '#type' => 'textfield',
    '#title' => t('Confirmation timelapse'),
    '#default_value' => $v['slider_action_timelapse'],
    '#description' => t('The grace time (in milliseconds) to wait before the page is relocated, in case "timelapse" confirmation method is selected. "0" will trigger relocation immediately.'),
    '#size' => 5,
    '#maxlength' => 5,
    '#required' => TRUE,
  );
  $options = drupal_map_assoc(array('yes', 'no', 'auto'));
  $form['advanced_options_container']['slider']['slider_navigation_icons'] = array(
    '#type' => 'select',
    '#title' => t('Display navigation icons'),
    '#options' => $options,
    '#default_value' => $v['slider_navigation_icons'],
    '#description' => t('Select whether to display +/- navigation icons on the sides of the slider. Options are "yes", "no", "auto" (the icons are automatically displayed based on the accuracy of the slider).'),
    '#required' => TRUE,
  );

  // Save configuration.
  $form['save'] = array(
    '#type' => 'submit',
    '#name' => 'save',
    '#value' => t('Save configuration'),
  );

  return $form;
}

/**
 * Pagerer pane level settings admin form - submission.
 */
function pagerer_pane_settings_form_submit($form, $form_state) {
  $pane = $form_state['build_info']['args'][0];
  $p = $pane . '_pane';
  $vars = _pagerer_get_variables();
  $v = $form_state['values'];

  // Reset theme defaults if button invoked.
  if ($form_state['triggering_element']['#name'] == 'reset_theme') {
    $theme = $v['theme_name'];
    $theme_registry = theme_get_registry();
    $default_theme_vars = $theme_registry[$theme]['variables'];
    $vars[$p]['theme_variables'] = $default_theme_vars;
    unset($vars[$p]['theme_variables']['tags']);
    variable_set('pagerer', $vars);
    drupal_set_message(t('The pane configuration has been reset to default %theme theme variables.', array('%theme' => $theme)), 'status');
    drupal_goto('admin/config/user-interface/pagerer/' . $pane);
  }

  $vars[$p]['theme_variables']['pager_breaker'] = $v['pager_breaker'];
  $vars[$p]['theme_variables']['pager_separator'] = $v['pager_separator'];
  $vars[$p]['theme_variables']['range_separator'] = $v['range_separator'];
  $vars[$p]['theme_variables']['display'] = $v['display'];
  $vars[$p]['theme_variables']['quantity'] = $v['quantity'];
  $vars[$p]['theme_variables']['label_display'] = $v['label_display'];
  $vars[$p]['theme_variables']['current_display'] = $v['current_display'];
  $vars[$p]['theme_variables']['total_display'] = $v['total_display'];
  $vars[$p]['theme_variables']['first_link'] = $v['first_link'];
  $vars[$p]['theme_variables']['previous_link'] = $v['previous_link'];
  $vars[$p]['theme_variables']['next_link'] = $v['next_link'];
  $vars[$p]['theme_variables']['last_link'] = $v['last_link'];
  if (isset($v['progr_links'])) {
    $vars[$p]['theme_variables']['progr_links'] = $v['progr_links'];
  }
  if (isset($v['factors'])) {
    $vars[$p]['theme_variables']['factors'] = $v['factors'];
  }
  $vars[$p]['theme_variables']['slider_action'] = $v['slider_action'];
  $vars[$p]['theme_variables']['slider_action_timelapse'] = $v['slider_action_timelapse'];
  $vars[$p]['theme_variables']['slider_navigation_icons'] = $v['slider_navigation_icons'];
  variable_set('pagerer', $vars);
  drupal_set_message(t('The configuration options have been saved.'), 'status');
  drupal_goto("admin/config/user-interface/pagerer");
}
