<?php

/**
 * @file
 * Default simple view template to display a list of rows.
 *
 * @ingroup views_templates
 */
?>
<?php if (!empty($title)): ?>
<h3><?php print $title; ?></h3>
<?php endif; ?>
<?php foreach ($rows as $id => $row): ?>
<div <?php if ($classes_array[$id]) { print 'class="' . $classes_array[$id] .'"';  } ?>>
  <?php print $row; ?>
</div>
<?php endforeach; ?>
<script type="text/javascript">
  (function ($) {
    $(document).ready(function () {
      if("jobs"=="<?php print $_GET['requestTab']?>"){
        $("#quicktabs-tab-node_company_tab-1").click();
      }
    } )
  })(jQuery);
</script>