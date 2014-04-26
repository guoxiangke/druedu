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
            <?php if(isset($form['field_date'])) : ?>
            <div class="date"><?php print render($form['field_date']); ?></div>
            <?php endif; ?>
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

     

    </span><!-- span9 -->
    <span class="span3">
      <div id="sidebar-media">
        <?php print render(block_get_blocks_by_region('edit_form_sidebar_right')); ?>
      </div>
    </span>

  </div><!-- fluid-row -->
</div><!-- container-fluid -->

<script type="text/javascript">
jQuery(document).ready(function($) {
  window.btn_clicked = false;
  $('.btn').click(function(event) {
    window.btn_clicked = true;
  });
  // Let's not leave accidently now
  $(window).bind('beforeunload', function() {
    if (!window.btn_clicked) {
      return 'Are you sure you want to leave?';
    }
  });
});
</script>
