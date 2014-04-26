<?php

/**
 * @file
 * Definition of views_handler_field_custom.
 */

/**
 * A handler to provide a field that is completely custom by the administrator.
 *
 * @ingroup views_field_handlers
 */
class views_handler_field_share_node extends views_handler_field {
  function query() {
    // do nothing -- to override the parent query.
  }

  function option_definition() {
    $options = parent::option_definition();
    $options['node_id'] = array('default' => '[nid]');
    return $options;
  }

  function options_form(&$form, &$form_state) {
    parent::options_form($form, $form_state);

    $form['node_id'] = array(
      '#type' => 'textfield',
      '#title' => t('NodeID'),
      '#default_value' => $this->options['node_id'],
      '#description' => t('Enter a node ID only. Must be an integer is authorized. You may enter data from this view as per the "Replacement patterns" below.'),
    );

    unset($form['empty_field_behavior']);
    foreach ($form as $key => $value) {
      if(isset($form[$key]['#fieldset']) && $form[$key]['#fieldset'] == 'empty_field_behavior') {
        unset($form[$key]);
      }
    }
    // Remove the checkbox
    unset($form['alter']);
  }

  function render($values) {
    if (!empty($values) && !empty($this->options['node_id'])) {
      global $base_url, $user;
      $tokens = $this->get_render_tokens($values);
      // Replace any tokens in the path.
      $nid = strtr($this->options['node_id'], $tokens);
      if(!is_numeric($nid)) {
        return '';
      }
      $node = node_load($nid);
      if(is_object($node) && user_access('Authorized to share a node')) {
        $text = '<i class="icon-share"></i> '.t('Share this @node_type', array('@node_type' => $node->type)); 
        $path = $base_url.'/node/'.$nid.'/share/'.$user->uid.'/nojs';
        // Check that the user has access to the menu router item, but only if the
        // path is for a valid menu router item, so that external URLs or paths not
        // handled by Drupal's menu router are always permitted.
        $router_item = menu_get_item($path);
        if ($router_item && !$router_item['access']) {
          return '';
        }
        $options = array('html' => TRUE, 'attributes' => array('class' => array('btn', 'btn-mini', 'use-ajax')));
        return l($text ,$path, $options);
      }
      return '';
    }
    return '';
  }
}
