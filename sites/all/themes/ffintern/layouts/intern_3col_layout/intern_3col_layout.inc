<?php

// Plugin definition
$plugin = array(
  'title' => t('54intern布局'),
  'icon' => 'intern_layout.png',
  'theme' => 'panels_intern_3col_layout',
  'css' => 'intern_3col_layout.css',
  'category' => t('Columns: 3'),
  'admin css' => 'intern_3col_layout_admin.css',
  'regions' => array(
		'first' => t('first column'),
        'main' => t('main content'),
        'second' => t('second sidebar'),
        'highlighted'=>t('highlighted region')

  ),
);