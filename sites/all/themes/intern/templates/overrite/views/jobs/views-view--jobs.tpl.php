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
	<div id="search-company" class="block advanced-search">
	<div class="block-content">
	 <?php print $exposed; ?>
	 
	 <div class="adv-option"><a href="#adv-option" class="hide"><?php print t('更多搜索条件'); ?></a></div>
	 
	</div>
	</div>
	<?php endif; ?>
	
     

</div>
			

<?php if ($header): ?>
<h1 class="title" id="page-title"><?php print $header; ?></h1>
<?php endif; ?>
			
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

<script type="text/javascript">
    (function($) {
        $(document).ready(function(){
		  $('#highlighted #edit-study-years-wrapper').css('display','none');
	  $('#highlighted #edit-company-type-wrapper').css('display','none');
	  $('#highlighted #edit-field-salary-tid-wrapper').css('display','none');
	  $('#highlighted #edit-company-size-wrapper').css('display','none');
	  $('#highlighted #edit-education-wrapper').css('display','none');
	  
    //advanced search
    $('#highlighted div.advanced-search .adv-option a').toggle(function(){
      $(this).html('减少搜索条件');
    //  $(this).parents('div.advanced-search').find('#adv-option').slideDown();
      $(this).removeClass('hide');
	  $(this).addClass('show');
	  $('#highlighted #edit-study-years-wrapper').css('display','block');
	  $('#highlighted #edit-company-type-wrapper').css('display','block');
	  $('#highlighted #edit-field-salary-tid-wrapper').css('display','block');
	  $('#highlighted #edit-company-size-wrapper').css('display','block');
	  $('#highlighted #edit-education-wrapper').css('display','block');
      return false;
    }, function(){
      $(this).html('更多搜索条件');
     // $(this).parents('div.advanced-search').find('#adv-option').slideUp();
       $(this).removeClass('show');
	   $(this).addClass('hide');
	  $('#highlighted #edit-study-years-wrapper').css('display','none');
	  $('#highlighted #edit-company-type-wrapper').css('display','none');
	  $('#highlighted #edit-field-salary-tid-wrapper').css('display','none');
	  $('#highlighted #edit-company-size-wrapper').css('display','none');
	  $('#highlighted #edit-education-wrapper').css('display','none');
      return false;
    });
        });
    })(jQuery);
</script>




