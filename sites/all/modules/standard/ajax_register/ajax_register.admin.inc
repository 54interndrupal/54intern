<?php

/**
 * @file
 * Provides form with AJAX REGISTER module settings.
 */

/**
 * Administrative settings form.
 */
function ajax_register_admin_form($form, $form_state) {

  $form['ajax_register_modal'] = array(
    '#type' => 'fieldset',
    '#title' => t('Modal window settings'),
  );

  $form['ajax_register_modal']['ajax_register_modal_width'] = array(
    '#type' => 'textfield',
    '#title' => t('Modal window width'),
    '#size' => 4,
    '#field_suffix' => 'px',
    '#default_value' => variable_get('ajax_register_modal_width', 550),
  );

  $form['ajax_register_modal']['ajax_register_modal_background_opacity'] = array(
    '#type' => 'select',
    '#title' => t('Background opacity'),
    '#options' => array(
      '0'   => '0%',
      '0.1' => '10%',
      '0.2' => '20%',
      '0.3' => '30%',
      '0.4' => '40%',
      '0.5' => '50%',
      '0.6' => '60%',
      '0.7' => '70%',
      '0.8' => '80%',
      '0.9' => '90%',
      '1'   => '100%',
    ),
    '#default_value' => variable_get('ajax_register_modal_background_opacity', '0.7'),
  );

  $form['ajax_register_modal']['ajax_register_modal_background_color'] = array(
    '#type' => 'textfield',
    '#title' => t('Background color'),
    '#size' => 6,
    '#maxlength' => 6,
    '#field_prefix' => '#',
    '#default_value' => variable_get('ajax_register_modal_background_color', '000000'),
  );

  $form['ajax_register_modal']['ajax_register_hide_captcha'] = array(
    '#type' => 'checkbox',
    '#title' => t('Hide captcha in modal dialog'),
    '#description' => t('Capctha protects your site from spambots.
      But they have no js enabled, so spambots will never see modal dialog and will be redirected to normal login/register form with captcha.'),
    '#default_value' => variable_get('ajax_register_hide_captcha', FALSE),
  );

  if (!module_exists('captcha')) {
    $form['ajax_register_modal']['ajax_register_hide_captcha']['#disabled'] = TRUE;
    $form['ajax_register_modal']['ajax_register_hide_captcha']['#title'] .= ' (' . t('requires CAPTCHA module') . ')';
  }

  $form['ajax_register_forms'] = array(
    '#type' => 'fieldset',
    '#title' => t('Form settings'),
  );

  $form['ajax_register_forms']['ajax_register_form_enable_modal_links'] = array(
    '#type' => 'checkbox',
    '#title' => t('Enable links in modal window'),
    '#description' => t('Check if links to another forms should appear in modal form'),
    '#default_value' => variable_get('ajax_register_form_enable_modal_links', TRUE),
  );

  $form['ajax_register_forms']['ajax_register_login_form_redirect'] = array(
    '#type' => 'textfield',
    '#title' => t('Login form redirect url'),
    '#description' => t('Url that the user will be redirected after a successful login. Leave empty for simple page reload.'),
    '#default_value' => variable_get('ajax_register_login_form_redirect', ''),
  );

  $form['ajax_register_forms']['ajax_register_register_form_redirect'] = array(
    '#type' => 'textfield',
    '#title' => t('Register form redirect url'),
    '#description' => t('Url that the user will be redirected after a successful registration. Leave empty for simple page reload. Enter @no_redirect for no redirect.',
      array('@no_redirect' => '<noredirect>')),
    '#default_value' => variable_get('ajax_register_register_form_redirect', ''),
  );

  return system_settings_form($form);
}
