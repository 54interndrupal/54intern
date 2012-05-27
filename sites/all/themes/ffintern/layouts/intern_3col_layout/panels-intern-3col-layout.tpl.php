<?php
// $Id: panels-twocol.tpl.php,v 1.1.2.1 2008/12/16 21:27:58 merlinofchaos Exp $
/**
 * @file
 * Template for a 2 column panel layout.
 *
 * This template provides a two column panel display layout, with
 * each column roughly equal in width.
 *
 * Variables:
 * - $id: An optional CSS id to use for the layout.
 * - $content: An array of content, each item in the array is keyed to one
 *   panel of the layout. This layout supports the following sections:
 *   - $content['left']: Content in the left column.
 *   - $content['right']: Content in the right column.
 */
?>
<div id="col-left" class="column">
  <div class="section">
    <?php print $content['first']; ?>
  </div>
</div>

<div class="column" id="col-main">
  <div class="section">
    <?php if(isset($content['highlighted'])&&( !empty($content['highlighted']))){ ?>
    <div id="col-highlighted" class="column">
      <div class="section">
        <?php print $content['highlighted']; ?>
      </div>
    </div>
    <?php }?>
    <div class="section">
      <div id="col-content" class="column"><div class="section">
        <?php print $content['main']; ?>
      </div></div>
      <div id="col-right" class="column sidebar"><div class="section">
        <?php print $content['second']; ?>
      </div></div>
    </div>
  </div>
</div>

