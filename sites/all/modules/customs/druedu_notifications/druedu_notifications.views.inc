<?php
/**
 * Implements hook_views_data().
 */
function druedu_notifications_views_data() {
  $data['views']['share_node'] = array(
    'title' => t('Share a node'),
    'help' => t('Provide a link to share a node.'),
    'field' => array(
      'handler' => 'views_handler_field_share_node',
    ),
  );
  return $data;
}