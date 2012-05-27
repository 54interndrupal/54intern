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

<div>
  <div class="d-1">
    <div class="views-field views-field-real-name"><?print $fields["field_real_name"]->content?></div>
    <div class="d-2">
      <div class="views-field views-field-picture"><?print $fields["picture"]->content?></div>
      <div class="d-3">
        <div class="views-field views-field-field-status"><?print $fields["field_status"]->content?></div>
        |&nbsp;&nbsp;
        <div class="views-field views-field-field-sex"><?print $fields["field_sex"]->content?></div>
        |&nbsp;&nbsp;
        <div class="views-field views-field-field-birth-date"><?print $fields["field_birth_date"]->content?></div>
      </div>
      <div class="views-field views-field-location"><label>居住地：</label><?print $fields["field_location"]->content?>
      </div>
      <div class="views-field views-field-cell-phone"><label>电话：</label> <?print $fields["field_cell_phone"]->content?>
      </div>
      <div class="views-field views-field-email"><label>E-mail：</label>

        <div class="field-content"><a
          href="mailto:<?print $fields['field_email']->content?>"><?print $fields["field_email"]->content?></a></div>
      </div>
    </div>
  </div>
  <div class="d-4">
    <span class="s-1">教育情况</span>

    <div class="d-4-1">
      <div class="views-field views-field-school"><label>所在学校：</label><?print $fields["field_school"]->content?> </div>
      <div class="views-field views-field-admission-date">
        <label>入学时间：</label><?print $fields["field_admission_date"]->content?> </div>
    </div>
    <div class="d-4-2">
      <div class="views-field views-field-disipline"><label>所在专业：</label><?print $fields["field_discipline"]->content?>
      </div>
      <div class="views-field views-field-education">
        <label>当前学历：</label><?print $fields["field_education"]->content?>
      </div>
    </div>
  </div>
</div>

<div class="d-5">
  <span class="s-1">
    求职信 ——  <?print $fields["field_letter_name"]->content?>
  </span>
  <?print $fields["field_letter_body"]->content?>
</div>
<div class="d-6">
  <span class="s-1">
    简历附件 ——  <?print $fields["field_resume_name"]->content?>
  </span>
  <?print $fields["field_resume_attachement"]->content?>
  <?print $fields["field_resume_memo"]->content?>
</div>
