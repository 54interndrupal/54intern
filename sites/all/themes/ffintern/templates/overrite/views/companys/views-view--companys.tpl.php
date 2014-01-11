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

  <?php if ($exposed): ?>
  <div id="search-company" class="block advanced-search">
    <div class="block-content">
      <?php print $exposed; ?>
    </div>
  </div>
  <?php endif; ?>


</div>



<?php if ($view->total_rows > 0) { ?>
<div class="views-result-count">
    <?php if ($view->total_rows == 22*100) { ?>
        显示前<span class="row-count"> 2200 </span>家相关公司
    <?php }else{?>
        共找到<span class="row-count"> <?php print $view->total_rows;?> </span>家相关公司
    <?php }?>
</div>
<div class="company-sort-bar">
  <div class="company-sorters"><span>排序: &nbsp;</span><span class="sorter"
                                                            onclick="sortCompany('field_last_review_created_value DESC')">默认</span><span
    class="separator">|</span><span class="sorter" onclick="sortCompany('field_review_count_value DESC')">点评数 <i
    class="icon-arrow-down"></i></span><span class="separator">|</span><span
    class="sorter" onclick="sortCompany('field_overall_value_rating DESC')">综合实习价值 <i
    class="icon-arrow-down"></i></span><span class="separator">|</span><span class="sorter"
                                                                             onclick="sortCompany('field_last_review_created_value DESC')">最近点评 <i
    class="icon-arrow-down"></i></span></div>
</div>
<?php } ?>

<?php if ($rows): ?>
<div class="view-content company-list">
  <?php print $rows; ?>

  <?php if ($pager): ?>
  <?php print $pager; ?>
  <?php endif; ?>
</div>
<?php elseif ($empty): ?>
<div class="view-content company-list">
  <?php print $empty; ?>
</div>
<?php endif; ?>
<div id="applyAddCompany">
  <span>没有找到想要的企业，请
    <?php if (user_is_anonymous()) { ?>
     <a href="<?php print url('ajax_register/login/nojs');?>" title=""
        class="ctools-use-modal ctools-modal-ctools-ajax-register-style form-submit" rel="nofollow">
  <?php
    }
    else {
      ?>
    <a href="<?php print url('node/add/company');?>" title=""
       class="form-submit" target="_blank">
  <?php }?>
    <i class="icon-plus">
    </i> 添加企业</a></span>
</div>
<?php
if (!user_is_anonymous()) {
  drupal_add_js(array(
    'company-modal-style' => array(
      'modalSize' => array(
        'type' => 'fixed',
        'width' => 750,
        'height' => 550,
      ),
      'modalOptions' => array(
        //'opacity' => (float) variable_get('ajax_register_modal_background_opacity', '0.8'),
        'background-color' => '#' . variable_get('ajax_register_modal_background_color', '000000'),
      ),
      'closeText' => '',
      'throbber' => theme('image', array('path' => ctools_image_path('ajax-loader.gif', 'ajax_register'))),
    ),
  ), 'setting');
}?>

<script>
  function sortCompany(sortKey) {
    jQuery("#edit-sort-bef-combine").val(sortKey);
    jQuery("#edit-submit-companys").click();
  }
</script>