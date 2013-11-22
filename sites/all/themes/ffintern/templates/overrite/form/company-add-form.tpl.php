<?php
/**
 * Created by JetBrains PhpStorm.
 * User: Edison
 * Date: 12-5-19
 * Time: 上午8:47
 * To change this template use File | Settings | File Templates.
 */
?>

<?php $nid = arg(1);

if (!empty($form["title"]["#value"])) {
  $form["title"]["#type"] = "hidden";
}
?>

<div class="pane-content pane-company-node-form pane-company-node-info-add-form">
  <div class="basic-info">
    <div class="basic-info-content">
      <?php print drupal_render($form["title"])?>
      <?php print drupal_render($form["field_company_type"])?>
      <?php print drupal_render($form["field_company_size"])?>
      <?php print drupal_render($form["field_industry"])?>
      <?php print drupal_render($form["field_location"])?>
      <?php print drupal_render($form["field_contact_address"])?>
      <?php print drupal_render($form["field_post_code"])?>
      <?php print drupal_render($form["field_website"])?>
      <?php print drupal_render($form["field_contact"])?>
      <?php print drupal_render($form["field_phone"])?>
      <?php print drupal_render($form["field_logo"])?>
      <?php print drupal_render($form["body"])?>
    </div>
    <div class="form-actions">
      <!--          --><?php //print_r($form["actions"]);?>
      <?php print drupal_render($form["actions"]["submit"]);?>
      <input type="button" class="form-button-cancel" onclick="javascript:history.go(0)" value="取消">
    </div>
    <?php print drupal_render_children($form);?>
  </div>
</div>
