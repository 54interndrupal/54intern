<span class="s-t">用户信息</span>
<?php unset($form['pass']['#attached']);?>
<?php print drupal_render($form["name"]);?>
<?php print  drupal_render($form["mail"]);?>
<?php print drupal_render($form["pass"]);?>
<span class="sp"></span>

<span class="s-t">公司基本信息</span>

<!--  --><?php //print_r($form);?>
<?php   print drupal_render_children($form);?>
<div class="d-term"><span>请仔细阅读<?php print(l("《实习圈用户使用协议》", "node/127",array('attributes' => array('target' => "blank"))))?></span>  </div>
