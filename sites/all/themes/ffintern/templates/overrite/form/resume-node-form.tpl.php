<?php //print_r($form['group_basic_information']['field_real_name']);?>
<?php GLOBAL $user; ?>
<?php
//  $resume = node_load($_SESSION['user_resume_id']);
//  $resume_view = node_view($resume);
//  $resume_index =  $resume_view['field_attached_resumes']['#items'][0]['value'];
////
////print_r($resume_view['field_apply_letters']);
////  print_r($resume_view['field_attached_resumes'][0]['entity']['field_collection_item'][$resume_index]['field_letter_body']['#items'][0]['safe_value'] );
//print_r(file_create_url($resume_view['field_attached_resumes'][0]['entity']['field_collection_item'][$resume_index]['field_resume_attachement']['#items'][0]['uri']));
//   print_r($resume_view['field_birth_date']['#items'][0]['value']);
?>

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
    <div class="quicktabs-wrapper" >
    <div class="block" id="user-center-tabs">
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



      <?php $readonly = (arg(3) == "preview");?>
      <?php if ($readonly) { ?>
      <?php
      print views_embed_view('resume_node_view', 'panel_pane_1', $_SESSION['user_resume_id']);?>



      <?php
    }
    else {
      ?>
      <div id="user-basic-info">

        <input type="hidden" id="userResumeUploaded" value="<?php print $_SESSION['user_resume_uploaded']?'Y':'N';?>"/>


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
      <?php print drupal_render_children($form); ?>
      <?php }?>

    </div>
  </div>

</div>

<div id="sidebar-second" class="column sidebar">
  <div class="section">
    <div class="panel-pane pane-views-panes pane-usercenter-user-info-panel-pane-1">
      <div class="panel-pane-title">
        <h2 class="pane-title">欢迎来到实习圈</h2>
      </div>
      <?php  print(views_embed_view("usercenter_user_info", 'panel_pane_1', $user->uid))?>
    </div>
    <!---->
    <!--      --><?php //$follow_block = views_embed_view('usercenter_user_followed', 'panel_pane_1',  $user->uid);?>
    <!--      --><?php //print $follow_block?>
  </div>
</div>

<div class="modal fade" id="resume-check" tabindex="-1" role="dialog" aria-labelledby="myModalLabel" aria-hidden="true">
  <div class="modal-dialog">
    <div class="modal-content">
      <div class="modal-header" style="">
        <button class="close" data-dismiss="modal" aria-hidden="true">X</button>
        <h4>提醒</h4>
      </div>
      <div class="modal-body" style="font-size: 16px;">

      </div>
    </div>
  </div>
</div>



