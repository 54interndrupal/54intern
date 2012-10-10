<?php

/**
 * @file
 * Bartik's theme implementation to display a node.
 *
 * Available variables:
 * - $title: the (sanitized) title of the node.
 * - $content: An array of node items. Use render($content) to print them all,
 *   or print a subset such as render($content['field_example']). Use
 *   hide($content['field_example']) to temporarily suppress the printing of a
 *   given element.
 * - $user_picture: The node author's picture from user-picture.tpl.php.
 * - $date: Formatted creation date. Preprocess functions can reformat it by
 *   calling format_date() with the desired parameters on the $created variable.
 * - $name: Themed username of node author output from theme_username().
 * - $node_url: Direct url of the current node.
 * - $display_submitted: Whether submission information should be displayed.
 * - $submitted: Submission information created from $name and $date during
 *   template_preprocess_node().
 * - $classes: String of classes that can be used to style contextually through
 *   CSS. It can be manipulated through the variable $classes_array from
 *   preprocess functions. The default values can be one or more of the
 *   following:
 *   - node: The current template type, i.e., "theming hook".
 *   - node-[type]: The current node type. For example, if the node is a
 *     "Blog entry" it would result in "node-blog". Note that the machine
 *     name will often be in a short form of the human readable label.
 *   - node-teaser: Nodes in teaser form.
 *   - node-preview: Nodes in preview mode.
 *   The following are controlled through the node publishing options.
 *   - node-promoted: Nodes promoted to the front page.
 *   - node-sticky: Nodes ordered above other non-sticky nodes in teaser
 *     listings.
 *   - node-unpublished: Unpublished nodes visible only to administrators.
 * - $title_prefix (array): An array containing additional output populated by
 *   modules, intended to be displayed in front of the main title tag that
 *   appears in the template.
 * - $title_suffix (array): An array containing additional output populated by
 *   modules, intended to be displayed after the main title tag that appears in
 *   the template.
 *
 * Other variables:
 * - $node: Full node object. Contains data that may not be safe.
 * - $type: Node type, i.e. story, page, blog, etc.
 * - $comment_count: Number of comments attached to the node.
 * - $uid: User ID of the node author.
 * - $created: Time the node was published formatted in Unix timestamp.
 * - $classes_array: Array of html class attribute values. It is flattened
 *   into a string within the variable $classes.
 * - $zebra: Outputs either "even" or "odd". Useful for zebra striping in
 *   teaser listings.
 * - $id: Position of the node. Increments each time it's output.
 *
 * Node status variables:
 * - $view_mode: View mode, e.g. 'full', 'teaser'...
 * - $teaser: Flag for the teaser state (shortcut for $view_mode == 'teaser').
 * - $page: Flag for the full page state.
 * - $promote: Flag for front page promotion state.
 * - $sticky: Flags for sticky post setting.
 * - $status: Flag for published status.
 * - $comment: State of comment settings for the node.
 * - $readmore: Flags true if the teaser content of the node cannot hold the
 *   main body content.
 * - $is_front: Flags true when presented in the front page.
 * - $logged_in: Flags true when the current user is a logged-in member.
 * - $is_admin: Flags true when the current user is an administrator.
 *
 * Field variables: for each field instance attached to the node a corresponding
 * variable is defined, e.g. $node->body becomes $body. When needing to access
 * a field's raw values, developers/themers are strongly encouraged to use these
 * variables. Otherwise they will have to explicitly specify the desired field
 * language, e.g. $node->body['en'], thus overriding any language negotiation
 * rule that was previously applied.
 *
 * @see template_preprocess()
 * @see template_preprocess_node()
 * @see template_process()
 */
?>
<?php //print debug($content['links']['flag']); ?>
<?php //print drupal_render($content['links']['flag']); 
//print flag_create_link('apply', $nid);
?>
<?php $node = node_load($node->nid); ?>
<div id="node-<?php print $node->nid; ?>" class="<?php print $classes; ?> clearfix"<?php print $attributes; ?>>

  <div class="content clearfix"<?php print $content_attributes; ?>>
    <div class='d-1'>
      <div style="float: right;margin: 10px 0 0 0;padding: 5px 0 5px 0;vertical-align: middle;">
      <?php ffintern_output_share_bar();?>
      </div>
      <div>
        <h2 <?php print $title_attributes; ?>>
          <?php print $node->title; ?>
        </h2>
      </div>
    </div>
    <div class='info c-5'>
      来源：<?php print $field_job_source[0]['taxonomy_term']->name; ?> &nbsp;
      <?php $node_statistics = statistics_get($node->nid);?>
      发布时间：<?php print format_date($changed, 'custom', 'Y-m-d'); ?>  &nbsp;
      发布：实习圈
    </div>

    <div class='summary'>
      <table>
        <tbody>
        <tr>
          <td>学历要求：</td>
          <td>
            <div class="field field-name-degree c-16">
              <?php print $field_education_requirement[0]['taxonomy_term']->name==''?'不限':$field_education_requirement[0]['taxonomy_term']->name; ?></div>
          </td>
          <td>岗位性质：</td>
          <td><div class="field field-name-jobnature c-16">
            <?php print $field_job_type[0]['taxonomy_term']->name==''?'实习':$field_job_type[0]['taxonomy_term']->name; ?>
          </div></td>
          <td>工作地点：</td>
          <td><div class="field field-name-joblocation c-16">
            <?php print $field_work_place[0]['taxonomy_term']->name; ?>
          </div></td>
        </tr>
        <tr>
          <td>学习年限：</td>
          <td>
            <div class="field field-name-years c-16">
              <?php print $field_study_years[0]['taxonomy_term']->name==''?'不限':$field_study_years[0]['taxonomy_term']->name; ?>
            </div>
          </td>
          <td> 每月薪水：</td>
          <td><div class="field field-name-salary c-16">
            <?php print $field_salary[0]['taxonomy_term']->name==''?'面议': $field_salary[0]['taxonomy_term']->name; ?>
          </div></td>
          <td>招聘人数：</td>
          <td> <div class="field field-name-number c-16">
            <?php $hireNumber = $field_number[0]['value']?>
            <?php print $hireNumber==0?'若干':$field_number[0]['value']; ?>
          </div></td>
        </tr>
        </tbody>
      </table>
    </div>

    <div class="field field-name-body">
      <span class="b" style="display:block;margin-bottom: 6px">职位简介</span>
      <?php print $body[0]['safe_value']; ?>
    </div>
    <?php if(!user_is_anonymous()&&!intern_user_is_company_user()){?>
    <div class="ops">
    <?php print flag_create_link('collect', $nid); ?>
    <?php
    global $user;

    //企业用户不能访问
    if (in_array(4, array_keys($user->roles))) {
    }
    else {
      print flag_create_link('apply', $nid);
    }
    ?>

    <span class="resume">
    <?php print l('填写简历',$_SESSION['resume_path']);?>
      </span>
    </div>
    <?php }?>
    <?php $source_url = trim($field_source_url[0]['value']);?>
    <?php if(!empty($source_url)){?>
     <span class="source-url">
        <?php $options = array('attributes'=>array('target'=>'_blank'));?>
        <?php print l('原站点申请',$source_url,$options) ?>
      </span>
     <?php }?>
      <span class="follow">
         <?php  print flag_create_link('bookmarks', $nid); ?>
      </span>
      <span class="foot-msg">
         ---- <?php print l('54intern.com',$bath_root)?>
      </span>
  </div>

  <div style="margin-top: 15px">
    <div class="tags" style="width: 400px;float: left;">
      <?php print(render($content['field_tags'])); ?>
    </div>

    <div style="float: right">
      <div style="float: right;">
        <?php ffintern_output_share_bar();?>
      </div>
      <?php
      // Remove the "Add new comment" link on the teaser page or if the comment
      // form is being displayed on the same page.
      if ($teaser || !empty($content['comments']['comment_form'])) {
        unset($content['links']['comment']['#links']['comment-add']);
      }
      // Only display the wrapper div if there are links.
      $links = render($content['links']);
      if ($links):
        ?>
        <div class="link-wrapper" style="float: right;">
          <?php print $links; ?>
        </div>
        <?php endif; ?>

    </div>
  </div>
</div>
