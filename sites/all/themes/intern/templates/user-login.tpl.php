<?php print  $name; ?>
<?php print $pass; ?>
<div class="password">
  <?php     print $remember_me;?>
  <div class="forget-password"><?php     print l(t('忘记密码'), 'user/password');?></div>
</div>
<div class="other-login-type">
  <span id="weibo-login-text"><?php     print t('微博账号登录');?></span>
  <!-- <a href="<?php     print url('weibo/login');?>"><img src="<?php     print base_path() . path_to_theme();?>/files/icon-weibo.png" alt="新浪微博" title="新浪微博登录" /></a> -->
  <a href="weibo/redirect?token=login"><img src="<?php     print base_path() . path_to_theme();?>/files/icon-weibo.png"
                                            alt="新浪微博" title="新浪微博登录"/></a>
  <a href="<?php     print url('qq_login/response');?>"><img
    src="<?php     print base_path() . path_to_theme();?>/files/icon-tencent-mb.png" alt="腾讯微博" title="腾讯微博登录"/></a>
</div>
<div style="display:none">
  <?php     //print $remember_me ;?>
  <?php     print $links;?>
  <?php     print $weibo_signin;?>

</div>
<?php print $login; //  drupal_render($variables['form']['name']); ?><br/>
<span id="geren-zhuce"><a href="#">没有账号？立即加入实习圈！</a></span>
<!-- <span id="geren-zhuce"><?php     print l(t('没有账号？立即加入实习圈!'), 'user/userregister');?></span> -->
<?php print $hidden; ?>