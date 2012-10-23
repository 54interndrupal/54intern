<?php

/**
 * @file
 * Default theme implementation to present the feedback form.
 *
 * @see template_preprocess_feedback_form_display()
 */
?>
<div id="block-feedback-form">
  <h2><span class="feedback-link closed" style="cursor: pointer"><span id="feedback-form-toggle"  >[ + ] 网站反馈 </span></span></h2>
  <div class="content"><?php print drupal_render($content); ?></div>
</div>
