<?php
/**
 * Created by JetBrains PhpStorm.
 * User: Edison
 * Date: 12-4-27
 * Time: 上午8:50
 * To change this template use File | Settings | File Templates.
 */ ?>
<?php if($is_front){?>
<div class='user-login-content'>
<div id="qiye-zhuce"><a href="user/companyregister" title="没有账号？立即加入实习圈！"></a></div>
<div class="zhuce-title"><?php print '> ' . t('企业用户登录') ?></div>
<?php  print  drupal_render($form['company_name']); ?>
<?php  print  drupal_render($form['name']); ?>
<?php  print  drupal_render($form['pass']); ?>
<div class="password">
  <?php  print  drupal_render($form['remember_me']); ?>
  <div class="forget-password"><a href="<?php print url("ajax_register/password/nojs") ?>" class="ctools-use-modal ctools-modal-ctools-ajax-pass-style"><?php print t('忘记密码');?></a></div>
</div>
<?php  print  drupal_render($form['submit']); ?><br/>
<?php     print drupal_render_children($form);?>
<div class="qiehuanrukou"><span id="normal-user-login-title"><a href="#"><?php print('>> ' . t('个人入口'))?></a></span>
</div>
</div>
<?php }else{
$form["company_name"]["#title"] = $form["company_name"]["#hint"];
$form["name"]["#title"] = $form["name"]["#hint"];
$form["pass"]["#title"] = $form["pass"]["#hint"];
unset($form["company_name"]["#hint"]);
unset($form["name"]["#hint"]);
unset($form["pass"]["#hint"]);
//print_r($form);
print drupal_render_children($form);
 }?>