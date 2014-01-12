<?php
  $gid = $_GET["og_group_ref"] ;
?>
<div id="content" class="column">
  <div class="section">

    <div class="review-modal node-review-form" id="reviewModal" ariaHidden="true">

      <div class="review-modal-content">
        <span class="review-tip"><span style="font-size: 16px;font-weight: bold"><?php print $form["title"]["#value"];?></span>（请帮我们完善下面的评价，这会帮到更多圈友 ：）</span>
        <?php print drupal_render($form["field_overall_value"])?>
        <?php print drupal_render($form["field_treatment_value"])?>
        <?php print drupal_render($form["field_training_value"])?>
        <?php print drupal_render($form["field_workload_value"])?>
        <?php print drupal_render($form["field_regularize_value"])?>

        <?php print drupal_render($form["body"])?>
        <?php print drupal_render($form["field_company_evaluation"])?>


        <?php print drupal_render($form["actions"]);?>
        <div style="display: none">
          <?php print drupal_render_children($form);?>
        </div>
      </div>
    </div>
  </div>
</div>
<div id="sidebar-second" class="column sidebar">
  <div class="section">

    <?php

    $block =intern_company_info_block($gid)
    ?>
    <div class="panel-pane pane-block pane-intern-company-company-info">
      <div class="pane-content">
        <?php print ($block);?>
      </div>
    </div>
  </div>
</div>
<script>
  var popularTagsHeight;
  (function ($) {
    $(document).ready(function () {
      var popularTags = $(".popular-tags");
      popularTagsHeight = popularTags.height();
      if(popularTagsHeight>32){
        popularTags.css("overflow","hidden");
        popularTags.css("height","32");
        popularTags.prepend("<span class='expander'><span>展开</span><i class='icon-double-angle-down'></i></span>");
        $(".expander", popularTags).click(function () {

            if($("i", this).hasClass("icon-double-angle-down")){
              popularTags.css("height",popularTagsHeight);

              $("span",this).text("收起");
              $("i", this).removeClass("icon-double-angle-down");
              $("i", this).addClass("icon-double-angle-up");
            }else{
              popularTags.css("height","32");
              $("span",this).text("展开");
              $("i", this).removeClass("icon-double-angle-up");
              $("i", this).addClass("icon-double-angle-down");
            }
        });
      }




      $('#show-detail').click(function () {

      });

    });
  })(jQuery);

</script>
