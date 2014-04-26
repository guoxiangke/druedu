<?php

/**
 * @file
 * Default simple view template to all the fields as a row.
 *
 * - $view: The view in use.
 * - $fields: an array of $field objects. Each one contains:
 *   - $field->content: The output of the field.
 *   - $field->raw: The raw data for the field, if it exists. This is NOT output safe.
 *   - $field->class: The safe class id to use.
 *   - $field->handler: The Views field handler object controlling this field. Do not use
 *     var_export to dump this object, as it can't handle the recursion.
 *   - $field->inline: Whether or not the field should be inline.
 *   - $field->inline_html: either div or span based on the above flag.
 *   - $field->wrapper_prefix: A complete wrapper containing the inline_html to use.
 *   - $field->wrapper_suffix: The closing tag for the wrapper.
 *   - $field->separator: an optional separator that may appear before a field.
 *   - $field->label: The wrap label text to use.
 *   - $field->label_html: The full HTML of the label to use including
 *     configured element type.
 * - $row: The raw result object from the query, with all data it fetched.
 *
 * @ingroup views_templates
 */
/*
Crystal:
$field->content should not contain any markup.
If the variable contains markup, edit the View, go to "FORMAT", "Show:" and click "Settings", and uncheck "Provide default field wrapper elements" to remove all the generated markup for this View.
*/
// echo "<pre>";
// print_r($row);die;
?>
<div class="bulletins" nid="<?php print $row->nid ?>">
	<div class="accordion" id="accordion<?php print $row->nid ?>">
	  <div class="accordion-group">
	    <div class="accordion-heading">
	      <a class="accordion-toggle" data-toggle="collapse" data-parent="#accordion<?php print $row->nid ?>" href="#bulletin<?php print $row->nid ?>">
	        <h3><span class="label label-info"><?php print $row->field_field_date_1['0']['rendered']['#markup'] ?></span><?php print $row->node_title; ?></h3>
	      </a>
	    </div>
			<div id="bulletin<?php print $row->nid ?>" class="accordion-body collapse <?php print $row->class_init_accordion; ?>">
	      <div class="accordion-inner clearfix">
					<?php foreach ($fields as $id => $field): ?>

					  <?php if (!empty($field->separator)): ?>
					    <?php print $field->separator; ?>
					  <?php endif; ?>

					  <?php print $field->wrapper_prefix; ?>
					    <?php print $field->label_html; ?>
					    <?php print $field->content; ?>
					  <?php print $field->wrapper_suffix; ?>
					<?php endforeach; ?>
				</div>
			</div>
		</div>
	</div>
	</div>        