<?php
/** Available variables:
 * $subject_links an array of links to subjects.
 *		Items can be accessed in a raw way by $subject_links['elements'] (nested array).
 *		A rendered array is available in $subject_links['render'], rendered by drupal_render().
 *
 * Note: the following has to be done in a preprocess! Can be done here for dev.
 * Adding classes to the wrapper element: $variable_name['render']['#attributes']['class'][] = 'my_class';
 * To add classes to the children elements, it has to be done during the render array building in the subject.module
 */
?>
<div class="books">
	<div class="inner">
    <?php print drupal_render($subject_links['render']); ?>
  </div>
</div>
