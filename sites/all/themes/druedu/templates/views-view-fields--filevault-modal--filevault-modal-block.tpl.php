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
?>
<?php global $base_url;?>
<?php $json = array(); ?>
<?php $file['id'] = $fields['id']->raw; ?>
<?php $file['filename'] = $fields['filename']->raw; ?>
<?php $file['mime_type'] = $fields['mime_type']->raw; ?>
<?php //dpm($fields); ?>
<?php if(strstr($fields['mime_type']->raw, 'image')) : ?>
      <?php $file['embedded'] = image_style_url('embedded', $fields['uri']->raw); ?>
      <?php $file['url'] = file_create_url($fields['uri']->raw); ?>
      <span class="payload hide">
        <img style="float:left; margin:10px;" src="<?php print $file['embedded']; ?>"/>
      </span>
      <div class="thumbnail">
        <div class="img_container"><img src="<?php print file_create_url($fields['uri']->raw); ?>"></div>
        <div class="caption">
          <p class="filename"><?php print $fields['filename']->content; ?></p>
          <p><button class="btn btn-inverse btn-mini insert"><?php print t('Insert'); ?></button></p>
        </div>
      </div>
<?php elseif(strstr($fields['mime_type']->raw, 'mp4')) : ?>
      <span class="payload">
          <video style="float:left; margin:10px;" width="320" height="240" controls="controls" poster="">
            <source src="<?php print file_create_url($fields['uri']->raw); ?>" type="video/mp4">
            <?php print t('Your browser does not support the video tag.'); ?>
          </video>
      </span>
      <div class="thumbnail">
        <div class="img_container"><img src="<?php print $base_url;?>/sites/default/files/icon-video.png" /></div>
        <div class="caption">
          <p class="filename"><?php print $fields['filename']->content; ?></p>
          <p><button class="btn btn-inverse btn-mini insert"><?php print t('Insert'); ?></button></p>
        </div>
      </div>
      <?php $file['original'] = file_create_url($fields['uri']->raw); ?>
      <?php $file['thumbnail'] = file_create_url($fields['uri']->raw); ?>
 <?php else : ?>
      <span class="payload">
        <a href="<?php print file_create_url($fields['uri']->raw); ?>" class="document" rel="tooltip" title="<?php print $fields['filename']->raw; ?>"><?php print $fields['filename']->content; ?></a>
      </span>
      <div class="thumbnail">
        <div class="img_container"><img src="<?php print $base_url;?>/sites/default/files/icon-file.png" /></div>
        <div class="caption">
          <p class="filename"><?php print $fields['filename']->content; ?></p>
          <p><button class="btn btn-inverse btn-mini insert"><?php print t('Insert'); ?></button></p>
        </div>
      </div>
      <?php $file['thumbnail'] = file_create_url($fields['uri']->raw); ?>
<?php endif; ?>
<?php $json[] = json_encode($file); ?>
<?php drupal_add_js(array('json' => $json), 'setting'); ?>
