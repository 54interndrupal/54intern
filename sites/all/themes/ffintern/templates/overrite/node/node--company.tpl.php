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
<?php //print debug($field_company_images); ?>
<div class="content">

  <input type="hidden" id="companyId" name="companyId" value="<?php print $nid?>"/>

  <div class="block" id="company-info">

    <div class="block-content">
      <div class="field field-name-pic">
        <div class="field-items">
          <?php $content['field_logo'][0]['#image_style'] = '120_30'?>
          <!--          --><?php //print print_r($content['field_logo']); ?>
          <?php print render($content['field_logo']); ?>
        </div>
        <div id="company_info_ops">
          <?php if (!user_is_anonymous() && !intern_user_is_company_user()) {
          drupal_add_js(drupal_get_path('module', 'intern_company') . '/js/intern_company.js');
        }
          ?>
        </div>
        <div id="company_vote_scores">
          <?php print intern_core_get_vote_score('field_treatment_value', $nid,'实习待遇');?>
          <?php print intern_core_get_vote_score('field_training_value', $nid,'培训力度');?>
          <?php print intern_core_get_vote_score('field_workload_value', $nid,'工作压力');?>
          <?php print intern_core_get_vote_score('field_regularize_value', $nid,'转正可能');?>
        </div>
      </div>


      <div class="company-brief-info c-1">

        <div class="field-add-review">
          <?php if (!user_is_anonymous() && !intern_user_is_company_user()) {
          $options = array(
            'query' => array('og_group_ref' => arg(1)) + drupal_get_destination(),
            'html' => TRUE,
          );
          $options['attributes']['target']="_blank";

          print l('<span class="form-submit add-content add-content-review">' . t('写点评') . '</span>', 'node/add/review', $options);
          ?>

          <?php
        }
        else {
          ?>
          <a href="<?php print url('ajax_register/login/nojs');?>" title=""
             class="ctools-use-modal ctools-modal-ctools-ajax-register-style  form-submit" rel="nofollow">写点评</a>
          <?php }?>
        </div>

        <div class="field field-name-name">
          <div class="field-items c-9"><?php print $title; ?></div>
        </div>

        <div class="company-fields">
          <div class="field-name-field-overall-value">
            <?php print intern_core_get_vote_info('field_overall_value', $nid);?>
          </div>
          <?php if (!empty($field_industry[0]['taxonomy_term']->name)) { ?>

          <div class="field field-name-industry">
            <div class="field-items"><?php print $field_industry[0]['taxonomy_term']->name; ?></div>
          </div>
          <?php } ?>
          <div class="field field-name-size">
            <div class="field-items"><?php print $field_company_size[0]['taxonomy_term']->name; ?></div>
          </div>
          <div class="field field-name-nature">
            <div class="field-items"><?php print $field_company_type[0]['taxonomy_term']->name; ?></div>
          </div>
          <?php if (!user_is_anonymous()) { ?>
          <div class="fix-company-info pull-right">
            <?php if (!user_is_anonymous() && !intern_user_is_company_user()) { ?>
            <a href="<?php print url('ajax_register/companyEdit/nojs/' . $nid);?>" title=""
               class="ctools-use-modal ctools-modal-company-modal-style" rel="nofollow" id="fixCompanyInfo">补充修订</a>
            <?php
          }
          else {
            ?>
            <a href="<?php print url('ajax_register/login/nojs');?>" title=""
               class="ctools-use-modal ctools-modal-ctools-ajax-register-style" rel="nofollow" id="fixCompanyInfo">补充修订</a>
            <?php }?>
          </div>
          <?php } ?>
        </div>

        <div class="field field-name-body">
          <label class='c-1'>企业简介：</label>


          <?php
          $body_content = $body[0]['safe_value'];
          if (drupal_strlen($body_content) > 150) {
            print '<span id=\'show-detail\' class="c-9">' . '展开>>' . '</span>';
            $body_sub_content = drupal_substr($body_content, 0, 150);
            $body_sub_content = rtrim(preg_replace('/(?:<(?!.+>)|&(?!.+;)).*$/us', '', $body_sub_content)) . '...';
            print '<div class="field-items" id="body-sub-content">' . $body_sub_content . '</div>';
            print '<div class="field-items" style="display:none" id="body-content">' . $body_content . '</div>';
          }
          else {
            print $body[0]['safe_value'];
          }

          ?>
        </div>
      </div>
    </div>
  </div>

  <div class="company-evaluations">
    <?php print intern_company_get_evaluations($nid);?>
  </div>
</div>
<?php if (count($field_company_images) > 0) { ?>
<div class="block" id="company-photos"><!-- 需要载入 jquery.jcarousel.min.js -->
  <div class="block-content">
    <ul>
      <?php
      if (count($field_company_images) > 0) {
        $field_company_image_output = '';
        foreach ($field_company_images as $field_company_image) {

          $uri = $field_company_image["uri"];
          $url = file_create_url($uri);
          //$newsimage_title = $newsimage["title"];
          //$newsimage_url= file_create_url($newsimage["uri"]);
          $field_company_image_url = image_style_url('138_102', $uri);
          $field_company_image_pic = '<img src="' . $field_company_image_url . '"/>';

          $field_company_image_output .= '<li>';
          $field_company_image_output .= '<a href="' . $url . '" class="company-photos-photo-link">';
          $field_company_image_output .= $field_company_image_pic;
          $field_company_image_output .= '</a></li>';

        }
        print  $field_company_image_output;

      }
      else {

      }
      ?>
    </ul>
  </div>
</div>
<?php } ?>

</div><!-- /.content -->

<?php
if (!user_is_anonymous()) {
  drupal_add_js(array(
    'review-modal-style' => array(
      'modalSize' => array(
        'type' => 'fixed',
        'width' => 800,
        'height' => 550,
      ),
      'modalOptions' => array(
        //'opacity' => (float) variable_get('ajax_register_modal_background_opacity', '0.8'),
        'background-color' => '#' . variable_get('ajax_register_modal_background_color', '000000'),
      ),
      'closeText' => '',
      'throbber' => theme('image', array('path' => ctools_image_path('ajax-loader.gif', 'ajax_register'))),
    ),
  ), 'setting');

  drupal_add_js(array(
    'company-modal-style' => array(
      'modalSize' => array(
        'type' => 'fixed',
        'width' => 750,
        'height' => 550,
      ),
      'modalOptions' => array(
        //'opacity' => (float) variable_get('ajax_register_modal_background_opacity', '0.8'),
        'background-color' => '#' . variable_get('ajax_register_modal_background_color', '000000'),
      ),
      'closeText' => '',
      'throbber' => theme('image', array('path' => ctools_image_path('ajax-loader.gif', 'ajax_register'))),
    ),
  ), 'setting');
}
?>
<script type="text/javascript">
  (function ($) {
    $(document).ready(function () {
      $('#show-detail').click(function () {
        if ($("#body-content:visible").size() == 0) {
          $('#show-detail').text('收起>>');
        } else {
          $('#show-detail').text('展开>>');
        }
        $("#body-content").toggle();
        $("#body-sub-content").toggle();
        return false;
      });

    });
  })(jQuery);
</script>



