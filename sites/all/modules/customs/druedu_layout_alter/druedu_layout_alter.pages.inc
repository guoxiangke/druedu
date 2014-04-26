<?php
/*
/* Page Callback - Druedu Login Page
*/
function druedu_layout_alter_login() {
  return drupal_get_form('user_login');
}

/**
 * Page Callback - Modal: delete Node
 */
function druedu_layout_alter_modal_node_delete($node, $ajax) {
  global $base_url;
  //$ajax can be 'ajax' or 'nojs'
  $is_ajax = $ajax === 'ajax';
  $nid = $node->nid;
  if ($is_ajax) {
    //$node = node_load($nid);
    //get validation node form
    $form_state = array();
    $form_state['build_info']['args'] = array($node);
    //need load file node.page from node module
    form_load_include($form_state, 'inc', 'node', 'node.pages');
    $form = drupal_build_form('node_delete_confirm', $form_state);
    //override action form because default one is wrong (ajax url) 
    $form['#action'] = $base_url.'/node/'.$nid.'/delete';
    /* AJAX RENDER */
    $commands = array();   
    //return form into a modal
    $commands[] = ajax_command_append('body', theme('modal_validation', array('params' => $form)));
    //execute modal opening  
    $commands[] = ajax_command_invoke(NULL, 'prepareModal');
    return array(
      '#type' => 'ajax',
      '#commands' => $commands,
    );
  }
  else {
    drupal_goto('node/'.$nid.'/delete', array(), 301);
  }
}