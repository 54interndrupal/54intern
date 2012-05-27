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
<div class="content">

	
	<div class="block" id="company-reviews">
	<div class="block-content">
	
	<div class="title">
	 <?php print views_embed_view('company_front_reviews','default',arg(1)); ?>
	</div>
	
	<a href="#review-form"><?php print t('+ 我要点评'); ?></a>
  <?php if ($rows): ?>
     
    <?php print $rows; ?>
    
	<?php elseif ($empty): ?>

		<?php print $empty; ?>

  <?php endif; ?>
	
	<?php if ($pager): ?>
		<?php print $pager; ?>
	<?php endif; ?>
	</div>
	</div>
	
  <div id="review-form" class="form">
	<h2 class="title"><?php print t('我来评价'); ?></h2>
	
	<?php 
	if(intern_access_company_content_form(arg(1))){
	print company_center_get_form_block('review'); 
	}else{
	  print t('您只有关注了本企业以后，才能参与评价');
	}	
	
	?>
	</div>
	
</div><!-- /.content -->
	
