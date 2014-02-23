<?php
function ucuser_admin_settings(){
	global $base_url;
	$form['ucuser_setting_ucapi'] = array(
    '#type' => 'textfield',
    '#title' => t('ucserver url'),
    '#maxlength' => 255, 
    '#default_value' => variable_get('ucuser_setting_ucapi', 'http://'),
  );
	$form['ucuser_setting_uckey'] = array(
    '#type' => 'textfield',
    '#title' => t('ucserver Communication key'),
    '#maxlength' => 255, 
    '#default_value' => variable_get('ucuser_setting_uckey', ''),
  );
	$form['ucuser_setting_ucappid'] = array(
    '#type' => 'textfield',
    '#title' => t('app id'),
    '#maxlength' => 255, 
    '#default_value' => variable_get('ucuser_setting_ucappid', ''),
  );
	
	 $form['ucuser_setting_ucdbhost'] = array(
    '#type' => 'textfield',
    '#title' => t('ucserver database host'),
    '#maxlength' => 255, 
    '#default_value' => variable_get('ucuser_setting_ucdbhost', 'localhost'),
  );
	$form['ucuser_setting_ucdbuser'] = array(
    '#type' => 'textfield',
    '#title' => t('ucserver database user'),
    '#maxlength' => 255, 
    '#default_value' => variable_get('ucuser_setting_ucdbuser', 'root'),
  );
	$form['ucuser_setting_ucdbpw'] = array(
    '#type' => 'textfield',
    '#title' => t('ucserver database password'),
    '#maxlength' => 255, 
    '#default_value' => variable_get('ucuser_setting_ucdbpw', ''),
  );
	$form['ucuser_setting_ucdbname'] = array(
    '#type' => 'textfield',
    '#title' => t('ucserver database name'),
    '#maxlength' => 255, 
    '#default_value' => variable_get('ucuser_setting_ucdbname', 'ucenter'),
  );
	$form['ucuser_setting_ucdbtablepre'] = array(
    '#type' => 'textfield',
    '#title' => t('ucserver database table pre'),
    '#maxlength' => 255, 
    '#default_value' => variable_get('ucuser_setting_ucdbtablepre', 'uc_'),
  );
	$form['ucuser_setting_description'] = array(
		'#prefix' => '<div class="setting-description">',
    '#markup' => t('The api url is: <span style="color:red;">%url</span>',array('%url'=>$base_url.'/api/ucapi')),
		'#suffix' => '</div>',
  );
	
	return system_settings_form($form);
}