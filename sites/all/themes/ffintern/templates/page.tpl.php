<?php

/**
 * @file
 * Bartik's theme implementation to display a single Drupal page.
 *
 * The doctype, html, head and body tags are not in this template. Instead they
 * can be found in the html.tpl.php template normally located in the
 * modules/system folder.
 *
 * Available variables:
 *
 * General utility variables:
 * - $base_path: The base URL path of the Drupal installation. At the very
 *   least, this will always default to /.
 * - $directory: The directory the template is located in, e.g. modules/system
 *   or themes/bartik.
 * - $is_front: TRUE if the current page is the front page.
 * - $logged_in: TRUE if the user is registered and signed in.
 * - $is_admin: TRUE if the user has permission to access administration pages.
 *
 * Site identity:
 * - $front_page: The URL of the front page. Use this instead of $base_path,
 *   when linking to the front page. This includes the language domain or
 *   prefix.
 * - $logo: The path to the logo image, as defined in theme configuration.
 * - $site_name: The name of the site, empty when display has been disabled
 *   in theme settings.
 * - $site_slogan: The slogan of the site, empty when display has been disabled
 *   in theme settings.
 * - $hide_site_name: TRUE if the site name has been toggled off on the theme
 *   settings page. If hidden, the "element-invisible" class is added to make
 *   the site name visually hidden, but still accessible.
 * - $hide_site_slogan: TRUE if the site slogan has been toggled off on the
 *   theme settings page. If hidden, the "element-invisible" class is added to
 *   make the site slogan visually hidden, but still accessible.
 *
 * Navigation:
 * - $main_menu (array): An array containing the Main menu links for the
 *   site, if they have been configured.
 * - $secondary_menu (array): An array containing the Secondary menu links for
 *   the site, if they have been configured.
 * - $breadcrumb: The breadcrumb trail for the current page.
 *
 * Page content (in order of occurrence in the default page.tpl.php):
 * - $title_prefix (array): An array containing additional output populated by
 *   modules, intended to be displayed in front of the main title tag that
 *   appears in the template.
 * - $title: The page title, for use in the actual HTML content.
 * - $title_suffix (array): An array containing additional output populated by
 *   modules, intended to be displayed after the main title tag that appears in
 *   the template.
 * - $messages: HTML for status and error messages. Should be displayed
 *   prominently.
 * - $tabs (array): Tabs linking to any sub-pages beneath the current page
 *   (e.g., the view and edit tabs when displaying a node).
 * - $action_links (array): Actions local to the page, such as 'Add menu' on the
 *   menu administration interface.
 * - $feed_icons: A string of all feed icons for the current page.
 * - $node: The node object, if there is an automatically-loaded node
 *   associated with the page, and the node ID is the second argument
 *   in the page's path (e.g. node/12345 and node/12345/revisions, but not
 *   comment/reply/12345).
 *
 * Regions:
 * - $page['header']: Items for the header region.
 * - $page['featured']: Items for the featured region.
 * - $page['highlighted']: Items for the highlighted content region.
 * - $page['help']: Dynamic help text, mostly for admin pages.
 * - $page['content']: The main content of the current page.
 * - $page['sidebar_first']: Items for the first sidebar.
 * - $page['triptych_first']: Items for the first triptych.
 * - $page['triptych_middle']: Items for the middle triptych.
 * - $page['triptych_last']: Items for the last triptych.
 * - $page['footer_firstcolumn']: Items for the first footer column.
 * - $page['footer_secondcolumn']: Items for the second footer column.
 * - $page['footer_thirdcolumn']: Items for the third footer column.
 * - $page['footer_fourthcolumn']: Items for the fourth footer column.
 * - $page['footer']: Items for the footer region.
 *
 * @see template_preprocess()
 * @see template_preprocess_page()
 * @see template_process()
 * @see bartik_process_page()
 */
?>
<div id="page-wrapper"><div id="page">

  <div id="header"><div class="section clearfix">
    <div id="topBan" class="block">
      <?php print render($page['header_top']); ?>
      <?php if ($logo): ?>
      <a href="<?php print $front_page; ?>" title="<?php print t('首页'); ?>" rel="home" id="logo"><img src="<?php print $logo; ?>" alt="<?php print t('首页'); ?>" /></a>
      <?php endif; ?>

    </div>
    <?php print render($page['navigation']); ?>

  </div></div> <!-- /.section, /#header -->

	<?php 
	$highlighted = render($page['highlighted']);
	if ($highlighted): ?>
	<div id="highlighted">
	<?php print $highlighted; ?>
	</div>
	<?php endif; ?>
	<div id="main-wrapper" class="inside-page-main-wrapper">
      <?php if ($breadcrumb): ?>
      <div id="breadcrumb">
        <?php print $breadcrumb; ?>
      </div>
      <?php endif; ?>
	  <?php if ($messages): ?>
    <div id="messages"><div class="section clearfix">
      <?php print $messages; ?>
    </div></div> <!-- /.section, /#messages -->
  <?php endif; ?>
	  <div id="main" class="clearfix">
	  	<div id="main-top"></div>
	  	<div id="main-content">
	  		<!--<?php print render($tabs); ?>-->
		  <?php print render($page['content']); ?>
		  </div>
		  <div id="main-bottom"></div>
		</div>
	  </div>
	</div> <!-- /#main, /#main-wrapper -->
	
</div></div> <!-- /#page, /#page-wrapper -->
<DIV style="DISPLAY: none" id=maskLayer><IFRAME
  style="FILTER: alpha(opacity=50)" id=maskLayer_iframe src="about:blank"
  frameBorder=0 scrolling=no></IFRAME>
  <DIV style="FILTER: alpha(opacity=50); -moz-opacity: 0.5; opacity: 0.5;"
       id=alphadiv></DIV>
  <DIV id=drag>
    <H3 id=drag_h></H3>
    <DIV id=drag_con></DIV><!-- drag_con end --></DIV></DIV><!-- maskLayer end -->
<DIV></DIV><!-- alpha div end -->
<DIV style="DISPLAY: none" id=sublist></DIV>

<div id="footer"><div class="section">
 <?php print render($page['footer']); ?>
</div></div> <!-- /.section, /#footer -->

