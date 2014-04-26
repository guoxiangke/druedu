<?php

/**
 * @file
 * Admin page callback file for the user module.
 * @see user.amdin.inc
 */

function druedu_user_admin($callback_arg = '') {
  $build['druedu_user_user_filter_form'] = drupal_get_form('druedu_user_user_filter_form');
  $build['druedu_user_user_admin_form'] = drupal_get_form('druedu_user_user_admin_form');
  //
  drupal_add_js(drupal_get_path('module', 'druedu_user').'/js/druedu_user.admin.js','file');
  drupal_set_title('Advanced membership management > School');
  return $build;
}

/**
 * Form builder; Return form for user administration filters.
 *
 * @see user_filter_form_submit()
 */
function druedu_user_user_filter_form($form, &$form_state) {
  $session = isset($_SESSION['og_user_overview_filter']) ? $_SESSION['og_user_overview_filter'] : array();
  $i = 0;
  $form['school_group'] = array(
    '#type' => 'fieldset',
    '#title' => t('School group'),
    /*/ This #states rule says that the "high school" fieldset should only
    // be shown if the "group_type" form element is set to "High School".
    '#states' => array(
      'visible' => array(
        ':input[name="group_type"]' => array('value' => 'school_group'),
      ),
    ),*/
  );

  //XXX choose grade.
  //get all grade nodes(content type == 'grade').
  $group_grade_nodes = druedu_user_get_nodes_by_group('grade');
  
  if(empty($group_grade_nodes)){
    $grade_groups[] = '-No Result-';
  }else{
    $grade_groups[] = '-Select-'; //default value
    foreach ($group_grade_nodes as $grade_nodes) {
       $grade_groups[$grade_nodes->nid] = $grade_nodes->title;
    }
  }
  
  // School group information.
  //$selected = isset($form_state['values']['grade_group']) ? $form_state['values']['grade_group'] :key($grade_groups);
  $selected = isset($_SESSION['og_user_overview_filter']['grade_group']) ?$_SESSION['og_user_overview_filter']['grade_group']:key($grade_groups);
  $form['school_group']['grade_group'] = array(
    '#type' => 'select',
    '#options' => $grade_groups,
    '#title' => t('Grade'),
    '#default_value' => $selected,//'-Select-',
    '#prefix' => '<div id="grade-container">',
    '#suffix' => '</div>',
    '#required' => true,
    /*'#states' => array(
      'visible' => array(   // action to take.
        ':input[name="group_type"]' => array('value' => 'school_group'),
      ),
    ),*/
    '#ajax' => array(
      'callback' => '_ajax_grade_group_callback',
      'wrapper' => 'subject-container',
      'effect' => 'slide',
      //'progress' => array('type' => 'none'),
    ),
  );

  
  $subject_groups = _ajax_get_subject_group_options($form, $form_state);
  //$selected = isset($form_state['values']['subject_group']) ? $form_state['values']['grade_group'] :key($subject_groups);
  $selected = isset($_SESSION['og_user_overview_filter']['subject_group']) ?$_SESSION['og_user_overview_filter']['subject_group']:key($grade_groups);
  /*
  if($_SESSION['og_user_overview_filter']['subject_group']){
    $selected = $_SESSION['og_user_overview_filter']['subject_group'];
    $subject_groups = array();
    $subject_groups[$selected] = node_load($selected)->title;
  }*/
  $form['school_group']['subject_group'] = array(
    '#type' => 'select',
    '#options' =>  $subject_groups,
    '#title' => t('Subject'),
    '#default_value' => $selected,
    '#prefix' => '<div id="subject-container">',
    '#suffix' => '</div>',
    '#ajax' => array(
      'callback' => '_ajax_subject_group_callback',
      'wrapper' => 'class-container',
      'effect' => 'slide',
      //'progress' => array('type' => 'none'),
    ),
    '#states' => array(
      'visible' => array(
       // ':input[name="grade_group"]' => array('!value' => '0'),
      ),
    ),
  );
  //XXX choose class
  $class_groups = _ajax_get_class_group_options($form, $form_state);
  //$selected = isset($form_state['values']['class_group']) ? $form_state['values']['class_group'] : key($class_groups);
  $selected = isset($_SESSION['og_user_overview_filter']['class_group']) ?$_SESSION['og_user_overview_filter']['class_group']:key($grade_groups);
  
  $form['school_group']['class_group'] = array(
    '#type' => 'select',
    '#options' => $class_groups,
    '#title' => t('Class'),
    '#default_value' => $selected,
    '#prefix' => '<div id="class-container">',
    '#suffix' => '</div>',
    '#states' => array(
      'visible' => array(
        //':input[name="subject_group"]' => array('!value' => '0'),
      ),
    ),
  );
 $form['school_group']['actions'] = array(
    '#type' => 'actions',
    '#attributes' => array('class' => array('container-inline')),
  );
  $form['school_group']['actions']['submit'] = array(
    '#type' => 'submit',
    '#value' => (count($session) ? t('Refine') : t('Filter')),
  );
  if (count($session)) {
    $form['school_group']['actions']['reset'] = array(
      '#type' => 'submit',
      '#value' => t('Reset'),
    );
  }
  //drupal_add_library('system', 'drupal.form');
  return $form;
}
function _ajax_get_subject_group_options($form, &$form_state) {
  if (!empty($form_state['values']['grade_group']) && ($grade = $form_state['values']['grade_group'])) {
    $subject_groups_nodes = druedu_user_get_nodes_by_group($grade);
    if(empty($subject_groups_nodes)){
      $subject_groups[] = '-No Result-';
    }else{
      $subject_groups[] = '-Select-'; //default value
      foreach ($subject_groups_nodes as $subject_nodes) {
        $subject_groups[$subject_nodes->nid] = $subject_nodes->title;
      }
    }
  }
  //default filter value form session
  elseif(isset($_SESSION['og_user_overview_filter']['grade_group'])) {
     $grade = $_SESSION['og_user_overview_filter']['grade_group'];
     $subject_groups_nodes = druedu_user_get_nodes_by_group($grade);
    if(empty($subject_groups_nodes)){
      $subject_groups[] = '-No Result-';
    }else {
      $subject_groups[] = '-Select-'; //default value
      foreach ($subject_groups_nodes as $subject_nodes) {
        $subject_groups[$subject_nodes->nid] = $subject_nodes->title;
      }
    }
  }
  else {
    $subject_groups[] = '-No Result-';
  }
  return $subject_groups;
}
function _ajax_get_class_group_options($form, &$form_state) {
  if (!empty($form_state['values']['subject_group']) && ($subject = $form_state['values']['subject_group'])) {
    if($grade = $form_state['values']['grade_group']){
      $group_class_nodes = druedu_user_get_nodes_by_group($grade,$subject);
    }
    if(empty($group_class_nodes)){
      $class_groups[] = '-No Result-';
    }else{
      $class_groups[] = '-Select-';
      foreach ($group_class_nodes as $class_node) {
        $class_groups[$class_node->nid] = $class_node->title;
      }
    }
  }
  //default filter value form session
  elseif(isset($_SESSION['og_user_overview_filter']['subject_group']) && isset($_SESSION['og_user_overview_filter']['grade_group'])) {
    $subject = $_SESSION['og_user_overview_filter']['subject_group'];
    $grade = $_SESSION['og_user_overview_filter']['grade_group'];
    $group_class_nodes = druedu_user_get_nodes_by_group($grade,$subject);
    if(empty($group_class_nodes)){
      $class_groups[] = '-No Result-';
    }else{
      $class_groups[] = '-Select-';
      foreach ($group_class_nodes as $class_node) {
        $class_groups[$class_node->nid] = $class_node->title;
      }
    }
  }
  else{
    $class_groups[] = '-No Result-';
  }
  return $class_groups;
}

/**
 * Callback element needs only select the portion of the form to be updated.
 * Since #ajax['callback'] return can be HTML or a renderable array (or an
 * array of commands), we can just return a piece of the form.
 * See @link ajax_example_advanced.inc AJAX Advanced Commands for more details
 * on AJAX framework commands.
 *
 * @return renderable array (the checkboxes fieldset)
 */
function _ajax_grade_group_callback($form, &$form_state) {
  // if change grade,class default be no result.
  $form_state['input']['class_group'] = 0;
  $form = drupal_build_form($form['#form_id'],$form_state);
  $commands[] = ajax_command_replace('#class-container', drupal_render($form['school_group']['class_group']));
  $commands[] = ajax_command_replace('#subject-container', drupal_render($form['school_group']['subject_group']));
  //return $form['school_group'];
  return array('#type' => 'ajax', '#commands' => $commands);
}
function _ajax_subject_group_callback($form, &$form_state) {
	return $form['school_group']['class_group'];
}

/**
 * Process result from user administration filter form.
 */
function druedu_user_user_filter_form_validate($form, &$form_state) {
  if(!isset($form_state['values']['op'])) {
    return;
  }
  $op = $form_state['values']['op'];
  switch ($op) {
    case t('Filter'):
    case t('Refine'): 
      if($form_state['values']['grade_group'] == 0)
        form_set_error('grade_group','Please choose a Grade  of destination before filtering the potential users.');
      break;
    case t('Reset'):
      break;
  }
  return;
}
/**
 * Process result from user administration filter form.
 */
function druedu_user_user_filter_form_submit($form, &$form_state) {
  $op = $form_state['values']['op'];
  $filters = array('group_type','grade_group','subject_group','class_group');
  switch ($op) {
    case t('Filter'):
    case t('Refine'):
      foreach ($filters as $filter) {
        if (isset($form_state['values'][$filter]) && $form_state['values'][$filter] != '-Select-') {
            $_SESSION['og_user_overview_filter'][$filter]= $form_state['values'][$filter];
        }
      }
      break;
    case t('Reset'):
      $_SESSION['og_user_overview_filter'] = array();
      break;
  }
  //$form_state['redirect'] = 'admin/og';
  return;
}
/**
 * get users form session.
 * 
 */
function druedu_user_get_user_by_filter() {
  $filters = isset($_SESSION['og_user_overview_filter'])?$_SESSION['og_user_overview_filter']:array();
  $group_type = isset($filters['group_type'])?$filters['group_type']:NULL;
  $grade = isset($filters['grade_group'])?$filters['grade_group']:NULL;
  $subject = isset($filters['subject_group'])?$filters['subject_group']:NULL;
  $class = isset($filters['class_group'])?$filters['class_group']:NULL;
  //class = 0
  $class = $class?$class:NULL;
  $subject = $subject?$subject:NULL;
  $return['filters'] = $filters;
  if(is_null($class) && is_null($subject)) {
   $gid = $grade;
  }elseif(is_null($class)) {
    $gid = $subject;
  }else {
   $gid = $class;
  }
  $return['filters'] = $filters;
  //dpm($filters,'$filters');
  $group_members = druedu_user_get_users_by_group($grade, $subject, $class,$type = 'all',$potential=FALSE);
  $group_members_admin = array();
  foreach ($group_members as $uid => $name) {
    $member_account = user_load($uid);
    //XXX issue: 'allow group admin' @see druedu_user_premission()
    if(user_access('allow group admin',$member_account)) {
      //$group_potential_admin $group_members_admin
      $group_roles = og_get_user_roles($group_type='node', $gid, $member_account->uid, $include = FALSE);
      foreach ($group_roles as $grid => $value) {
        if($value == 'administrator member'){
           $group_members_admin[$member_account->uid] = $member_account->name;
           break;
        }
      }
    };
  }
  //potential admin = part of grade && extra permission && not an admin of the current group already
  $grade_members = druedu_user_get_users_by_group($grade, NULL, NULL,$type = 'all',$potential=FALSE);
  $return['grade_members_all'] = $grade_members;
  
  //dpm($grade_members,'$grade_members-all');
  $group_potential_admin = array();
  foreach ($grade_members as $uid => $name) {
    $member_account = user_load($uid);
    if(user_access('allow group admin',$member_account)) {
      $group_potential_admin[$uid] = $member_account->name;
    };
  }
  $group_potential_admin =  array_diff($group_potential_admin, $group_members_admin);
  $return['group_members_admin'] = $group_members_admin;
  $return['group_potential_admin'] = $group_potential_admin;
  //dpm($group_members_admin,'$group_members_admin');
  //dpm($group_potential_admin,'$group_potential_admin');
  if(!is_null($class)) {// one enough && $subject && $grade
    // all users in that grade.
    //$grade_members = druedu_user_get_users_by_group($grade, NULL, NULL, $type = 'all',$potential=TRUE);
   // $class_members = druedu_user_get_users_by_group($grade, $subject, $class, $type = 'all',$potential=TRUE);
    // class members = all calss members - 2 * admins
    $class_members = array_diff($group_members,$group_members_admin,$group_potential_admin);
    //dpm($class_members,'$class_members');
    // class potential members = all grade members - class members[+admin] - group_potential_admin
    $potential_members = array_diff($grade_members,$class_members,$group_members_admin,$group_potential_admin);
    //dpm($potential_members,'$potential_members');
    
    $return['class_members'] = $class_members;
    $return['potential_members'] = $potential_members;
  }
  return $return;
}
/**
 * Form builder; User administration page.
 *
 * @ingroup forms
 * @see user_admin_account_validate()
 * @see user_admin_account_submit()
 */
function druedu_user_user_admin_form($form, &$form_state) {//dpm($form_state);
  //XXX

  $return = druedu_user_get_user_by_filter();
  $form_state['druedu_user_defaults'] = $return;
  $filters = $return['filters'];
  $grade_members = $return['grade_members_all'];
  $group_members_admin = $return['group_members_admin']; 
  $group_potential_admin = $return['group_potential_admin'];
  $class_members = array();
  if(isset($return['class_members'])) {
    $class_members = $return['class_members'];
  }
  $potential_members = array();
  if(isset($return['potential_members'])) {
    $potential_members = $return['potential_members'];
  }
  
  $form['wrapper'] = array(
    '#type' => 'fieldset', 
    '#title' => t('User selection'), 
    '#weight' => -2, 
    '#collapsible' => FALSE, 
    '#collapsed' => FALSE,
    '#states' => array(
      'visible' => array(
        //':input[name="group_type"]' => array('value' => 'school_group'),
      ),
    ),
  );
  $form['wrapper']['warning'] = array(
      '#markup' => 'Operate Message',
      '#prefix' => '<div id="op-warning" class="messages warning">',
      '#suffix' => '</div>',
      '#weight' => -3,
    );
  //$destination = drupal_get_destination();
  $form['wrapper']['user_search'] = array(
    '#type' => 'fieldset', 
    '#title' => t('Search'), 
    '#weight' => -2, 
    '#collapsible' => FALSE, 
    '#collapsed' => FALSE,
  );
  $form['wrapper']['user_search']['search'] = array(
    '#type' => 'textfield',
    '#title' => t('Search'),
    // The autocomplete path is provided in hook_menu in ajax_example.module.
    '#autocomplete_path' => 'admin/advanced_membership_management/school/autocomplete',
    '#weight' => -1,
  );
  $form['wrapper']['user_search']['select'] = array(
    '#type' => 'submit',
    '#value' => t('Select'),
    '#attributes' =>array('class' => array('op-warning')),
  );
  
  $form['wrapper']['selection'] = array(
    '#type' => 'fieldset', 
    '#title' => t('Selection'), 
    '#weight' => 0, 
    '#collapsible' => FALSE, 
    '#collapsed' => FALSE,
    '#prefix' => '<div id="selection-container">',
    '#suffix' => '</div>',
  );
   $form['wrapper']['selection']['potential_administrators'] = array(
    '#type' => 'select',
    '#title' => t('Potential administrators'),
    '#options' =>$group_potential_admin,
    '#multiple' => TRUE,
    //'#default_value' => $category['selected'],
    //'#description' => t('Potential administrators'),
   );
  //hide members form if no select class.
  if($filters['class_group'] != 0)
  $form['wrapper']['selection']['potential_members'] = array(
    '#type' => 'select',
    '#title' => t('Potential members'),
    '#options' =>$potential_members,
    '#multiple' => TRUE,
    //'#default_value' => $category['selected'],
    //'#description' => t('Potential members'),
   );
  $form['wrapper']['members'] = array(
    '#type' => 'fieldset', 
    '#title' => t('Group members'), 
    '#weight' => 2, 
    '#prefix' => '<div id="members-container">',
    '#suffix' => '</div>',
    '#collapsible' => FALSE, 
    '#collapsed' => FALSE,
  );
   $form['wrapper']['members']['administrators'] = array(
    '#type' => 'select',
    '#title' => t('Group administrators'),
    '#options' =>$group_members_admin,
    '#multiple' => TRUE,
    //'#default_value' => $category['selected'],
    //'#description' => t('Group administrators'),
   );
  //hide members form if no select class.
  if($filters['class_group'] != 0)
  $form['wrapper']['members']['class_members'] = array(
    '#type' => 'select',
    '#title' => t('Group members'),
    '#options' =>$class_members,
    '#multiple' => TRUE,
    //'#default_value' => $category['selected'],
    //'#description' => t('Group members'),
   );
  
  $form['wrapper']['options'] = array(
    '#type' => 'fieldset',
    '#title' => t('Update options'),
    '#weight' => 1, 
    '#attributes' => array('class' => array('container-inline')),
  );

  $form['wrapper']['options']['remove'] = array(
    '#type' => 'button',
    '#value' => t('Remove'),
    '#attributes' =>array('class' => array('op-warning')),
  );
  $form['wrapper']['options']['add'] = array(
    '#type' => 'button',
    '#value' => t('Add'),
    '#attributes' =>array('class' => array('op-warning')),
    //no ajax,prevent default. and do somthings
    //@see js/druedu_user.admin.js
  );
  
  $form['wrapper']['posts_admins'] = array(
    '#type' => 'textfield',
    '#title' => t('Post admins'),
    '#weight' => 4,
    '#default_value' => implode(",", array_keys($group_members_admin)),
    '#attributes' => array('class' => array('container-inline')),
    
  );
  //hide members form if no select class.
  if(isset($filters['class_group']))
  $form['wrapper']['posts_members'] = array(
    '#type' => 'textfield',
    '#title' => t('Post members'),
    '#weight' => 4,
    '#default_value' => implode(",", array_keys($class_members)),
    '#attributes' => array('class' => array('container-inline')),
    
  );
  /*
  $form['wrapper']['show_change_admin_add'] = array(
    '#type' => 'textarea',
    '#title' => t('To Adding admins...'),
    '#weight' => 3,
    '#default_value' => implode(",", $group_members_admin),
    '#attributes' => array('class' => array('container-inline')),
    '#cols' =>3,
  );
  //hide members form if no select class.
  if($filters['class_group'])
  $form['wrapper']['show_change_member_add'] = array(
    '#type' => 'textfield',
    '#title' => t('To Add members...'),
    '#weight' => 3,
    '#default_value' => implode(",", $class_members),
    '#attributes' => array('class' => array('container-inline')),
    '#disabled' => TRUE,
    '#cols' =>3,
  );
   $form['wrapper']['show_change_admin_del'] = array(
    '#type' => 'textarea',
    '#title' => t('To be del admins...'),
    '#weight' => 3,
    '#default_value' => implode(",", $group_members_admin),
    '#attributes' => array('class' => array('container-inline')),
    '#cols' =>3,
  );
  //hide members form if no select class.
  if($filters['class_group'])
  $form['wrapper']['show_change_member_del'] = array(
    '#type' => 'textfield',
    '#title' => t('To be del members...'),
    '#weight' => 3,
    '#default_value' => implode(",", $class_members),
    '#attributes' => array('class' => array('container-inline')),
    '#disabled' => TRUE,
    '#cols' =>3,
  );*/
  $form['wrapper']['actions'] = array('#type' => 'actions');
  $form['wrapper']['actions']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Confirm settings'),
  );
  //
  return $form;
  /*if (isset($form_state['values']['posts_admins'])) {
    return confirm_form($form, 
                   'zhenli?', 
                    'admin/og', t('This action cannot be undone.'), 
                    t('Do'), t('Cancel'));//form_confirm($form, $form_state, array_filter($form_state['values']['nodes']));
 }else{
   return $form;
 }*/
}

function druedu_user_user_admin_form_submit($form, &$form_state) {
  $default_admins = $form_state['druedu_user_defaults']['group_members_admin'];
  $post_admins = explode(',', $form_state['values']['posts_admins']);//0=>id
  $post_admins = array_unique(array_filter($post_admins));//unique and del empty
  $default_admins = array_keys($default_admins); //id=>name
  $added_admins = array_diff($post_admins, $default_admins);
  $deleted_admins = array_diff($default_admins ,$post_admins);
  /*
  dpm($post_admins,'$post_admins');
  dpm($default_admins,'$default_admins');
  dpm($added_admins,'$added_admins');
  dpm($deleted_admins,'$deleted_admins');*/
  
  if($form_state['druedu_user_defaults']['filters']['class_group']){
    $default_members = $form_state['druedu_user_defaults']['class_members']; 
    $post_members = explode(',', $form_state['values']['posts_members']);
    $post_members = array_unique(array_filter($post_members));//unique and del empty
    $default_members = array_keys($default_members);
    $added_members = array_diff($post_members, $default_members);
    $deleted_members = array_diff($default_members ,$post_members);
    /*
    dpm($post_members,'$post_members');
    dpm($default_members,'$default_members');
    dpm($added_members,'$added_members');
    dpm($deleted_members,'$deleted_members');*/
  }
  //profile_field_form()
  $filters = $form_state['druedu_user_defaults']['filters'];
  
  if($gid = $filters['class_group']) {
    $bundle = 'class';
    //og_group($group_type, $gid, $values = array())
    //og_ungroup($group_type, $gid, $entity_type = 'user', $etid = NULL)
  }elseif($gid = $filters['subject_group']) {
    $bundle = 'subject';
  }else {
    $gid = $filters['grade_group'];
    $bundle = 'grade';
  }

   $group_type = 'node';
   $og_roles = og_roles($group_type, $bundle, $gid , $force_group = FALSE, $include_all = TRUE);
   foreach ($og_roles as $key => $value) {
     if($value == 'administrator member') {
       $admin_rid = $key;
       break;
     }
   }
  //add amdin
  
   if(count($added_admins))
   foreach ($added_admins as $key => $uid) {
     if($entity = user_load($uid)){
       if(og_is_member($group_type, $gid, $entity_type='user', $entity , $states = array(OG_STATE_ACTIVE))){
          og_role_grant($group_type, $gid, $uid, $admin_rid) ;
       }else{
         // subscribe to the group.
         $join_array = array(
          'entity_type' => 'user',
          'entity' =>$entity
         );
         og_group($group_type, $gid, $join_array);
         og_role_grant($group_type, $gid, $uid, $admin_rid) ;
       }
     }
    
   }
  //remove admin
  if(count($deleted_admins))
   foreach ($deleted_admins as $key => $uid) {
     $entity = user_load($uid);
     og_role_revoke($group_type, $gid, $uid, $admin_rid);
   }
  
  //
  if($bundle == 'class'){
     //add members
    if(count($added_members))
     foreach ($added_members as $key => $uid) {
       $entity = user_load($uid);
       {
         // subscribe to the group.
         $join_array = array(
          'entity_type' => 'user',
          'entity' =>$entity
         );
         og_group($group_type, $gid, $join_array);
       }
     }
    //remove members
    if(count($deleted_members))
     foreach ($deleted_members as $key => $uid) {
       //og_ungroup($group_type, $gid, $uid);
       og_ungroup($group_type, $gid, $entity_type = 'user', $etid = $uid);
     }
  }
  // unset the filter
  //$_SESSION['og_user_overview_filter'] = array();
  drupal_set_message(t('Your settings have been saved!'), 'status', FALSE);
}
/**
 * Menu callback; Retrieve a JSON object containing autocomplete suggestions for existing users.
 * of potential_members of the group.
 */
function _ajax_member_autocomplete($string = '') {
  $matches = array();
  $return = druedu_user_get_user_by_filter();
  
  $filters = $return['filters'];
  $grade_members = $return['grade_members_all'];
  $group_members_admin = $return['group_members_admin']; 
  $group_potential_admin = $return['group_potential_admin'];
  if(isset($return['class_members'])) {
    $class_members = $return['class_members'];
  }
  if(isset($return['potential_members'])) {
    $potential_members = $return['potential_members'];
  }
  // grade & subject only has admin(already+potential) to choose.
  //class has all the grade members to choose.
  if($filters['class_group']) {//class level
    $preg_members = $grade_members;
  }else {//subject level & grade level
    $preg_members = $group_members_admin+$group_potential_admin;
  }
  
  if ($string) {
    $pattern = '/^'.$string.'/';
    foreach ($preg_members as $uid=>$name) {
      if(preg_match($pattern, $name)) {
        $matches[$name] = check_plain($name);
      }
    }
  }

  drupal_json_output($matches);
}
/**
 * 
 */
function druedu_user_public() {
  $build['druedu_public_filter_form'] = drupal_get_form('druedu_user_public_filter_form');
  $build['druedu_public_admin_form'] = drupal_get_form('druedu_public_admin_form');
  //
  drupal_add_js(drupal_get_path('module', 'druedu_user').'/js/druedu_user.admin.js','file');
  drupal_set_title('Advanced membership management > Public');
  return $build;
}


/**
 * Form builder; Return form for user administration filters.
 *
 * @see user_filter_form_submit()
 */
function druedu_user_public_filter_form($form, &$form_state) {
  $session = isset($_SESSION['og_public_filter']) ? $_SESSION['og_public_filter'] : array();

  $form['public_group'] = array(
    '#type' => 'fieldset',
    '#title' => t('Public group'),
    // This #states rule says that the "high school" fieldset should only
    // be shown if the "group_type" form element is set to "High School".
    /*'#states' => array(
      'visible' => array(
        ':input[name="group_type"]' => array('value' => 'public_group'),
      ),
    ),*/
  );

  //XXX choose a public group.
  //get all grade nodes(content type == 'group').
  $group_grade_nodes = druedu_user_get_nodes_by_group('group');
  
  if(empty($group_grade_nodes)){
    $public_groups[] = '-No Result-';
  }else{
    $public_groups[] = '-Select-'; //default value
    foreach ($group_grade_nodes as $grade_nodes) {
       $public_groups[$grade_nodes->nid] = $grade_nodes->title;
    }
  }
  $selected = isset($_SESSION['og_public_filter']['gid']) ?$_SESSION['og_public_filter']['gid']:key($public_groups);
  $form['public_group']['gid'] = array(
    '#type' => 'select',
    '#options' => $public_groups,
    '#title' => t('Group'),
    '#default_value' => $selected,//'-Select-',
    '#prefix' => '<div id="group-container">',
    '#suffix' => '</div>',
    '#required' =>true,
  );

  //XXX choose grade.
  //get all grade nodes(content type == 'grade').
  $group_grade_nodes = druedu_user_get_nodes_by_group('grade');
  
  if(empty($group_grade_nodes)){
    $grade_groups[] = '-No Result-';
  }else{
    $grade_groups[] = '-Select-'; //default value
    foreach ($group_grade_nodes as $grade_nodes) {
       $grade_groups[$grade_nodes->nid] = $grade_nodes->title;
    }
  }
  
  // School group information.
  //$selected = isset($form_state['values']['grade_group']) ? $form_state['values']['grade_group'] :key($grade_groups);
  $selected = isset($_SESSION['og_public_filter']['grade_group']) ?$_SESSION['og_public_filter']['grade_group']:key($grade_groups);
  $form['public_group']['grade_group'] = array(
    '#type' => 'select',
    '#options' => $grade_groups,
    '#title' => t('Grade'),
    '#default_value' => $selected,//'-Select-',
    '#prefix' => '<div id="grade-container">',
    '#suffix' => '</div>',
  );

  
 $form['public_group']['actions'] = array(
    '#type' => 'actions',
    '#attributes' => array('class' => array('container-inline')),
  );
  $form['public_group']['actions']['submit'] = array(
    '#type' => 'submit',
    '#value' => (count($session) ? t('Refine') : t('Filter')),
  );
  if (count($session)) {
    $form['public_group']['actions']['reset'] = array(
      '#type' => 'submit',
      '#value' => t('Reset'),
    );
  }
  return $form;
}
/**
 * 
 */
function druedu_user_public_filter_form_validate($form, &$form_state) {
  $op = $form_state['values']['op'];
  switch ($op) {
    case t('Filter'):
    case t('Refine'):
      if($form_state['values']['gid'] ==0)
      form_set_error('gid','Please choose a Public group of destination before choosing the potential users by Grade.');
      break;
    case t('Reset'):
      break;
  }
  return;
}

/**
 * 
 */
function druedu_user_public_filter_form_submit($form, &$form_state) {
  $op = $form_state['values']['op'];
  $filters = array('group_type', 'gid', 'grade_group');//publicArt & grade6
  switch ($op) {
    case t('Filter'):
    case t('Refine'):
      foreach ($filters as $filter) {
        if (isset($form_state['values'][$filter]) && $form_state['values'][$filter] != '-Select-') {
            $_SESSION['og_public_filter'][$filter]= $form_state['values'][$filter];
        }
      }
      break;
    case t('Reset'):
      $_SESSION['og_public_filter'] = array();
      break;
  }
  //$form_state['redirect'] = 'admin/og';
  return;
}

/**
 * Form builder; User administration page.
 *
 * @ingroup forms
 * @see druedu_public_admin_form_submit()
 */
function druedu_public_admin_form($form, &$form_state) {
  //XXX
  $return = druedu_user_public_get_user_by_filter();
  $form_state['druedu_user_defaults'] = $return;
  $filters = $return['filters'];
  //$grade_members = $return['grade_members_all'];
  $public_members_admin = $return['public_members_admin']; 
  $public_potential_admin = $return['public_potential_admin'];
  $public_members = $return['public_members'];
  $public_potential_user = $return['public_potential_user'];  

  $form['wrapper'] = array(
    '#type' => 'fieldset', 
    '#title' => t('User selection'), 
    '#weight' => -2, 
    '#collapsible' => FALSE, 
    '#collapsed' => FALSE,
    /*'#states' => array(
      'visible' => array(
        ':input[name="group_type"]' => array('value' => 'school_group'),
      ),
    ),*/
  );
  $form['wrapper']['warning'] = array(
      '#markup' => 'Operate Message',
      '#prefix' => '<div id="op-warning" class="messages warning">',
      '#suffix' => '</div>',
      '#weight' => -3,
    );
  //$destination = drupal_get_destination();
  $form['wrapper']['user_search'] = array(
    '#type' => 'fieldset', 
    '#title' => t('Search'), 
    '#weight' => -2, 
    '#collapsible' => FALSE, 
    '#collapsed' => FALSE,
  );
  $form['wrapper']['user_search']['search'] = array(
    '#type' => 'textfield',
    '#title' => t('Search'),
    // The autocomplete path is provided in hook_menu in ajax_example.module.
    //@see _ajax_public_autocomplete()
    '#autocomplete_path' => 'admin/advanced_membership_management/public/autocomplete',
    '#weight' => -1,
  );
  $form['wrapper']['user_search']['select'] = array(
    '#type' => 'submit',
    '#value' => t('Select'),
    '#attributes' =>array('class' => array('op-warning')),
  );
  
  $form['wrapper']['selection'] = array(
    '#type' => 'fieldset', 
    '#title' => t('Selection'), 
    '#weight' => 0, 
    '#collapsible' => FALSE, 
    '#collapsed' => FALSE,
    '#prefix' => '<div id="selection-container">',
    '#suffix' => '</div>',
  );
   $form['wrapper']['selection']['potential_administrators'] = array(
    '#type' => 'select',
    '#title' => t('Potential administrators'),
    '#options' =>isset($_SESSION['og_public_filter']['gid'])?$public_potential_admin:array(),
    '#multiple' => TRUE,
    //'#default_value' => $category['selected'],
    //'#description' => t('Potential administrators'),
   );

  $form['wrapper']['selection']['potential_members'] = array(
    '#type' => 'select',
    '#title' => t('Potential members'),
    '#options' =>isset($_SESSION['og_public_filter']['gid'])?$public_potential_user:array(),
    '#multiple' => TRUE,
    //'#default_value' => $category['selected'],
    //'#description' => t('Potential members'),
   );
  $form['wrapper']['members'] = array(
    '#type' => 'fieldset', 
    '#title' => t('Group members'), 
    '#weight' => 2, 
    '#prefix' => '<div id="members-container">',
    '#suffix' => '</div>',
    '#collapsible' => FALSE, 
    '#collapsed' => FALSE,
  );
   $form['wrapper']['members']['administrators'] = array(
    '#type' => 'select',
    '#title' => t('Group administrators'),
    '#options' =>$public_members_admin,
    '#multiple' => TRUE,
    //'#default_value' => $category['selected'],
    //'#description' => t('Group administrators'),
   );
  $form['wrapper']['members']['class_members'] = array(
    '#type' => 'select',
    '#title' => t('Group members'),
    '#options' =>$public_members,
    '#multiple' => TRUE,
    //'#default_value' => $category['selected'],
    //'#description' => t('Group members'),
   );
  
  $form['wrapper']['options'] = array(
    '#type' => 'fieldset',
    '#title' => t('Update options'),
    '#weight' => 1, 
    '#attributes' => array('class' => array('container-inline')),
  );
  $form['wrapper']['options']['remove'] = array(
    '#type' => 'button',
    '#value' => t('Remove'),
    '#attributes' =>array('class' => array('op-warning')),
  );
  $form['wrapper']['options']['add'] = array(
    '#type' => 'button',
    '#value' => t('Add'),
    '#attributes' =>array('class' => array('op-warning')),
    //no ajax,prevent default. and do somthings
    //@see js/druedu_user.admin.js
  );
  $form['wrapper']['posts_admins'] = array(
    '#type' => 'textfield',
    '#title' => t('Post admins'),
    '#weight' => 4,
    '#default_value' => implode(",", array_keys($public_members_admin)),
    '#attributes' => array('class' => array('container-inline')),
    
  );
  $form['wrapper']['posts_members'] = array(
    '#type' => 'textfield',
    '#title' => t('Post members'),
    '#weight' => 4,
    '#default_value' => implode(",", array_keys($public_members)),
    '#attributes' => array('class' => array('container-inline')),
    
  );
  $form['wrapper']['actions'] = array('#type' => 'actions');
  $form['wrapper']['actions']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Confirm settings'),
  );

  return $form;
}

/**
 * public group user management
 * get users form session 
 * return group admins and members,and potential members and admins.
 */
function druedu_user_public_get_user_by_filter() {
 
////////////////////////////////////////////////////////////////
  $filters = isset($_SESSION['og_public_filter']) ? $_SESSION['og_public_filter'] : array();
  $return['filters'] = $filters;
  $group_type = isset($filters['group_type'])?$filters['group_type']:NULL;
  $gid = isset($filters['gid'])?$filters['gid']:NULL;//public group
  $grade = isset($filters['grade_group'])?$filters['grade_group']:NULL;

  //get group's admins and memebers with gid 


  {
    //All members of the public group
    $all_memebers = druedu_user_get_users_by_group($gid);
    $public_members_admin = array();
    foreach ($all_memebers as $uid => $name) {
      $member_account = user_load($uid);
      //XXX issue: 'allow group admin' @see druedu_user_premission()
      if(user_access('allow group admin',$member_account)) {
        $group_roles = og_get_user_roles($group_type='node', $gid, $member_account->uid, $include = FALSE);
        foreach ($group_roles as $grid => $value) {
          if($value == 'administrator member'){
             $public_members_admin[$member_account->uid] = $member_account->name;
             break;
          }
        }
      };
    }
    $public_members = array_diff($all_memebers,$public_members_admin); 
    $return['public_members'] = $public_members;
    $return['public_members_admin'] = $public_members_admin;

  }

  if($grade) {
    $all_users = druedu_user_get_users_by_group($grade);
  }else {
    $query = db_select('users', 'u')
      ->fields('u', array('name','uid'))
      ->condition('u.status', '1')
      ->orderBy('u.uid', 'ASC');
    $result = $query->execute();
    while($record = $result->fetchAssoc()) {
        $all_users[$record['uid']] = $record['name'];
    }
  }

  foreach ($all_users as $uid => $name) {
    $member_account = user_load($uid);
    if(user_access('allow group admin',$member_account)) {
      $public_potential_admin[$uid] = $member_account->name;
    };
  }
  $return['public_potential_admin']  = array_diff($public_potential_admin, $public_members_admin);
  $return['public_potential_user']  = array_diff($all_users,$all_memebers,$public_potential_admin);
////////////////////////////
  return $return;
}
/**
 * get_role_members_by_group($gid/'grade/class/subject')
 * parameter $group int or string 
 * @see druedu_user_get_users_by_group()
 * return array('admins'=>$group_members_admin,'members'=>$group_members);
 */
function druedu_user_get_role_members($group) {

  //get group's admins and memebers with gid 
  $group_all = druedu_user_get_users_by_group($grade);
  foreach ($group_all as $uid => $name) {
    $member_account = user_load($uid);
    //XXX issue: 'allow group admin' @see druedu_user_premission()
    if(user_access('allow group admin',$member_account)) {
      //$group_potential_admin $group_members_admin
      $group_roles = og_get_user_roles($group_type='node', $gid, $member_account->uid, $include = FALSE);
      foreach ($group_roles as $grid => $value) {
        if($value == 'administrator member'){
           $group_members_admin[$member_account->uid] = $member_account->name;
           break;
        }
      }
    };
  }
  $group_members = array_diff($group_all,$group_members_admin);
  return array('admins'=>$group_members_admin,'members'=>$group_members);
}
/**
 * Menu callback; Retrieve a JSON object containing autocomplete suggestions for existing users.
 * of potential_members of the group.
 */
function _ajax_public_autocomplete($string = '') {
  $matches = array();
  $return = druedu_user_public_get_user_by_filter();
  
  $preg_members = $return['public_potential_admin'] + $return['public_potential_user'];
  if ($string) {
    $pattern = '/^'.$string.'/';
    foreach ($preg_members as $uid=>$name) {
      if(preg_match($pattern, $name)) {
        $matches[$name] = check_plain($name);
      }
    }
  }

  drupal_json_output($matches);
}


function druedu_public_admin_form_submit($form, &$form_state) {
  $default_admins = $form_state['druedu_user_defaults']['public_members_admin'];
  $post_admins = explode(',', $form_state['values']['posts_admins']);//0=>id
  $post_admins = array_unique(array_filter($post_admins));//unique and del empty
  $default_admins = array_keys($default_admins); //id=>name
  $added_admins = array_diff($post_admins, $default_admins);
  $deleted_admins = array_diff($default_admins ,$post_admins);
  /*
  dpm($post_admins,'$post_admins');
  dpm($default_admins,'$default_admins');
  dpm($added_admins,'$added_admins');
  dpm($deleted_admins,'$deleted_admins');*/
  

  $default_members = $form_state['druedu_user_defaults']['public_members']; 
  $post_members = explode(',', $form_state['values']['posts_members']);
  $post_members = array_unique(array_filter($post_members));//unique and del empty
  $default_members = array_keys($default_members);
  $added_members = array_diff($post_members, $default_members);
  $deleted_members = array_diff($default_members ,$post_members);
 /*
  dpm($post_members,'$post_members');
  dpm($default_members,'$default_members');
  dpm($added_members,'$added_members');
  dpm($deleted_members,'$deleted_members'); */

  //profile_field_form()
  $filters = $form_state['druedu_user_defaults']['filters'];
  

  $gid = $filters['gid'];
  $bundle = 'group';

   $group_type = 'node';
   $og_roles = og_roles($group_type, $bundle, $gid , $force_group = FALSE, $include_all = TRUE);
   foreach ($og_roles as $key => $value) {
     if($value == 'administrator member') {
       $admin_rid = $key;
       break;
     }
   }
  //add amdin
  
   if(count($added_admins))
   foreach ($added_admins as $key => $uid) {
     if($entity = user_load($uid)){
       if(og_is_member($group_type, $gid, $entity_type='user', $entity , $states = array(OG_STATE_ACTIVE))){
          og_role_grant($group_type, $gid, $uid, $admin_rid) ;
       }else{
         // subscribe to the group.
         $join_array = array(
          'entity_type' => 'user',
          'entity' =>$entity
         );
         og_group($group_type, $gid, $join_array);
         og_role_grant($group_type, $gid, $uid, $admin_rid) ;
       }
     }
    
   }
  //remove admin
  if(count($deleted_admins))
   foreach ($deleted_admins as $key => $uid) {
     $entity = user_load($uid);
     og_role_revoke($group_type, $gid, $uid, $admin_rid);
   }

  //add members
  if(count($added_members))
   foreach ($added_members as $key => $uid) {
     $entity = user_load($uid);
     {
       // subscribe to the group.
       $join_array = array(
        'entity_type' => 'user',
        'entity' =>$entity
       );
       og_group($group_type, $gid, $join_array);
     }
   }
  //remove members
  if(count($deleted_members))
   foreach ($deleted_members as $key => $uid) {
     //og_ungroup($group_type, $gid, $uid);
     og_ungroup($group_type, $gid, $entity_type = 'user', $etid = $uid);
   }
  // unset the filter
  //$_SESSION['og_user_overview_filter'] = array();
  drupal_set_message(t('Your settings have been saved!'), 'status', FALSE);
}