<?php

/**
 * @file
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
<div class='author-info c-6'>
  <div class='framed'><?php print $fields['picture']->content ?></div>
  <?php print $fields['name']->content ?>
</div>
<div class="review-rating">
  <?php print $fields['field_overall_value']->content ?>
  <?php print intern_core_render_vote('实习待遇', $fields['field_treatment_value']->content); ?>
  <?php print intern_core_render_vote('培训力度', $fields['field_training_value']->content); ?>
  <?php print intern_core_render_vote('工作环境', $fields['field_workload_value']->content); ?>
  <?php print intern_core_render_vote('转正可能', $fields['field_regularize_value']->content); ?>
  <div class="counter c-5">#<?php print $fields['counter']->content ?></div>
</div>
<div class="review-content">
  <?php print $fields['body']->content ?>
  <?php if ($fields['field_company_evaluation']->content!='<div class="field-content"></div>') { ?>
  <div class="review-evaluation c-6">
    <label class="c-6">企业印象：</label><?php print $fields['field_company_evaluation']->content ?>
  </div>
  <?php }?>
  <div class="review-footer c-5">
    <div class="ops">
      <?php print(flag_create_link('collect', $fields['nid']->content));?>
      <?php print(flag_create_link('zan', $fields['nid']->content));?>
      <?php print(flag_create_link('report', $fields['nid']->content));?>
    </div>
    <?php print $fields['timestamp']->content ?>
    <?php print $fields['og_group_ref']->content?>
    <input type="hidden" name="reviewId" value="<?php print($fields['nid']->content);?>"/>
  </div>
</div>

