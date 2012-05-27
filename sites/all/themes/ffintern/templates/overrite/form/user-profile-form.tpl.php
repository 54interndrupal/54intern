<?php if (intern_user_is_company_user()) {
    Global $user;
    $uid = $user -> uid;
    $nid = intern_user_get_company_id($uid);
    hide($form["account"]["name"]);
    unset($form["account"]["mail"]["#description"]);
    unset($form["account"]['pass']['#attached']);
    unset($form["account"]["current_pass"]["#description"]);
    unset($form["account"]["pass"]["#description"]);
    unset($form['picture']);
    unset($form['locale']);
    unset($form['timezone']);
  ?>

<div id="content" class="column">
  <div class="section">
    <?php print ffintern_company_center_main_header($nid);?>
    <?php
    $setting_tabs_block = module_invoke('intern_company', 'block_view', 'company center setting tabs');
    ?>
    <div class="pane-content"><?php print $setting_tabs_block['content']?>
    </div>
    <div class="pane-content pane-company-node-form">
      <div class="basic-info">
        <div class="basic-info-title">
          <span class="title">个人信息</span><span></span>
        </div>
        <div class="basic-info-content">
          <div class="form-item"><label>用户名</label><span
            style="display:inline-block;padding-top: 4px;font-size: 14px"><?php print $form["account"]["name"]["#value"];?></span>
          </div>
<!--          --><?php //print_r($form)?>
          <?php print drupal_render($form["field_real_name"])?>
          <?php print drupal_render($form["account"]["mail"])?>
          <?php print drupal_render($form["field_phone"])?>
          <?php print drupal_render($form["field_cell_phone"])?>
        </div>
      </div>
      <div class="contact-info">
        <div class="contact-info-title">
          <span class="title">修改密码</span><span class="c-1" style="font-size: 12px;font-weight: normal;"> ( 留空为不改变当前密码 )</span>
        </div>
        <div class="contact-info-content">
          <?php print drupal_render($form["account"]["current_pass"])?>
          <?php print drupal_render($form["account"]["pass"])?>
        </div>
        <div class="form-actions">
<!--                    --><?php //print_r($form["actions"]);?>
          <?php print drupal_render($form["actions"]["submit"]);?>
          <input type="button" class="form-button-cancel" onclick="javascript:history.go(0)" value="取消">
        </div>
<!--        --><?php //print_r($form)?>
        <?php print drupal_render_children($form);?>

      </div>

    </div>

  </div>
</div>

<div id="sidebar-second" class="column sidebar">
  <div class="section">
    <?php print ffintern_company_center_right_column($nid);?>
  </div>
</div>


<?php } ?>