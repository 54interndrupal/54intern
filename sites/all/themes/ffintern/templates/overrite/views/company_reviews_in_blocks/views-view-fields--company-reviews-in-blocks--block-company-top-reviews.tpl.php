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


<?php $review_content = views_embed_view('company_reviews_in_blocks', 'panel_pane_1', $fields['nid']->content);
 if(drupal_strlen($review_content)>10){
    $review_content = drupal_substr($review_content,0,10)."...";
 }
?>

<div>
  <div class='row row-<?php print $fields['counter']->content ?>'><?php print $fields['counter']->content ?></div>

  <div class='company-comment' onclick='window.open("/company/<?php print $fields['nid']->content?>")'>
    <?php print $fields['title']->content ?>
    <p><span class='c-1 title'>"<?php print $review_content ?>" </span><span class='c-2 daycount'> <?php print $fields['field_review_count']->content ?> 条评论</span></p>
  </div>
</div>