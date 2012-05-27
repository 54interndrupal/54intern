<?php
// $Id$


function userreg_admin_settings(){
  $form = array();
	$email_token_help = t('可用的变量有：[site:name], [site:url], [user:name], [user:mail], [user:one-time-login-url]');
  
	$userreg_mail_user_register_subject_default = t('[site:name]注册确认邮件');
	$userreg_mail_user_register_body_default = t("尊敬的[user:name]：
    您好，感谢您注册（[site:url]）。这是一封注册确认邮件。请点击以下链接完成确认：
    [user:one-time-login-url]
    如果链接不能点击，请复制地址到浏览器，然后直接打开。
           [site:name]");
		
	$userreg_mail_company_register_subject_default = t('[site:name]企业用户注册确认邮件');
	$userreg_mail_company_register_body_default = t("尊敬的[user:name]：
    您好，感谢您注册（[site:url]）称为我们的企业会员。这是一封注册确认邮件。请点击以下链接完成确认：
    [user:one-time-login-url]
    如果链接不能点击，请复制地址到浏览器，然后直接打开。
           [site:name]");	
		
	$form['email_userreg_user'] = array(
    '#type' => 'fieldset',
    '#title' => t('普通用户注册验证邮件'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
    '#description' => t('在这里可以配置普通用户注册时，验证邮件的内容.') . ' ' . $email_token_help,
    //'#group' => 'email',
  );
  $form['email_userreg_user']['userreg_mail_user_register_subject'] = array(
    '#type' => 'textfield',
    '#title' => t('Subject'),
    '#default_value' => variable_get('userreg_mail_user_register_subject',$userreg_mail_user_register_subject_default),
    '#maxlength' => 180,
  );
  $form['email_userreg_user']['userreg_mail_user_register_body'] = array(
    '#type' => 'textarea',
    '#title' => t('Body'),
    '#default_value' => variable_get('userreg_mail_user_register_body',$userreg_mail_user_register_body_default),
    '#rows' => 15,
  );
	
  $form['email_userreg_company'] = array(
    '#type' => 'fieldset',
    '#title' => t('企业用户注册验证邮件'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
    '#description' => t('在这里可以配置普通用户注册后，审核通过后所发验证邮件的内容.') . ' ' . $email_token_help,
    //'#group' => 'email',
  );
  $form['email_userreg_company']['userreg_mail_company_register_subject'] = array(
    '#type' => 'textfield',
    '#title' => t('Subject'),
    '#default_value' => variable_get('userreg_mail_company_register_subject', $userreg_mail_company_register_subject_default),
    '#maxlength' => 180,
  );
  $form['email_userreg_company']['userreg_mail_company_register_body'] = array(
    '#type' => 'textarea',
    '#title' => t('Body'),
    '#default_value' => variable_get('userreg_mail_company_register_body', $userreg_mail_company_register_body_default),
    '#rows' => 15,
  );	
	return system_settings_form($form);

}
