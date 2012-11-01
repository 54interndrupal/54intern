<?php

/**
 * @file
 * Page callback for ajax links.
 */

/**
 * Returns USER LOGIN / REGITER / PASSWORD form.
 * @param $form_type
 *   Type of form that should be loaded.
 * @param $js
 *   Show whether user has enabled js in his browser.
 */
function ajax_register_page_callback($form_type, $js) {
  Global $user;
  // Check whether js is enabled.
  if ($js) {

    // Include ctools modal plugin.
    ctools_include('modal');

    $form_state = array('ajax' => TRUE);

    // Array with ajax response.
    $commands = array();
//    if($form_type!='login'){
//      print $form_type;
//    }
//    print($form_type);
    if ($form_type == 'password') {
      // Show USER PASSWORD form.
      module_load_include('pages.inc', 'user');
//      $form_state['title'] = t('Request new password');
      $commands = ctools_modal_form_wrapper('user_pass', $form_state);
    }
    elseif ($form_type == 'register') {
      // Show USER REGISTER form.
//      $form_state['title'] = t('Create new account');
      $commands = ctools_modal_form_wrapper('user_register_form', $form_state);
    }
    elseif ($form_type == 'login') {
          // Show USER LOGIN form.
//      $form_state['title'] = t('Log In');
      $commands = ctools_modal_form_wrapper('user_login', $form_state);
    }
    elseif ($form_type == 'companylogin') {
      // Show COMPANY USER LOGIN form.
//      $form_state['title'] = t('Log In');
      $commands = ctools_modal_form_wrapper('intern_company_user_login_form', $form_state);
    }
    elseif ($form_type == 'profile') {
      // Show USER profile form.
      module_load_include('pages.inc', 'user');
      $user = user_load($user->uid);
      $form_state['build_info']['args'] = array($user);
      $commands = ctools_modal_form_wrapper('user_profile_form', $form_state);
    }
//    print($form_state['executed']);
    // If form was submited.
    if (!empty($form_state['executed'])) {
      // Include additinal ajax commands.
      ctools_include('ajax');

      if ($form_type == 'password') {
        $commands[] = ctools_modal_command_display(t('Successfull password request'), theme('status_messages'));
      }
      elseif ($form_type == 'register') {
        $redirect_url = trim(variable_get('ajax_register_register_form_redirect', ''));
        if ($redirect_url != '<noredirect>') {
          // Redirect user after login to user provided url.
          // If redirect url is empty page will be reloaded.
          $commands[] = ctools_ajax_command_redirect($redirect_url);
        }
        else {
          // If register form has no redirect after successfull registration
          // just replace it with status messages.
          $commands[] = ctools_modal_command_display(t('Successfull registration'), theme('status_messages'));
        }
      }
      elseif ($form_type == 'login') {
        // Set message about successfull login.
        drupal_set_message(t('Login was successfull. Page has been reloaded.'));
//        $commands[] = ctools_modal_command_display('', theme('status_messages'));

        // Redirect user after login to user provided url.
        // If redirect url is empty page will be reloaded.
//        $redirect_url = variable_get('ajax_register_login_form_redirect', '');
//        $commands[] = ctools_ajax_command_redirect($redirect_url);
        $commands[] = ctools_ajax_command_reload();
      }
      elseif ($form_type == 'companylogin') {
        // Set message about successfull login.
        drupal_set_message(t('Login was successfull. Page has been reloaded.'));
//        $commands[] = ctools_modal_command_display('', theme('status_messages'));

        // Redirect user after login to user provided url.
        // If redirect url is empty page will be reloaded.
//        $redirect_url = variable_get('ajax_register_login_form_redirect', '');
//        $commands[] = ctools_ajax_command_redirect($redirect_url);
        $commands[] = ctools_ajax_command_reload();
      }
      elseif ($form_type == 'profile') {
        $commands[] = ctools_modal_command_display('', theme('status_messages').'<script>jQuery(".authcache-user-picture").html(jQuery.cookie("drupal_user_picture").replace(/\+/g," "));jQuery(".authcache-user").html(jQuery.cookie("drupal_user"));</script>');
      }
    }

    return array('#type' => 'ajax', '#commands' => $commands);
  }
  else {
    // If user has no js support redirect him to standart drupal forms.
    drupal_goto('user/' . $form_type);
  }
}
