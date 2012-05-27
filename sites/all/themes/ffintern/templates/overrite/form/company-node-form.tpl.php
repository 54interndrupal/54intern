<?php
/**
 * Created by JetBrains PhpStorm.
 * User: Edison
 * Date: 12-5-19
 * Time: 上午8:47
 * To change this template use File | Settings | File Templates.
 */
?>
<?php $nid = arg(1); ?>
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
          <span class="title">公司基本信息</span><span></span>
        </div>
        <div class="basic-info-content">
          <div class="form-item"><label>公司名称</label><span style="display:inline-block;padding-top: 4px;font-size: 14px"><?php print $form["title"]["#value"];?></span></div>
          <?php print drupal_render($form["field_company_type"])?>
          <?php print drupal_render($form["field_company_size"])?>
          <?php print drupal_render($form["field_industry"])?>
          <?php print drupal_render($form["field_group_city"])?>
          <?php print drupal_render($form["field_contact_address"])?>
          <?php print drupal_render($form["field_post_code"])?>
          <?php print drupal_render($form["field_website"])?>
          <?php print drupal_render($form["field_logo"])?>
          <?php print drupal_render($form["body"])?>
        </div>
      </div>
      <div class="contact-info">
        <div class="contact-info-title">
          <span class="title">公司联系信息</span><span></span>
        </div>
        <div class="contact-info-content">
          <?php print drupal_render($form["field_contact"])?>
          <?php print drupal_render($form["field_sex"])?>
          <?php print drupal_render($form["field_job_position"])?>
          <?php print drupal_render($form["field_cell_phone"])?>
          <?php print drupal_render($form["field_email"])?>
          <?php print drupal_render($form["field_email"])?>
          <?php print drupal_render($form["field_phone"])?>
          <?php print drupal_render($form["field_fax"])?>
        </div>
        <div class="form-actions">
<!--          --><?php //print_r($form["actions"]);?>
          <?php print drupal_render($form["actions"]["submit"]);?>
          <input type="button" class="form-button-cancel" onclick="javascript:history.go(0)" value="取消">
        </div>
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
