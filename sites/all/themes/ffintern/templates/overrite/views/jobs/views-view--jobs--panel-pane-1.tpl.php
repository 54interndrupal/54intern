<?php
/**
 * @file views-view.tpl.php
 * Main view template
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
 * - $admin_links: A rendered list of administrative links
 * - $admin_links_raw: A list of administrative links suitable for theme('links')
 *
 * @ingroup views_templates
 */
?>
<div id="highlighted">
  <!-- 高级搜索区块放在Drupal 7核心提供的highlighted区域 -->
  <?php if ($exposed): ?>
  <div id="search-job" class="block advanced-search">
    <div class="block-content">
      <?php print $exposed; ?>
      <!--
      <div class="adv-option"><a href="#adv-option" class="hide"><?php print t('更多搜索条件'); ?></a></div> -->

    </div>
  </div>
  <?php endif; ?>
</div>
<!--
<?php if ($header): ?>
<h1 class="title" id="page-title"><?php print $header; ?></h1>
<?php endif; ?> -->
<div id="quicktabs-jobs_main_tabs" class="quicktabs-wrapper quicktabs-style-intern">

  <div class="item-list">
    <span class="city_more" onclick="residencySelect('edit-field-location-tid',true);">更多实习城市</span>
    <ul class="quicktabs-tabs quicktabs-style-intern">
      <li
        class="last <?php if (!isset($_GET['field_location_tid']) || $_GET['field_location_tid'] == 'All') print 'active';?>"><a href="javascript:resetCity('All');"
        id="quicktabs-tab-jobs_tabs-5" class="active">全国</a></li>
      <li class="first <?php if (isset($_GET['field_location_tid']) && $_GET['field_location_tid'] == '200') print 'active';?>"><a href="javascript:resetCity('200')"
                           id="quicktabs-tab-jobs_tabs-0" class="active">上海</a></li>
      <li class="last <?php if (isset($_GET['field_location_tid']) && $_GET['field_location_tid'] == '100') print 'active';?>"><a href="javascript:resetCity('100')"
                          id="quicktabs-tab-jobs_tabs-1" class="active">北京</a></li>
      <li class="last  <?php if (isset($_GET['field_location_tid']) && $_GET['field_location_tid'] == '400') print 'active';?>"><a href="javascript:resetCity('400')"
                           id="quicktabs-tab-jobs_tabs-2" class="active">深圳</a></li>
      <li class="last  <?php if (isset($_GET['field_location_tid']) && $_GET['field_location_tid'] == '302') print 'active';?>"><a href="javascript:resetCity('302')"
                          id="quicktabs-tab-jobs_tabs-3" class="active">广州</a></li>
      <li class="last <?php if (isset($_GET['field_location_tid']) && $_GET['field_location_tid'] == '802') print 'active';?>"><a href="javascript:resetCity('802')"
                          id="quicktabs-tab-jobs_tabs-4" class="active">杭州</a></li>
      <li class="last <?php if (isset($_GET['field_location_tid']) && $_GET['field_location_tid'] == '2002') print 'active';?>"><a href="javascript:resetCity('2002')"
                          id="quicktabs-tab-jobs_tabs-6" class="active">西安</a></li>
    </ul>

  </div>
  <?php if ($rows): ?>
  <div class="view-content job-list">
    <?php print $rows; ?>

    <?php if ($pager): ?>
    <?php print $pager; ?>
    <?php endif; ?>
  </div>
  <?php elseif ($empty): ?>
  <div class="view-content job-list">
    <?php print $empty; ?>
  </div>
  <?php endif; ?>
</div>



<script type="text/javascript">
  function resetCity(cityCode){
    document.getElementById('edit-field-location-tid').value = cityCode;
    document.getElementById('sel-edit-field-location-tid').disabled=true;
    document.getElementById('sel-edit-job-category').disabled=true;
    document.getElementById('edit-submit-jobs').click();
  }

</script>




