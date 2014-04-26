<?php hide($params['actions']); ?>
<?php $options['class'] = (isset($options['class'])) ? $options['class'] : ''; ?>
<div class="modal fade <?php print $options['class']; ?>" id="validationDelete-modal" role="dialog" aria-labelledby="validationLabel" aria-hidden="false">
      <form class="confirmation" action="<?php print $params['#action'];?>" method="post" id="<?php print $params['#id'];?>" accept-charset="UTF-8">
            <div class="modal-header">
                  <button type="button" class="close" data-dismiss="modal" aria-hidden="true">×</button>
                  <h3 id="validationLabel"><?php if(isset($options['label'])) { print $options['label']; } else { print t('Are you sure?'); } ?></h3>
            </div><!-- modal-header --> 
            <div class="modal-body"><?php print drupal_render_children($params);?></div><!-- modal-body -->
            <div class="modal-footer"><?php $temp = show($params['actions']); print drupal_render($temp);?></div><!-- modal-body -->
      </form>
</div>