<!--  --><?php //print_r($form["actions"]);?>
<div class="modal fade review-modal" id="reviewModal" role="dialog" ariaHidden="true">
  <div class="modal-dialog">
    <div class="modal-content">
      <div class="modal-header">
        <button type="button" class="close" data-dismiss="modal" aria-hidden="true">&times;</button>
        <h4 class="modal-title" id="reviewModalTitle">我要点评</h4>
      </div>
      <div class="modal-body">
        <span class="review-tip">（请帮我们完善下面的评价，这会帮到更多圈友：）</span>
        <?php print drupal_render($form["field_overall_value"])?>
        <?php print drupal_render($form["field_treatment_value"])?>
        <?php print drupal_render($form["field_training_value"])?>
        <?php print drupal_render($form["field_regularize_value"])?>

        <?php print drupal_render($form["body"])?>
        <?php print drupal_render($form["field_company_evaluation"])?>


        <?php print drupal_render($form["actions"]);?>
        <?php print drupal_render_children($form);?>
      </div>
    </div>
  </div>
</div>
