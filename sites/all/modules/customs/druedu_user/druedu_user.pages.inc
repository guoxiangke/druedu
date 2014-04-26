<?php 
function druedu_user_preferences_form($form, &$form_states) {
	$args = arg();
	$uid = $args[1];
	$user_preferences = druedu_get_user_preferences($uid);
	$form_states['op'] = 'insert';
	if(!empty($user_preferences)) {
		$form_states['op'] = 'update';
		$user_preferences = json_decode($user_preferences['preferences']);
	}
	$form_states['uid'] = $uid;
	$form['sidebar'] = array(
		'#type' => 'fieldset',
		'#title' => '<i class="icon-resize-horizontal"></i>'.t('Smart layout'), 
		'#weight' => 0,
		'#collapsed' => TRUE,
		'#collapsible' => TRUE,
		'#attributes' => array('class' => array('clearfix')),
	);
	$form['sidebar']['sidebar_left'] = array(
		'#type' => 'radios', 
		'#title' => t('Sidebar left'), 
		'#default_value' => (isset($user_preferences->sidebar_left)) ? $user_preferences->sidebar_left : 0, 
		'#options' => array(t('Hidden'), t('Show')),
		'#attributes' => array('class' => array('clearfix')),
		'#weight' => 0,
	);
	$form['sidebar']['sidebar_right'] = array(
		'#type' => 'radios', 
		'#title' => t('Sidebar right'), 
		'#default_value' => (isset($user_preferences->sidebar_right)) ? $user_preferences->sidebar_right : 0, 
		'#options' => array(t('Hidden'), t('Show')),
		'#attributes' => array('class' => array('clearfix')),
		'#weight' => 1,
	);
	$form['submit'] = array(
		'#type' => 'submit', 
		'#value' => t('Save preferences'), 
	);
	return $form;
}

function druedu_user_preferences_form_submit($form, &$form_states) {
	$preferences = array(
		'sidebar_left' => $form_states['values']['sidebar_left'],
		'sidebar_right' => $form_states['values']['sidebar_right'],
	);
	$form_states['preferences'] = $preferences;
	$preferences = json_encode($preferences);
	$saved = druedu_set_user_preferences($form_states['uid'], $preferences, $form_states['op']);
	if($saved) {
		drupal_set_message(t('Preferences has been saved'));
	}
	else {
		drupal_set_message(t('Preferences has been not saved'), 'warning');
	}
}

