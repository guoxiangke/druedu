<?php
/**
 * @file
 * Include file of druedu homework module.
 *
 * This file contain functions to create custom page on druedu homework.
 * Dashboard and ajax callback are here.
 */

/**
 * Implementation of druedu_homework_dashboard().
 * 
 * This is the main function to the homework dashboard.
 * According to permission of the current user, views display will be called.  
 */
function druedu_homework_dashboard() {
  $variables = '';
  //module_load_include('inc', 'druedu_homework', 'includes/druedu_homework.views');
  $views = views_get_view('homework_dashboard'); 
  // Dashboard admin : see all homework
  if(user_access('access admin dashboard') || user_access('access teacher dashboard')) {
    $block = module_invoke('druedu_homework', 'block_view', 'homework_add_assignment_set');
    $variables .= render($block['content']);
  }
  if(user_access('access admin dashboard')) {
    $title_display_1 = $views->display['all_homework_admin_dashboard']->display_title;
    $variables .= '<h2 class="block-title">'.$title_display_1.'</h2>';
    $variables .= views_embed_view('homework_dashboard', 'all_homework_admin_dashboard'); 
  }
  //Dashboard student
  elseif(user_access('access student dashboard')) {
    $title_display_1 = $views->display['current_homework_dashboard']->display_title;
    $variables .= '<h2 class="block-title">'.$title_display_1.'</h2>';
    $variables .= views_embed_view('homework_dashboard', 'current_homework_dashboard'); 

    $title_display_2 = $views->display['completed_homework']->display_title;
    $variables .= '<h2 class="block-title">'.$title_display_2.'</h2>';
    $variables .= views_embed_view('homework_dashboard', 'completed_homework'); 
  }
  //Dashboard teacher
  elseif(user_access('access teacher dashboard')) {
    
  }

  return $variables;
}

/*
* implementation helper function to last activity (using heartbeat module)
* @param int $nid
*    int : node id we want to get last activity
* @param int $uid
*    int : user id we want to get last activity on the node
* @param array $message_id
*    array of string : machine name of the heartbeat template
* @RETURN object entity heartbeat
*/
function _druedu_homework_get_last_activity($nid, $uid = NULL, $message_id = array()) {
  $heartbeat_activity = db_select('heartbeat_activity', 'heartbeat_activity');
  $heartbeat_activity->fields('heartbeat_activity', array('uaid'));
  $heartbeat_activity->condition('nid', $nid);
  if(!is_null($uid)) {
    $heartbeat_activity->condition('uid', $uid);
  }
  if(!empty($message_id)) {
    $heartbeat_activity->condition('message_id', $message_id, 'IN');
  }
  $heartbeat_activity->range(0, 1);
  $heartbeat_activity->orderBy('timestamp', 'DESC');
  $result = $heartbeat_activity->execute();
  $heartbeat_activity = array();
  while($record = $result->fetchAssoc()) {
    $heartbeat_activity = $record['uaid'];
  }
  $heartbeat_activities = heartbeat_activity_load($heartbeat_activity);
  return $heartbeat_activities;
}

/*
* implementation og the hook_menu ajax callback to get last submission.
* Render a modal with informations of the last submission
* @param string $ajax
*    string : value can be ajax or nojs
* @param int $nid
*    int : node id we want to get last submission on the node
* @param array $message_id
*    array of string : machine name of the heartbeat template
* @return array of command ajax if @param $ajax = 'ajax' else redirect to the node
*/
function druedu_homework_last_submission($ajax, $node) {
  $is_ajax = $ajax === 'ajax';
  if(is_object($node)) {
    $nid =  $node->nid;
  }
  else {
    $node = node_load($node);
    $nid = $node;
  }

  if ($is_ajax) {
    global $user;
    //$last_comment = _druedu_homework_get_last_activity($nid, $user->uid, 'heartbeat_homework_timeline_comment_form');
    /* PREPARE VALUE HEADER */
    $student = user_load($node->uid);
    $firstname = $student->field_firstname[LANGUAGE_NONE][0]['value'];
    $lastname = $student->field_lastname[LANGUAGE_NONE][0]['value'];
    /* OUTPUT HEADER */
    $output_header = t('Submission of'). ' ' . $firstname . ' ' . $lastname;
    /* PREPARE VALUE BODY */
    $last_submissions_info = _druedu_homework_last_submission($node);
    $nb_file = (!empty($last_submissions_info['last_submission']->field_attachments)) ? sizeof($last_submissions_info['last_submission']->field_attachments[LANGUAGE_NONE]) : 0 ;
    $on_time_values = _druedu_homework_submission_on_time($node);
    if($on_time_values['has_submission']) {
      $on_time = ($on_time_values['submission_on_time']) ? '<span class="green">'.t('ON TIME').'</span>' : '<span class="red">'.t('LATE').'</span>';
      $on_time_value = date('D j M Y', $on_time_values['submission_on_time_value']);
    }

    /* OUTPUT BODY */
    $output_body .= '<div class="submit-info" submission="'. $field_collection_entity_id.'">';
    $output_body .= $firstname . ' ' . $lastname . ' '; 
    $output_body .= t('submitted') . ' ' . $nb_file . ' ' . t('files for this homework') . ' ';
    if (isset($on_time)) {
        $output_body .= $on_time; 
        //$output_body .=  '( '. $on_time_value . ' )';
    }
    $difficulty = (!empty($node->field_assignment_difficulty)) ? taxonomy_term_load($node->field_assignment_difficulty[LANGUAGE_NONE][0]['tid'])->name : t('none') ;
    $difficulty = '<span class="difficulty '.strtolower(str_replace(' ', '_', $difficulty)).'">'. $difficulty . '</span>';
    $output_body .= '<br><span class="level">'. t('This assignment is') . ' ' . $difficulty .'</span>';

    $output_body .= '</div>';
    $message_id = array('heartbeat_homework_timeline_submission_form', 'heartbeat_homework_timeline_comment_form', 'heartbeat_first_homework_assignment_activity');
    $activity = _druedu_homework_get_last_activity($node->nid, NULL, $message_id);
    $output_body .= (!is_null($activity)) ? '<div class="comment img-polaroid img-rounded"><h4>'.t('Last Info').'</h4>'.$activity->message.'</div>' : '';
    $output_body .= '<span class="more">'.l(t('View more'), 'node/'.$node->nid, array('attributes' => array('class' => array('label', 'label-important')))).'</span>';
    /* PREPARE VALUE FOOTER */
    foreach ($last_submissions_info['last_submission']->field_attachments[LANGUAGE_NONE] as $key => $filevault) {
      $filevault = filevault_load($filevault['filevault_id']);
      $field_submission_filevault[$key]['fid'] = $filevault->id;
      $field_submission_filevault[$key]['link'] = l($filevault->filename, file_create_url($filevault->uri), array('attributes' => array('class' => array('btn', 'btn-link'))));
    }
    /* OUTPUT FOOTER */
    foreach($field_submission_filevault as $file) {
      $output_footer .= '<div class="item" filevault="'. $file['fid'] .'">';      
      $output_footer .= '<i class="icon-paper-clip icon-small"></i>'. $file['link'] .'<i class="icon-remove-sign delete-item hide icon-small"></i>';
      $output_footer .= '</div>';
    }

    /* AJAX RENDER */
    $commands = array();   
    $commands[] = ajax_command_append('body', 
      '<div class="modal fade" id="submission-modal" role="dialog" aria-labelledby="submissionLabel" aria-hidden="false">'
            .   '<div class="modal-header">'
                  . '<button type="button" class="close" data-dismiss="modal" aria-hidden="true">×</button>'
                  .   '<h3 id="submissionLabel">' . $output_header . '</h3>'
            . '</div>'// modal-header 
            . '<div class="modal-body">' . $output_body . '</div>'//<!-- modal-body -->
            . '<div class="modal-footer">' . $output_footer . '</div>'//<!-- modal-body -->
          . '</div>');  
    $commands[] = ajax_command_invoke(NULL, 'prepareModal');
    return array(
      '#type' => 'ajax',
      '#commands' => $commands,
    );
  }
  else {
    drupal_goto('node/'.$nid, array(), 301);
  }
}

/*
* implementation of a helper function to get last submission of a node
* @param object $node
*    object : al infromation about a node (use node_load($nid))
*
* @return array associative $last_submision
*   key last_submission => object entity field collection
*   key has_submission => TRUE if have submission else FALSE
*  
*/
function _druedu_homework_last_submission($node, $uid = NULL) {
  /* SEARCH SUBMISSION TO DISPLAY BY DEFAULT */
  $has_submission = FALSE;
  $last_submission_info = NULL;
  if(!empty($node->field_submission)) {
    $config_last = FALSE;
    $field_collection_entity_id = NULL;
    $node->field_submission[LANGUAGE_NONE] = array_reverse($node->field_submission[LANGUAGE_NONE]);
    if(!is_null($uid) && !empty($uid) && is_numeric($uid)) {
      foreach ($node->field_submission[LANGUAGE_NONE] as $key => $value) {
        $field_collection_entity_id = $value['value'];
        $last_submission_info = field_collection_item_load($field_collection_entity_id);
        if($uid == $last_submission_info->field_uid[LANGUAGE_NONE][0]['value']){
          $config_last = TRUE;
          $has_submission = TRUE;
          break;
        }
      }
    }
    else {
      $has_submission = TRUE;
      $homework_config = variable_get('druedu_homework_config');
      $status_marked_submission = $homework_config['status_marked_submission'];
      $status_assignment = $node->field_assignment_status[LANGUAGE_NONE][0]['tid'];
      if($status_assignment == $status_marked_submission){
        foreach ($node->field_submission[LANGUAGE_NONE] as $key => $value) {
          $field_collection_entity_id = $value['value'];
          $last_submission_info = field_collection_item_load($field_collection_entity_id);
          $uid = $last_submission_info->field_uid[LANGUAGE_NONE][0]['value'];
          if($uid == node_load($node->field_assignments_set_referenced[LANGUAGE_NONE][0]['target_id'])->uid) {
            $config_last = TRUE;
            break;
          }
        }
      }
    }
    if(!$config_last) {
      $node->field_submission[LANGUAGE_NONE] = array_reverse($node->field_submission[LANGUAGE_NONE]);
      $key = sizeof($node->field_submission[LANGUAGE_NONE]) - 1;
      $field_collection_entity_id = $node->field_submission[LANGUAGE_NONE][$key]['value'];
      $last_submission_info = field_collection_item_load($field_collection_entity_id);
    }
  }
  return $last_submission = array(
    'last_submission' => $last_submission_info,
    'has_submission' => $has_submission,
  ); 
}

function _druedu_homework_submission_on_time($assignment, $date_ref = NULL) {
  $submission_on_time = NULL;
  $submission_on_time_value = NULL;
  $has_submission = FALSE;
  if(!empty($assignment->field_submission)) {
    $has_submission = TRUE;
    foreach ($assignment->field_submission[LANGUAGE_NONE] as $key => $value) {
      $submission = field_collection_item_load($value['value']);
      if($submission->field_uid[LANGUAGE_NONE][0]['value'] == $assignment->uid && !empty($submission->field_submission_date)) {
        $submission_on_time_value = $submission->field_submission_date[LANGUAGE_NONE][0]['value'];
        break;
      }
    }
    if(is_null($date_ref)) {
      $date_ref = time();
    }
    $submission_on_time = (isset($submission_on_time_value) && $submission_on_time_value < $date_ref) ? TRUE : FALSE;
  }
  else {
    $has_submission = FALSE;
  }
  return $last_submission = array(
    'submission_on_time' => $submission_on_time,
    'submission_on_time_value' => $submission_on_time_value,
    'has_submission' => $has_submission,
  ); 
}

function _druedu_homework_prepare_value_last_submission_block($last_submissions_info, $nid) {
  global $user;
  $last_submission_block = array();
  if($last_submissions_info['has_submission']) {
    $last_submission_user = user_load($last_submissions_info['last_submission']->field_uid[LANGUAGE_NONE][0]['value']);
    $last_submissions_firstname = field_get_items('user', $last_submission_user, 'field_firstname'); 
    $last_submissions_lastname = field_get_items('user', $last_submission_user, 'field_lastname'); 
    $last_submission_block['last_submissions']['firstname'] = field_view_value('user', $last_submission_user, 'field_firstname', $last_submissions_firstname[0]);
    $last_submission_block['last_submissions']['lastname'] = field_view_value('user', $last_submission_user, 'field_lastname', $last_submissions_lastname[0]);
    $last_submission_block['field_collection_entity_id'] = $last_submissions_info['last_submission']->item_id;
    $last_submission_block['last_submissions']['nb_file'] = (!empty($last_submissions_info['last_submission']->field_attachments)) ? sizeof($last_submissions_info['last_submission']->field_attachments[LANGUAGE_NONE]) : 0 ;
    $last_submission_block['last_submissions']['field_submission_comment'] = (!empty($last_submissions_info['last_submission']->field_submission_comment)) ? $last_submissions_info['last_submission']->field_submission_comment[LANGUAGE_NONE][0]['safe_value'] : NULL ;
    $last_submission_block['last_submissions']['field_submission_date'] = (!empty($last_submissions_info['last_submission']->field_submission_date)) ? date('d M Y @ g:h A', $last_submissions_info['last_submission']->field_submission_date[LANGUAGE_NONE][0]['value']) : NULL;
    foreach ($last_submissions_info['last_submission']->field_attachments[LANGUAGE_NONE] as $key => $filevault) {
        $filevault = filevault_load($filevault['filevault_id']);
        $last_submission_block['last_submissions']['field_submission_filevault'][$key]['fid'] = $filevault->id;
        $last_submission_block['last_submissions']['field_submission_filevault'][$key]['link'] = l($filevault->filename, file_create_url($filevault->uri), array('attributes' => array('class' => array('btn', 'btn-link'))));
      }
    /* AUTHORIZE EDITION */
    if($last_submissions_info['last_submission']->field_uid[LANGUAGE_NONE][0]['value'] == $user->uid) {
      $last_submission_block['can_edit'] = TRUE;
      $last_submission_block['form'] = drupal_get_form('druedu_homework_update_last_submission_form', $nid);
    }
  }
  else {
    $last_submission_block['has_submission'] = FALSE;
  }
  return $last_submission_block;
}











