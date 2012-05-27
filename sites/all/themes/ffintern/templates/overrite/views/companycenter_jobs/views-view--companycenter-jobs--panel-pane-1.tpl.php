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
  <div class="view-filters">
    <?php print $exposed; ?>
  </div>
  <?php endif; ?>

  <div id="quicktabs-front_main_tabs" class="quicktabs-wrapper quicktabs-style-intern2">
    <div class="item-list">
      <ul class="quicktabs-tabs quicktabs-style-intern2">
        <li class="first <?php if (!isset($_GET['status']) || $_GET['status'] == '1') print 'active';?>"><a href="javascript:resetStatus('1')"
                                                                                                           id="quicktabs-tab-jobs_tabs-0" class="active">发布中的职位</a></li>        <li
          class="last <?php if (isset($_GET['status']) && $_GET['status'] == 'All') print 'active';?>"><a href="javascript:resetStatus('All');"
                                                                                                                                       id="quicktabs-tab-jobs_tabs-1" class="active">所有职位</a></li>

      </ul>
    </div>
  <?php if ($attachment_before): ?>
  <div class="attachment attachment-before">
    <?php print $attachment_before; ?>
  </div>
  <?php endif; ?>
  <div class="d-add-job">
    <?php
      $options  = array(
        'query' => array('og_group_ref' => arg(1)) + drupal_get_destination(),
        'html' => TRUE
      );
      print l('<span class="add-content add-content-job">'.t('添加职位').'</span>', 'node/add/job', $options);
      ?>
  </div>

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
    function resetStatus(cityCode){
      document.getElementById('edit-status').value = cityCode;
      document.getElementById('edit-submit-companycenter-jobs').click();
    }
  </script>


