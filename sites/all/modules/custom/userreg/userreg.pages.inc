<?php
// $Id$

function userreg_company_register_page() {
  $output = '';
  drupal_set_title('');
  $output .= '<div class="reg"> <div class="reg-title">';
  $output .= '<h2>' . t('企业用户快速注册') . '</h2>';
  $output .= '</div><div class="reg-box"><div class="reg-form">';
  $form = drupal_get_form('userreg_company_register_form');

  $output .= drupal_render($form);
  $output .= '</div>
	 	<div class="reg-showcase">
	 	   <div class="reg-showcase-title">
	 	    <h2>'.t('欢迎加入实习圈').'</h2>'.
	 	   '</div>
	 	   <div class="reg-showcase-box">
	 	     <span class="ss s-1">'.t('为您提供实习候选人').'</span>
	 	     <span class="ss s-2">'.t('帮您展现企业优势').'</span>
	 	     <span class="ss s-3">'.t('助您在实习生群体中树立良好口碑').'</span>
	 	     <span class="ss s-4">'.t('为您构建实习生项目在线工作管理平台').'</span>
	 	   </div>
	 	</div>
	 	</div>
	</div>';
  return $output;
}

function userreg_company_register_form($form, &$form_state) {
  $form = array();
  global $user;
  $form['title'] = array(
    '#type' => 'textfield',
    '#title' => t('公司名'),
    '#required' => TRUE,
    '#attributes' => array('class' => array('company_name')),
  );

  $node = (object) array(
    'uid' => $user->uid,
    'name' => (isset($user->name) ? $user->name : ''),
    'type' => 'company',
    'language' => LANGUAGE_NONE
  );
  field_attach_form('node', $node, $form, $form_state);

  hide($form["body"]);
  hide($form["group_group"]);
  hide($form["field_logo"]);
//  hide($form["field_industry"]);
  hide($form["field_company_type"]);
  hide($form["field_company_size"]);
  hide($form["field_email"]);
  hide($form["field_license"]);
  hide($form["field_company_images"]);
  hide($form["field_website"]);
  hide($form["field_source_company_name"]);

  $form['name'] = array(
    '#type' => 'textfield',
    '#title' => t('用户名'),
    '#required' => TRUE,
    '#weight' => 96,
  );
  $form['mail'] = array(
    '#type' => 'textfield',
    '#title' => t('电子邮箱'),
    '#required' => TRUE,
    '#weight' => 97,
  );
  $form['pass'] = array(
    '#type' => 'password_confirm',
    //'#title' => t('密码'),
    '#required' => TRUE,
    '#weight' => 98,
  );
  $form['actions'] = array('#type' => 'actions');
  $form['actions']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('同意以下协议并注册'),
  );

  $form['#validate'][] = 'userreg_company_register_form_validate_handler';
  $form['#submit'][] = 'userreg_company_register_form_submit_handler';



  return $form;

}

function userreg_company_register_form_validate_handler(&$form, &$form_state) {
  $pseudo_entity = (object) $form_state['values'];
  $pseudo_entity->type = 'company';
  field_attach_form_validate('node', $pseudo_entity, $form, $form_state);

  if (isset($form_state['values']['name'])) {
    if ($error = user_validate_name($form_state['values']['name'])) {
      form_set_error('name', $error);
    }
    elseif ((bool) db_select('users')->fields('users', array('uid'))
      ->condition('name', db_like($form_state['values']['name']), 'LIKE')->range(0, 1)->execute()->fetchField()
    ) {
      form_set_error('name', t('The name %name is already taken.', array('%name' => $form_state['values']['name'])));
    }
  }

  // Validate the e-mail address, and check if it is taken by an existing user.
  if ($error = user_validate_mail($form_state['values']['mail'])) {
    form_set_error('mail', $error);
  }
  elseif ((bool) db_select('users')->fields('users', array('uid'))
    ->condition('mail', db_like($form_state['values']['mail']), 'LIKE')->range(0, 1)->execute()->fetchField()
  ) {
    // Format error message dependent on whether the user is logged in or not.
    if ($GLOBALS['user']->uid) {
      form_set_error('mail', t('The e-mail address %email is already taken.', array('%email' => $form_state['values']['mail'])));
    }
    else {
      form_set_error('mail', t('The e-mail address %email is already registered. <a href="@password">Have you forgotten your password?</a>', array(
        '%email' => $form_state['values']['mail'],
        '@password' => url('ajax_register/password/nojs')
      )));
    }
  }


}

/**
 * Submit handler that builds and saves all profiles in the form.
 *
 */
function userreg_company_register_form_submit_handler(&$form, &$form_state) {

  $pseudo_entity = (object) $form_state['values'];
  $pseudo_entity->type = 'company';

  drupal_set_message('尊敬的企业用户，您已注册成功，实习圈审核您的注册信息后，将会给您发送通知邮件。谢谢。');
  $userinfo = array(
    'name' => $form_state['values']['name'],
    'pass' => $form_state['values']['pass'],
    'mail' => $form_state['values']['mail'],
    'init' => $form_state['values']['mail'],
    'status' => 0,
    'login' => REQUEST_TIME
  );
  //将用户的角色设置为企业用户，这里企业用户的role id为4
  $roles = array(
    2 => 'authenticated user',
    4 => '企业用户',
  );
  $userinfo['roles'] = $roles;
  //我们将查询到的信息保存到Drupal7的用户表中
  $account = user_save(drupal_anonymous_user(), $userinfo);
  $pseudo_entity->uid = $account->uid;
  //不发表
  $pseudo_entity->status = 0;
  //简体中文
  $pseudo_entity->language = 'zh-hans';
  $pseudo_entity->title = $form_state['values']['title'];
  field_attach_submit('node', $pseudo_entity, $form, $form_state);
  //user_save($user);
  node_save($pseudo_entity);
  $form_state['redirect'] = 'user/companyregister/success';
}

function userreg_company_register_success_page() {
  $output = '';
  $output .= t('您已成功注册企业用户，请耐心等待审批。');
  return $output;
}

function userreg_user_register_page() {
  $output = '';
  drupal_set_title('');
  $output .= '<div class="reg">';
  $user_register_form = drupal_get_form('userreg_user_register_form');
  $output .= drupal_render($user_register_form);
  $output .= '</div>';
  return $output;
}

function userreg_user_register_form($form, &$form_state) {

  $form['name'] = array(
    '#type' => 'textfield',
    '#title' => t('用户名'),
    '#required' => TRUE,
    '#weight' => 96,
  );
  $form['mail'] = array(
    '#type' => 'textfield',
    '#title' => t('电子邮箱'),
    '#required' => TRUE,
    '#weight' => 97,
  );
  $form['pass'] = array(
    '#type' => 'password_confirm',
    //'#title' => t('密码'),
    '#required' => TRUE,
    '#weight' => 98,
  );
  $form['actions'] = array('#type' => 'actions');
  $form['actions']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('注册'),
  );
  return $form;

}

function userreg_user_register_form_validate(&$form, &$form_state) {
  $pseudo_entity = (object) $form_state['values'];
  $pseudo_entity->type = 'company';
  field_attach_form_validate('node', $pseudo_entity, $form, $form_state);

  if (isset($form_state['values']['name'])) {
    if ($error = user_validate_name($form_state['values']['name'])) {
      form_set_error('name', $error);
    }
    elseif ((bool) db_select('users')->fields('users', array('uid'))
      ->condition('name', db_like($form_state['values']['name']), 'LIKE')->range(0, 1)->execute()->fetchField()
    ) {
      form_set_error('name', t('The name %name is already taken.', array('%name' => $form_state['values']['name'])));
    }
  }

  // Validate the e-mail address, and check if it is taken by an existing user.
  if ($error = user_validate_mail($form_state['values']['mail'])) {
    form_set_error('mail', $error);
  }
  elseif ((bool) db_select('users')->fields('users', array('uid'))
    ->condition('mail', db_like($form_state['values']['mail']), 'LIKE')->range(0, 1)->execute()->fetchField()
  ) {
    // Format error message dependent on whether the user is logged in or not.
    if ($GLOBALS['user']->uid) {
      form_set_error('mail', t('The e-mail address %email is already taken.', array('%email' => $form_state['values']['mail'])));
    }
    else {
      form_set_error('mail', t('The e-mail address %email is already registered. <a href="@password">Have you forgotten your password?</a>', array(
        '%email' => $form_state['values']['mail'],
        '@password' => url('ajax_register/password/nojs')
      )));
    }
  }


}

/**
 * Submit handler that builds and saves all profiles in the form.
 *
 */
function userreg_user_register_form_submit(&$form, &$form_state) {
  $userinfo = array(
    'name' => $form_state['values']['name'],
    'pass' => $form_state['values']['pass'],
    'mail' => $form_state['values']['mail'],
    'init' => $form_state['values']['mail'],
    'status' => 0,
    'login' => REQUEST_TIME
  );
  //$userinfo['roles'] = $roles;
  //我们将查询到的信息保存到Drupal7的用户表中
  $account = user_save(drupal_anonymous_user(), $userinfo);

  $to = $form_state['values']['mail'];
  //$values = $form_state['values'];
  $values['uid'] = $account->uid;
  $values['name'] = $account->name;
  $values['pass'] = $account->pass;
  $values['login'] = $account->login;
  $values['mail'] = $account->mail;

  $from = variable_get('site_mail', ini_get('sendmail_from'));

  //drupal_set_message('pass:'.$account->pass);
  drupal_mail('userreg', 'user_success', $to, language_default(), $values, $from);
  $form_state['redirect'] = 'user/userregister/success';
}

function userreg_user_register_success_page() {
  $output = '';
  $output .= t('您已注册，我们向您的邮箱发送了一封电子邮件。');
  return $output;
}

function userreg_user_register_check_mail() {
  $uid = arg(3);
  $hashed_pass = arg(4);
  global $user;
  // Check if the user is already logged in. The back button is often the culprit here.
  if ($user->uid) {
    drupal_set_message(t('你现在已经登录，所以不需要再使用这个链接了。'));
    drupal_goto('user/' . $user->uid);
  }
  else {

    //
    $result = db_query('SELECT * FROM {users} u WHERE uid = :uid', array(':uid' => $uid));

    $account = $result->fetchObject();
    if (empty($account)) {
      drupal_set_message(t('这个一次性登录链接已经无效。'));
      drupal_goto();
      return;
    }

    $new_hash = md5($account->pass . $account->mail . $account->login);


    if ($hashed_pass == $new_hash) {
      // First stage is a confirmation form, then login

      //watchdog('user', 'User %name used one-time login link at time %timestamp.', array('%name' => $account->name, '%timestamp' => $timestamp));
      // Set the new user.
      //$user = $account;
      //通过email验证,账户状态设置为1
      $account->status = 1;
      db_query("UPDATE {users} SET status = 1 WHERE uid = :uid", array(':uid' => $uid));
      //user_save($account);
      $account = user_load($account->uid);
      $user = $account;
      //$user->login = time();
      //db_query("UPDATE {users} SET login = %d WHERE uid = %d", $user->login, $user->uid);

      // Regenerate the session ID to prevent against session fixation attacks.
      //sess_regenerate();
      $account = (array) $account;
      user_login_finalize($account);

      //drupal_set_message(t('您的帐户已经通过了验证，欢迎成为我们的注册用户.现在请先完善您的个人简历吧'));
      drupal_set_message(l('稍候完善我的简历', 'user/' . $user->uid));
      drupal_goto('node/add/resume', array("query" => array('destination' => 'user/' . $user->uid)));
      //drupal_goto('node/add/resume');


      $output = '';

      return $output;


    }
    else {
      drupal_set_message(t('这个一次性登录链接已经无效。'));
      drupal_goto();
    }
  }
}

function userreg_company_register_check_mail() {
  $uid = arg(3);
  $hashed_pass = arg(4);
  global $user;
  // Check if the user is already logged in. The back button is often the culprit here.
  if ($user->uid) {
    drupal_set_message(t('你现在已经登录，所以不需要再使用这个链接了。'));
    drupal_goto('user/' . $user->uid);
  }
  else {

    //
    $result = db_query('SELECT * FROM {users} u WHERE uid = :uid', array(':uid' => $uid));

    $account = $result->fetchObject();
    if (empty($account)) {
      drupal_set_message(t('这个一次性登录链接已经无效。'));
      drupal_goto();
      return;
    }

    $new_hash = md5($account->pass . $account->mail . $account->login);


    if ($hashed_pass == $new_hash) {
      // First stage is a confirmation form, then login

      //watchdog('user', 'User %name used one-time login link at time %timestamp.', array('%name' => $account->name, '%timestamp' => $timestamp));
      // Set the new user.
      //$user = $account;
      //通过email验证,账户状态设置为1
      $account->status = 1;
      db_query("UPDATE {users} SET status = 1 WHERE uid = :uid", array(':uid' => $uid));
      //通过email验证,company状态设置为1
      db_query("UPDATE {node} SET status = 1 WHERE uid = :uid AND type = 'company'", array(':uid' => $uid));
      //user_save($account);
      $account = user_load($account->uid);
      $user = $account;
      //$user->login = time();
      //db_query("UPDATE {users} SET login = %d WHERE uid = %d", $user->login, $user->uid);

      // Regenerate the session ID to prevent against session fixation attacks.
      //sess_regenerate();
      $account = (array) $account;
      user_login_finalize($account);

      drupal_set_message(t('您的帐户已经通过了验证，欢迎成为我们的企业用户.'));
      //drupal_set_message(l('稍候完善我的简历','user/'.$user->uid));
      //drupal_goto('node/add/resume',array("query" => array('destination'=>'user/'.$user->uid)));


      $output = t('您的帐户已经通过了验证，欢迎成为我们的企业用户.');

      return $output;


    }
    else {
      drupal_set_message(t('这个一次性登录链接已经无效。'));
      drupal_goto();
    }
  }
}

function userreg_add_resume() {
  $output = "";
  global $user;
  if (empty($user->uid)) {
    $output .= t('只有登录用户才能完善自己的简历');
    return $output;
  }
  //检查是不是已经填写了简历
  $resume_id = db_select('node', 'n')
    ->condition('n.uid', $user->uid)
    ->condition('n.type', 'resume')
    ->fields('n', array('nid'))
    ->range(0, 1)
    ->execute()
    ->fetchField();

  if (!empty($resume_id)) {
    $output .= t('您已经添加了简历');
    drupal_set_message('您已经添加了简历');
    // drupal_set_message(l('稍候完善我的简历','user/'.$user->uid, array("query" => drupal_get_destination())));
    drupal_goto('user/' . $user->uid);
    return $output;
  }
  $output .= "<div class='add-resume-tips'>" . l('稍候完善我的简历', 'user/' . $user->uid) . "</div>";
  module_load_include('inc', 'node', 'node.pages');
  $form = node_add('resume');
  $output .= drupal_render($form);
  return $output;
}


