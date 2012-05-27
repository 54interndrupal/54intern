<?php
// $Id$

/**
 * 企业详细导航tabs的主题函数
 */
function theme_company_center_tabs_block(){
	$output = "";
	if((arg(0)=='company'&& arg(1)>0) ||(arg(0)=='node'&& arg(1)>0)){
		$gid = arg(1);
		$output .= '<ul id="company-center-tabs">';
		$output .= '<li>'.  l('<span>'.t('企业首页').'</span>','company/'.$gid, array('html' => TRUE,)). '</li>';
		$output .= '<li>'.  l('<span>'.t('企业点评').'</span>','company/'.$gid.'/reviews', array('html' => TRUE,)). '</li>';
		$output .= '<li>'.  l('<span>'.t('实习经历分享').'</span>','company/'.$gid.'/shares', array('html' => TRUE,)). '</li>';
		$output .= '<li>'.  l('<span>'.t('企业招聘').'</span>','company/'.$gid.'/jobs', array('html' => TRUE,)). '</li>';
		$output .= '<li>'.  l('<span>'.t('企业讨论区').'</span>','company/'.$gid.'/discussions', array('html' => TRUE,)). '</li>';
		$output .= '<li>'.  l('<span>'.t('企业活动').'</span>','company/'.$gid.'/events', array('html' => TRUE,)). '</li>';
		$output .= '</ul>';
	}
	return $output;
}

/**
 * 企业中心导航tabs的主题函数
 */
function theme_company_center_nav_block(){
	$output = "";
	if((arg(0)=='companycenter'&& arg(1)>0)){
		$gid = arg(1);
		$output .= '<ul id="company-center-tabs">';
		$output .= '<li>'.  l('<span>'.t('职务管理').'</span>','companycenter/'.$gid, array('html' => TRUE,)). '</li>';
		$output .= '<li>'.  l('<span>'.t('收件箱').'</span>','companycenter/'.$gid.'/resumes', array('html' => TRUE,)). '</li>';
		$output .= '<li>'.  l('<span>'.t('已购简历').'</span>','companycenter/'.$gid.'/buyresumes', array('html' => TRUE,)). '</li>';
		$output .= '<li>'.  l('<span>'.t('活动管理').'</span>','companycenter/'.$gid.'/events', array('html' => TRUE,)). '</li>';
		$output .= '<li>'.  l('<span>'.t('搜简历').'</span>','resumes', array('html' => TRUE,'attributes' => array('target' => '_blank'))). '</li>';
		$output .= '</ul>';
	}
	return $output;
}

/**
 * 企业中心的主题函数
 */
function theme_company_center_center_block(){
	$output = "";
	if((arg(0)=='companycenter'&& arg(1)>0)){
	  $company = node_load(arg(1));
		if($company->type =='company'){
		$gid = arg(1);
		$output .= '<div id="company-center">';
		$output .= '<li>'.  l('<span>'.t('职务管理').'</span>','companycenter/'.$gid.'/jobs', array('html' => TRUE,)). '</li>';
		$output .= '<li>'.  l('<span>'.t('简历管理').'</span>','companycenter/'.$gid.'/resumes', array('html' => TRUE,)). '</li>';
		$output .= '<li>'.  l('<span>'.t('活动管理').'</span>','companycenter/'.$gid.'/events', array('html' => TRUE,)). '</li>';
		$output .= '</div>';
		}
	
	}
	return $output;
}

/**
 * 企业中心
 */
function company_center_page(){
  global $user;
	$company_role = 4;
	//print debug('123456');
	if(array_key_exists($company_role,$user->roles) ){
	  //print debug($_GET['destination']);
		$company_id = db_select('node','n')
		->condition('n.uid',$user->uid)
		->condition('n.type','company')
		->fields('n',array('nid'))
		->range(0,1)
		->execute()
		->fetchField();
		$path = '';
		if(empty($company_id)){
		  $path = 'node/add/company';
			$output = t('您现在还没有添加企业信息');
			$output .= l(t('现在添加'), $path);
			return $output;
		}else{
		  $path = 'companycenter/'.$company_id;
			menu_set_active_item($path);
      return menu_execute_active_handler(NULL, FALSE);
		}


	}else{
	  $output = t('您现在还不是企业用户,注册企业用户后,才可以访问企业中心');
		return $output;
	}

}


