<?php
// $Id: node.tpl.php,v 1.10 2009/11/02 17:42:27 johnalbin Exp $
  ?>
<div id = "node-<?php print $node->nid; ?>" class="<?php print $classes; ?> clearfix" >
<h1 class="title" ><a href ="<?php print $node_url; ?>" ><?php print $title; ?></a></h1>
<div class="content clearfix">
  <?php print $content; ?>
</div>
</div> <!-- /.node -->
