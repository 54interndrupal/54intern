
  <div id="branding" class="clearfix">
    <?php print $breadcrumb; ?>
    <?php print render($title_prefix); ?>
    <?php if ($title): ?>
      <h1 class="page-title"><?php print $title; ?></h1>
    <?php endif; ?>
    <?php print render($title_suffix); ?>
    <?php print render($primary_local_tasks); ?>
  </div>

  <div id="page">
    <?php if ($secondary_local_tasks): ?>
      <div class="tabs-secondary clearfix"><ul class="tabs secondary"><?php print render($secondary_local_tasks); ?></ul></div>
    <?php endif; ?>

    <div id="content" class="clearfix">
      <div class="element-invisible"><a id="main-content"></a></div>
      <?php if ($messages): ?>
        <div id="console" class="clearfix"><?php print $messages; ?></div>
      <?php endif; ?>
      <?php if ($page['help']): ?>
        <div id="help">
          <?php print render($page['help']); ?>
        </div>
      <?php endif; ?>
      <?php if ($action_links): ?><ul class="action-links"><?php print render($action_links); ?></ul><?php endif; ?>
      <?php print render($page['content']); ?>
    </div>
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
    <div id="footer">
      <?php print $feed_icons; ?>
    </div>

  </div>
