<div class='user-login-content'>
<div id="geren-zhuce"><a href="<?php 	print base_path();?>ajax_register/register/nojs" title="没有账号？立即加入实习圈！" class="ctools-use-modal ctools-modal-ctools-ajax-register-style"></a></div>
<div class="zhuce-title"><?php print '> '.t('个人用户登录') ?></div>
<?php  print  $name; ?>
<?php  print $pass; ?>
<div class="password">
<?php 	print $remember_me ;?>
<div class="forget-password"><a href="<?php print url("ajax_register/password/nojs") ?>" class="ctools-use-modal ctools-modal-ctools-ajax-pass-style"><?php print t('忘记密码');?></a> </div>
</div>
  <?php 	print $hidden ;?>
  <?php  print $login; ?><br />

  <div class="qiehuanrukou"><span  id="company-user-login-title"><a href="#"><?php print('>> '.t('企业入口'))?></a></span></div>



  <div class="other-login-type">
    <div id="weibo-login-text"><?php 	print '>> '.t('合作网站账号登录') ;?></div>
    <a href="weibo/redirect?token=login"><img src="<?php 	print base_path().path_to_theme() ;?>/css/img/site/bt_wbs.gif" alt="新浪微博" title="新浪微博登录" /></a>
    <a href="<?php print url('qq_login/response') ;?>"><img src="<?php 	print base_path().path_to_theme() ;?>/css/img/site/bt_rrs.gif" alt="腾讯微博" title="腾讯微博登录" /></a>
    <a href="<?php print url('qq_login/response') ;?>"><img src="<?php 	print base_path().path_to_theme() ;?>/css/img/site/bt_qqs.gif" alt="腾讯微博" title="腾讯微博登录" /></a>
  </div>
  <div style="display:none">
    <?php 	print $links ;?>
    <?php 	print $weibo_signin ;?>
  </div>
</div>