<?php
/*
Available variables :
$content_information : 	all fields from the node are grouped into this variables.
						Only fields not display on the main region (middle) are availables.
						Can be render field by field using render($content_information['my_field'])
						Or can be display in one time using render($content_information) (not recommended).

$authoring_info :		All informations about the node authoring. (keys: user object, date created, date updated, published date, status)

use <?php dpm($variable_name); ?> function to explore the variables.

*/
?>
<aside id="<?php print $block_html_id; ?>" class="<?php print $classes; ?> contextual-content" <?php print $attributes; ?>>
  <div class="inner">
    <h2 class="title"><i class="icon-bolt"></i><?php print t('Meta content'); ?></h2>
    <?php print render($title_prefix); ?>
    <?php if ($title): ?>
      <h2<?php print $title_attributes; ?>><?php print $title; ?></h2>
    <?php endif;?>
    <?php print render($title_suffix); ?>
    <?php print render($content_information); ?>
  </div>
</aside>
