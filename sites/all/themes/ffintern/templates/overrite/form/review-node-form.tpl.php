<div class="review-modal node-review-form" id="reviewModal" ariaHidden="true">

  <div class="c-17 model-header-title" id="model-header-title">
    <span class="active"> 我要点评 </span>
  </div>
   <div class="review-modal-content">
    <span class="review-tip">（请帮我们完善下面的评价，这会帮到更多圈友：）</span>
    <?php print drupal_render($form["field_overall_value"])?>
    <?php print drupal_render($form["field_treatment_value"])?>
    <?php print drupal_render($form["field_training_value"])?>
    <?php print drupal_render($form["field_regularize_value"])?>

    <?php print drupal_render($form["body"])?>
    <?php print drupal_render($form["field_company_evaluation"])?>


    <?php print drupal_render($form["actions"]);?>
     <div style="display: none">
    <?php print drupal_render_children($form);?>
     </div>
  </div>
</div>
<script type="text/javascript">
  (function ($) {
    Drupal.behaviors.userProfile = {
      attach:function (context) {
        if ($("#model-header-title").size() > 0) {
          if($(".ctools-modal-content .modal-header #model-header-title").size()>0){
            $(".ctools-modal-content .modal-content #model-header-title").remove();
          } else{
             $(".ctools-modal-content .modal-header").addClass("colored").append($('#model-header-title'));
          }
        }
      }
    }
  })(jQuery);
</script>
