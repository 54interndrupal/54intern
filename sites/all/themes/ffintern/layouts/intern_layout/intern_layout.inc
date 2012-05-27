<?php

// Plugin definition
$plugin = array(
  'title' => t('54intern布局'),
  'icon' => 'intern_layout.png',
  'theme' => 'panels_intern_layout',
  'css' => 'intern_layout.css',
	'category' => t('Columns: 2'),
  'admin css' => 'intern_layout_admin.css',
  'regions' => array(
		'main' => t('main content'),
    'second' => t('second sidebar'),
  ),
);