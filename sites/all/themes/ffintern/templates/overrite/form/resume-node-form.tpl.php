<?php //print_r($form['group_basic_information']['field_real_name']);?>
<?php GLOBAL $user; ?>


<div id="content" class="column">
  <div class="section">
    <?php
    $block = module_invoke('intern_user', 'block_view', 'user center showcase');
    ?>
    <div class="block" id="user-center-showcase">
      <div class="block-content">
        <?php print ($block['content']);?>
      </div>
    </div>
    <?php
    $block = module_invoke('intern_user', 'block_view', 'user resume tabs');
    ?>
    <div class="block" id="user-center-showcase">
      <div class="block-content">
        <?php print ($block['content']);?>
      </div>
    </div>
    <?php
    hide($form['group_job_target']);
    hide($form['group_other_information']);
    hide($form['field_hukou']);
    hide($form['field_id_card']);
    hide($form['field_political']);
    hide($form['field_nation']);
    ?>

    <!--  --><?php //print_r( $form['title']);?>
    <?php $form['field_birth_date']["und"][0]["value"]["date"]["#title"] = '出生日期';?>
    <?php $form['field_birth_date']["und"][0]["value"]["date"]["#required"] = 1;?>
    <?php $form['field_admission_date']["und"][0]["value"]["date"]["#title"] = '入学时间';?>
    <?php $form['field_admission_date']["und"][0]["value"]["date"]["#required"] = 1;?>


    <div id="user-basic-info">
      <?php print drupal_render($form['title']);?>
      <?php print drupal_render($form['field_real_name']);?>
      <?php print drupal_render($form['field_sex']);?>
      <?php print drupal_render($form['field_birth_date']["und"][0]["value"]["date"]);?>
      <?php print drupal_render($form['field_admission_date']["und"][0]["value"]["date"]);?>
      <?php print drupal_render($form['field_education']);?>
      <?php print drupal_render($form['field_school']);?>
      <?php print drupal_render($form['field_discipline']);?>
      <?php print drupal_render($form['field_status']);?>
      <?php print drupal_render($form['field_location']);?>
      <?php print drupal_render($form['field_email']);?>
      <?php print drupal_render($form['field_cell_phone']);?>
      <?php print drupal_render($form['field_phone']);?>
      <?php print drupal_render($form['field_contact_address']);?>
      <?php print drupal_render($form['field_post_code']);?>
    </div>
    <div id="user-attached-resume" style="display: none;">
      <?php print drupal_render($form['field_attached_resumes']["und"][0]["field_resume_name"]);?>
      <?php print drupal_render($form['field_attached_resumes']["und"][0]["field_resume_attachement"]);?>
      <?php print drupal_render($form['field_attached_resumes']["und"][0]["field_resume_memo"]);?>
      <?php hide($form['field_attached_resumes']); ?>

    </div>
    <div id="user-apply-letter" style="display:none">
      <?php print drupal_render($form['field_apply_letters']["und"][0]["field_letter_name"]);?>
      <?php print drupal_render($form['field_apply_letters']["und"][0]["field_letter_body"]);?>
      <?php hide($form['field_apply_letters']); ?>
    </div>
    <?php print drupal_render($form['field_attached_resumes']); ?>
    <?php  print drupal_render_children($form);?>


  </div>

  </div>

  <div id="sidebar-second" class="column sidebar">
    <div class="section">
      <?php  print(views_embed_view("usercenter_user_info", 'panel_pane_1', $user->uid))?>

    </div>
  </div>

  <script type="text/javascript">
    (function ($) {
      $(document).ready(function () {
        $("#user-basic-info-tab").click(function () {
          $("#user-basic-info-tab").addClass("active");
          $("#user-basic-info").show();
          $("#user-attached-resume-tab").removeClass("active");
          $("#user-attached-resume").hide();
          $("#user-apply-letter-tab").removeClass("active");
          $("#user-apply-letter").hide();
        });
        $("#user-attached-resume-tab").click(function () {
          $("#user-attached-resume-tab").addClass("active");
          $("#user-attached-resume").show();
          $("#user-basic-info-tab").removeClass("active");
          $("#user-basic-info").hide();
          $("#user-apply-letter-tab").removeClass("active");
          $("#user-apply-letter").hide();
        });
        $("#user-apply-letter-tab").click(function () {
          $("#user-apply-letter-tab").addClass("active");
          $("#user-apply-letter").show();
          $("#user-attached-resume-tab").removeClass("active");
          $("#user-attached-resume").hide();
          $("#user-basic-info-tab").removeClass("active");
          $("#user-basic-info").hide();
        });

      });
    })(jQuery);

  </script>



