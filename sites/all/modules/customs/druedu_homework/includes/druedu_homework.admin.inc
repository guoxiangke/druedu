<?php
/**
 * @file
 * Include file to the admin part of druedu homework module.
 *
 * This file contain functions to create an admin part.
 */

/*
* Implementation admin form to configure homework vocabulary
*/
function druedu_homework_config_form($form, &$form_state) {
   $homework_config = variable_get('druedu_homework_config');
   $difficulties_options = _druedu_homework_get_vocabularies();
   $limit_submission_options = _druedu_homework_get_term_by_vocabulary('status_assignment');

  $form['difficulty'] = array(
    '#type' => 'radios',
    '#title' => t('Difficulties Vocabulary'),
    '#default_value' => isset($homework_config['difficulty']) ? $homework_config['difficulty'] : 0,
    '#options' => $difficulties_options,
    '#description' => t('Choose which taxonomy vocabulary you want use for difficulty homework.'),
  );

  $form['status_active_submission'] = array(
    '#type' => 'select',
    '#title' => t('Status Active submission'),
    '#default_value' => isset($homework_config['status_active_submission']) ? $homework_config['status_active_submission'] : 0,
    '#options' => $limit_submission_options,
    '#description' => t('Choose which term will be used to know a submission is active.'),
  );

  $form['status_submitted_submission'] = array(
    '#type' => 'select',
    '#title' => t('Status Submitted submission'),
    '#default_value' => isset($homework_config['status_submitted_submission']) ? $homework_config['status_submitted_submission'] : 0,
    '#options' => $limit_submission_options,
    '#description' => t('Choose which term will be used to know a submission has been submitted.'),
  );

  $form['status_marked_submission'] = array(
    '#type' => 'select',
    '#title' => t('Status Marked submission'),
    '#default_value' => isset($homework_config['status_marked_submission']) ? $homework_config['status_marked_submission'] : 0,
    '#options' => $limit_submission_options,
    '#description' => t('Choose which term will be used to know a submission has been marked.'),
  );

	$form['submit'] = array(
	        '#type' => 'submit',
	        '#value' => t('submit'),
	        '#weight' => 1,
	);	
	return $form;
}

/*
* Submit function of the homework admin form
*/
function druedu_homework_config_form_submit($form, &$form_state) {
	$result['difficulty'] = $form_state['values']['difficulty'];
  $result['status_marked_submission'] = $form_state['values']['status_marked_submission'];
  $result['status_submitted_submission'] = $form_state['values']['status_submitted_submission'];
  $result['status_active_submission'] = $form_state['values']['status_active_submission'];
	variable_set('druedu_homework_config', $result);
}