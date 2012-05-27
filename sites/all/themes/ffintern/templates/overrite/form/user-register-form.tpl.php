<?php

unset($form['account']['name']['#description']);
unset($form['account']['mail']['#description']);
unset($form['account']['pass']['#description']);
unset($form['account']['pass']['#attached']);
unset($form['weibo_signin']);
$form['account']['name']['#title'] = t('用户名');
$form['account']['mail']['#title'] = t('邮箱');
?>
<div class="user-reg-popup">
  <div class="d-2">
    <div class="user-reg">
      <div class="user-reg-title">
        <span class="s-1">欢迎加入<span class="s-2">实习圈</span> !</span>
        <span class="s-3">我们先出发，一起给未来更多可能。</span>
      </div>
      <div class="user-reg-form">
        <?php print drupal_render_children($form)?>
        <div class="c-1 d-term"><span>点击注册即表示已阅读并同意<?php print(l("《实习圈用户使用协议》", "node/127"))?></span></div>
      </div>

    </div>
    <div class="company-reg-showcase">
      <span class="sc" ></span>
       <?php print l('<span class="cpy-reg">企业注册入口</span>', "user/companyregister", array('html' => TRUE,))?>
    </div>
  </div>
  <div class="other-login">
    <span style="display: inline-block;padding:0 10px 0 0;vertical-align: top">  使用合作网站账号登录 </span>
    <a href="weibo/redirect?token=login"><span class="wbxl"></span></a>
    <a href="<?php print url('qq_login/response');?>"><span class="rrxl"></span></a>
    <a href="<?php print url('qq_login/response');?>"><span class="qqxl"></span></a>
  </div>
</div>