<div class='user-login-content'>
<div id="geren-zhuce"><a href="<?php 	print base_path();?>ajax_register/register/nojs" title="没有账号？立即加入实习圈！" class="ctools-use-modal ctools-modal-ctools-ajax-register-style"><span>注册实习圈</span></a></div>
<div class="zhuce-title"><?php print '> 个人用户登录' ?></div>
<?php  print  $name; ?>
<?php  print $pass; ?>
<div class="password">
<?php 	print $remember_me ;?>              s
<div class="forget-password"><a href="<?php print url("ajax_register/password/nojs") ?>" class="ctools-use-modal ctools-modal-ctools-ajax-pass-style"><?php print '忘记密码';?></a> </div>
</div>
  <?php 	print $hidden ;?>
  <?php  print $login; ?><br />

  <div class="qiehuanrukou"><span  id="company-user-login-title"><a href="#"><?php print('>> 企业入口')?></a></span></div>



  <div class="other-login-type">
    <div id="weibo-login-text"><?php 	print '>> 合作网站账号登录' ;?></div>
    <a href="csna/weibo"><img src="<?php 	print base_path().path_to_theme() ;?>/css/img/site/bt_wbs.gif" alt="新浪微博登录" title="新浪微博登录" /></a>
    <a href="<?php print url('csna/qq') ;?>"><img src="<?php 	print base_path().path_to_theme() ;?>/css/img/site/bt_qqs.gif" alt="qq账号登录" title="qq账号登录" /></a>
    <a href="<?php print url('csna/renren') ;?>"><img src="<?php 	print base_path().path_to_theme() ;?>/css/img/site/bt_rrs.gif" alt="人人账号登录" title="人人账号登录" /></a>

  </div>
  <div style="display:none">
    <?php 	print $links ;?>
    <?php 	print $weibo_signin ;?>
  </div>
</div>