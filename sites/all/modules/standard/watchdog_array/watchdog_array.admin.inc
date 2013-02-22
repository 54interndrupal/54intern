<?php

/**
 * @file
 * Presents the admin interface for the module.
 */

/**
 * The actual settings form in admin/config/development/watchdog-array.
 */
function watchdog_array_config() {
  $form = array();

  $form['watchdog_array_encapsulate_array_in_pre'] = array(
    '#type'          => 'checkbox',
    '#title'         => t('Encapsulate the array passed with the &lt;pre&gt; tag'),
    '#description'   => t('Encapsulating the array with the &lt;pre&gt; tag will make the array more readable in the admin interface.'),
    '#default_value' => variable_get('watchdog_array_encapsulate_array_in_pre', TRUE),
  );

  return system_settings_form($form);
}
