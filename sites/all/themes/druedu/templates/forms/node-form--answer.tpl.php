<?php
/**
* @file
* Theme implementation to display a node form.
*
* @see druedu_layer_alter_preprocess_node_form()
*/
//HELP
//Use dpm($form); Outputs the form variable for inspection.
//General principle to alter classes: access $form['field_name']['#attributes']['class'];
//Example - add a classe to a field wrapper: $form['body']['#attributes']['class'][] = 'my_class';
//Please place the class alteration at the beginning of this template - eventually, they will belong to druedu_layer_alter_preprocess_node_form()
// global $base_url;
// dpm($form,__LINE__.__FILE__);
// hide($form['field_subjects_groups_audience']);
// $form['title']['#attributes']['placeholder'] = "Subject name";
?>

<div class="container-fluid editing">
	<div class="row-fluid">
		<?php print drupal_render_children($form); ?>
	</div><!-- fluid-row -->
</div><!-- container-fluid -->