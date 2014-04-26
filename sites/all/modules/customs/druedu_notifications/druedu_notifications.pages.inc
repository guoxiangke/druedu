<?php

/**
 * Menu callback for unsubscribe page
 *
 * @param $type
 *   Either 'sid' or 'uid' (for unsubscribe all)
 * @param $id
 *   Subscription id or user id, depending on type
 */
function _druedu_notifications_page_unsubscribe_subscription_4ajax($node,$sid,$view_mode='full') {
	$subscription = notifications_subscription_load($sid);
  // If everything is ok and signed to skip confirmation, go ahead
  if ($subscription->sid) {//1||notifications_check_signature('skip')
    $subscription->delete();
    // $node = node_load($node->nid);

   	$node_view = node_view($node,$view_mode);
   	// hide "Add new comment"
   	unset($node_view['links']['comment']);
   	$replace_node_links = render($node_view['links']);
    $commands[] = ajax_command_replace('#notifications-links-'.$node->nid, $replace_node_links);
    
    return array('#type' => 'ajax', '#commands' => $commands);

    // drupal_set_message(t('Your subscription has been removed.'));
    // drupal_goto();
  }
  else {
    // Ask for confirmation
    // $node_view = node_view($node,$view_mode);
   	// // hide "Add new comment"
   	// unset($node_view['links']['comment']);
   	// $replace_node_links = render($node_view['links']);
    $commands[] = ajax_command_after('#notifications-links-'.$node->nid, '<div class="messages warning">This link is out of date, Please refresh the page.</div>');
  	return array('#type' => 'ajax', '#commands' => $commands);
  }

  //drupal_access_denied();
}

/**
 * Menu callback add subscription
 *
 * Presents confirmation page or not depending on confirm parameter
 * @see notifications_page_subscribe
 * rm the notifications_check_signature()
 */
function _druedu_notifications_page_subscribe_4ajax($node,$substype,$view_mode='full') {
  $account = $GLOBALS['user'];
  // Build subscriptions object
  if ($substype->user_access($account, 'subscribe')) {
    $subscription = $substype
      ->instance()
      ->set_user($account)
      ->set_properties_from_url();
    // If everything is ok and signed to skip confirmation, go ahead // && notifications_check_signature('skip')

    if ($subscription->check_destination() && $subscription->check_fields()) {
     	$subscription->save();
	    $node_view = node_view($node,$view_mode);
   		unset($node_view['links']['comment']);
	   	$replace_node_links = render($node_view['links']);
	    $commands[] = ajax_command_replace('#notifications-links-'.$node->nid, $replace_node_links);
      	return array('#type' => 'ajax', '#commands' => $commands);
      // drupal_set_message(t('Your subscription was activated.'));
      // drupal_goto();
    }
    else {
      // Ask for confirmation
      drupal_set_title(t('Confirm your subscription'));
      return drupal_get_form('notifications_subscription_subscribe_form', $subscription);
    }
  }
  drupal_set_message(t('Subscription or parameters not allowed.'), 'error');
  drupal_goto();
  return "HOW WE REACHED HERE?";
}