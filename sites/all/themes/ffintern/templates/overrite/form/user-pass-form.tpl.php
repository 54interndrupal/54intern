<?php

//  print_r($form);
?>

<div class="user-pass-popup">
   <span class="s-1">忘记密码了?</span>
   <span class="s-2">提示：输入在本站注册时使用的用户名或电子邮件地址，我们帮您找回密码。</span>
   <?php print drupal_render_children($form)?>
</div>