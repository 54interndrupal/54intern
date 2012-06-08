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
<div <?php if ($classes_array[$id]) {
  print 'class="' . $classes_array[$id] . '"';
} ?>>
  <?php print $row; ?>
</div>
<?php endforeach; ?>
<script type="text/javascript">
  (function ($) {
    $(document).ready(function () {
      $(".toggleReviewDetail").toggle(
        function () {
          var parentNode = $(this).parent().parent().parent().parent();
          $(".full-content",parentNode).show();
          $(".sub-content",parentNode).hide();
          $(this).text('收起>>');
        },
        function () {
          var parentNode = $(this).parent().parent().parent().parent();
          $(".full-content",parentNode).hide();
          $(".sub-content",parentNode).show();
          $(this).text('查看详细>>');
        }
      );

    });
  })(jQuery);
</script>