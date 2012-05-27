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

  <!-- �߼�����������Drupal 7�����ṩ��highlighted���� -->
  <?php if ($exposed): ?>
  <div id="search-company" class="block advanced-search">
    <div class="block-content">
      <?php print $exposed; ?>
    </div>
  </div>
  <?php endif; ?>


</div>


<?php if ($header): ?>
<h1 class="title" id="page-title"><?php print $header; ?></h1>
<?php endif; ?>

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





