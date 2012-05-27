<?php
// $Id: template.php,v 1.45 2010/12/01 00:18:15 webchick Exp $

/**
 * Return a themed breadcrumb trail.
 *
 * @param $breadcrumb
 *   An array containing the breadcrumb links.
 * @return a string containing the breadcrumb output.
 */
function intern_breadcrumb($variables) {
  $breadcrumb = $variables['breadcrumb'];

  if (!empty($breadcrumb)) {
    // Provide a navigational heading to give context for breadcrumb links to
    // screen-reader users. Make the heading invisible with .element-invisible.
    $output = '<h2 class="element-invisible">' . t('You are here') . '</h2>';

    $output .= '<div class="breadcrumb">' . implode(' › ', $breadcrumb) . '</div>';
    return $output;
  }
}

function intern_theme() {  
  return array(    
    'user_login_block' => array(      
      'template' => 'user-login',
      'render element' => 'form',
      'path'	=> drupal_get_path('theme','intern').'/templates',		
		),    
			// other theme registration code...  
	'invite_form' => array(      
      'template' => 'invite-form',
      'render element' => 'form',
      'path'	=> drupal_get_path('theme','intern').'/templates',		
		),    
			// other theme registration code...  
	);
}
function intern_preprocess_user_login_block(&$variables) {  
	//$variables['intro_text'] = t('This is my awesome login form'); 
  //$variables['form']['actions']['submit']['#attributes'] = array('class' => 'but');	
	$variables['name'] = drupal_render($variables['form']['name']);
	$variables['pass'] = drupal_render($variables['form']['pass']);
	$variables['login'] = drupal_render($variables['form']['actions']['submit']);
	$variables['links'] = drupal_render($variables['form']['links']);
	$variables['remember_me'] = drupal_render($variables['form']['remember_me']);
	$variables['weibo_signin'] = drupal_render($variables['form']['weibo_signin']);
	$variables['hidden'] = drupal_render_children($variables['form']);
}
function intern_preprocess_invite_form(&$variables) {  
	//$variables['intro_text'] = t('This is my awesome login form'); 
  //$variables['form']['actions']['submit']['#attributes'] = array('class' => 'but');	
	//$variables['op'] = drupal_render($variables['form']['#op']);
	if($variables['form']['#op'] == 'block'){
	//print debug($variables['form']['#op']);
	 // unset($variables['form']['invite']);
	 $variables['invite'] = drupal_render($variables['form']['invite']);
	 $variables['link'] = drupal_render($variables['form']['link']);
	 // unset($variables['form']['link']);
	}
	$variables['form'] = drupal_render_children($variables['form']);
}

function intern_menu_link__main_menu(array $variables) {
  $element = $variables['element'];
  $sub_menu = '';

  if ($element['#below']) {
    $sub_menu = drupal_render($element['#below']);
  }
  $output = l('<span>'.$element['#title'].'</span>', $element['#href'], array('html' => TRUE,));
  return '<li' . drupal_attributes($element['#attributes']) . '>' . $output . $sub_menu . "</li>\n";
}

function intern_access_company_contacts($nid) {
  global $user;
  if(empty($user->uid)){
    return FALSE;
  }
  if($user->uid ==1 || user_access('administer nodes')){
    return TRUE;
  }
  //当前 简历 的作者 
  $node = node_load($nid);
  if($node->uid == $user->uid){
    return TRUE;
  }
  $company_role = 4;
  //print debug('123456');
  if(!array_key_exists($company_role,$user->roles) ){
    return FALSE;
  }else{
    //已经购买的
    $buy_flag=flag_get_flag('buy');
	if($buy_flag->is_flagged($nid,$user->uid)){
	   return TRUE;
	}else{
	//投了简历的
	    $company_id = db_select('node','n')
		->condition('n.uid',$user->uid)
		->condition('n.type','company')
		->fields('n',array('nid'))
		->range(0,1)
		->execute()
		->fetchField();
		if(empty($company_id)){
		  $company_id = 0;
		}
		$query = new EntityFieldQuery();
		$query->entityCondition('entity_type', 'apply');
		$query->entityCondition('bundle', 'apply');
		$query->fieldCondition('field_resume_id','target_id',$nid);
		$query->fieldCondition('field_company_id','target_id',$company_id);
		$flag = (bool)$query->range(0, 1)->count()->execute();
		if($flag){
		   return TRUE;
		}   
	}
	
	
  }
  
  return FALSE;
}

function intern_access_company_content_form($nid) {
  global $user;
  if(empty($user->uid)){
    return FALSE;
  }
  if($user->uid ==1 || user_access('administer nodes')){
    return TRUE;
  }
  //只有关注了该企业的用户才可以发言
  $guanzhu_flag=flag_get_flag('bookmarks');
	if($guanzhu_flag->is_flagged($nid,$user->uid)){
	   return TRUE;
	}
  $membership =og_get_membership('node', $nid, 'user', $user->uid);
  if(!empty($membership)){
    return TRUE;
  }
  
  return FALSE;
}


			