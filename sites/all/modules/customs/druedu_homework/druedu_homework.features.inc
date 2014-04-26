<?php
/**
 * @file
 * druedu_homework.features.inc
 */

/**
* Implementation of hook_views_api().
*/
function druedu_homework_views_api() {
  return array(
    'api' => 3,
  );
}


/**
 * Implements hook_ctools_plugin_api().
 */
function druedu_homework_ctools_plugin_api() {
  list($module, $api) = func_get_args();
  if ($module == "cer" && $api == "default_cer_presets") {
    return array("version" => "1");
  }
  list($module, $api) = func_get_args();
  if ($module == "heartbeat" && $api == "heartbeat") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_image_default_styles().
 */
function druedu_homework_image_default_styles() {
  $styles = array();

  // Exported image style: avatar_homework_submission.
  $styles['avatar_homework_submission'] = array(
    'name' => 'avatar_homework_submission',
    'effects' => array(
      13 => array(
        'label' => 'Scale and crop',
        'help' => 'Scale and crop will maintain the aspect-ratio of the original image, then crop the larger dimension. This is most useful for creating perfectly square thumbnails without stretching the image.',
        'effect callback' => 'image_scale_and_crop_effect',
        'dimensions callback' => 'image_resize_dimensions',
        'form callback' => 'image_resize_form',
        'summary theme' => 'image_resize_summary',
        'module' => 'image',
        'name' => 'image_scale_and_crop',
        'data' => array(
          'width' => '50',
          'height' => '50',
        ),
        'weight' => '1',
      ),
    ),
  );

  return $styles;
}

/**
 * Implements hook_node_info().
 */
function druedu_homework_node_info() {
  $items = array(
    'assignment' => array(
      'name' => t('Assignment'),
      'base' => 'node_content',
      'description' => t('An assignment is automatically create after choose an user during creation of an assignment set content type.'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
    'assignment_set' => array(
      'name' => t('Assignment set'),
      'base' => 'node_content',
      'description' => t('Create an assignment set, only teacher can create a new one.'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
  );
  return $items;
}