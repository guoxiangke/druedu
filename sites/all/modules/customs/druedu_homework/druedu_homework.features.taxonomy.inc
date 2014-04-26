<?php
/**
 * @file
 * druedu_homework.features.taxonomy.inc
 */

/**
 * Implements hook_taxonomy_default_vocabularies().
 */
function druedu_homework_taxonomy_default_vocabularies() {
  return array(
    'difficulties_homework' => array(
      'name' => 'Difficulties - Homework',
      'machine_name' => 'difficulties_homework',
      'description' => '',
      'hierarchy' => '0',
      'module' => 'taxonomy',
      'weight' => '0',
    ),
    'status_assignment' => array(
      'name' => 'Status - Assignment',
      'machine_name' => 'status_assignment',
      'description' => '',
      'hierarchy' => '0',
      'module' => 'taxonomy',
      'weight' => '0',
    ),
  );
}
