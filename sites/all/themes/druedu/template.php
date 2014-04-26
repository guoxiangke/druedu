<?php
/**
* @file
* Contains the theme's functions to manipulate Drupal's default markup.
*
* A QUICK OVERVIEW OF DRUPAL THEMING
*
*   The default HTML for all of Drupal's markup is specified by its modules.
*   For example, the comment.module provides the default HTML markup and CSS
*   styling that is wrapped around each comment. Fortunately, each piece of
*   markup can optionally be overridden by the theme.
*
*   Drupal deals with each chunk of content using a "theme hook". The raw
*   content is placed in PHP variables and passed through the theme hook, which
*   can either be a template file (which you should already be familiary with)
*   or a theme function. For example, the "comment" theme hook is implemented
*   with a comment.tpl.php template file, but the "breadcrumb" theme hooks is
*   implemented with a theme_breadcrumb() theme function. Regardless if the
*   theme hook uses a template file or theme function, the template or function
*   does the same kind of work; it takes the PHP variables passed to it and
*   wraps the raw content with the desired HTML markup.
*
*   Most theme hooks are implemented with template files. Theme hooks that use
*   theme functions do so for performance reasons - theme_field() is faster
*   than a field.tpl.php - or for legacy reasons - theme_breadcrumb() has "been
*   that way forever."
*
*   The variables used by theme functions or template files come from a handful
*   of sources:
*   - the contents of other theme hooks that have already been rendered into
*     HTML. For example, the HTML from theme_breadcrumb() is put into the
*     $breadcrumb variable of the page.tpl.php template file.
*   - raw data provided directly by a module (often pulled from a database)
*   - a "render element" provided directly by a module. A render element is a
*     nested PHP array which contains both content and meta data with hints on
*     how the content should be rendered. If a variable in a template file is a
*     render element, it needs to be rendered with the render() function and
*     then printed using:
*       <?php print render($variable); ?>
*
* ABOUT THE TEMPLATE.PHP FILE
*
*   The template.php file is one of the most useful files when creating or
*   modifying Drupal themes. With this file you can do three things:
*   - Modify any theme hooks variables or add your own variables, using
*     preprocess or process functions.
*   - Override any theme function. That is, replace a module's default theme
*     function with one you write.
*   - Call hook_*_alter() functions which allow you to alter various parts of
*     Drupal's internals, including the render elements in forms. The most
*     useful of which include hook_form_alter(), hook_form_FORM_ID_alter(),
*     and hook_page_alter(). See api.drupal.org for more information about
*     _alter functions.
*
* OVERRIDING THEME FUNCTIONS
*
*   If a theme hook uses a theme function, Drupal will use the default theme
*   function unless your theme overrides it. To override a theme function, you
*   have to first find the theme function that generates the output. (The
*   api.drupal.org website is a good place to find which file contains which
*   function.) Then you can copy the original function in its entirety and
*   paste it in this template.php file, changing the prefix from theme_ to
*   druedu_. For example:
*
*     original, found in modules/field/field.module: theme_field()
*     theme override, found in template.php: druedu_field()
*
*   where druedu is the name of your sub-theme. For example, the
*   zen_classic theme would define a zen_classic_field() function.
*
*   Note that base themes can also override theme functions. And those
*   overrides will be used by sub-themes unless the sub-theme chooses to
*   override again.
*
*   Zen core only overrides one theme function. If you wish to override it, you
*   should first look at how Zen core implements this function:
*     theme_breadcrumbs()      in zen/template.php
*
*   For more information, please visit the sessionveloper's Guide on
*   Drupal.org: http://drupal.org/node/173880
*
* CREATE OR MODIFY VARIABLES FOR YOUR THEME
*
*   Each tpl.php template file has several variables which hold various pieces
*   of content. You can modify those variables (or add new ones) before they
*   are used in the template files by using preprocess functions.
*
*   This makes THEME_preprocess_HOOK() functions the most powerful functions
*   available to themers.
*
*   It works by having one preprocess function for each template file or its
*   derivatives (called theme hook suggestions). For example:
*     THEME_preprocess_page    alters the variables for page.tpl.php
*     THEME_preprocess_node    alters the variables for node.tpl.php or
*                              for node--forum.tpl.php
*     THEME_preprocess_comment alters the variables for comment.tpl.php
*     THEME_preprocess_block   alters the variables for block.tpl.php
*
*   For more information on preprocess functions and theme hook suggestions,
*   please visit the Theme Developer's Guide on Drupal.org:
*   http://drupal.org/node/223440 and http://drupal.org/node/1089656
*/

/**
* Implements hook_theme().
*/


/**
* Override or insert variables into the maintenance page template.
*
* @param $variables
*   An array of variables to pass to the theme template.
* @param $hook
*   The name of the template being rendered ("maintenance_page" in this case.)
*/
/* -- Delete this line if you want to use this function
function druedu_preprocess_maintenance_page(&$variables, $hook) {
// When a variable is manipulated or added in preprocess_html or
// preprocess_page, that same work is probably needed for the maintenance page
// as well, so we can just re-use those functions to do that work here.
druedu_preprocess_html($variables, $hook);
druedu_preprocess_page($variables, $hook);
}
// */

// /**
// * Implementation of a per grid view preprocess
// */
// function druedu_preprocess_views_view_grid(&$vars) {
// 	if (isset($vars['view']->name)) {
// 		$function = __FUNCTION__ . '__' . $vars['view']->name . '__' . $vars['view']->current_display;
//
// 		if (function_exists($function)) {
// 			$function($vars);
// 		}
// 	}
// }
//
// /**
// * Then the specific preprocess for a grid view
// */
// function druedu_preprocess_views_view_grid__og_user_groups__user_group_list(&$vars) {
//
// }

/**
* Override or insert variables into the html templates.
*
* @param $variables
*   An array of variables to pass to the theme template.
* @param $hook
*   The name of the template being rendered ("html" in this case.)
*/
/* -- Delete this line if you want to use this function
function druedu_preprocess_html(&$variables, $hook) {
$variables['sample_variable'] = t('Lorem ipsum.');

// The body tag's classes are controlled by the $classes_array variable. To
// remove a class from $classes_array, use array_diff().
//$variables['classes_array'] = array_diff($variables['classes_array'], array('class-to-remove'));
}
// */
/*
function druedu_preprocess_page(&$variables, $hook) {

  // Load the easy breadcrumb block
  $block = module_invoke('easy_breadcrumb', 'block_view', 'easy_breadcrumb');
  $variables['easy_breadcrumb'] = render($block);

  //HACK UPLOAD
  global $user;
  $_SESSION['uid'] = $user->uid;

  setcookie("uid", $user->uid);

}*/

function druedu_preprocess_node(&$variables, $hook) {
  if (isset($variables['node'])) {
  // If the node type is "blog" the template suggestion will be "page--blog.tpl.php".
   $variables['theme_hook_suggestions'][] = 'node__'. str_replace('_', '-', $variables['node']->type);
  }
  if (isset($variables['content']) && isset($variables['content']['links']) && isset($variables['content']['links']['comment'])) {
  	unset($variables['content']['links']['comment']);
  }
}

/**
* Override or insert variables into the node templates.
*
* @param $variables
*   An array of variables to pass to the theme template.
* @param $hook
*   The name of the template being rendered ("node" in this case.)
*/
/* -- Delete this line if you want to use this function

function druedu_preprocess_node(&$variables, $hook) {
$variables['sample_variable'] = t('Lorem ipsum.');


// Optionally, run node-type-specific preprocess functions, like
// druedu_preprocess_node_page() or druedu_preprocess_node_story().
$function = __FUNCTION__ . '_' . $variables['node']->type;
if (function_exists($function)) {
$function($variables, $hook);
}
}
// */

/**
* Override or insert variables into the comment templates.
*
* @param $variables
*   An array of variables to pass to the theme template.
* @param $hook
*   The name of the template being rendered ("comment" in this case.)
*/
/* -- Delete this line if you want to use this function
function druedu_preprocess_comment(&$variables, $hook) {
$variables['sample_variable'] = t('Lorem ipsum.');
}
// */

/**
* Override or insert variables into the region templates.
*
* @param $variables
*   An array of variables to pass to the theme template.
* @param $hook
*   The name of the template being rendered ("region" in this case.)
*/

function druedu_preprocess_region(&$variables, $hook) {
  if ($variables['region'] == 'sidebar_right' || $variables['region'] == 'sidebar_left') {
    $args = arg();
    $is_front = drupal_is_front_page();
    if($args[0] == 'user' || $args[0] == 'groups' || $is_front) {
      $variables['sidebarRight'] = 'show';   
      $variables['sidebarLeft'] = 'show';   
    }
    else {
      $sidebars_layout = _druedu_layout_alter_sidebars();
      if($variables['region'] == 'sidebar_right') {
        $variables['sidebarRight'] = ($sidebars_layout['right']) ? 'show' : 'hide'; 
      }
      if($variables['region'] == 'sidebar_left') {
        $variables['sidebarLeft'] = ($sidebars_layout['left']) ? 'show' : 'hide'; 
      }
    }
  }
}

/**
* Override or insert variables into the block templates.
*
* @param $variables
*   An array of variables to pass to the theme template.
* @param $hook
*   The name of the template being rendered ("block" in this case.)
*/
/* -- Delete this line if you want to use this function
function druedu_preprocess_block(&$variables, $hook) {
// Add a count to all the blocks in the region.
// $variables['classes_array'][] = 'count-' . $variables['block_id'];

// By default, Zen will use the block--no-wrapper.tpl.php for the main
// content. This optional bit of code undoes that:
//if ($variables['block_html_id'] == 'block-system-main') {
//  $variables['theme_hook_suggestions'] = array_diff($variables['theme_hook_suggestions'], array('block__no_wrapper'));
//}
}
// */

/**
* Override or insert variables into the page templates.
*
* @param $variables
*   An array of variables to pass to the theme template.
* @param $hook
*   The name of the template being rendered ("page" in this case.)
*/

function druedu_preprocess_page(&$variables, $hook) {
  global $base_url, $user;
  $full_path = $base_url.'/'.current_path();

  drupal_add_js(array('current_url' => $full_path), 'setting');

  if(isset($variables['node'])) {
    $variables['theme_hook_suggestions'][] = 'page__'.$variables['node']->type;
  }
	// Load the easy breadcrumb block
	$block = module_invoke('easy_breadcrumb', 'block_view', 'easy_breadcrumb');
	$variables['easy_breadcrumb'] = render($block);

	$variables['sidebar_right'] = block_get_blocks_by_region('sidebar_right');

  	// User menu
  	$variables['secondary_nav'] = FALSE;
  	if($variables['secondary_menu']) {
    $secondary_menu = menu_load(variable_get('menu_secondary_links_source', 'user-menu'));
    // Build links
    $tree = menu_tree_page_data($secondary_menu['menu_name']);
    $variables['secondary_menu'] = twitter_bootstrap_menu_navigation_links($tree);

    //#431: Change the use menu to give friendly url like "/profile/admin" instead of "/user"
    foreach ($variables['secondary_menu'] as $key => $value) {
      if($value['href'] == 'user') {
        global $user;
        $variables['secondary_menu'][$key]['href'] = 'user/'.$user->uid;
        //$variables['secondary_menu'][$key]['link_path'] = 'user/'.$user->uid;
      }
    }

    // Build list
    $variables['secondary_nav'] = theme('twitter_bootstrap_btn_dropdown', array(
      'links' => $variables['secondary_menu'],
      'label' => $secondary_menu['title'],
      'type' => 'inverse', // Default white style "btn"
      'attributes' => array(
        'id' => 'user-menu',
        'class' => array('pull-right'),
      ),
      'heading' => array(
        'text' => t('Secondary menu'),
        'level' => 'h2',
        'class' => array('element-invisible'),
      ),
    ));
  }

   // Menu jumper for grades and groups located on the top bar
    if($user->uid != 0) {
      $og_groups_nav = array();
      //get all grades of the current user
      $grades = _get_groups_by_user_and_node_type(NULL, 'grade');
      if(sizeof($grades)) {
        $og_groups_nav['my_grades'] = array(
            'title' => t('My Grades') ,
            'attributes' => array('class' => array('level-0')),
        );
        foreach ($grades as $nid => $grade) {
          $og_groups_nav['grade-nav-'.$nid] = array(
            'title' => $grade,
            'href' => 'node/'.$nid,
            'link_path' => 'node/'.$nid,
            'attributes' => array('class' => array('level-1')),
          );
        }
      }
      //get all groups of the current user
      $groups = _get_groups_by_user_and_node_type(NULL, 'group');
      if(sizeof($groups)) {
        $og_groups_nav['my_groups'] = array(
            'title' => t('My Groups') ,
            'attributes' => array('class' => array('level-0')),
        );
        foreach ($groups as $nid => $group) {
          $og_groups_nav['group-nav-'.$nid] = array(
            'title' => $group,
            'href' => 'node/'.$nid,
            'link_path' => 'node/'.$nid,
            'attributes' => array('class' => array('level-1')),
          );
        }
      }
      if(sizeof($og_groups_nav) > 2) {
       // Build list
        $variables['grades_nav'] = theme('twitter_bootstrap_btn_dropdown', array(
          'links' => $og_groups_nav,
          'label' => NULL,
          'type' => 'inverse', // Default white style "btn"
          'attributes' => array(
            'id' => 'grade-menu',
            'class' => array('pull-right'),
          ),
          'heading' => array(
            'text' => t('Grade menu'),
            'level' => 'h2',
            'class' => array('element-invisible'),
          ),
        ));
      }
      else {
        // Build current grade/group context info
        $variables['grades_nav'] = '<div id="grade-menu" class="pull-right info">'._druedu_image_and_title_og_groups('user_menu_profile').'</div>';
      }
    }
  //page level id for specific theme
  //use case:if you have a page like this: http://example.com/mypage,
  //and you want add a css ID on that page:<div id="mypage">..</div>,
  //you can push the "mypage" to $specific_pages.
  $specific_pages = array();
  $specific_pages[]='questions';
  $specific_pages[]='question';
  foreach ($specific_pages as $value){
    if(arg(0)==$value){
        if($value =='question'){
            $variables['page_id'] = 'questions';
        }else{
            $variables['page_id'] = $value;
        }
       
    }
  }
  $sidebars_layout = _druedu_layout_alter_sidebars();
  $variables['sidebarRight'] = $sidebars_layout['right']; 
  $variables['sidebarLeft'] = $sidebars_layout['left']; 
}

/**
* Implements hook_js_alter().
*
* This function swap out jQuery to use an updated version of the library.
*/
function druedu_js_alter(&$javascript) {
	$javascript['misc/jquery.js']['data'] = drupal_get_path('theme', 'druedu').'/js/jquery.js';
  if(isset($javascript['misc/jquery.form.js'])) {
    $javascript['misc/jquery.form.js']['data'] = drupal_get_path('theme', 'druedu').'/js/jquery.form.js';
  }
}

/**
* Implements hook_css_alter().
*
* This function swap out jQuery UI to use a bootstraped version of the library.
*/
function druedu_css_alter(&$css) {
  if (isset($css['misc/ui/jquery.ui.theme.css'])) {
    $css['misc/ui/jquery.ui.theme.css']['data'] = drupal_get_path('theme', 'druedu') . 'css/jquery.ui.theme.css';
  }
}


/**
* Returns HTML for a menu link and submenu - Add names of links to the class in the menu
*
* @param $variables
*   An associative array containing:
*   - element: Structured array data for a menu link.
*
* @ingroup themeable
*/
function druedu_menu_link(array $variables) {

	$element = $variables['element'];
	$sub_menu = '';
	// Sanitize title
	$element['#title'] = check_plain($element['#title']);

	// Add title to class
	$element['#attributes']['class'][] = "primary_menu_".filter_var(strtolower($element['#title']), FILTER_SANITIZE_STRING, FILTER_FLAG_STRIP_LOW.FILTER_FLAG_STRIP_HIGH);

//@TODO What is it for?
	if ($element['#below']) {
		// Ad our own wrapper
		unset($element['#below']['#theme_wrappers']);
		$sub_menu = '<ul>' . drupal_render($element['#below']) . '</ul>';
		$element['#localized_options']['html'] = TRUE;
		$element['#href'] = "";
	}

	$output = l($element['#title'], $element['#href'], $element['#localized_options']);

	return '<li' . drupal_attributes($element['#attributes']) . '>' . $output . $sub_menu . "</li>\n";
}

/**
* Returns HTML for a menu link and submenu - Theme the links of the main menu
*
* @param $variables
*   An associative array containing:
*   - element: Structured array data for a menu link.
*
* @ingroup themeable
*/
function druedu_menu_link__main_menu($variables) {

	$element = $variables['element'];

	//If the element has an "active-trail" class, add the "active" class to it and its link
	if(in_array('active-trail', $element['#attributes']['class']) && !in_array('active', $element['#attributes']['class'])) {
		$element['#attributes']['class'][] = 'active';
	}

	// If the link of an element has the active class, add an active-trail class, and also add them to the element itself
	if(isset($element['#localized_options']['attributes']['class']) && in_array('active', $element['#localized_options']['attributes']['class'])) {
		$element['#localized_options']['attributes']['class'][] = "active-trail";
		$element['#attributes']['class'][] = 'active';
		$element['#attributes']['class'][] = "active-trail";
	}
	// Sanitize title
	$element['#title'] = check_plain($element['#title']);
	$icon = '<i class="icon-'. filter_var(strtolower($element['#title']), FILTER_SANITIZE_STRING, FILTER_FLAG_STRIP_LOW.FILTER_FLAG_STRIP_HIGH) .'"></i> ';
	$element['#localized_options']['html'] = TRUE;
	$output = l($icon. ' ' .$element['#title'], $element['#href'], $element['#localized_options']);
	return '<li' . drupal_attributes($element['#attributes']) . '>' . $output . "</li>\n";
}

/**
* Returns HTML for a menu - Theme the wrapper of the main menu
*
* @param $variables
*   An associative array
*
* @ingroup themeable
*/
function druedu_menu_tree__main_menu($variables){
    return "<ul class=\"nav nav-list\">\n" . $variables['tree'] ."</ul>\n";
}


/**
* theme_twitter_bootstrap_btn_dropdown
*/
function druedu_twitter_bootstrap_btn_dropdown($variables) {
	$type_class = '';

	// Type class
	if(isset($variables['type']))
		$type_class = ' btn-'. $variables['type'];

	// Start markup
	$output = '<div'. drupal_attributes($variables['attributes']) .'>';

	// Ad as string if its not a link
	if(is_array($variables['label'])) {
		$output .= l($variables['label']['title'], $variables['label']['href'], $variables['label']);
	}

	$output .= '<a class="btn'. $type_class .' dropdown-toggle" data-toggle="dropdown" href="#">';


	// If user profile display the user image and name
	if($variables['attributes']['id'] == "user-menu" ) {
		global $user;
		$user_fields = user_load($user->uid);

		//Array of field names that compose a full name, in order.
		$fields_names = array('field_firstname','field_lastname');
		$full_name = array();
		//Good, foreach keeps the order!
		foreach($fields_names as $field_name) {
			$field_array = field_get_items('user', $user_fields, $field_name);
			if(!empty($field_array) && isset($field_array[0]['safe_value'])) {
				$full_name[] = $field_array[0]['safe_value'];
			}
		}
    $style = 'user_menu_profile';
    $styled_profile_image = (!empty($user_fields->picture)) ? theme('image_style', array('style_name' => $style, 'path' => $user_fields->picture->uri)) : theme('image_style', array('style_name' => $style, 'path' => variable_get('user_picture_default')));
		$output .=  $styled_profile_image.'<span class="username">'.implode($full_name,' ').'</span>';

	} 
    // If user profile display the user image and name
  elseif($variables['attributes']['id'] == "grade-menu" ) {
    $output .= _druedu_image_and_title_og_groups('user_menu_profile');
  } 
  else {
		// Its a link so create one
		if(is_string($variables['label'])) {
			$output .= check_plain($variables['label']);
		}
	}

	// Finish markup
	$output .= '
		<span class="caret"></span>
	</a>
	' . $variables['links'] . '
		</div>';

	return $output;
}

function druedu_search_form($form, &$form_state) {

	$form = search_form($form, $form_state);

	return $form;
}

/**
* Theme function for the breadcrumb.
*
* @param Assoc $variables
*   arguments
*
* @return string
*   HTML for the themed breadcrumb.
*/
function druedu_easy_breadcrumb($variables) {

  $breadcrumb = $variables['breadcrumb'];
  $segments_quantity = $variables['segments_quantity'];
  $separator = $variables['separator'];

  $html = '';

  if ($segments_quantity > 0) {
    $html .= '<ul class="breadcrumb">';
    for ($i = 0, $s = $segments_quantity - 1; $i < $segments_quantity; ++$i) {
      $html .= ($i == 0) ? '<li><i class="icon-home"></i></li>' : null;
      if($i == $s) {
      	if(strstr($breadcrumb[$i], t('Edit'))) {
      		$breadcrumb[$i] = '<em>' . t('Edit') . '</em>';
      	}
      	else {
      		$pattern = "/<span ?.*>(.*)<\/span>/";
		    preg_match($pattern, $breadcrumb[$i], $str);
		    if(isset($str[1]) && strlen($str[1]) > 70) {
		      	$breadcrumb[$i] = '<span>'.substr($str[1], 0, 70).'...</span>';
		    }
      	}
      }
      $html .= '<li>' . $breadcrumb[$i] . '</li>';
      if ($i < $s) {
        $html .= '<li class="divider"><i class="icon-chevron-right"></i></li>';
      }
    }
    $html .= '</ul>';
  }
  return $html;
}

/**
 * Convenience function for outputting an array including it's line number & file
 *
 * @return void
 */
function pr($var = false, $showHtml = false, $showFrom = true) {
  if ($showFrom) {
    $calledFrom = debug_backtrace();
    echo '<strong>' . substr(str_replace(ROOT, '', $calledFrom[0]['file']), 1) . '</strong>';
    echo ' (line <strong>' . $calledFrom[0]['line'] . '</strong>)';
  }
  echo "\n<pre>\n";

  $var = print_r($var, true);
  if ($showHtml) {
    $var = str_replace('<', '&lt;', str_replace('>', '&gt;', $var));
  }
  echo $var . "\n</pre>\n";
}

function druedu_preprocess_user_profile(&$variables) {
	if($variables['elements']['#view_mode'] == 'full') {
		//remove displayed of user picture on user page
		unset($variables['elements']['user_picture']);
		unset($variables['user_profile']['user_picture']);
	}
}
/**
 * _form_BASE_FORM_ID_alter
 */
function druedu_form_user_profile_form_alter(&$form, &$from_state, $form_id) {
  global $user;

  $form['actions']['submit']['#value'] = t('Save Profile');

  $form['account']['#type'] = 'fieldset';
  $form['account']['#title'] =  '<i class="icon-cog"></i>'.t('Account informations');
  $form['account']['#collapsible'] = TRUE;
  $form['account']['#collapsed'] = TRUE; 

  $form['timezone']['#collapsed'] = TRUE;
  $form['timezone']['#title'] = '<i class="icon-time"></i>'.$form['timezone']['#title'];  
  $special_case = array('field_firstname' , 'field_lastname', 'field_title');
  foreach($form as $key => $field) {
    if(is_array($field) && (strstr($key,'field_') || strstr($key, 'group_')) && !in_array($key , $special_case)) {
      ($form[$key][$field['#language']]['#required']) ? $required = '  <span class="summary">('.t('Field required').')</span>' : $required = '';
      $form[$key]['#type'] = 'fieldset';
      $form[$key]['#title'] =  $form[$key][LANGUAGE_NONE]['#title']. $required;
      $form[$key]['#collapsible'] = TRUE;
      $form[$key]['#collapsed'] = TRUE;
      if(isset($form[$key][LANGUAGE_NONE][0]['#title'])) $form[$key][LANGUAGE_NONE][0]['#title'] = NULL;
      if(isset($form[$key][LANGUAGE_NONE]['#title'])) $form[$key][LANGUAGE_NONE]['#title'] = NULL;
      if(isset($form[$key][LANGUAGE_NONE][0]['value']['#title'])) $form[$key][LANGUAGE_NONE][0]['value']['#title'] = NULL;

      //ADD icon on title
      $form[$key]['#title'] = '<i class="icon-pencil icon-'.$key.'"></i>'.$form[$key]['#title'];

    }
  }

  if($user->uid != 1) {
    $form['account']['pass']['#prefix'] = '<div class="hide">';
    $form['account']['pass']['#suffix'] = '</div>';
    $form['og_user_group_ref']['#access'] = FALSE;
    $form['account']['current_pass']['#access'] = FALSE;
    $form['timezone']['#access'] = FALSE;
    $form['field_firstname']['#disabled'] = TRUE;
     $form['field_lastname']['#disabled'] = TRUE;
  }

  //user edit page default pic process
  $account = $form['#user'];
  if(is_null($account->picture)){
     $filepath = variable_get('user_picture_default', '');
    if (module_exists('image') && file_valid_uri($filepath) && $style = variable_get('user_picture_style', '')) {
      $temp['user_picture'] = theme('image_style', array('style_name' => $style, 'path' => $filepath, 'alt' => $alt, 'title' => $alt));
    }
    else {
      $temp['user_picture'] = theme('image', array('path' => $filepath, 'alt' => $alt, 'title' => $alt));
    }
    $attributes = array('attributes' => array('title' => $account->name.t('\'s pictures')), 'html' => TRUE);
    $temp['user_picture'] = l($temp['user_picture'], "user/$account->uid", $attributes);
    $form['picture']['picture_current'] = array(
      '#prefix' => '<div class="user-picture">',
      '#suffix' => '</div>',
      '#markup' => $temp['user_picture'],
    );
  }
  $form['picture']['#type'] = 'fieldset';
  $form['picture']['#title'] =  '<i class="icon-picture"></i>'.t('Picture');
  $form['picture']['#collapsible'] = TRUE;
  $form['picture']['#collapsed'] = TRUE;

  foreach ($special_case as $key) {
    $form['account'][$key] = $form[$key];
    unset($form[$key]);
  }
}

/**
 * Processes variables for book-navigation.tpl.php.
 *
 * The $variables array contains the following elements:
 * - book_link
 *
 * @see book-navigation.tpl.php
 */
function druedu_preprocess_book_navigation(&$variables) {
  $book_link = $variables['book_link'];

  // Provide extra variables for themers. Not needed by default.
  $variables['book_id'] = $book_link['bid'];
  $variables['book_title'] = check_plain($book_link['link_title']);
  $variables['book_url'] = 'node/' . $book_link['bid'];
  $variables['current_depth'] = $book_link['depth'];

  if ($book_link['mlid']) {

    if ($prev = book_prev($book_link)) {
      $prev_href = url($prev['href']);
      drupal_add_html_head_link(array('rel' => 'prev', 'href' => $prev_href));
      $variables['prev_url'] = $prev_href;
      $variables['prev_title'] = check_plain($prev['title']);
    }

    if ($book_link['plid'] && $parent = book_link_load($book_link['plid'])) {
      $parent_href = url($parent['href']);
      drupal_add_html_head_link(array('rel' => 'up', 'href' => $parent_href));
      $variables['parent_url'] = $parent_href;
      $variables['parent_title'] = check_plain($parent['title']);
    }

    if ($next = book_next($book_link)) {
      $next_href = url($next['href']);
      drupal_add_html_head_link(array('rel' => 'next', 'href' => $next_href));
      $variables['next_url'] = $next_href;
      $variables['next_title'] = check_plain($next['title']);
    }
  }

  $variables['has_links'] = FALSE;
  // Link variables to filter for values and set state of the flag variable.
  $links = array('prev_url', 'prev_title', 'parent_url', 'parent_title', 'next_url', 'next_title');
  foreach ($links as $link) {
    if (isset($variables[$link])) {
      // Flag when there is a value.
      $variables['has_links'] = TRUE;
    }
    else {
      // Set empty to prevent notices.
      $variables[$link] = '';
    }
  }
}

/**
 * Ovveride function of twitter_bootstrap theme to returns HTML for a button form element.
 */
function druedu_button($variables) {
  $element = $variables['element'];
  $label = $element['#value'];
  element_set_attributes($element, array('id', 'name', 'value', 'type'));

  $element['#attributes']['class'][] = 'form-' . $element['#button_type'];
  if (!empty($element['#attributes']['disabled'])) {
    $element['#attributes']['class'][] = 'form-button-disabled';
  }

  return '<button' . drupal_attributes($element['#attributes']) . '>'. $label .'</button>
  '; // This line break adds inherent margin between multiple buttons
}

/**
 * Implements hook_preprocess_comment().
 */
function druedu_preprocess_comment(&$variables) {
  // Change the comments time format for all sites with druedu_slashed_date_time.
  $comment = $variables['comment'];
  $variables['created'] = format_date($comment->created,'druedu_slashed_date_time');
  $variables['submitted'] = t('Submitted by !username on !datetime', array('!username' => $variables['author'], '!datetime' => $variables['created']));  
}

/**
 * Preprocess function for the yesno template.
 * @see rate_preprocess_rate_template_yesno
 */
function druedu_preprocess_rate_template_yesno(&$variables) {
  extract($variables);

  $buttons = array();
  foreach ($links as $link) {
    $button = theme('rate_button', array('text' => $link['text'], 'href' => $link['href'], 'class' => 'rate-yesno-btn'));
    $button .= $link['votes'];
    $buttons[] = $button;
  }
  $variables['buttons'] = $buttons;

  $info = array();
  if ($mode == RATE_CLOSED) {
    $info[] = t('Voting is closed.');
  }
  if ($mode != RATE_COMPACT && $mode != RATE_COMPACT_DISABLED) {
    if (isset($results['user_vote'])) {
      $info[] = t('Useful? You said \'@option\'!', array('@option' => t($results['user_vote'])));
    }
  }
  $variables['info'] = implode(' ', $info);
}

/**
 * Preprocess function for views template  (view level)
 */
function druedu_preprocess_views_view_unformatted(&$vars) {
  $view = $vars['view'];
  if($view->name == 'og_user_heartbeat_activity' && $view->display_id = 'home_feed') {
    $group = og_context();
    $vars['group'] = node_load($group['gid']);
  }
}

/**
 * A preprocess function for our theme('flag'). It generates the
 * variables needed there.
 *
 * The $variables array initially contains the following arguments:
 * - $flag
 * - $action
 * - $content_id
 * - $after_flagging
 *
 * See 'flag.tpl.php' for their documentation.
 */
function druedu_preprocess_flag(&$variables) {
  $variables['flag_classes_array'][] = 'btn';
  $variables['flag_classes_array'][] = 'btn-mini';
  $variables['flag_classes_array'][] = 'btn-primary';
  $variables['flag_classes'] .= ' btn btn-mini btn-primary';
} 

/*
* Helper function to set image and title of the current group.
*/
function _druedu_image_and_title_og_groups($image_cache, $nid = NULL, $array = FALSE) {
    if(empty($nid)){
      $nid = $_SESSION['og_context']['gid'];
    }
    $current_group_node = node_load($nid);
    $current_group_title = $current_group_node->title;
    $group_display = field_info_instance('node', 'field_group_picture', $current_group_node->type);
    if(empty($current_group_node->field_group_picture)) {
      if($group_display['settings']['default_image'] != 0) {
        $default_image = file_load($group_display['settings']['default_image']);
        $group_image[0] = (array) $default_image;
      }
      else {
        if($array) {
          return array('title' => $current_group_title, 'image' => array());
        }
        return '<span class="current_grade">'.$current_group_title.'</span>';
      }
    }
    else {
      $group_image = field_get_items('node', $current_group_node, 'field_group_picture');
    }
    $output_group_image = field_view_value('node', $current_group_node, 'field_group_picture', $group_image[0], array(
        'type' => 'image',
        'settings' => array(
          'image_style' => $image_cache,
        ),
    ));
    if($array) {
      return array('title' => $current_group_title, 'image' => $output_group_image);
    }
    return drupal_render($output_group_image).'<span class="current_grade">'.$current_group_title.'</span>';
}

