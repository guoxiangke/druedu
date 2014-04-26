<?php
function druedu_notification_share_form($form, &$form_state, $node) {
	global $user;
	$form_state['node'] = $node;

	$default = notification_default_grades_select($node, FALSE, TRUE, 'view', FALSE);
	$default_grades = $default['default_grades'];
	$form_state['all_grades'] = $default_grades;

	if(isset($form_state['values'])) {
		$current_user_groups_formated = array();
		if(is_numeric($form_state['values']['grades'])) {
			$current_user_groups_formated[] = $form_state['values']['grades'];
			$default_users = druedu_user_get_users_by_groups($current_user_groups_formated);
			foreach ($default_users as $key => $default_user) {
				$default_user = user_load($key);
				if(!node_access('view', $node, $default_user)) {
					unset($default_users[$key]);
				}
			}
			if(isset($default_users[$user->uid])) {
				unset($default_users[$user->uid]);
			}
		}
		else {
			$default_users = $default['default_users'];
		}
	}
	else{
		$default_users = $default['default_users'];
	}

	$form['#validate'] = array('druedu_notification_share_form_validate');
	$form['filters'] = array(
		'#type' => 'fieldset',
		'#title' => t('Filters'),
		'#collapsible' => TRUE,
		'#collapsed' => TRUE,
		'#weight' => 0,
	);
	$form['filters']['grades'] = array(
		'#type' => 'select',
		'#title' => t('Grades'),
		'#options' => $default_grades,
		'#ajax' => array(
			'callback' => 'share_form_filters_callback',
			'event' =>'change',
			'wrapper' => 'wrapper_potential_user',
			'effect' => 'fade',
		    'progress' => array('type' => 'throbber', 'message' => NULL),
		),
		'#weight' => 1,
	);

	$form['filters']['username'] = array(
		'#type' => 'textfield',
		'#title' => t('Username'),
		'#value' => '',
		'#weight' => 2,
	);

	if(sizeof($default_users) > 0) {
		$form['potential_users'] = array(
			'#type' => 'checkboxes',
			'#options' => $default_users, 
			'#prefix' => '<div id="wrapper_potential_user">',
			'#suffix' => '</div>',
			'#required' => TRUE,
			'#weight' => 1,
		);
	}
	else {
		$form['potential_users'] = array(
			'#markup' => '<div id="wrapper_potential_user">'.t('No users available.').'</div>',
			'#weight' => 1,
		);	
	}

	$form['selected_fieldset'] = array(
		'#type' => 'fieldset',
		'#title' => t('Users selected'),
		'#collapsible' => TRUE,
		'#collapsed' => FALSE,
		'#weight' => 2,
	);
	$form['selected_fieldset']['selected_container'] = array(
		'#markup' => '<div id="share_user_selected_container">
						<div class="no_selected_wrapper">'.t('No users selected').'<div>
					</div>',
		'#weight' => 2,
	);
	if(!isset($form_state['values'])) {
		$default_users_json = json_encode($default_users);
		$form['selected_fieldset']['users_potential_selected'] = array(
			'#type' => 'hidden',
			'#default_value' => $default_users_json, 
			'#weight' => 2,
		);
		$form['selected_fieldset']['users_selected'] = array(
			'#type' => 'hidden',
			'#default_value' => '', 
			'#weight' => 2,
		);
	}

	$form['actions']['confirm'] = array(
		'#type' => 'checkbox',
		'#title' => t('Confirmation'),
		'#default_value' => FALSE,
		'#prefix' => '<div id="wrapper_action_validate">',
		'#suffix' => '</div><div class="email_submit"></div>',
		'#weight' => 3,
	);

	$form['actions']['submit'] = array(
		'#type' => 'submit',
		'#value' => t('Send email(s)'),
		'#attributes' => array(
			'class' => array('btn-primary'),
		),
		'#disabled' => FALSE,
		'#prefix' => '<div id="wrapper_action_submit">',
		'#suffix' => '</div>',
		'#ajax' => array(
			'callback' => 'share_form_submit_callback',
			'event' =>'click',
			'effect' => 'fade',
		    'progress' => array('type' => 'throbber', 'message' => NULL),
		),
		'#weight' => 3,
	);

	return $form;
}

function druedu_notification_share_form_validate($form, &$form_state){
	form_clear_error();
	if (!$form_state['values']['confirm']) {
    	form_set_error('confirm', t('Validation is required.'));
  	}
}

function druedu_notification_share_form_submit($form, &$form_state) {
	$form_error = form_get_errors();
	if(empty($form_error)) {
		global $base_url;
		$node = $form_state['node'];
		$users_selected = $form_state['input']['users_selected'];
		$users_selected = explode(';', $users_selected);
		//values is arguments to sent to message type.
		$message_arguments = array(
			'arguments' => array(
				'!content_type' => $node->type,
				'!url' => $base_url.'/'.drupal_get_path_alias('node/'.$node->nid),
			),
			'timestamp' => NULL,
		);
		foreach ($users_selected as $user_id) {
			if(!empty($user_id)) {
				$account = user_load($user_id);
				$message = message_create('share_subscription_node', $message_arguments, $account);
				message_notify_send_message($message);
			}
		}
	}
	return;
}

function share_form_submit_callback($form, &$form_state) {
	$form_error = form_get_errors();
	$commands = array();   
	if(empty($form_error)) {
		$users_selected = $form_state['input']['users_selected'];
		$users_selected = explode(';', $users_selected);
		$has_user_selected = FALSE;
		foreach ($users_selected as $user_id) {
			if(!empty($user_id)) {
				$has_user_selected = TRUE;
				break;
			}
		}
		if(!$has_user_selected) {
			$commands[] = ajax_command_replace('.email_submit', '<div class="email_submit">'.t('Please select minimum one user.').'</div>');
		}	
		else{
			$commands[] = ajax_command_replace('.email_submit', '<div class="email_submit">'.t('Emails sent').'</div>');
		}
	}
	else{
		$commands[] = ajax_command_replace('.email_submit', '<div class="email_submit">'.theme('status_messages').'</div>');
	}
	return array('#type' => 'ajax', '#commands' => $commands);	
}

function share_form_filters_callback($form, &$form_state){	
	$commands = array();   
	$commands[] = ajax_command_replace('#wrapper_action_submit', drupal_render($form['actions']['submit']));
	$commands[] = ajax_command_replace('#wrapper_potential_user', drupal_render($form['potential_users']));
	$commands[] = ajax_command_invoke(NULL, 'druedu_notification_default_checkboxes');
	return array('#type' => 'ajax', '#commands' => $commands);
}