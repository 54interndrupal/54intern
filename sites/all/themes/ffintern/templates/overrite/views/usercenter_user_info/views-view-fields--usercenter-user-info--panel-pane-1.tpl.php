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
<?php _ajax_register_include_modal();
global $_authcache_is_cacheable;
drupal_add_css(drupal_get_path('module', 'avatar_selection') . '/avatar_selection.css');
$js_file = drupal_get_path('module', 'avatar_selection') . '/js/avatar_selection.js';
drupal_add_js($js_file);
?>
<div class="user-info">

  <div class="views-field views-field-picture user-picture authcache-user-picture"><?php if(!$_authcache_is_cacheable)print $fields['picture']->content;?></div>
  <div class="views-field">
    <a href="<?php print base_path() . 'user?qt-user_center_tab=2#qt-user_center_tab' ?>"><span style="font-size: 14px;color: #336600">申请的职位 ></span></a>
  </div>
  <div class="views-field">
    <a href="<?php print base_path() . 'user?qt-user_center_tab=0#qt-user_center_tab' ?>"><span style="font-size: 14px;color: #000033">关注的企业 ></span></a>
  </div>
  <div class="views-field">
    <a href="<?php print base_path() . 'user?qt-user_center_tab=3#qt-user_center_tab' ?>"><span style="font-size: 14px;color: #993300">收藏的文章 ></span></a>
  </div>
  <div class="views-field views-field-edit">
    <div class="field-content">
      <a href="<?php print url("ajax_register/profile/nojs");?>"
         class="ctools-use-modal ctools-modal-ctools-ajax-register-style"><span class="edt-acct">帐号编辑</span></a>

    </div>
  </div>
</div>
<div class="views-field-name">
  <div class="field-content "><a class="authcache-user-link"><?php if(!$_authcache_is_cacheable){ print $fields['name']->content;}else{print '!username';}?></a></div>
</div>
<?php $block = module_invoke('intern_user', 'block_view', 'user resume status'); ?>
<?php print($block['content']);?>