#############################################################################
# datasource: <?php print $datasource['id'] . "\n"; ?>
#############################################################################

source <?php print $datasource['id'] . "\n"; ?>
{
<?php foreach ($datasource['conf'] as $key => $value):?>
<?php print $key . ' = ' . $value; ?>
<?php endforeach; ?>

<?php foreach ($datasource['query'] as $value):?>
<?php print $value; ?>
<?php endforeach; ?>
}

<?php if (!empty($datasource['delta']['id'])): ?>
source <?php print $datasource['delta']['id'] . ' : ' . $datasource['id'] . "\n"; ?>
{
<?php foreach ($datasource['delta']['query'] as $value):?>
<?php print $value; ?>
<?php endforeach; ?>
}
<?php endif; ?>

#############################################################################
# index: <?php print $datasource['id'] . "\n"; ?>
#############################################################################

index <?php print $datasource['id'] . "\n"; ?>
{
source = <?php print $datasource['id'] . "\n"; ?>
<?php foreach ($datasource['index'] as $key => $value): ?>
<?php print $key . ' = ' . $datasource['index'][$key]; ?>
<?php endforeach; ?>
}

<?php if (!empty($datasource['delta']['id'])): ?>
index <?php print $datasource['delta']['id'] . ' : ' . $datasource['id'] . "\n"; ?>
{
source = <?php print $datasource['delta']['id'] . "\n"; ?>
<?php foreach ($datasource['delta']['index'] as $key => $value) :  ?>
<?php print $key . ' = ' . $datasource['delta']['index'][$key]; ?>
<?php endforeach; ?>
}
<?php endif; ?>
