<?php

/**
 * Implements hook_views_plugins().
 */
function views_photo_grid_views_plugins() {
  $module_path = drupal_get_path('module', 'views_photo_grid');

  return array(
    'module' => 'views_photo_grid',
    'style' => array(
      'views_photo_grid' => array(
        'title' => t('Photo grid'),
        'help' => t('Displays photos in a grid.'),
        'handler' => 'views_photo_grid_plugin_style',
        'theme' => 'views_photo_grid_style',
        'uses row plugin' => FALSE,
        'uses options' => TRUE,
        'uses fields' => TRUE,
        'type' => 'normal',
        'theme path' => $module_path . '/views',
        // 'path' => $module_path . '/views',
      ),
    ),
  );
}

