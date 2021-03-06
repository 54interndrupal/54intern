﻿<?php
// $Id: template.php,v 1.45 2010/12/01 00:18:15 webchick Exp $


function ffintern_preprocess_html() {
  drupal_add_css(path_to_theme() . '/css/ie.css', array(
    'group' => CSS_THEME, 'browsers' =>
    array('IE' => 'IE', '!IE' => FALSE), 'preprocess' => FALSE
  ));
  // Add conditional CSS for IE8 and below.
  drupal_add_css(path_to_theme() . '/css/ie9.css', array(
    'group' => CSS_THEME, 'browsers' =>
    array('IE' => 'IE 9', '!IE' => FALSE), 'preprocess' => FALSE
  ));
    // Add conditional CSS for IE6.
  drupal_add_css(path_to_theme() . '/css/ie7.css', array(
    'group' => CSS_THEME, 'browsers' =>
    array('IE' => 'lt IE 7', '!IE' => FALSE), 'preprocess' => FALSE
  ));

  drupal_add_js(path_to_theme() . '/bootstrap/js/bootstrap.min.js', array(
    'group' => JS_LIBRARY
  ));

//  drupal_add_js(path_to_theme() . '/bootstrap/assets/js/html5shiv.js', array(
//    'group' => JS_LIBRARY, 'browsers' =>
//    array('IE' => 'IE 9', '!IE' => FALSE), 'preprocess' => FALSE
//  ));
//  drupal_add_js(path_to_theme() . '/bootstrap/assets/js/respond.min.js', array(
//    'group' => JS_LIBRARY, 'browsers' =>
//    array('IE' => 'IE 9', '!IE' => FALSE), 'preprocess' => FALSE
//  ));
}



/**
 * Preprocesses template variables for the page template.
 */
function ffintern_preprocess_page(&$variables) {

  //for resume node type
  if (isset($variables['node']) && $variables['node']->type == 'resume' && arg(2) != 'edit') {
    $variables['theme_hook_suggestions'][] = 'page__node__' . $variables['node']->type;
//    print_r($variables['theme_hook_suggestions']);
  }

  if (arg(0) == 'jobs' || arg(0) == 'companycenter' || arg(0) == 'node'|| arg(0) == 'fortune500'||arg(0)=='finance') {
    _ffintern_add_quicktab_css();
  }
}
/**
 * Preprocesses template variables for username template.
 */
function ffintern_username($variables) {
  $output = '<span' . drupal_attributes($variables['attributes_array']) . '>' . intern_user_get_user_name($variables['name']) . $variables['extra'] . '</span>';
  return $output;
}



function _ffintern_add_quicktab_css() {
  drupal_add_css(drupal_get_path('module', 'quicktabs') . '/css/quicktabs.css');
  drupal_add_css(drupal_get_path('module', 'quicktabs') . '/quicktabs_tabstyles/tabstyles/intern/intern.css');
  drupal_add_css(drupal_get_path('module', 'quicktabs') . '/quicktabs_tabstyles/tabstyles/intern2/intern2.css');
}

function getIP(){
  global $ip;
  if (getenv("HTTP_CLIENT_IP"))
    $ip = getenv("HTTP_CLIENT_IP");
  else if(getenv("HTTP_X_FORWARDED_FOR"))
    $ip = getenv("HTTP_X_FORWARDED_FOR");
  else if(getenv("REMOTE_ADDR"))
    $ip = getenv("REMOTE_ADDR");
  else $ip = "Unknow";
  return $ip;
}

function ffintern_tongbu() {
	$tmp="";
        include("/sites/all/modules/ucuser/config.inc.php");
	$tmplink=mysql_connect(UC_DBHOST,UC_DBUSER,UC_DBPW);
	$uname=$_COOKIE['drupal_user'];
	$uid=$_COOKIE['uc_uid'];
	
	//echo $uname.$uid;
	//exit();
	$ip=getIP();
	if($_GET['transfer']==1){
		mysql_query("delete from ".UC_DBTABLEPRE."tongbu where uid='$uid' or uname='$uname' ");
	    $tmp="";
	}
//  $tmp.=$ip;
$result=mysql_query("select content, type from ".UC_DBTABLEPRE."tongbu where    ip='$ip' order by id desc ") or die(mysql_error());
if($row=mysql_fetch_array($result,MYSQL_BOTH) and $_GET['transfer']!=1){
	$tmp.=$row['content'];
	
	$resulta=mysql_query("select content, type from ".UC_DBTABLEPRE."tongbu where ip='$ip' and isfromdrupal='http://forum.54intern.com/forum.php' ") or die(mysql_error());
	if($rowa=mysql_fetch_array($resulta,MYSQL_BOTH) ){
		$tmp.='<meta http-equiv="refresh" content="0;url=http://www.shixiquan.com/?transfer=1" />';
	}
	mysql_query("delete from ".UC_DBTABLEPRE."tongbu where (not isfromdrupal='http://forum.54intern.com/forum.php') and (uid='$uid' or uname='$uname') ");
} 

mysql_close($tmplink);

		return $tmp;
}

/**
 * Return a themed breadcrumb trail.
 *
 * @param $breadcrumb
 *   An array containing the breadcrumb links.
 * @return a string containing the breadcrumb output.
 */
function ffintern_breadcrumb($variables) {
  $breadcrumb = $variables['breadcrumb'];

  if (!empty($breadcrumb)) {
    // Provide a navigational heading to give context for breadcrumb links to
    // screen-reader users. Make the heading invisible with .element-invisible.
    $output = '<h2 class="element-invisible">' . t('You are here') . '</h2>';

    $output .= '<div class="breadcrumb">' . implode(' › ', $breadcrumb) . '</div>';
    return $output;
  }
}

/**
 * Theme function to output tablinks for classic Quicktabs style tabs.
 *
 * @ingroup themeable
 */
function ffintern_qt_quicktabs_tabset($vars) {
  $tabId = $vars['tabset']['tablinks'][0]['#options']['attributes']['id'];
  $output = theme_qt_quicktabs_tabset($vars);
//   if(strstr( $tabId , 'quicktabs-tab-front_main_tabs')){
//         $output.= l('<span class=\'tab-more-link\'>更多 >></span>', 'jobs' , array('html' => TRUE,));
//   }
  return $output;
}


function ffintern_theme() {
  return array(
    'user_login_block' => array(
      'template' => 'user-login',
      'render element' => 'form',
      'path' => drupal_get_path('theme', 'ffintern') . '/templates',
    ),
    'shixiquan_companylogin_form' => array(
      'template' => 'company-login-form',
      'render element' => 'form',
      'path' => drupal_get_path('theme', 'ffintern') . '/templates/overrite/form',
    ),
    // other theme registration code...
    'invite_form' => array(
      'template' => 'invite-form',
      'render element' => 'form',
      'path' => drupal_get_path('theme', 'ffintern') . '/templates',
    ),
    'review_node_form' => array(
      'template' => 'review-node-form',
      'render element' => 'form',
      'path' => drupal_get_path('theme', 'ffintern') . '/templates/overrite/form',
    ),
    'company_node_form' => array(
      'template' => 'company-node-form',
      'render element' => 'form',
      'path' => drupal_get_path('theme', 'ffintern') . '/templates/overrite/form',
    ),
    'intern_company_edit_company_form' => array(
      'template' => 'company-node-form',
      'render element' => 'form',
      'path' => drupal_get_path('theme', 'ffintern') . '/templates/overrite/form',
    ),
    'intern_company_add_company_form' => array(
      'template' => 'company-add-form',
      'render element' => 'form',
      'path' => drupal_get_path('theme', 'ffintern') . '/templates/overrite/form',
    ),
    'resume_node_form' => array(
      'template' => 'resume-node-form',
      'render element' => 'form',
      'path' => drupal_get_path('theme', 'ffintern') . '/templates/overrite/form',
    ),
    'job_node_form' => array(
      'template' => 'job-node-form',
      'render element' => 'form',
      'path' => drupal_get_path('theme', 'ffintern') . '/templates/overrite/form',
    ),
    'intern_review_add_form' => array(
      'template' => 'review-node-form',
      'render element' => 'form',
      'path' => drupal_get_path('theme', 'ffintern') . '/templates/overrite/form',
    ),

    'userreg_company_register_form' => array(
      'template' => 'userreg-company-register-form',
      'render element' => 'form',
      'path' => drupal_get_path('theme', 'ffintern') . '/templates/overrite/form',
    ),
    'user_register_form' => array(
      'template' => 'user-register-form',
      'render element' => 'form',
      'path' => drupal_get_path('theme', 'ffintern') . '/templates/overrite/form',
    ),
    'user_login' => array(
      'render element' => 'form',
    ),
    'user_profile_form' => array(
      'template' => 'user-profile-form',
      'render element' => 'form',
      'path' => drupal_get_path('theme', 'ffintern') . '/templates/overrite/form',
    ),
    'intern_company_user_login_form' => array(
      'render element' => 'form',
    ),
    'user_pass' => array(
      'template' => 'user-pass-form',
      'render element' => 'form',
      'path' => drupal_get_path('theme', 'ffintern') . '/templates/overrite/form',
    ),
    // other theme registration code...
  );
}

function ffintern_user_login(&$variables) {

  // Include the CTools tools that we need.
  ctools_include('modal');
  ctools_include('ajax');
  ctools_modal_add_js();
  drupal_add_js(drupal_get_path('theme', "ffintern") . "/js/userLogin.js");
  $form = $variables['form'];
//  print_r($form);
  $form['name']['#title'] = t('用户名');
  unset($form['name']['#hint']);
  unset($form['name']['#hint_remove_title']);
  unset($form['name']['#description']);
  $form['pass']['#title'] = t('密码');
  unset($form['pass']['#hint']);
  unset($form['pass']['#hint_remove_title']);
  unset($form['pass']['#description']);
  unset($form['weibo_signin']);
  $register_link = ctools_modal_text_button(t('马上注册 >>'), 'ajax_register/register/nojs', '', 'ctools-modal-ctools-ajax-register-style');
  $login_link = ctools_modal_text_button(t('企业登录'), 'ajax_register/companylogin/nojs', '', 'ctools-modal-ctools-ajax-register-style');

  $output = '<div class="c-17 user-login-header" id="user-login-header"><span class="active"> 个人登陆 </span>
           <span class="inactive"> ' . $login_link . ' </span>
        </div> ';
  $output .= '<div class="user-login-popup">
    <div class="d-1">
    <span class="c-10 s-1">您目前没有登陆，请输入以下信息后登录实习圈：</span>
  ';

  $output .= drupal_render($form['name']);
  $output .= drupal_render($form['pass']);
  $output .= drupal_render($form['actions']);
  $output .= drupal_render($form['remember_me']);
  $output .= '</div>
  <div class="d-2">
    <span class="s-2">使用合作网站帐户登录</span>
    <a href="' . base_path() . 'csna/weibo" title="新浪微博账号登陆"><span class="wbxxl"></span> </a>
    <a href="' . base_path() . 'csna/qq" title="QQ账号登陆"><span class="qqxxl"></span></a>
    <a href="' . base_path() . 'csna/renren" title="人人账号登陆"><span class="rrxxl"></span></a>
    <span class="zhuce"><span class="c-5">还不是实习圈用户？</span>' . $register_link . '</div>
  </div>
  </div>';
  $output .= drupal_render_children($form);
//  $output['#suffix']= _ffintern_add_login_script();
  return $output;
}

function ffintern_intern_company_user_login_form(&$variables) {
  // Include the CTools tools that we need.
  ctools_include('modal');
  ctools_include('ajax');
  ctools_modal_add_js();
  drupal_add_js(drupal_get_path('theme', "ffintern") . "/js/userLogin.js");
  $form = $variables['form'];

  $register_link = l('<span class="company-register">注册企业用户</span>', '/user/companyregister', array('html' => TRUE));
  $login_link = ctools_modal_text_button(t('个人登录'), 'ajax_register/login/nojs', '', 'ctools-modal-ctools-ajax-register-style');
  unset($form['weibo_signin']);

  $output = '<div class="c-17 user-login-header" id="user-login-header"><span class="inactive"> ' . $login_link . '</span>
           <span class="active"> 企业登录 </span>
        </div> ';
  $output .= '<div class="user-login-popup">
    <div class="d-1">
    <span class="c-10 s-1">您目前没有登陆，请输入以下信息后登录实习圈：</span>
  ';
  $output .= drupal_render($form['company_name']);
  $output .= drupal_render($form['name']);
  $output .= drupal_render($form['pass']);
  $output .= drupal_render($form['actions']);
  $output .= drupal_render($form['remember_me']);
  $output .= drupal_render_children($form);
  $output .= '</div>
  <div class="c-17 d-3">
      <span class="s-1">还不是实习圈企业用户？</span>
      <span class="s-2">
        -为您提供实习候选人<br>
        -帮您展现企业优势<br>
        -助您在实习生群体中树立良好口碑<br>
        -为您构建实习生项目在线管理平台
      </span>
      ' . $register_link . '
  </div>
  </div>';
//  $output .= _ffintern_add_login_script();
  return $output;
}


function ffintern_preprocess_user_login_block(&$variables) {
  //$variables['intro_text'] = t('This is my awesome login form');
  //$variables['form']['actions']['submit']['#attributes'] = array('class' => 'but');
  $variables['form']['actions']['submit']['#value'] = '登录 ';
  $variables['form']['name']['#attributes'] = array('tabindex' => -5);
  $variables['form']['pass']['#attributes'] = array('tabindex' => -4);

  $variables['name'] = drupal_render($variables['form']['name']);

  $variables['pass'] = drupal_render($variables['form']['pass']);
  $variables['login'] = drupal_render($variables['form']['actions']['submit']);
  $variables['links'] = drupal_render($variables['form']['links']);
  $variables['remember_me'] = drupal_render($variables['form']['remember_me']);
  $variables['weibo_signin'] = drupal_render($variables['form']['weibo_signin']);
  $variables['hidden'] = drupal_render_children($variables['form']);
}

function ffintern_preprocess_invite_form(&$variables) {
  //$variables['intro_text'] = t('This is my awesome login form');
  //$variables['form']['actions']['submit']['#attributes'] = array('class' => 'but');	
  //$variables['op'] = drupal_render($variables['form']['#op']);
  if ($variables['form']['#op'] == 'block') {
    //print debug($variables['form']['#op']);
    // unset($variables['form']['invite']);
    $variables['invite'] = drupal_render($variables['form']['invite']);
    $variables['link'] = drupal_render($variables['form']['link']);
    // unset($variables['form']['link']);
  }
  $variables['form'] = drupal_render_children($variables['form']);
}

function ffintern_preprocess_user_profile_form(&$variables) {
  drupal_add_css();
}

function ffintern_review_node_form(&$variables) {
  $header = '<div class="review-node-form-header"><span class="form-header-title c-10">' . t("我的点评") . '</span></div>';

  $form = $variables['form'];

  hide($form ['field_rating']);
  hide($form ['field_advantage']);
  hide($form ['field_shortcoming']);

  $form['actions']['submit']['#value'] = t('发布点评');

  $element = $form['body']['und'][0]['value'];

  $form['body']['und'][0]['value']['#attributes']['title'] = $element['#title'];
  $form['body']['und'][0]['value']['#hint']['#hint_remove_title'] = TRUE;
  $class = 'hint-enabled';
  $form['body']['und'][0]['value']['#attributes']['class'][] = $class;
  hide($form['body']['und'][0]['value']['#title']);
  unset($form['body']['und'][0]['value']['#resizable']);
//  print_r( $form['title']) ;
  return $header . drupal_render_children($form);
}

function ffintern_menu_tree__main_menu($variables) {
  $searchForm = drupal_get_form('shixiquan_search_form');

  $output = drupal_render($searchForm);
  return '<div class="navbar navbar-inverse bts-docs-nav" role="banner"><div class="container"><div class="collapse navbar-collapse bts-navbar-collapse" role="navigation"><ul class="nav navbar-nav">' . $variables['tree'] . '</ul><div class="nav navbar-nav navbar-right" style="padding:7px 0 0 0">'.$output.'</div></div></div><div id="navBottom"></div></div>';
}

function ffintern_menu_link__main_menu(array $variables) {

//  print_r($variables);

  $element = $variables['element'];
//    print_r($element);
  $sub_menu = '';
  $mlid = $element['#original_link']['mlid'];

  if ($element['#below']) {
    $sub_menu = drupal_render($element['#below']);
  }
  $params = explode('/', request_uri());

  $attributes = array();
//   print($params[2]);
  if ($mlid == 626 && arg(0) == $element['#href']) {
    $attributes['class'][] = 'active';
    $element['#attributes']['class'][]='active';

  }
  else {
    if ($mlid == 638 && arg(0) == $element['#href']) {
      $attributes['class'][] = 'active';
      $element['#attributes']['class'][]='active';

    }
    else {
      if ($mlid == 624 && ((isset($params[1]) && $params[1] == 'company') || arg(0) == 'companys'||(arg(2)=='review'))) {
        $attributes['class'][] = 'active';
        $element['#attributes']['class'][]='active';

      }
      else {
        if ($mlid == 625 && ((isset($params[1]) && $params[1] == 'job') || arg(0) == 'fortune500')) {
          $attributes['class'][] = 'active';
          $element['#attributes']['class'][]='active';

        }
        else {
          if ($mlid == 1436 && (isset($params[1]) && ($params[1] == 'article'||$params[1] == 'wikis'))) {
            $attributes['class'][] = 'active';
            $element['#attributes']['class'][]='active';

          }elseif (intern_user_is_company_user()&& ($mlid == 638) && ((isset($params[1])&&$params[1]=='node'&&arg(2)!='review') || arg(0)=='user')){
            $attributes['class'][] = 'active';
            $element['#attributes']['class'][]='active';

          }elseif  (!intern_user_is_company_user()&&($mlid == 626) &&((isset($params[1])&&$params[1]=='node'&&arg(2)!='review'))){
            $attributes['class'][] = 'active';
            $element['#attributes']['class'][]='active';

          }
        }

      }
    }
  }

  $attributes['class'][] = 'menu-' . $element['#original_link']['mlid'];

  $output = l($element['#title'], $element['#href'], array(
    'html' => TRUE,
    'attributes' => $attributes
  ));
//  print('x'.$element['#href'].'x'.','.$_GET['q']);
  if ( $element['#href'] == $_GET['q'] || ($_GET['q'] == 'frontpage'&&$element['#href']=='<front>' && drupal_is_front_page())) {
    $element['#attributes']['class'][] = 'active';
  }

  return '<li' . drupal_attributes($element['#attributes']) . '>' . $output . "</li>\n";
}

function ffintern_access_company_contacts($nid) {
  global $user;
  if (empty($user->uid)) {
    return FALSE;
  }
  if ($user->uid == 1 || user_access('administer nodes')) {
    return TRUE;
  }
  //当前 简历 的作者 
  $node = node_load($nid);
  if ($node->uid == $user->uid) {
    return TRUE;
  }
  $company_role = 4;
  //print debug('123456');
  if (!array_key_exists($company_role, $user->roles)) {
    return FALSE;
  }
  else {
    //已经购买的
    $buy_flag = flag_get_flag('buy');
    if ($buy_flag->is_flagged($nid, $user->uid)) {
      return TRUE;
    }
    else {
      //投了简历的
      $company_id = db_select('node', 'n')
        ->condition('n.uid', $user->uid)
        ->condition('n.type', 'company')
        ->fields('n', array('nid'))
        ->range(0, 1)
        ->execute()
        ->fetchField();
      if (empty($company_id)) {
        $company_id = 0;
      }
      $query = new EntityFieldQuery();
      $query->entityCondition('entity_type', 'apply');
      $query->entityCondition('bundle', 'apply');
      $query->fieldCondition('field_resume_id', 'target_id', $nid);
      $query->fieldCondition('field_company_id', 'target_id', $company_id);
      $flag = (bool) $query->range(0, 1)->count()->execute();
      if ($flag) {
        return TRUE;
      }
    }


  }

  return FALSE;
}

function ffintern_access_company_content_form($nid) {
  global $user;
  if (empty($user->uid)) {
    return FALSE;
  }
  if ($user->uid == 1 || user_access('administer nodes')) {
    return TRUE;
  }
  //只有关注了该企业的用户才可以发言
  $guanzhu_flag = flag_get_flag('bookmarks');
  if ($guanzhu_flag->is_flagged($nid, $user->uid)) {
    return TRUE;
  }
  $membership = og_get_membership('node', $nid, 'user', $user->uid);
  if (!empty($membership)) {
    return TRUE;
  }

  return FALSE;
}

function ffintern_output_share_bar() {
  print('<!-- JiaThis Button BEGIN -->' .
    '<div id="ckepop" style="display:block">' .
    '<span class="jiathis_txt" style="font-size:12px">分享到：</span>' .
    '<a class="jiathis_button_tsina"></a>' .
    '<a class="jiathis_button_renren"></a>' .
    '<a class="jiathis_button_kaixin001"></a>' .
    '</div>' .
    '<script type="text/javascript" src="http://v2.jiathis.com/code/jia.js" charset="utf-8"></script>' .
    '<!-- JiaThis Button END -->');
}

/**
 * Returns HTML for a textarea form element.
 *
 * @param $variables
 *   An associative array containing:
 *   - element: An associative array containing the properties of the element.
 *     Properties used: #title, #value, #description, #rows, #cols, #required,
 *     #attributes
 *
 * @ingroup themeable
 */
function ffintern_textarea($variables) {
  $element = $variables['element'];
  element_set_attributes($element, array('id', 'name', 'cols', 'rows'));
  _form_set_class($element, array('form-textarea'));

  $wrapper_attributes = array(
    'class' => array('form-textarea-wrapper'),
  );

  $output = '<div' . drupal_attributes($wrapper_attributes) . '>';
  $output .= '<textarea' . drupal_attributes($element['#attributes']) . '>' . check_plain($element['#value']) . '</textarea>';
  $output .= '</div>';
  return $output;
}

function ffintern_select($variables) {
  $element = $variables['element'];
//  print_r($element);

  if ($element['#parents'][0] == 'field_location_tid' || $element['#parents'][0] == 'job_category'
    || $element['#parents'][0] == 'field_location' || $element['#parents'][0] == 'field_job_category'
    || $element['#parents'][0] == 'field_industry_tid' || $element['#parents'][0] == 'field_industry'
  ) {
    $selectValue = $element['#value'];
    if (is_array($selectValue)) {
      $selectValue = $selectValue[0];
    }


    $selectOption = '不限';
    foreach ($element['#options'] as $index => $choice) {
      if ($index == $selectValue) {
        $selectOption = $choice;
        break;
      }

      if (is_array($choice)) {
      }
      elseif (is_object($choice)) {
        if (isset($choice->option[$selectValue])) {
          $selectOption = $choice->option[$selectValue];
          break;
        }

      }
    }
    $error_class = '';
    if (isset($element['#parents']) && form_get_error($element)) {
      $error_class = 'error';
    }

    drupal_add_js(drupal_get_path('theme', "ffintern") . "/popups/drag.js");
    drupal_add_css(drupal_get_path('theme', "ffintern") . "/popups/alpha.css");
    drupal_add_css(drupal_get_path('theme', "ffintern") . "/popups/css.css");
    $output = '<input type="hidden" name="' . $element['#name'] . '" id="' . $element['#id'] . '" value="' . $selectValue . '">';
    if ($element['#parents'][0] == 'field_location_tid' || $element['#parents'][0] == 'field_location') {
      drupal_add_js(drupal_get_path('theme', "ffintern") . "/popups/city_func.js");
      drupal_add_js(drupal_get_path('theme', "ffintern") . "/popups/city_arr.js");
      $output .= '<div class="input-group">'.
        '<input type="text" name="citySelect" onclick="residencySelect(\'' . $element['#id'] . '\');" id="sel-' . $element['#id'] . '" class="form-control'.$error_class.'" value="' . $selectOption . '"/>'.
        '<span class="input-group-addon"  onclick="jQuery(\'#sel-'.$element['#id'].'\').click()"><i class="icon-search"></i></span>'.
        '</div>';
    }
    else {
      if ($element['#parents'][0] == 'job_category' || $element['#parents'][0] == 'field_job_category') {
        drupal_add_js(drupal_get_path('theme', "ffintern") . "/popups/funtype_func.js");
        drupal_add_js(drupal_get_path('theme', "ffintern") . "/popups/funtype_arr.js");
        $output .= '<div class="input-group"><input type="text" name="jobCategorySelect"  onclick="funtypeSelect_2(\'' . $element['#id'] . '\');" id="sel-' . $element['#id'] . '" class="form-control '.$error_class.'" value="' . $selectOption . '">'.
          '<span class="input-group-addon" onclick="jQuery(\'#sel-'.$element['#id'].'\').click()"><i class="icon-search"></i></span>'
          .'</div>';
      }
      else {
        if ($element['#parents'][0] == 'field_industry_tid' || $element['#parents'][0] == 'field_industry') {
          drupal_add_js(drupal_get_path('theme', "ffintern") . "/popups/industry_func.js");
          drupal_add_js(drupal_get_path('theme', "ffintern") . "/popups/industry_arr.js");
          $output .= '<div  class="input-group"><input type="text" name="industrySelect"  onclick="IndustrySelect_2(\'' . $element['#id'] . '\');" id="sel-' . $element['#id'] . '" class="form-control '.$error_class.'" value="' . $selectOption . '">'.
            '<span class="input-group-addon" onclick="jQuery(\'#sel-'.$element['#id'].'\').click()"><i class="icon-search"></i></span>'.
            '</div>';
        }
      }
    }
    return $output;
  }
  else {
    element_set_attributes($element, array('id', 'name', 'size'));
    _form_set_class($element, array('form-select'));
    return '<select' . drupal_attributes($element['#attributes']) . '>' . form_select_options($element) . '</select>';
  }

}

function ffintern_company_center_right_column($nid) {
  drupal_add_css(drupal_get_path('theme', 'ffintern') . '/layouts/intern_layout/intern_layout.css');
  $compnay_info_view = views_embed_view("company_info", 'panel_pane_2', $nid);
  $user_follow_company = views_embed_view("user_follow_company", 'panel_pane_1', $nid);
  $shortcuts_block = module_invoke('intern_company', 'block_view', 'company center shortcuts');
  $company_reviews_block = views_embed_view('company_reviews_in_blocks', 'block_my_company_reviews', $nid);
  $output = '
    <div class="panel-pane pane-views-panes pane-company-info-panel-pane-2">
      <div class="panel-pane-title">
        <h2 class="pane-title">欢迎访问实习圈</h2>
      </div>
      <div class="pane-content">' .
    $compnay_info_view .
    '</div>
    </div>
  ';

  $output .= '
  <div class="panel-pane pane-block pane-intern-company-company-center-shortcuts" >
    <div class="panel-pane-title">
       <h2 class="pane-title">快速通道</h2>
    </div>
    <div class="pane-content">' . $shortcuts_block["content"] . '
    </div>
  </div>
  ';
  $output .= $user_follow_company;
  $output .= '
  <div class="panel-separator"></div><div class="panel-pane pane-views pane-company-reviews-in-blocks" >
    <div class="panel-pane-title">
      <h2 class="pane-title">关于我的最新点评</h2>
    </div>
    <div class="pane-content">
    ' . $company_reviews_block .
    '
    </div>
  </div>
    ';

  return $output;
}

function ffintern_company_center_main_header($nid) {
  _ffintern_add_quicktab_css();
  $showcase_block = module_invoke('intern_company', 'block_view', 'company center showcase');

  $output = '
  <div class="pane-content">' . $showcase_block['content'] .
    '</div>
  ';
  $nav_block = module_invoke('intern_company', 'block_view', 'company center tabs');
  $output .= '
  <div class="pane-content">' . $nav_block['content'] .
    '</div>
  ';
  return $output;
}


/**
 * Process variables for comment.tpl.php.
 *
 * @see comment.tpl.php
 */
function ffintern_preprocess_comment(&$variables) {
  $comment = $variables['elements']['#comment'];
  $variables['picture'] = theme_get_setting('toggle_comment_user_picture') ? theme('intern_comment_user_picture', array('account' => $comment)) : '';
}










			