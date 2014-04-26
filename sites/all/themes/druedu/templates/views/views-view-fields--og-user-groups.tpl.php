<?php

/**
 * @file
 * Template to all the fields as a row.
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
?>
<?php $class = $fields['group_access_1']->content; ?>
<?php $nid = $fields['nid']->content; ?>
<?php $ajax_link = l(t('UNSUBSCRIBE'), 'groups/'.$nid.'/remove-user/nojs', array('attributes' => array('class' => array('use-ajax')))); ?>
<?php $tooltip = NULL; ?>
<?php $exclude = array('group_access_1', 'nid'); ?>
<?php if($class) $exclude[] = 'nothing'; ?>
<?php 
if(is_numeric($class)) {
	if($class) {$class = 'private'; } else {$class = 'public'; }
}
else {$class = 'subscribe'; }
?>
<li class="<?php print $class . ' ' . $nid; ?> group" <?php print $tooltip; ?>>
<?php foreach ($fields as $id => $field): ?>
  <?php if (!empty($field->separator)): ?>
    <?php print $field->separator; ?>
  <?php endif; ?>
   <?php if(!in_array($id, $exclude)) : ?>
  <?php print $field->wrapper_prefix; ?>
    <?php print $field->label_html; ?>
    <?php print $field->content; ?>
  <?php print $field->wrapper_suffix; ?>
<?php endif; ?>
<?php endforeach; ?>
</li>
