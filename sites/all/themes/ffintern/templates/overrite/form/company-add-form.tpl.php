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
<div class="c-17 model-header-title" id="model-header-title">
  <span class="active"> 添加企业信息 </span>
</div>

<div class="pane-content pane-company-node-form pane-company-node-info-add-form">
  <div class="basic-info">
    <div class="basic-info-content">
      <span class="modal-tip"> （添加企业信息，帮注更多圈友了解这个企业：）</span>
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
    </div>
    <?php print drupal_render_children($form);?>
  </div>
</div>

<script type="text/javascript">
  (function ($) {
    Drupal.behaviors.userProfile = {
      attach:function (context) {
        if ($("#model-header-title").size() > 0) {
          if($(".ctools-modal-content .modal-header #model-header-title").size()>0){
            $(".ctools-modal-content .modal-content #model-header-title").remove();
          } else{
            $(".ctools-modal-content .modal-header").addClass("colored").append($('#model-header-title'));
          }
        }
      }
    }
  })(jQuery);
</script>
