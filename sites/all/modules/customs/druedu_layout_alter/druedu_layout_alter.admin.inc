<?php
function druedu_layout_config_form($form, $form_state) {
	global $base_url;
	$druedu_layout_config = variable_get('druedu_layout_config');
	//Content type
	$node_types = node_type_get_types();
	$form['#prefix'] = t('The settings below are applied depending on the device used to visit the pages:<br/>
<li>on desktop, it is always applied.</li><li>on tablets, the right sidebar is forcefully closed.</li><li>on smaller resolutions (handheld), the 2 bars are closed by default.</li><br/>');
	$form['#prefix'] .= t('Configure the display of the sidebars on page load (Show or Hidden).<br>
		Status Forced : the settings on  this page can not be altered.<br>
		Status User preference : let the user control the display on the preferences in the user profile.<br>');
	$form['nodes'] = array(
		'#type' => 'fieldset',
		'#prefix' => t('<br>Define how the sidebars are displayed for each content type, including the edit form.'),
		'#title' => t('By content type'),
		'#collapsible' => TRUE,
		'#collapsed' => TRUE,
	);
	$form['nodes']['prefixNodeTable'] = array(
		'#markup' => '<table><thead><tr><th>'.t('Content types').'</th><th>'.t('Sidebar Left').'</th><th>'.t('Sidebar Right').'</th><th>'.t('Status').'</th></tr></thead>', 
	);
	foreach ($node_types as $key => $node_type) {
		$form['nodes'][$node_type->type]['name'] = array(
			'#markup' => '<tbody><tr><td>'.$node_type->name.'</td>', 
		);
		$form['nodes']['left_'.$node_type->type] = array(
			'#type' => 'radios', 
  			'#default_value' => (isset($druedu_layout_config['node'][$node_type->type]))? $druedu_layout_config['node'][$node_type->type]['left'] : 0, 
			'#options' => array(t('Hidden'), t('Show')),
			'#prefix' => '<td>',
			'#suffix' => '</td>',
		);
		$form['nodes']['right_'.$node_type->type] = array(
			'#type' => 'radios', 
  			'#default_value' => (isset($druedu_layout_config['node'][$node_type->type]))? $druedu_layout_config['node'][$node_type->type]['right'] : 0,
			'#options' => array(t('Hidden'), t('Show')),
			'#prefix' => '<td>',
			'#suffix' => '</td>',
		);
		$form['nodes']['status_'.$node_type->type] = array(
			'#type' => 'radios', 
  			'#default_value' => (isset($druedu_layout_config['node'][$node_type->type]))? $druedu_layout_config['node'][$node_type->type]['status'] : 0,
			'#options' => array(t('Forced'), t('User preferences')),
			'#prefix' => '<td>',
			'#suffix' => '</td></tr>',
		);
	}
	$form['nodes']['suffixNodeTable'] = array(
		'#markup' => '</tbody></table>', 
	);
	//End Content type
	//Views
	$views = _get_list_views('page');
	$form['views'] = array(
		'#type' => 'fieldset',
		'#title' => t('By View Name/display ID'),
		'#prefix' => t('Define how the sidebars are displayed for each Views with a display type page.'),
		'#collapsible' => TRUE,
		'#collapsed' => TRUE,
	);
	$form['views']['prefixViewsTable'] = array(
		'#markup' => '<table><thead><tr><th>'.t('Views ID / Display name').'</th><th>'.t('Sidebar Left').'</th><th>'.t('Sidebar Right').'</th><th>'.t('Status').'</th></tr></thead>', 
	);
	foreach ($views as $key => $view) {
		$form['views'][$view['name'].'/'.$view['id']]['name'] = array(
			'#markup' => '<tbody><tr><td>'.$view['name'].' / '.$view['id'].'</td>', 
		);
		$form['views']['left_'.$view['name'].'-/-'.$view['id']] = array(
			'#type' => 'radios', 
  			'#default_value' => (isset($druedu_layout_config['views'][$view['name'].'-/-'.$view['id']]))? $druedu_layout_config['views'][$view['name'].'-/-'.$view['id']]['left'] : 0, 
			'#options' => array(t('Hidden'), t('Show')),
			'#prefix' => '<td>',
			'#suffix' => '</td>',
		);
		$form['views']['right_'.$view['name'].'-/-'.$view['id']] = array(
			'#type' => 'radios', 
  			'#default_value' => (isset($druedu_layout_config['views'][$view['name'].'-/-'.$view['id']]))? $druedu_layout_config['views'][$view['name'].'-/-'.$view['id']]['right'] : 0,
			'#options' => array(t('Hidden'), t('Show')),
			'#prefix' => '<td>',
			'#suffix' => '</td>',
		);
		$form['views']['status_'.$view['name'].'-/-'.$view['id']] = array(
			'#type' => 'radios', 
  			'#default_value' => (isset($druedu_layout_config['views'][$view['name'].'-/-'.$view['id']]))? $druedu_layout_config['views'][$view['name'].'-/-'.$view['id']]['status'] : 0,
			'#options' => array(t('Forced'), t('User preferences')),
			'#prefix' => '<td>',
			'#suffix' => '</td></tr>',
		);
	}
	$form['views']['suffixViewsTable'] = array(
		'#markup' => '</table>', 
	);
	//Other Path
	$form['path'] = array(
		'#type' => 'fieldset',
		'#title' => t('Others Path'),
		'#prefix' => t('Define how the sidebars are displayed on a specific Path.').'<br>'.t('For example : questions/my-questions'),
		'#description' => t('Can use wildcard(*) to match a section').'<br>'. t('For example : questions/*'),
		'#collapsible' => TRUE,
		'#collapsed' => TRUE,
	);
	$form['path']['prefixViewsTable'] = array(
		'#markup' => '<table id="pathTable"><thead><tr><th>'.t('Paths').'</th><th>'.t('Sidebar Left').'</th><th>'.t('Sidebar Right').'</th><th>'.t('Status').'</th></tr></thead>', 
	);
	$count_custom_path = 0;
	foreach($druedu_layout_config['path'] as $key => $path) {
		$form['path']['pathUrl_'.$count_custom_path] = array(
			'#type' => 'textfield',
			'#title' => $base_url.'/',
			'#default_value' => (isset($path['path']))? $path['path'] : '',
			'#prefix' => '<tr><td>',
			'#suffix' => '</td>',
		);
		$form['path']['left_path_'.$count_custom_path] = array(
			'#type' => 'radios', 
  			'#default_value' => (isset($druedu_layout_config['path'][$key]))? $druedu_layout_config['path'][$count_custom_path]['left'] : 0, 
			'#options' => array(t('Hidden'), t('Show')),
			'#prefix' => '<td>',
			'#suffix' => '</td>',
		);
		$form['path']['right_path_'.$count_custom_path] = array(
			'#type' => 'radios', 
  			'#default_value' => (isset($druedu_layout_config['path'][$key]))? $druedu_layout_config['path'][$count_custom_path]['right'] : 0,
			'#options' => array(t('Hidden'), t('Show')),
			'#prefix' => '<td>',
			'#suffix' => '</td>',
		);
		$form['path']['status_path_'.$count_custom_path] = array(
			'#type' => 'radios', 
  			'#default_value' => (isset($druedu_layout_config['path'][$key]))? $druedu_layout_config['path'][$count_custom_path]['status'] : 0,
			'#options' => array(t('Forced'), t('User preferences')),
			'#prefix' => '<td>',
			'#suffix' => '</td></tr>',
		);
		$count_custom_path += 1;
	}
	$form['path']['pathUrl_'.$count_custom_path] = array(
			'#type' => 'textfield',
			'#title' => $base_url.'/',
			'#default_value' => '',
			'#prefix' => '<tr><td>',
			'#suffix' => '</td>',
	);
	$form['path']['left_path_'.$count_custom_path] = array(
		'#type' => 'radios', 
  		'#default_value' => 0, 
		'#options' => array(t('Hidden'), t('Show')),
		'#prefix' => '<td>',
		'#suffix' => '</td>',
	);
	$form['path']['right_path_'.$count_custom_path] = array(
		'#type' => 'radios', 
  		'#default_value' => 0,
		'#options' => array(t('Hidden'), t('Show')),
		'#prefix' => '<td>',
		'#suffix' => '</td>',
	);
	$form['path']['status_path_'.$count_custom_path] = array(
		'#type' => 'radios', 
  		'#default_value' => 0,
		'#options' => array(t('Forced'), t('User preferences')),
		'#prefix' => '<td>',
		'#suffix' => '</td></tr>',
	);
	$form['path']['suffixViewsTable'] = array(
		'#markup' => '</table>', 
	);
	// $form['path']['Add'] = array(
	// 	'#type' => 'button',
	// 	'#value' => t('Add More'),
	// 	'#ajax' => array(
	// 		'callback' => 'druedu_layout_admin_add_more_callback',
 //      		'wrapper' => 'pathTable',
	// 		'method' => 'replace',
	// 		'effect' => 'fade',
	// 	),
	// );
	//End Other Path
	//submit button
	$form['submit'] = array(
		'#type' => 'submit',
		'#value' => t('Submit'),
	);
	return $form;
}

// function druedu_layout_admin_add_more_callback(&$form, &$form_state) {
// 	dpm($form_state);
// 	return '';
// }

function druedu_layout_config_form_submit(&$form, &$form_state) {
	foreach ($form_state['values'] as $key => $value) {
		if(strstr($key, 'pathUrl_')) {
			$count_custom_path = str_replace('pathUrl_', '', $key);
			$result['path'][$count_custom_path]['path'] = $value;
			continue;
		}
		if(strstr($key, 'left_')) {
			$name = str_replace('left_', '', $key);
			if(strstr($name, '-/-')) {
				$result['views'][$name]['left'] = $value;
			}
			elseif(strstr($name, 'path_')){
				$count_custom_path = str_replace('left_path_', '', $key);
				$result['path'][$count_custom_path]['left'] = $value;
			}
			else{
				$result['node'][$name]['left'] = $value;
			}
			continue;
		}
		if(strstr($key, 'right_')) {
			$name = str_replace('right_', '', $key);
			if(strstr($name, '-/-')) {
				$result['views'][$name]['right'] = $value;
			}
			elseif(strstr($name, 'path_')){
				$count_custom_path = str_replace('right_path_', '', $key);
				$result['path'][$count_custom_path]['right'] = $value;
			}
			else{
				$result['node'][$name]['right'] = $value;
			}
			continue;
		}
		if(strstr($key, 'status_')) {
			$name = str_replace('status_', '', $key);
			if(strstr($name, '-/-')) {
				$result['views'][$name]['status'] = $value;
			}
			elseif(strstr($name, 'path_')){
				$count_custom_path = str_replace('status_path_', '', $key);
				$result['path'][$count_custom_path]['status'] = $value;
			}
			else{
				$result['node'][$name]['status'] = $value;
			}
			continue;
		}
	}
	//check if path is done
	foreach($result['path'] as $key => $path){
		if(!isset($path['path']) || empty($path['path'])) {
			unset($result['path'][$key]);
		}
	}

	variable_set('druedu_layout_config', $result);
}

function _get_list_views($type = null) {
	$join = db_select('views_display', 'views_display');
	if(!is_null($type)) {
		$join->condition('display_plugin', $type);
	}
	$join->fields('views_display');
	$query = db_select('views_view');
    $query->join($join, 'views_display', 'views_view.vid = views_display.vid');
    $result = $query
      	->fields('views_display', array('id'))
      	->fields('views_view', array('name'))
      	->orderBy('views_display.position ', 'ASC')
      	->execute();
    $array_result = array();
    while($record = $result->fetchAssoc()) {
    	$array_result[] = $record;
  	}
  	return $array_result;
}
