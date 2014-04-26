<?php

function druedu_redirect_config($form, $form_state) {
	$form = array();
  $form['description'] = array('#markup' => 'Enter below which page (url) to redirect after a node been deleted or click on the cancel button. Both Drupal path and alias are valid.<br/>By default, the redirection is made to the homepage ("< front>") or to the node itself ("node") after update.');
	$synch_types = variable_get('synch_types', NULL);
  if(!$synch_types){
    $synch_types = array();
  }else{
    $synch_types = array_filter(unserialize($synch_types));
  }
  $node_types = node_type_get_types();
  //variable_del('druedu_redirect_settings');//init //
  $druedu_redirect_settings = unserialize(variable_get('druedu_redirect_settings', null));
  //dpm($druedu_redirect_settings);
  foreach ($node_types as $node_type => $node_type_obj) {
  	if($node_type == 'answer') continue; //except for answer.
    $form['node_types'][$node_type] = array(
      '#type' => 'textfield',
      '#default_value' =>$druedu_redirect_settings[$node_type]?$druedu_redirect_settings[$node_type]:'<front>',
      '#field_prefix' => url(NULL, array('absolute' => TRUE)) . (variable_get('clean_url', 0) ? '' : '?q='),
    );
    $form['node_types'][$node_type.'_update'] = array(
      '#type' => 'textfield',
      '#default_value' =>$druedu_redirect_settings[$node_type.'_update']?$druedu_redirect_settings[$node_type.'_update']:'node',
      '#field_prefix' => url(NULL, array('absolute' => TRUE)) . (variable_get('clean_url', 0) ? '' : '?q='),
    );
    $form['node_types'][$node_type.'_passby'] = array(
      '#type' => 'checkbox',
      '#default_value' =>$druedu_redirect_settings[$node_type.'_passby']?$druedu_redirect_settings[$node_type.'_passby']:FALSE,
    );
    $form['node_types'][$node_type.'_passby_del'] = array(
      '#type' => 'checkbox',
      '#default_value' =>$druedu_redirect_settings[$node_type.'_passby_del']?$druedu_redirect_settings[$node_type.'_passby_del']:FALSE,
    );
  }
	// Add the buttons.
	$form['actions'] = array('#type' => 'actions');
  $form['actions']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save'),
    '#weight' => 5,
  );
	return $form;
}
/**
 * Form submit handler for the open_users_synch_setting() form.
 */
function druedu_redirect_config_validate($form, &$form_state){
	$node_types = node_type_get_types();
	$settings = array();

	foreach ($node_types as $node_type => $node_type_obj){
		$settings[$node_type] = $form_state['values'][$node_type];
	}
	
	foreach ($settings as $key => $value) {
  	if($key == 'answer') continue; //except for answer.
		$value = drupal_get_normal_path($value);
		 if (!trim($value) || !validate_path_alias_4druedu($value)) {
       form_set_error($key, t("Path '@link_path' not found.", array('@link_path' => $value)));
     }
	}
}

/**
 * Form submit handler for the open_users_synch_setting() form.
 */
function druedu_redirect_config_submit($form, &$form_state){
	$node_types = node_type_get_types();
	$settings = array();

	foreach ($node_types as $node_type => $node_type_obj){
		$settings[$node_type] = $form_state['values'][$node_type];
    $settings[$node_type.'_update'] = $form_state['values'][$node_type.'_update'];
    $settings[$node_type.'_passby'] = $form_state['values'][$node_type.'_passby'];
    $settings[$node_type.'_passby_del'] = $form_state['values'][$node_type.'_passby_del'];
	}
	$settings = serialize($settings);
	if(variable_get('druedu_redirect_settings', null) == $settings){
   	drupal_set_message(t('No changes found!'),'status');
	}else{
	  variable_set('druedu_redirect_settings', $settings);
		drupal_set_message(t('Settings were saved!'),'status');
	}
}

/**
 * Returns HTML for the role order and new role form.
 *
 * @param $variables
 *   An associative array containing:
 *   - form: A render element representing the form.
 *
 * @ingroup themeable
 */
function theme_druedu_redirect_config($variables) {
  $form = $variables['form'];

  $header = array(t('Node type'), t('delete&Cancel Redirection'), t('Update Redirection'),'update bypass','delete bypass');
  $rows[] = array(array('data' => drupal_render($form['description']), 'colspan' => 5, 'class' => 'druedu-redirect-des'));
  $node_types = node_type_get_types();
  foreach (element_children($form['node_types']) as $node_type) {
  	$row = array();
    if(is_null($node_types[$node_type]->name)){continue;}
    $row[] = $node_types[$node_type]->name;
    $row[] = drupal_render($form['node_types'][$node_type]);
    $row[] = drupal_render($form['node_types'][$node_type.'_update']);
    $row[] = drupal_render($form['node_types'][$node_type.'_passby']);
    $row[] = drupal_render($form['node_types'][$node_type.'_passby_del']);
  	$rows[] = $row;  
  }
  //$rows = array_unique($rows);
  $output = theme('table', array('header' => $header, 'rows' => $rows, 'attributes' => array('id' => 'druedu-redirect')));
  $output .= drupal_render_children($form);

  return $output;
}
/**
 * Check if the given path is valid (exists).
 *
 * @param string $path_alias
 *   the path to be checked.
 *
 * @return boolean
 *   TRUE if the path is valid, false otherwise.
 * @see easy_breadcrumb_validate_path_alias
 */
function validate_path_alias_4druedu($path_alias) {

  // Check if the path is stored in the actual menu router.
  $valid = drupal_valid_path(drupal_get_normal_path($path_alias));

  // If don't exists in the actual menu router, then check if it's an url_alias
  // (was generated by the pathauto module).
  if (empty($valid)) {
    $drupal_path = drupal_lookup_path('source', $path_alias);
    $valid = !empty($drupal_path);
  }

  return $valid;
}