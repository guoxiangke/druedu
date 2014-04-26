<?php
/**
 * @file
 * druedu_homework.default_cer_presets.inc
 */

/**
 * Implements hook_default_cer().
 */
function druedu_homework_default_cer() {
  $export = array();

  $cnr_obj = new stdClass();
  $cnr_obj->disabled = FALSE; /* Edit this to true to make a default cnr_obj disabled initially */
  $cnr_obj->api_version = 1;
  $cnr_obj->entity_types_content_fields = 'node*assignment_set*field_assignments_referencing*node*assignment*field_assignments_set_referenced';
  $cnr_obj->enabled = 1;
  $export['node*assignment_set*field_assignments_referencing*node*assignment*field_assignments_set_referenced'] = $cnr_obj;

  return $export;
}
