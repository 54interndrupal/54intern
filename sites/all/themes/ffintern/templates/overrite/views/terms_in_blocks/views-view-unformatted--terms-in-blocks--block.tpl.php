<?php
/**
 * Created by JetBrains PhpStorm.
 * User: Edison
 * Date: 12-5-9
 * Time: 下午9:43
 * To change this template use File | Settings | File Templates.
 */


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
<div class="views-row views-row-suffix">
   <div class="views-field views-field-name">
     <span class="field-content">
       <a class="term active" href="<?php print url('wikis/all/all')?>">所有文章</a>
     </span>
   </div>
</div>
<script type="text/javascript">
  (function ($) {
    $(document).ready(function () {
      $(".view-id-terms_in_blocks .view-content .views-row").hover(function () {
        $(this).addClass('selected');
      }, function () {
        $(this).removeClass('selected');
      })
      $(".view-id-terms_in_blocks .view-content .views-row").click(function () {
        window.location = $('.term', $(this)).attr('href');
      })

      $(".view-id-terms_in_blocks .view-content .term").each(function (i){
         if( window.location.href.indexOf($(this).attr('href') )>0){
           $(this).addClass('active');
         }else{
           $(this).removeClass('active');
         }
      })
    });
  })(jQuery);

</script>