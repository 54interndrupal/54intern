<?php

/**
 * @file
 * Main view template.
 *
 * Variables available:
 * - $classes_array: An array of classes determined in
 *   template_preprocess_views_view(). Default classes are:
 *     .view
 *     .view-[css_name]
 *     .view-id-[view_name]
 *     .view-display-id-[display_name]
 *     .view-dom-id-[dom_id]
 * - $classes: A string version of $classes_array for use in the class attribute
 * - $css_name: A css-safe version of the view name.
 * - $css_class: The user-specified classes names, if any
 * - $header: The view header
 * - $footer: The view footer
 * - $rows: The results of the view query, if any
 * - $empty: The empty text to display if the view is empty
 * - $pager: The pager next/prev links to display, if any
 * - $exposed: Exposed widget form/info to display
 * - $feed_icon: Feed icon to display, if any
 * - $more: A link to view more, if any
 *
 * @ingroup views_templates
 */
?>
<div class="<?php print $classes; ?>">
  <?php print render($title_prefix); ?>
  <?php if ($title): ?>
  <?php print $title; ?>
  <?php endif; ?>
  <?php print render($title_suffix); ?>
  <?php if ($header): ?>
  <div class="view-header">
    <?php print $header; ?>
  </div>
  <?php endif; ?>

  <?php if ($exposed): ?>
  <div class="view-filters" style="display: none">
    <?php print $exposed; ?>
  </div>
  <?php endif; ?>
  <div class="d-add-job">
    <?php
    $options = array(
      'query' => array('og_group_ref' => arg(1)) + drupal_get_destination(),
      'html' => TRUE
    );
    print l('<span class="add-content add-content-job">' . t('添加职位') . '</span>', 'node/add/job', $options);
    ?>
  </div>
  <div id="quicktabs-front_main_tabs" class="quicktabs-wrapper quicktabs-style-intern2">
    <div class="item-list">
      <ul class="quicktabs-tabs quicktabs-style-intern2">
        <li class="first <?php if ($_GET['sub_status'] == '4' && empty($_GET["deadline"]["value"]["date"])) {
          print 'active';
        }?>"><a
          href="javascript:resetStatus('4')"
          id="quicktabs-tab-jobs_tabs-0" class="active">发布中职位</a></li>
        <li class="first <?php if (!empty($_GET["deadline"]["value"]["date"])) {
          print 'active';
        }?>"><a
          href="javascript:resetStatus('10')"
          id="quicktabs-tab-jobs_tabs-10" class="active">即将到期</a></li>
        <li class="first <?php if ( $_GET['sub_status'] == '0') {
          print 'active';
        }?>"><a
          href="javascript:resetStatus('0')"
          id="quicktabs-tab-jobs_tabs-2" class="active">未发布</a></li>
        <li class="first <?php if ($_GET['sub_status'] == '3') {
          print 'active';
        }?>"><a
          href="javascript:resetStatus('3')"
          id="quicktabs-tab-jobs_tabs-5" class="active">待审核</a></li>
        <li class="first <?php if ( $_GET['sub_status'] == '1') {
          print 'active';
        }?>"><a
          href="javascript:resetStatus('1')"
          id="quicktabs-tab-jobs_tabs-3" class="active">已暂停</a></li>
        <li class="first <?php if ( $_GET['sub_status'] == '2') {
          print 'active';
        }?>"><a
          href="javascript:resetStatus('2')"
          id="quicktabs-tab-jobs_tabs-4" class="active">已到期</a></li>
        <li
          class="last <?php if ( $_GET['sub_status'] == 'All') {
            print 'active';
          }?>"><a
          href="javascript:resetStatus('All');"
          id="quicktabs-tab-jobs_tabs-1" class="active">全部</a></li>

      </ul>
    </div>
    <?php if ($attachment_before): ?>
    <div class="attachment attachment-before">
      <?php print $attachment_before; ?>
    </div>
    <?php endif; ?>


    <?php if ($rows): ?>
    <div class="view-content">
      <?php print $rows; ?>
    </div>
    <?php elseif ($empty): ?>
    <div class="view-empty">
      <?php print $empty; ?>
    </div>
    <?php endif; ?>
    <?php if ($pager): ?>
    <?php print $pager; ?>
    <?php endif; ?>
    <?php if ($attachment_after): ?>
    <div class="attachment attachment-after">
      <?php print $attachment_after; ?>
    </div>
    <?php endif; ?>

    <?php if ($more): ?>
    <?php print $more; ?>
    <?php endif; ?>

    <?php if ($footer): ?>
    <div class="view-footer">
      <?php print $footer; ?>
    </div>
    <?php endif; ?>

    <?php if ($feed_icon): ?>
    <div class="feed-icon">
      <?php print $feed_icon; ?>
    </div>
    <?php endif; ?>

  </div><?php /* class view */ ?>

</div>

<script type="text/javascript">
  function resetStatus(statusCode) {
    document.getElementById('edit-deadline-value-date').value ='';
    document.getElementById('edit-sub-status').value ='All';
    if(statusCode == 10){
      document.getElementById('edit-deadline-value-date').value ='<?php print date('Y-m-d', time()+7*24*3600);?>';
      document.getElementById('edit-sub-status').value = 4;
    }else{
      document.getElementById('edit-sub-status').value = statusCode;
    }
    document.getElementById('edit-submit-companycenter-jobs').click();
  }

  (function ($) {
    $(document).ready(function () {
      $(".view-companycenter-jobs .views-table").after( $(".view-companycenter-jobs .pager").parent(".item-list"));
      var sub_status = '<?php print $_GET["sub_status"]?>';
      var empty = $(".view-companycenter-jobs .views-table").size() == 0;
      if(!empty && sub_status=='4'){
        $("#edit-actionintern-job-refresh-action").show();
        $("#edit-actionintern-job-stop-action").show();
      }else if(!empty && (sub_status == '1'||sub_status=='2')){
        $("#edit-actionintern-job-republish-action").show();
      }
    });
  })(jQuery);
</script>


