<?php
/**
 * @file views-view-fields.tpl.php
 * Default simple view template to all the fields as a row.
 *
 * - $view: The view in use.
 * - $fields: an array of $field objects. Each one contains:
 *   - $field->content: The output of the field.
 *   - $field->raw: The raw data for the field, if it exists. This is NOT output safe.
 *   - $field->class: The safe class id to use.
 *   - $field->handler: The Views field handler object controlling this field. Do not use
 *     var_export to dump this object, as it can't handle the recursion.
 *   - $field->inline: Whether or not the field should be inline.
 *   - $field->inline_html: either div or span based on the above flag.
 *   - $field->wrapper_prefix: A complete wrapper containing the inline_html to use.
 *   - $field->wrapper_suffix: The closing tag for the wrapper.
 *   - $field->separator: an optional separator that may appear before a field.
 *   - $field->label: The wrap label text to use.
 *   - $field->label_html: The full HTML of the label to use including
 *     configured element type.
 * - $row: The raw result object from the query, with all data it fetched.
 *
 * @ingroup views_templates
 */
?>
<?php
$company_nid = (string) $fields['nid']->content;
?>
<div class="field field-name-pic">
  <div class="field-items">
    <?php print $fields['field_logo']->content ?>
  </div>
</div>
<!--<div class='company-info'>-->
<!--  <div class="field field-name-jobs">-->
<!--    --><?php //if (intern_company_get_company_job_count($company_nid) > 0) { ?>
<!--    <a href="--><?php //print url("company/" . $company_nid); ?><!--?requestTab=jobs" target="_blank">实习机会</a>-->
<!--    --><?php
//  }
//  else {
//
?>
<!--    --><?php //}?>
<!--  </div>-->
<!--</div>-->
<div class="company-vote-info">
  <?php print $fields['field_overall_value']->content ?>
<span class="review-count">
  <?php if (empty($fields['field_review_count']->content)) { ?>
  0封点评, <a href="<?php print url("node/add/review")."?og_group_ref=" . $company_nid."&destination=node/".$company_nid; ?>" target="_blank">
  我要点评
  </a>
    <?php
    print $fields['field_review_count']->content;?>
  </a>
  <?php
}
else {
  ?>
  <a href="<?php print url("company/" . $company_nid); ?>" target="_blank">
    <?php
    print $fields['field_review_count']->content;?>
  </a>封点评</span>
    <?php } ?>
</div>
<div class='company-content'>
  <div class="field field-name-title">
    <?php print $fields['title']->content ?>
  </div>
  <div class="company-attributes">
    <span>地区：<?php print $fields['field_location']->content ?></span>
    &nbsp;|&nbsp;<span>行业：<?php print $fields['field_industry']->content ?></span>
  </div>


  <?php $review_content = views_embed_view('company_reviews_in_blocks', 'panel_pane_1', $company_nid);
  if (empty($fields['field_review_count']->content)) {
    ?>
    <span>公司简介:&nbsp;<?php print $fields['body']->content ?> </span>
    <?php
  }
  else {?>
    <div class="review-content">
      最新点评:&nbsp;<?php print $review_content;?>
    </div>

    <div class="company-scores">
      <?php print intern_core_get_vote_score('field_treatment_value', $company_nid, '实习待遇');?>
      <?php print intern_core_get_vote_score('field_training_value', $company_nid, '培训力度');?>
      <?php print intern_core_get_vote_score('field_workload_value', $company_nid, '工作环境');?>
      <?php print intern_core_get_vote_score('field_regularize_value', $company_nid, '转正可能');?>
    </div>
    <?php }?>


</div>


