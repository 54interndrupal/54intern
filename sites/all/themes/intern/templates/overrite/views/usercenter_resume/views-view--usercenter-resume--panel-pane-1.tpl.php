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
<div class="tabs">

<?php 
  $uid = arg(1);
$query = db_select('flag_content','fc')
  ->fields('fc',array('content_id'))
  ->condition('content_type','user')
  ->condition('fid',3)
  ->condition('uid',arg(1));
  
  $result = $query->execute();
  $uids = $uid;
  foreach($result as $record){
     $uids = $uids.'+'.$record->content_id;
  }
  
print views_embed_view('usercenter_microblogs','panel_pane_1',$uids); 

?>

<div id="newest-status" class="block">
<?php if ($header): ?>
<h2 class="block-title"><span><?php print $header; ?></span></h2>
<?php endif; ?>
<div class="block-content">
<?php if ($rows): ?>

		<?php print $rows; ?>

<?php elseif ($empty): ?>
		<?php print $empty; ?>
<?php endif; ?>
</div>
</div><!-- /#newest-status -->
</div><!-- /.tabs -->







