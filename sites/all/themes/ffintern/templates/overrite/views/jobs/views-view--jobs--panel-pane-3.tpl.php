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
<?php
$isShowCompany = true;
if(!empty($_GET['field_location_tid'])){
  $isShowCompany = false;
}
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

  <div id="highlighted">
    <!-- 高级搜索区块放在Drupal 7核心提供的highlighted区域 -->
    <?php if ($exposed): ?>
    <div id="search-job" class="block advanced-search">
      <div class="block-content">
        <?php print $exposed; ?>
      </div>
    </div>
    <?php endif; ?>
  </div>

  <div id="quicktabs-fortune500_main_tabs" class="quicktabs-wrapper quicktabs-style-intern">
    <div class="item-list">
      <ul class="quicktabs-tabs quicktabs-style-intern">
        <li class="<?php if($isShowCompany){ ?>active<?php }?> first"><a href="#" onclick="changeTab('quicktabs-tabpage-fortune500_main_tabs-0',this)"
                                    id="quicktabs-tab-front_main_tabs-0" <?php if($isShowCompany){ ?>class="active"<?php }?>>500强企业</a></li>
        <li class="<?php if(!$isShowCompany){ ?>active<?php }?> last"><a href="#" onclick="changeTab('quicktabs-tabpage-fortune500_main_tabs-1',this)"
                            id="quicktabs-tab-front_main_tabs-1" <?php if(!$isShowCompany){ ?>class="active"<?php }?>>500强职位</a></li>
      </ul>
    </div>
    <div id="quicktabs-container-fortune500_main_tabs" class="quicktabs_main quicktabs-style-intern">
      <div id="quicktabs-tabpage-fortune500_main_tabs-0" class="quicktabs-tabpage <?php if(!$isShowCompany){ ?>"quicktabs-hide<?php }?>">
        <?php print views_embed_view('companys', 'panel_pane_3'); ?>
      </div>

      <div id="quicktabs-tabpage-fortune500_main_tabs1" class="quicktabs-tabpage <?php if($isShowCompany){ ?>"quicktabs-hide<?php }?>">
        <?php if ($rows): ?>

        <div class="view-content">
          <?php print $rows; ?>
        </div>

        <?php else: ?>

        <?php endif; ?>

        <?php if ($pager): ?>
        <?php print $pager; ?>
        <?php endif; ?>


        <?php if ($more): ?>
        <?php print $more; ?>
        <?php endif; ?>

        <?php if ($footer): ?>
        <div class="view-footer">
          <?php print $footer; ?>
        </div>
        <?php endif; ?>

      </div>


    </div>
  </div>
</div><?php /* class view */ ?>

<script type="text/javascript">
  function changeTab(tabName, tab){
    jQuery(".quicktabs-tabpage").addClass("quicktabs-hide");
    jQuery('#'+tabName).removeClass("quicktabs-hide");
    jQuery(".active",jQuery("#quicktabs-fortune500_main_tabs")).removeClass("active");
    jQuery(tab).addClass("active");
    jQuery(tab).parent("li").addClass("active");
  }

</script>