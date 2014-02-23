<?php

error_reporting(0);

define('UC_CLIENT_VERSION', '1.6.0');
define('UC_CLIENT_RELEASE', '20110501');

define('API_DELETEUSER', 1);		//note 用户删除 API 接口开关
define('API_RENAMEUSER', 1);		//note 用户改名 API 接口开关
define('API_GETTAG', 0);		//note 获取标签 API 接口开关
define('API_SYNLOGIN', 1);		//note 同步登录 API 接口开关
define('API_SYNLOGOUT', 1);		//note 同步登出 API 接口开关
define('API_UPDATEPW', 1);		//note 更改用户密码 开关
define('API_UPDATEBADWORDS', 0);	//note 更新关键字列表 开关
define('API_UPDATEHOSTS', 0);		//note 更新域名解析缓存 开关
define('API_UPDATEAPPS', 0);		//note 更新应用列表 开关
define('API_UPDATECLIENT', 0);		//note 更新客户端缓存 开关
define('API_UPDATECREDIT', 1);		//note 更新用户积分 开关
define('API_GETCREDITSETTINGS', 0);	//note 向 UCenter 提供积分设置 开关
define('API_GETCREDIT', 0);		//note 获取用户的某项积分 开关
define('API_UPDATECREDITSETTINGS', 0);	//note 更新应用积分设置 开关

define('API_RETURN_SUCCEED', '1');
define('API_RETURN_FAILED', '-1');
define('API_RETURN_FORBIDDEN', '-2');


@define('IN_API', true);
@define('CURSCRIPT', 'api');

define('UCUSER_ROOT', drupal_get_path('module', 'ucuser').'/');
include_once UCUSER_ROOT.'/config.inc.php';

function _ucuser_get_code($text=''){
	$text = $text ? $text :$_SERVER['REQUEST_URI'];
	//preg_match('@code=(?P<code>.+)(^&.+|$)@i',$text, $matches);'/<img.*?src="(.*?)"/
	//print $text.'<br>';
	preg_match('/code=(.+)/',$text, $matches);
	//print_r($matches);
	//$text = $matches[0];
	parse_str($matches[0],$tarr);
	//print_r($ttt);
	//print $text;
	$text = $tarr['code'];
	return $text;
}

function ucuser_ucapi(){
		$get = $post = array();
	
		$code = @$_GET['code'];
		
		if(!$code){
			$code = _ucuser_get_code();
		}
		
		parse_str(_ucuser_authcode($code, 'DECODE', UC_KEY), $get);
//print_r($get);

		if(time() - $_GET['time'] > 3600) {
			//file_put_contents('test.txt',"sss");
			exit('Authracation has expiried'.time() ." - ".$_GET['time'] );
		}
		if(empty($get)) {
			
			exit('Invalid Request');
		}
	
		include_once UCUSER_ROOT.'./uc_client/lib/xml.class.php';
		$post = xml_unserialize(file_get_contents('php://input'));
	//file_put_contents('test.txt',"ttt".$get['action']);
		if(in_array($get['action'], array('test', 'deleteuser', 'renameuser', 'gettag', 'synlogin', 'synlogout', 'updatepw', 'updatebadwords', 'updatehosts', 'updateapps', 'updateclient', 'updatecredit', 'getcredit', 'getcreditsettings', 'updatecreditsettings', 'addfeed'))) {

			echo _ucuser_ucapi($get, $post);
			exit();
		} else {
			exit(API_RETURN_FAILED);
		}
	
	
}


function _ucuser_ucapi($get=array(), $post=array()){
	
	switch($get['action']){
		case 'test':
			$return = API_RETURN_SUCCEED;
			
		break;
		
		case 'deleteuser':
			if(!API_DELETEUSER) {
				$return = API_RETURN_FORBIDDEN;
			}else{
				$uidstring = str_replace("'", '', stripslashes($get['ids']));
				$uids = explode(',',$uidstring);
				if(empty($uids)){
					$return = API_RETURN_FORBIDDEN;
				}else{
					$uc_uids = db_select('ucuser_idrelation', 'ui')
						->fields('ui')
						->condition('ui.ucuid', $uids)
						->execute();
					
					$drupal_uid = array();
					while($uid = $uc_uids->fetchAssoc()){
						$drupal_uid[] = $uid['drupaluid'];
						
					}
					user_delete_multiple($drupal_uid);
					db_delete('ucuser_idrelation')
					->condition('ucuid', $uc_uids)
					->execute();
					$return = API_RETURN_SUCCEED;
				}
			}
			
		break;
		
		case 'renameuser':
			if(!API_RENAMEUSER) {
				$return = API_RETURN_FORBIDDEN;
			}else{
				$uid = $get['uid'];
				if(!$uid){
					$return = API_RETURN_FORBIDDEN;
				}else{
					$uc_uids = db_select('ucuser_idrelation', 'ui')
						->fields('ui')
						->condition('ui.ucuid', $uid)
						->execute()
						->fetchAssoc();
					
					$drupal_uid = $uc_uids['drupaluid'];
					$account = user_load($drupal_uid);
					$userinfo['name'] = $get['newusername'];
					if(user_save($account, $userinfo)){
						$return = API_RETURN_SUCCEED;
					}else{
						$return = API_RETURN_FAILED;
					}
				}
			}
			
		break;
		
		case 'gettag':
			$return = API_RETURN_SUCCEED;
		break;
		
		case 'synlogin':
			$uid = $get['uid'];
    		$username = $get['username'];
			if(!API_SYNLOGIN) {
      			return API_RETURN_FORBIDDEN;
    		}
			
			$account = user_load_by_name($get['username']);

			if($account){
			}else{
				$link=mysql_connect("localhost","root","54internal");
				mysql_select_db("shixiquan");
				$result=mysql_query("SELECT max(uid) as muid FROM `shixiquan`.users");
				$row=mysql_fetch_array($result, MYSQL_BOTH);
				$muid=$row['muid'];
				mysql_query("INSERT INTO `shixiquan`.users SET uid='$muid',name='$username', pass='$password',mail='$email',signature_format='plain_text',created='".$this->base->time."', access= '".$this->base->time."',login='".$this->base->time."',status='1',timezone='Asia/Shanghai', language='zh-hans',picture=0,init='$email'");
			/*	list($uc_uid,$username,$email) = uc_get_user($get['username']);
				$userinfo = array(
					'name' => $username,
					'pass' => $get['password'],
					'mail' => $email,
					'signature_format'=>'plain_text',
					'created' => time(),
					'login' => time(),
					'timezone'=>'Asia/Shanghai', 
					'language'=>'zh-hans',
					'picture'=>0,
					'init' => $email,
					'status' => 1,
					'access' => time()
				);
				user_save($account, $userinfo); */
			}
			
			
			require_once '/var/www/htdocs/54intern/includes/bootstrap.inc';
			drupal_bootstrap(DRUPAL_BOOTSTRAP_FULL);
			drupal_load('module', 'user');
			
			user_external_login_register( $username, 'ucuser');

			$return = API_RETURN_SUCCEED;
		break;
		
		case 'synlogout':
			require_once '/var/www/htdocs/54intern/includes/bootstrap.inc';
			drupal_bootstrap(DRUPAL_BOOTSTRAP_FULL);
    		drupal_load('module', 'user');
   			module_load_include('pages.inc', 'user', 'user');
      		user_logout(); 
			$return = API_RETURN_SUCCEED;
		break;
		
		case 'updatepw':
			$account = user_load_by_name($get['username']);

			if($account){
				$userinfo = array(
					'pass' => $get['password'],
				);
			}else{
				list($uc_uid,$username,$email) = uc_get_user($get['username']);
				$userinfo = array(
					'name' => $username,
					'pass' => $get['password'],
					'mail' => $email,
					'init' => $email,
					'status' => 1,
					'access' => time()
				);
			}
			if(user_save($account, $userinfo)){
				$return = API_RETURN_SUCCEED;
			}else{
				$return = API_RETURN_FAILED;
			}
		break;
		
		case 'updatebadwords':
			$return = API_RETURN_SUCCEED;
		break;
		
		case 'updatehosts':
			$return = API_RETURN_SUCCEED;
		break;
		
		case 'updatehosts':
			$return = API_RETURN_SUCCEED;
		break;
		
		case 'updateapps':
			$return = API_RETURN_SUCCEED;
		break;
		
		case 'updateclient':
			$return = API_RETURN_SUCCEED;
		break;
		
		case 'updatecredit':
			$return = API_RETURN_SUCCEED;
		break;
		
		case 'getcredit':
			$return = API_RETURN_SUCCEED;
		break;
		
		case 'getcreditsettings':
			$return = API_RETURN_SUCCEED;
		break;
		
		case 'updatecreditsettings':
			$return = API_RETURN_SUCCEED;
		break;
		
		case 'addfeed':
			$return = API_RETURN_SUCCEED;
		break;
		
		default:
			$return = API_RETURN_FAILED;
		break;
	}
	
	return $return;
}



function _ucuser_authcode($string, $operation = 'DECODE', $key = '', $expiry = 0) {
	$ckey_length = 4;

	$key = md5($key ? $key : UC_KEY);
	$keya = md5(substr($key, 0, 16));
	$keyb = md5(substr($key, 16, 16));
	$keyc = $ckey_length ? ($operation == 'DECODE' ? substr($string, 0, $ckey_length): substr(md5(microtime()), -$ckey_length)) : '';

	$cryptkey = $keya.md5($keya.$keyc);
	$key_length = strlen($cryptkey);

	$string = $operation == 'DECODE' ? base64_decode(substr($string, $ckey_length)) : sprintf('%010d', $expiry ? $expiry + time() : 0).substr(md5($string.$keyb), 0, 16).$string;
	$string_length = strlen($string);

	$result = '';
	$box = range(0, 255);

	$rndkey = array();
	for($i = 0; $i <= 255; $i++) {
		$rndkey[$i] = ord($cryptkey[$i % $key_length]);
	}

	for($j = $i = 0; $i < 256; $i++) {
		$j = ($j + $box[$i] + $rndkey[$i]) % 256;
		$tmp = $box[$i];
		$box[$i] = $box[$j];
		$box[$j] = $tmp;
	}

	for($a = $j = $i = 0; $i < $string_length; $i++) {
		$a = ($a + 1) % 256;
		$j = ($j + $box[$a]) % 256;
		$tmp = $box[$a];
		$box[$a] = $box[$j];
		$box[$j] = $tmp;
		$result .= chr(ord($string[$i]) ^ ($box[($box[$a] + $box[$j]) % 256]));
	}

	if($operation == 'DECODE') {
		if((substr($result, 0, 10) == 0 || substr($result, 0, 10) - time() > 0) && substr($result, 10, 16) == substr(md5(substr($result, 26).$keyb), 0, 16)) {
			return substr($result, 26);
		} else {
				return '';
			}
	} else {
		return $keyc.str_replace('=', '', base64_encode($result));
	}

}


function _ucuser_stripslashes($string) {
	if(is_array($string)) {
		foreach($string as $key => $val) {
			$string[$key] = _ucuser_stripslashes($val);
		}
	} else {
		$string = stripslashes($string);
	}
	return $string;
}