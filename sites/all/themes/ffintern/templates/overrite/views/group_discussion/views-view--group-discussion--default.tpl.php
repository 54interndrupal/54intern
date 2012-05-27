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
<div id="forum-block" class="block">
<?php if ($header): ?>
<h2 class="block-title"><span><?php print $header; ?></span></h2>
<?php endif; ?>
<div class="block-content">
<?php print $exposed; ?>
<h4 class="add-new-post"><?php 
$options  = array(
    'query' => array('og_group_ref' => arg(1)) + drupal_get_destination(),
  );
print l(t('+ 我要发言'), 'node/add/discussion', $options); 
?></h4>

<?php if ($rows): ?>
		<?php print $rows; ?>
<?php elseif ($empty): ?>
	<div class="view-content forum-list">
		<?php print $empty; ?>
	</div>
<?php endif; ?>

</div>
</div>
