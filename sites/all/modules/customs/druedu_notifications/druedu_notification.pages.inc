<?php
function druedu_notification_get_share_form_callback($node, $user, $ajax) {
	global $base_url;
	$is_ajax = $ajax === 'ajax';
	$nid = $node->nid;
  	if ($is_ajax) {
  		module_load_include('inc', 'druedu_notifications', 'druedu_notification.form');
		$form = drupal_get_form('druedu_notification_share_form', $node);
		//override action form because default one is wrong (ajax url) 
    	$form['#action'] = $base_url.'/node/'.$nid;
    	$options['label'] = t('Share this').' '.str_replace('_', ' ', $node->type);
    	$options['class'] = 'large';
		$commands = array();
		$commands[] = ajax_command_append('body', theme('modal_validation', array('params' => $form, 'options' => $options)));
	    //execute modal opening  
	     $commands[] = ajax_command_invoke(NULL, 'prepareModal');
		return array('#type' => 'ajax', '#commands' => $commands);
	}
}