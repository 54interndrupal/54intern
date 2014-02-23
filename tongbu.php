<?php
//session_start();
//print_r($_SESSION);
//print_r($_COOKIE);
?>

<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN"
  "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
<head>
  <meta http-equiv="Content-Type" content="text/html; charset=UTF-8"/>
  <title>Untitled Document</title>


  <?php
//session_start();
  include_once 'sites/all/modules/custom/ucuser/config.inc.php';

  $link = mysql_connect(UC_DBHOST, UC_DBUSER, UC_DBPW) or die(mysql_error());;
  mysql_select_db(UC_DBNAME) or die(mysql_error());;


//setcookie("user","php",time()+3600,"/","www.54intern.com");

  $uname = $_COOKIE['drupal_user'];

  $js = "";
//同步登录论坛
  if ($uname) {
    setcookie("uname", $uname, time() + 3600, "/", "www.54intern.com");
    $result = mysql_query("select * from " . UC_DBTABLEPRE . "tongbu where uname='$uname' and type='login'") or die(mysql_error());
    if ($row = mysql_fetch_array($result, MYSQL_BOTH)) {
      //echo $row['content'];
      $js = $row['content'];
      $pattern = '~\<script.*?\<\/script\>~s';
      preg_match_all($pattern, $js, $content);
      //print_r($content[0]);
      if (strpos($content[0][0], 'forum.54intern.com') > 0) {
        echo $content[0][0];
      }
      if (strpos($content[0][1], 'forum.54intern.com') > 0) {
        echo $content[0][1];
      }
    }
  }
  else {

    //1.论坛同步退出  2.主站同步登录 3主站同步退出

    $uname = $_COOKIE['uname'];
    $ip = $_SERVER['REMOTE_ADDR'];
    if ($uname) {
      //1.论坛同步退出
      $result = mysql_query("select * from " . UC_DBTABLEPRE . "tongbu where uname='$uname' and type='logout'") or die(mysql_error());
      if ($row = mysql_fetch_array($result, MYSQL_BOTH)) {
        $js = $row['content'];
        $pattern = '~\<script.*?\<\/script\>~s';
        preg_match_all($pattern, $js, $content);
        //print_r($content[0]);
        if (strpos($content[0][0], 'forum.54intern.com') > 0) {
          echo $content[0][0];
        }
        if (strpos($content[0][1], 'forum.54intern.com') > 0) {
          echo $content[0][1];
        }
      }
      setcookie("uname", '', time() - 3600, "/", "www.54intern.com");
    }
    else {
      //2.主站同步登录
      $comefrom = "http://forum.54intern.com";
      $result = mysql_query("select * from " . UC_DBTABLEPRE . "tongbu where isfromdrupal='$comefrom' and type='login' and ip='$ip' order by id desc") or die(mysql_error());
      //echo "ss".$comefrom;
      if ($row = mysql_fetch_array($result, MYSQL_BOTH)) {
        //echo $row['content'];
        $js = $row['content'];
        $pattern = '~\<script.*?\<\/script\>~s';
        preg_match_all($pattern, $js, $content);
        //print_r($content[0]);
        if (strpos($content[0][0], 'www.54intern.com') > 0) {
          echo $content[0][0];
        }
        if (strpos($content[0][1], 'www.54intern.com') > 0) {
          echo $content[0][1];
        }
        echo '<script type="text/javascript">parent.window.location.href="http://www.54intern.com";</script>';
      }
    }
  }
  ?>


</head>

<body>
</body>
</html>