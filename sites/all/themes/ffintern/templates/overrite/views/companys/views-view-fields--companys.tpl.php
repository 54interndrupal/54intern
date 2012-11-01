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
<div class='company-info'>
  <div class="field field-name-name">
    <div class="field-items">
      <?php print $fields['title']->content ?>
    </div>
  </div>
  <div class="field field-name-size">
    <div class="field-items">
      关注人数： <?php print $fields['count']->content ?>人
    </div>
  </div>
<!--  <div class="field field-name-ops">-->
<!--    <div class="field-items">-->
<!--      --><?php //print $fields['ops']->content ?>
<!--    </div>-->
<!--  </div>-->
  <div class="field field-name-jobs">
    <?php if (intern_company_get_company_job_count($company_nid) > 0) { ?>
    <a href="<?php print url("company/" . $company_nid); ?>?requestTab=jobs">实习机会</a>
    <?php }
  else { ?>
    <span class="c-1"> 未发布实习机会<?php print $company_nid?></span>
    <?php }?>
  </div>
</div>

<div class='company-content'><span class='c-9'>企业简介:</span> <span
  class="c-10"><?php print $fields['body']->content ?> </span>
  <?php
  print views_embed_view('company_reviews_in_blocks', 'panel_pane_1', $company_nid);?>  </div>
<?php

/*
 print l(t('关注这个企业'),'flag/flag/bookmarks/'.$fields['nid']->content,
array(
'attributes' => array('class' => array('follow')),
'query' => array('token' => flag_get_token($fields['nid']->content))
)); 
*/
?>

<?php
global $user;
//企业用户不能访问
if (in_array(4, array_keys($user->roles))) {
}
else {
  // print $fields['ops']->content;
}
?>




