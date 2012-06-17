<?php if (intern_user_is_company_user()) {
  Global $user;
  $uid = $user->uid;
  $nid = intern_user_get_company_id($uid);
  unset($form["field_job_source"]);
  unset($form["field_source_url"]);
  unset($form["field_source_classes"]);
//   print_r($form["field_job_sub_status"]);
//    print_r($form['field_deadline']["und"][0]["value"]["date"]);
  $form['field_deadline']["und"][0]["value"]["date"]["#title"] = '职位有效期';
  ?>

<div id="content" class="column">
  <div class="section">
    <?php print ffintern_company_center_main_header($nid);?>
    <div class="pane-content pane-company-node-form pane-job-node-form">
      <div class="basic-info">
        <div class="basic-info-title">
          <?php if (empty($form["title"]["#value"])) { ?>
          <span class="title">新增职位</span><span></span>
          <?php }
        else { ?>
          <span class="title">编辑职位</span><span></span>
          <?php }?>
        </div>
        <div class="basic-info-content">

          <!--          --><?php //print_r($form["field_deadline"])?>
          <?php print drupal_render($form["title"])?>
          <?php print drupal_render($form["field_department"])?>
          <?php print drupal_render($form["field_number"])?>
          <?php print drupal_render($form["field_job_category"])?>
          <?php print drupal_render($form["field_work_place"])?>
          <?php print drupal_render($form["field_salary"])?>
          <?php print drupal_render($form["field_job_type"])?>
          <?php print drupal_render($form["field_work_months"])?>
          <?php print drupal_render($form["field_work_days"])?>
          <?php print drupal_render($form['field_deadline']["und"][0]["value"]["date"]);?>
          <?php print drupal_render($form["field_study_years"])?>
          <?php print drupal_render($form["field_education_requirement"])?>
          <?php print drupal_render($form["body"])?>

        </div>
      </div>
      <!--      --><?php //print_r($form["actions"]);?>
      <?php print drupal_render($form["actions"]);?>
      <?php print drupal_render_children($form);?>
    </div>
  </div>
</div>

<div id="sidebar-second" class="column sidebar">
  <div class="section">
    <?php print ffintern_company_center_right_column($nid);?>
  </div>
</div>


<?php } ?>