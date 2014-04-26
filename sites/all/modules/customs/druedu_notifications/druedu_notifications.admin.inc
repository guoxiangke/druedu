<?php
function druedu_notification_config_form($form, &$form_state) {
	$druedu_notifications_config = variable_get('druedu_notifications_config');
	//Content type
	$node_types = node_type_get_types();
	foreach ($node_types as $key => $node_type) {
		$options_share[$node_type->type] = $node_type->name; 
	}
	$form['fieldset_share'] = array(
		'#type' => 'fieldset',
		'#title' => t('Share a node'),	
		'#collapsed' => FALSE,
		'#collapsible' => TRUE,
	);
	$form['fieldset_share']['content_types'] = array(
		'#type' => 'checkboxes',
		'#options' => $options_share,
		'#default_value' => (isset($druedu_notifications_config['share_a_node']))? $druedu_notifications_config['share_a_node'] : NULL,
	);

	$form['submit'] = array(
		'#type' => 'submit',
		'#value' => t('Submit'),
	);

	return $form;
}

function druedu_notification_config_form_submit($form, &$form_state) {
	$config['share_a_node'] = $form_state['values']['content_types'];
	variable_set('druedu_notifications_config', $config);
}