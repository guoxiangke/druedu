<?php
/**
 * @file
 * Include file of druedu homework module.
 *
 * This file contain functions to create all form presents on druedu module expected admin form.
 */

function druedu_homework_timeline_comment_form($form, &$form_state) {
	$args = arg();
	$nid = $args[1];
	$form['comment'] = array(
  		'#type' => 'textarea',
  		'#title' => NULL,
  		'#cols' => 50,
  		'#rows' => 3,
 		'#weight' => 0,
	);

	$form['submit'] = array(
	    '#type' => 'submit',
	    '#value' => t('Leave a comment'),
	    '#weight' => 1,
	    '#ajax' => array(
		    'callback' => 'druedu_homework_timeline_comment_ajax_callback',
		    'wrapper' => 'body',
		    'method' => 'append',
		    'effect' => 'fade',
		    'progress' => array('type' => 'throbber', 'message' => NULL),
		),
	);	
	
	$form['node_nid'] = array(
	    '#type' => 'hidden',
	    '#value' => $nid,
	);
	return $form;
}

function druedu_homework_timeline_comment_ajax_callback($form, &$form_state) {
	$commands = array();   
	$commands[] = ajax_command_remove('#druedu-homework-timeline-comment-form .system-messages');
    $commands[] = ajax_command_prepend('#druedu-homework-timeline-comment-form', theme('status_messages'));
  	$commands[] = ajax_command_invoke(null, 'reset_homework_timeline_comment_form');
	return array('#type' => 'ajax', '#commands' => $commands);
}

function druedu_homework_timeline_comment_form_submit($form, &$form_state) {
	$nid = $form_state['input']['node_nid'];
	global $user;
  	$user = user_load($user->uid);
  	
    $current_firstname = field_get_items('user', $user, 'field_firstname');
    $firstname = field_view_value('user', $user, 'field_firstname', $current_firstname[0]);
    $current_firstname = field_get_items('user', $user, 'field_lastname');
    $lastname = field_view_value('user', $user, 'field_lastname', $current_firstname[0]);
	$message_id = 'heartbeat_homework_timeline_comment_form';
	$variables = array(
		'firstname' => $firstname['#markup'],
		'lastname' => $lastname['#markup'],
	    'message' => $form['comment']['#value'],
	);
	heartbeat_api_log($message_id, $user->uid, 0, $nid, 0, $variables);
	drupal_set_message(t('Your message has been saved.'));

}

function druedu_homework_timeline_comment_form_validate($form, &$form_state) {
	if(empty($form_state['values']['comment']) || $form_state['values']['comment']== '') {
		form_set_error('comment', t('Please write a message before send.'));
	}
}

function druedu_homework_submission_form($form, &$form_state) {
	$homework_config = variable_get('druedu_homework_config');
	if (!isset($homework_config) && !isset($homework_config['difficulty'])) {
  		drupal_set_message(t('Submission form not available. Please contact an administrator.'), 'error');
	}
	else {
		global $user;
		$account = user_load($user->uid);
		$args = arg();
		$nid = $args[1];
		$node = node_load($nid);
		$form['#attributes']['class'][] = 'clearfix';
		$form['uploaded_file'] = array(
		    '#type' => 'hidden',
		    '#value' => isset($form_state['input']['uploaded_file']) ? $form_state['input']['uploaded_file'] : NULL,
		    '#weight' => 0,
	  	);
		$difficulties = taxonomy_get_tree($homework_config['difficulty']);
		foreach ($difficulties as $difficulty) {
			$options[$difficulty->tid] = '<span class="difficulty ' . strtolower(str_replace(' ', '_', $difficulty->name)) .'">' . t($difficulty->name) . '</span>';
		}
		$picture = (!empty($account->picture)) ? theme('image_style', array('style_name' => 'avatar_homework_submission', 'path' => $account->picture->uri)) : theme('image_style', array('style_name' => 'avatar_homework_submission', 'path' => variable_get('user_picture_default')));
		$class = ($user->uid == $node->uid) ? 'student' : null;
		$form['avatar'] = array(
	  		'#markup' => '<div class="submission_form_left '.$class.' span1">' . $picture . '</div>',
	 		'#weight' => 1,
		);

		$form['prefix'] = array(
	  		'#markup' => '<div class="submission_form_right span11">',
	 		'#weight' => 2,
		);
		if(!user_access('administer assignment')) {
		    $form['difficulty'] = array(
			    '#type' => 'radios',
			    '#title' => t('This homework was'),
			    '#default_value' => isset($form_state['values']['difficulty']) ? $form_state['values']['difficulty'] : NULL,
			    '#options' => $options,
			    '#weight' => 3,
				'#attributs' => array('class' => array('clearfix')),
		  	);
		}

	  	$form['submission_comment'] = array(
	  		'#type' => 'textarea',
	  		'#title' => t('Leave a comment'),
	  		'#default_value' => isset($form_state['values']['submission_comment']) ? $form_state['values']['submission_comment'] : NULL,
	  		'#size' => 50,
	 		'#weight' => 4,
	 		'#resizable' => FALSE
		);

	  	if(user_access('administer assignment')) {
			$node = node_load($nid);
			$can_mark = ($node->field_assignment_status[LANGUAGE_NONE][0]['tid'] != $homework_config['status_marked_submission']) ? TRUE : FALSE; 
	  	}
	  	if(isset($can_mark) && $can_mark) {
			$form['submission_marked'] = array(
				'#type' => 'checkbox',
		  		'#title' => t('Mark this assignment when sending the submission.'),
		  		'#default_value' => 0,
		 		'#weight' => 5,
			);
		}
		$form['submission_submit'] = array(
		    '#type' => 'submit',
		    '#value' => t('Submit'),
		    '#weight' => 6,
		    '#ajax' => array(
		    	'callback' => 'druedu_homework_submission_ajax_callback',
		        'wrapper' => 'body',
		        'method' => 'append',
		        'effect' => 'fade',
		        'progress' => array('type' => 'throbber', 'message' => NULL),
			),
		);	

		$form['node_nid'] = array(
		    '#type' => 'hidden',
		    '#value' => $nid,
		);
		
		$form['suffix'] = array(
	  		'#markup' => '</div>',
	 		'#weight' => 7,
		);
		return $form;
	}
}

function druedu_homework_submission_ajax_callback($form, &$form_state) {
	global $user;
	$nid = $form_state['input']['node_nid'];
	$node = node_load($nid);
	$commands = array();
	if($form_state['values']['submission_marked'] != 0) {
		$commands[] = ajax_command_remove('#druedu-homework-submission-form .form-item-submission-marked');
	}
	$commands[] = ajax_command_remove('#wrapper_status_message_submission_form');
    $commands[] = ajax_command_before('#submission_form', '<div id="wrapper_status_message_submission_form">'.theme('status_messages').'</div>');
    $form_error = form_get_errors();
    if(($node->uid != $user->uid || !$node->field_locked[LANGUAGE_NONE][0]['value']) && empty($form_error)) {
  		$commands[] = ajax_command_invoke(null, 'reset_homework_submission_form');
  		/* LAST SUBMISSION */
	    // $last_submissions_info = _druedu_homework_last_submission($node);
	    // /* PREPARE VALUE LAST SUBMISSION*/
	    // $last_submission_block = _druedu_homework_prepare_value_last_submission_block($last_submissions_info);
	    // $last_submission_block['difficulty'] = (!empty($node->field_assignment_difficulty)) ? taxonomy_term_load($node->field_assignment_difficulty[LANGUAGE_NONE][0]['tid'])->name : NULL ;
	    // /* ON TIME */
	    $node_ref = node_load($node->field_assignments_set_referenced[LANGUAGE_NONE][0]['target_id']);
	    // $on_time = _druedu_homework_submission_on_time($node, $node_ref->field_assignment_due_date[LANGUAGE_NONE][0]['value']);
	    // $last_submission_block['on_time'] = ($on_time['has_submission'] && $on_time['submission_on_time']) ? '<span class="green">'.t('ON TIME').'</span>' : '<span class="red">'.t('LATE').'</span>';
	    // $last_submission_block['nid'] = $nid;
	    $last_submissions_student_info = _druedu_homework_last_submission($node, $node->uid);
	    $last_submissions_teacher_info = _druedu_homework_last_submission($node, $node_ref->uid);
	    /* PREPARE VALUE LAST SUBMISSION*/
	    //$variables['last_submission_block'] = _druedu_homework_prepare_value_last_submission_block($last_submissions_info);
	    $last_submission_student_block = _druedu_homework_prepare_value_last_submission_block($last_submissions_student_info, $node->nid);
	    $last_submission_teacher_block = _druedu_homework_prepare_value_last_submission_block($last_submissions_teacher_info, $node->nid);
	    $last_submission_block = theme('last_submission_student_block', array('last_submission_block' => $last_submission_student_block));
	    $last_submission_block .= theme('last_submission_teacher_block', array('last_submission_block' => $last_submission_teacher_block));
  		$commands[] = ajax_command_html('#last_submission_block #flip .state', $last_submission_block);
  	}
	return array('#type' => 'ajax', '#commands' => $commands);
}
		
function druedu_homework_submission_form_submit($form, &$form_state) {
	global $user;
  	$user = user_load($user->uid);
	$nid = $form_state['input']['node_nid'];
	$node = node_load($nid);
	/* check if the homework is not blocked */
	if($node->uid == $user->uid && $node->field_locked[LANGUAGE_NONE][0]['value']) {
		drupal_set_message(t('This homework is currently locked, submission hasn\'t been saved'), 'warning');
	}
	else {
		/* Prepare data to timeline */
		$entities = explode(';', $form_state['input']['uploaded_file']);
		$nb_file = sizeof($entities) - 1;
		($nb_file > 1) ? $file_s = 'files' : $file_s = 'file';
	    $current_firstname = field_get_items('user', $user, 'field_firstname');
	    $firstname = field_view_value('user', $user, 'field_firstname', $current_firstname[0]);
	    $current_firstname = field_get_items('user', $user, 'field_lastname');
	    $lastname = field_view_value('user', $user, 'field_lastname', $current_firstname[0]);
		/* Save on node (field_collection) */
		$field_collection = entity_create('field_collection_item', array('field_name' => 'field_submission'));
		$field_collection->setHostEntity('node', $node);
		//$field_collection->field_submission_status[LANGUAGE_NONE][]['tid'] = (isset($form_state['values']['difficulty'])) ? $form_state['values']['difficulty'] : NULL;

		$field_collection->field_submission_date[LANGUAGE_NONE][]['value'] = time();
		$field_collection->field_submission_comment[LANGUAGE_NONE][]['value'] = $form_state['values']['submission_comment'];
		$field_collection->field_uid[LANGUAGE_NONE][]['value'] = $user->uid;
		/* Save on node (Heartbeat) */
		$message_id = 'heartbeat_homework_timeline_submission_form';
		$variables = array(
			'name' => $firstname['#markup'] . ' ' . $lastname['#markup'] . ' ' . t('submit'),
			'nb_file'=> $nb_file . ' ' . t($file_s) . ' ' . t('for this homework') . '.',
		    'message' => $form['submission_comment']['#value'],
		);
		/* Save field_collection */
		$heartbeat_data = heartbeat_api_log($message_id, $user->uid, 0, $nid, 0, $variables);
		$heartbeat = heartbeat_activity_load($heartbeat_data);
		/* Atach field to field collection and heartbeat */
		foreach ($entities as $key => $entity) {
			if(!empty($entity) && $entity != '') {
				$entity = json_decode($entity);
				$heartbeat->field_attachments[LANGUAGE_NONE][] = array(
					'filevault_id' => $entity->id,
					'filevault_vid' => 0,
				);
				$field_collection->field_attachments[LANGUAGE_NONE][] = array(
					'filevault_id' => $entity->id,
					'filevault_vid' => 0,
				);
			}
		}
		$field_collection->save();
		/* Save heartbeat extra fields*/
		field_attach_insert("heartbeat_activity", $heartbeat);
		if(user_access('administer assignment') &&
		 isset($form_state['values']['submission_marked']) &&
		  !is_null($form_state['values']['submission_marked']) &&
		   $form_state['values']['submission_marked'] != 0) {
				$homework_config = variable_get('druedu_homework_config');
				$node->field_assignment_status[LANGUAGE_NONE][0]['tid'] = $homework_config['status_marked_submission'];
				unset($node->field_assignment_status[LANGUAGE_NONE][0]['taxonomy_term']);
				$node->field_assignment_marked_date[LANGUAGE_NONE][0]['value'] = time();
				drupal_set_message(t('This homework has been marked'));
		}
		if(isset($form_state['values']['difficulty'])) {
			$node->field_assignment_difficulty[LANGUAGE_NONE][0]['tid'] = $form_state['values']['difficulty'];
			unset($node->field_assignment_difficulty[LANGUAGE_NONE][0]['taxonomy_term']);
		}
		node_save($node);
		drupal_set_message(t('Your files for this homework has been saved.'));
	}
}

function druedu_homework_submission_form_validate($form, &$form_state) {
	global $user;
	$nid = $form_state['input']['node_nid'];
	$node = node_load($nid);
	$node_ref = node_load($node->field_assignments_set_referenced[LANGUAGE_NONE][0]['target_id']);
	$due_date = $node_ref->field_assignment_due_date[LANGUAGE_NONE][0]['value'];
	if($user->uid == $node->uid && $due_date < time() && empty($form_state['values']['submission_comment'])) {
		form_set_error('submission_comment', t('Due date is past, please leave a message with your submission.'));
	}
	if($user->uid == $node->uid && is_null($form_state['values']['difficulty'])) {
		form_set_error('difficulty', t('Please select difficultiy of this submission.'));
	}
}

function druedu_homework_status_locked_assignment_form($form, &$form_state) {
	$args = arg();
	$nid = $args[1];
	$node = node_load($nid);
	$is_lock = t('Lock');
	$icon = '<i class="icon-lock"></i>';
	if($node->field_locked[LANGUAGE_NONE][0]['value']) {
		$is_lock = t('Unlock');
		$icon = '<i class="icon-unlock"></i>';
	}

	$form['status_locked_assignment_submit'] = array(
  		'#type' => 'submit',
  		'#value' => $icon . ' ' . $is_lock,
  		'#attributes' => array('class' => array('btn', 'btn-mini')),
  		'#ajax' => array(
		    'callback' => 'druedu_homework_status_locked_assignment_ajax_callback',
		    'wrapper' => 'body',
	    	'method' => 'append',
		    'effect' => 'fade',
		    'progress' => array('type' => 'throbber', 'message' => NULL),
		),
	);

	$form['node_nid'] = array(
	    '#type' => 'hidden',
	    '#value' => $nid,
	);
	return $form;
}

function druedu_homework_status_locked_assignment_ajax_callback($form, &$form_state) {
	$commands = array();
	$nid = $form_state['input']['node_nid'];
	$node = node_load($nid);
	$is_lock = t('Lock');
	$icon = '<i class="icon-lock"></i>';

	if($node->field_locked[LANGUAGE_NONE][0]['value']) {
		$is_lock = t('Unlock');
		$icon = '<i class="icon-unlock"></i>';
		$commands[] = ajax_command_invoke(null, 'show_homework_submission_form');
	}
	else{
		$commands[] = ajax_command_invoke(null, 'hide_homework_submission_form');
	}
	$commands[] = ajax_command_html('#edit-status-locked-assignment-submit', $icon . ' ' .$is_lock);
	$commands[] = ajax_command_remove('#wrapper_status_message_status_locked_assignment_form');
    $commands[] = ajax_command_before('#main-menu', '<div id="wrapper_status_message_status_locked_assignment_form">'.theme('status_messages').'</div>');
	return array('#type' => 'ajax', '#commands' => $commands);
}

function druedu_homework_status_locked_assignment_form_submit($form, &$form_state) {
	$nid = $form_state['input']['node_nid'];
	$node = node_load($nid);
	if($node->field_locked[LANGUAGE_NONE][0]['value']) {
		$node->field_locked[LANGUAGE_NONE][0]['value'] = 0;
		drupal_set_message($node->title .' '. t('has been unlocked.'));
		$message = t('This assignment has been unlocked');
	}
	else {
		$node->field_locked[LANGUAGE_NONE][0]['value'] = 1;
		drupal_set_message($node->title .' '. t('has been locked.'));
		$message = t('This assignment has been locked');
	}
	_druedu_homework_heartbeat_homework_assignment_activity($node, $message);
	node_save($node);
}

function druedu_homework_status_marked_assignment_form($form, &$form_state) {
	$args = arg();
	$nid = $args[1];
	$form['status_marked_assignment'] = array(
  		'#type' => 'submit',
  		'#value' => t('Marked this assignment'),
  		'#attributes' => array('class' => array('btn', 'btn-mini')),
  		'#ajax' => array(
		    'callback' => 'druedu_homework_status_marked_assignment_ajax_callback',
		    'wrapper' => 'body',
	    	'method' => 'append',
		    'effect' => 'fade',
		    'progress' => array('type' => 'throbber', 'message' => NULL),
		),
	);

	$form['node_nid'] = array(
	    '#type' => 'hidden',
	    '#value' => $nid,
	);
	return $form;
}

function druedu_homework_status_marked_assignment_ajax_callback($form, &$form_state) {
	$nid = $form_state['input']['node_nid'];
	$node = node_load($nid);
	$marked_date = date('d M Y @ g:h A', $node->field_assignment_marked_date[LANGUAGE_NONE][0]['value']);
	$marked_output = '<div class="marked">'.t('This assignment has been marked').' : ' . $marked_date .'</div>';
	$commands = array();   
	$commands[] = ajax_command_remove('#wrapper_status_message_status_marked_assignment_form');
    $commands[] = ajax_command_before('#main-menu', '<div id="wrapper_status_message_status_marked_assignment_form">'.theme('status_messages').'</div>');
	$commands[] = ajax_command_replace('#druedu-homework-status-marked-assignment-form', $marked_output);
	$commands[] = ajax_command_remove('.form-item-submission-marked');
	return array('#type' => 'ajax', '#commands' => $commands);
}

function druedu_homework_status_marked_assignment_form_submit($form, &$form_state) {
	$nid = $form_state['input']['node_nid'];
	$node = node_load($nid);
	$homework_config = variable_get('druedu_homework_config');
	$node->field_assignment_marked_date[LANGUAGE_NONE][0]['value'] = time();
	$node->field_assignment_status[LANGUAGE_NONE][0]['tid'] = $homework_config['status_marked_submission'];
	drupal_set_message($node->title .' '. t('has been marked.'));
	$message = t('This homework has been marked');
	_druedu_homework_heartbeat_homework_assignment_activity($node, $message);

	node_save($node);
}

/* @TODO AJAX */
/*
function status_marked_assignment_callback($form, $form_state) {

}
*/

function druedu_homework_update_last_submission_form($form, &$form_state, $nid) {
	$form['delete_files_last_submission'] = array(
  		'#type' => 'hidden',
  		'#value' => '',
	);
	$form['add_files_last_submission'] = array(
  		'#type' => 'hidden',
  		'#value' => '',
	);
	$form['last_submission'] = array(
  		'#type' => 'hidden',
  		'#value' => '',
	);
	$form['submit_last_submission'] = array(
  		'#type' => 'submit',
  		'#prefix' => '<div class="hide">',
  		'#suffix' => '</div>',
  		'#value' => '',
  		'#ajax' => array(
		    'callback' => 'druedu_homework_update_last_submission_ajax_callback',
		    'wrapper' => 'body',
		    'method' => 'append',
		    'effect' => 'fade',
		    'progress' => array('type' => 'throbber', 'message' => NULL),
		),
	);		
	$form['node_nid'] = array(
	    '#type' => 'hidden',
	    '#value' => $nid,
	);
	return $form;
}

function druedu_homework_update_last_submission_ajax_callback($form, &$form_state) {
	global $user;
	$commands = array();   
	$commands[] = ajax_command_remove('#wrapper_status_message_update_last_submission_form');
    $commands[] = ajax_command_after('article.node-assignment header', '<div id="wrapper_status_message_update_last_submission_form">'.theme('status_messages').'</div>');
    $nid = $form_state['input']['node_nid'];
	$node = node_load($nid);
	if($node->uid != $user->uid || !$node->field_locked[LANGUAGE_NONE][0]['value']) {
		$block_id = '#last_submission_teacher_block';
		if($node->uid == $user->uid) {
			$block_id = '#last_submission_student_block';
		}
		$commands[] = ajax_command_invoke(null, 'reset_update_last_submission_form');
		$commands[] = ajax_command_replace($block_id.' form', render($form));
		$commands[] = ajax_command_invoke(null, 'initialiseSubmissionId', array($block_id));
	}
	return array('#type' => 'ajax', '#commands' => $commands);
}

function druedu_homework_update_last_submission_form_submit($form, &$form_state) {
	global $user;
	$nid = $form_state['input']['node_nid'];
	$node = node_load($nid);
	if($node->uid == $user->uid && $node->field_locked[LANGUAGE_NONE][0]['value']) {
		drupal_set_message(t('This homework is currently locked, cannot update this submission'), 'warning');
	}
	else {
		$entity_id = $form_state['input']['last_submission'];
		$nb_delete = 0;
		$nb_add = 0;
		$current_firstname = field_get_items('user', $user, 'field_firstname');
	    $firstname = field_view_value('user', $user, 'field_firstname', $current_firstname[0]);
	    $current_firstname = field_get_items('user', $user, 'field_lastname');
	    $lastname = field_view_value('user', $user, 'field_lastname', $current_firstname[0]);
		if(!empty($entity_id) 
			&& (!empty($form_state['input']['delete_files_last_submission']) || !empty($form_state['input']['add_files_last_submission']))) {
			$field_collection_item = field_collection_item_load($entity_id);
			if(!empty($form_state['input']['delete_files_last_submission'])) {
				$file_to_delete = explode(';', $form_state['input']['delete_files_last_submission']);
				unset($file_to_delete[sizeof($file_to_delete)-1]);
				foreach($file_to_delete as $fileId) {
					foreach ($field_collection_item->field_attachments[LANGUAGE_NONE] as $key => $value) {
						if($value['filevault_id'] == $fileId) {
							unset($field_collection_item->field_attachments[LANGUAGE_NONE][$key]);
							$nb_delete += 1;
							break;
						}
					}
				}
			}
			
			$file_to_add = explode(';', $form_state['input']['add_files_last_submission']);
			if(!empty($file_to_add)) {
				unset($file_to_add[sizeof($file_to_add)-1]);
			}
			$nb_add = sizeof($file_to_add);
			/* Save on heartbeat */
			$message_id = 'heartbeat_homework_timeline_submission_form';
			$message = $nb_add . ' ' . t('files added') . ' ' . $nb_delete . ' ' . t('Deleted');
			$variables = array(
				'name' => t('Last submission updated') . ' : ',
				'nb_file'=> '',
			    'message' => $message,
			);
			$heartbeat_data = heartbeat_api_log($message_id, $user->uid, 0, $node->nid, 0, $variables);

			$heartbeat = heartbeat_activity_load($heartbeat_data);
			foreach ($file_to_add as $key => $entity) {
				if(!empty($entity) && $entity != '') {
					$entity = json_decode($entity);
					$heartbeat->field_attachments[LANGUAGE_NONE][] = array(
						'filevault_id' => $entity->id,
						'filevault_vid' => 0,
					);
					$field_collection_item->field_attachments[LANGUAGE_NONE][] = array(
						'filevault_id' => $entity->id,
						'filevault_vid' => 0,
					);
				}
			}
			$field_collection_item->save();
			/* Save heartbeat extra fields*/
			field_attach_insert("heartbeat_activity", $heartbeat);
			drupal_set_message($message);
		}
	}
}

function druedu_homework_status_close_assignment_set_form($form, &$form_state) {
	$args = arg();
	$nid = $args[1];
	$node = node_load($nid);
	if($node->field_assignment_set_status[LANGUAGE_NONE][0]['value'] == 0) {
		$status = t('Close');
		$icon = '<i class=" icon-lock"></i>';
	}
	else {
		$status = t('Open');
		$icon = '<i class=" icon-unlock"></i>';
	}

	$form['status_close_assignment_set_submit'] = array(
  		'#type' => 'submit',
  		'#value' => $status,
  		'#attributes' => array('class' => array('btn', 'btn-mini')),
  		'#ajax' => array(
		    'callback' => 'druedu_homework_status_close_assignment_set_ajax_callback',
		    'wrapper' => '#druedu-homework-status-close-assignment-set-form',
		    'method' => 'append',
		    'effect' => 'fade',
		    'progress' => array('type' => 'throbber', 'message' => NULL),
		),
	);

	$form['node_nid'] = array(
	    '#type' => 'hidden',
	    '#value' => $nid,
	);

	return $form;
}

function druedu_homework_status_close_assignment_set_ajax_callback($form, &$form_state) {
	$nid = $form_state['input']['node_nid'];
	$node = node_load($nid);
	if($node->field_assignment_set_status[LANGUAGE_NONE][0]['value'] == 0) {
		$status = t('Close');
		$icon = '<i class=" icon-lock"></i>';
	}
	else {
		$status = t('Open');
		$icon = '<i class=" icon-unlock"></i>';
	}
	$commands = array();   
	$commands[] = ajax_command_html('#edit-status-close-assignment-set-submit', $icon . ' ' . $status);
	$commands[] = ajax_command_remove('#wrapper_status_message_status_close_assignment_set_form');
    $commands[] = ajax_command_before('#main-menu', '<div id="wrapper_status_message_status_close_assignment_set_form">'.theme('status_messages').'</div>');
	return array('#type' => 'ajax', '#commands' => $commands);
}

function druedu_homework_status_close_assignment_set_form_submit($form, &$form_state) {
	$nid = $form_state['input']['node_nid'];
	$node = node_load($nid);
	if($node->field_assignment_set_status[LANGUAGE_NONE][0]['value'] == 0) {
		$new_status = 1;
		$message = t('This assignment has been locked');
		drupal_set_message('All assignments has been locked.');
	}
	else{
		$new_status = 0;
		$message = t('This assignment has been unlocked');
		drupal_set_message('All assignments has been unlocked.');
	}
	foreach ($node->field_assignments_referencing[LANGUAGE_NONE] as $node_ref) {
		$node_ref = node_load($node_ref['target_id']);
		$node_ref->field_locked[LANGUAGE_NONE][0]['value'] = $new_status;
		_druedu_homework_heartbeat_homework_assignment_activity($node_ref, $message);
		node_save($node_ref);
	}
	$node->field_assignment_set_status[LANGUAGE_NONE][0]['value'] = $new_status;
	node_save($node);
}

function druedu_homework_filter_assignment_set_form($form, &$form_state) {
	$param = drupal_get_query_parameters();
	 if(!empty($param)) {
      $name_search = $param['name'];
      $status_search = $param['status'];
      $difficulty_search = $param['difficulty'];
    }
    else {
      $name_search = t('Search by name...');
      $status_search = '_none';
      $difficulty_search = '_none';
    }
	$form['name'] = array(
	  	'#type' => 'textfield',
	  	'#default_value' => $name_search,
	  	'#size' => 30,
	);

	$option_difficulty = array('_none' => '- ' .t('Select'). ' -');
	foreach (_druedu_homework_get_term_by_vocabulary('difficulties_homework') as $key => $value) {
		$option_difficulty[$key] = $value;
	}
	$form['difficulty'] = array(
	  	'#type' => 'select',
	  	'#options' => $option_difficulty,
	  	'#default_value' => $difficulty_search,
	);

	$option_status = array('_none' => '- ' .t('Select'). ' -');
	foreach (_druedu_homework_get_term_by_vocabulary('status_assignment') as $key => $value) {
		$option_status[$key] = $value;
	}
	$form['status'] = array(
	  	'#type' => 'select',
	  	'#options' => $option_status,
	  	'#default_value' => $status_search,
	);

	$form['submit'] = array(
  		'#type' => 'submit',
  		'#value' => t('Search'),
	);
	return $form;
}

function druedu_homework_filter_assignment_set_form_submit($form, &$form_state) {
	$args = arg();
	$node = node_load($args[1]);
	$param = drupal_get_query_parameters();
    $page = (isset($param['page'])) ? $param['page'] : 0;
    $name = (isset($form_state['input']['name']) && $form_state['input']['name'] != t('Search by name...')) ? $form_state['input']['name'] : '';
    $difficulty = (isset($form_state['input']['difficulty']) && $form_state['input']['difficulty'] != '_none') ? $form_state['input']['difficulty'] : '';
    $status = (isset($form_state['input']['status']) && $form_state['input']['status'] != '_none') ? $form_state['input']['status'] : '';
	$options = array('query' => array('page' => $page, 'name' => $name, 'difficulty' => $difficulty, 'status'=> $status));
	drupal_goto('node/'.$node->nid, $options);
}
