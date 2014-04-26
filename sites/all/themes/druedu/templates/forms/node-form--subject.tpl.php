<?php
/**
 * @file
 * Theme implementation to display a node form.
 *
 * Use dpm($form); Outputs the form variable for inspection.
 * General principle to alter classes: access $form['field_name']['#attributes']['class'];
 * Example - add a classe to a field wrapper: $form['body']['#attributes']['class'][] = 'my_class';
 * Please place the class alteration at the beginning of this template - eventually,
 * they will belong to druedu_layer_alter_preprocess_node_form()
 *
 * Actions moved to druedu_layout_module.
 *
 * @see druedu_layer_alter_preprocess_node_form()
 *
 */
?>
<div class="container-fluid editing">

  <div class="row-fluid">
    <span class="span12">
      <table class="first">
        <tr>
          <td>
            <div class="title"><?php print render($form['title']); ?></div>
          </td>
          <td class="actions"><?php print render($form['actions']); ?></td>
        </tr>
      </table>
    </span>
  </div>

  <div class="row-fluid">
    <span class="span9 form-body">
      <?php if(isset($form) && isset($form['body']) && $form ): ?>
          <?php print render($form['body']); ?>
      <?php endif; ?>
      <?php if(isset($form) && isset($form['field_attachments']) && $form ): ?>
          <?php print render($form['field_attachments']); ?>
      <?php endif; ?>
       <? if(!$variables['form']['other_settings']['#empty'] && !$variables['form']['other_settings_plus']['#empty']) : ?>
       <ul class="nav nav-tabs">
        <li class="active"><a href="#additional" data-toggle="tab"><?php print t('Additional settings'); ?></a></li>
        <li><a href="#other" data-toggle="tab"><?php print t('Other settings'); ?></a></li>
      </ul>
       <?php endif; ?>
      <div class="tab-content">
        <? if(!$variables['form']['other_settings']['#empty']) : ?>
        <div class="tab-pane active" id="additional">
          <?php print render($form['other_settings']); ?>
        </div> 
        <?php endif; ?>
        <? if(!$variables['form']['other_settings_plus']['#empty']) : ?>
       <div class="tab-pane" id="other"> 
         <?php print drupal_render_children($form); ?>
        </div> 
        <?php else: ?>
          <?php print drupal_render_children($form); ?>
        <?php endif; ?>
      </div>

    </span><!-- span9 -->
    <span class="span3">
       <?php if(isset($form) && !isset($form['field_attachments']) && $form ): ?>
      <div id="sidebar-media">
        <?php $temp = block_get_blocks_by_region('edit_form_sidebar_right'); print render($temp); ?>
      </div>
       <?php endif; ?>
    </span>

  </div><!-- fluid-row -->
</div><!-- container-fluid -->