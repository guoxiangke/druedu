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

?>
<div class="container-fluid editing">

  <div class="row-fluid">
    <span class="span9 title">
      <?php print render($form['title']); ?>
    </span>
    <span class="span3">
      <button class="btn btn-primary form-submit" id="edit-submit" name="op" value="Save" type="submit">Save</button>
      <button onclick="history.go(-1); return true;" class="btn form-submit" id="edit-cancel" name="op" value="Cancel" type="button">Cancel</button>
      <a href="#mymedia-modal" role="button" class="btn btn-success" data-toggle="modal"><i class="icon-picture"></i> My Media</a>
    </span>
  </div>

  <div class="row-fluid">

 <span class="span9 form-body">
      <?php if(isset($form) && isset($form['body']) && $form ): ?>
          <?php print render($form['body']); ?>
      <?php endif; ?>

       <ul class="nav nav-tabs">
        <li class="active"><a href="#additional" data-toggle="tab"><?php print t('Additional settings'); ?></a></li>
        <li><a href="#other" data-toggle="tab"><?php print t('Other settings'); ?></a></li>
      </ul>
      <div class="tab-content">
        <div class="tab-pane active" id="additional">
          <?php print render($form['other_settings']); ?>
        </div> 
       <div class="tab-pane" id="other"> 
         <?php print drupal_render_children($form); ?>
        </div> 
      </div>
    </span><!-- span9 -->

    <span class="span3 mymedia">

    </span>

  </div><!-- fluid-row -->
</div><!-- container-fluid -->

<div class="modal hide fade large" id="mymedia-modal" role="dialog" aria-labelledby="myModalLabel" aria-hidden="true">

  <div class="modal-header">
    <button type="button" class="close" data-dismiss="modal" aria-hidden="true">×</button>
    <h3 id="myModalLabel">My Media</h3>
  </div>

  <div class="modal-body">

      <div class="row-fluid">
        <ul class="thumbnails">
          <li class="span2">
            <div class="thumbnail">
              <img src="<?php echo $base_url; ?>/sites/default/files/300x200.gif" >
              <div class="caption">
                <p class="filename">filename.jpg</p>
                <p><a href="#" class="btn btn-primary">Insert</a></p>
              </div>
            </div>
          </li>
          <li class="span2">
            <div class="thumbnail">
              <img src="<?php echo $base_url; ?>/sites/default/files/300x200.gif" >
              <div class="caption">
                <p class="filename">filename.jpg</p>
                <p><a href="#" class="btn btn-primary">Insert</a></p>
              </div>
            </div>
          </li>
          <li class="span2">
            <div class="thumbnail">
              <img src="<?php echo $base_url; ?>/sites/default/files/300x200.gif" >
              <div class="caption">
                <p class="filename">filename.jpg</p>
                <p><a href="#" class="btn btn-primary">Insert</a></p>
              </div>
            </div>
          </li>
          <li class="span2">
            <div class="thumbnail">
              <img src="<?php echo $base_url; ?>/sites/default/files/300x200.gif" >
              <div class="caption">
                <p class="filename">filename.jpg</p>
                <p><a href="#" class="btn btn-primary">Insert</a></p>
              </div>
            </div>
          </li>
          <li class="span2">
            <div class="thumbnail">
              <img src="<?php echo $base_url; ?>/sites/default/files/300x200.gif" >
              <div class="caption">
                <p class="filename">filename.jpg</p>
                <p><a href="#" class="btn btn-primary">Insert</a></p>
              </div>
            </div>
          </li>
          <li class="span2">
            <div class="thumbnail">
              <img src="<?php echo $base_url; ?>/sites/default/files/300x200.gif" >
              <div class="caption">
                <p class="filename">filename.jpg</p>
                <p><a href="#" class="btn btn-primary">Insert</a></p>
              </div>
            </div>
          </li>
          <li class="span2">
            <div class="thumbnail">
              <img src="<?php echo $base_url; ?>/sites/default/files/300x200.gif" >
              <div class="caption">
                <p class="filename">filename.jpg</p>
                <p><a href="#" class="btn btn-primary">Insert</a></p>
              </div>
            </div>
          </li>
          <li class="span2">
            <div class="thumbnail">
              <img src="<?php echo $base_url; ?>/sites/default/files/300x200.gif" >
              <div class="caption">
                <p class="filename">filename.jpg</p>
                <p><a href="#" class="btn btn-primary">Insert</a></p>
              </div>
            </div>
          </li>
          <li class="span2">
            <div class="thumbnail">
              <img src="<?php echo $base_url; ?>/sites/default/files/300x200.gif" >
              <div class="caption">
                <p class="filename">filename.jpg</p>
                <p><a href="#" class="btn btn-primary">Insert</a></p>
              </div>
            </div>
          </li>
          <li class="span2">
            <div class="thumbnail">
              <img src="<?php echo $base_url; ?>/sites/default/files/300x200.gif" >
              <div class="caption">
                <p class="filename">filename.jpg</p>
                <p><a href="#" class="btn btn-primary">Insert</a></p>
              </div>
            </div>
          </li>
          <li class="span2">
            <div class="thumbnail">
              <img src="<?php echo $base_url; ?>/sites/default/files/300x200.gif" >
              <div class="caption">
                <p class="filename">filename.jpg</p>
                <p><a href="#" class="btn btn-primary">Insert</a></p>
              </div>
            </div>
          </li>
          <li class="span2">
            <div class="thumbnail">
              <img src="<?php echo $base_url; ?>/sites/default/files/300x200.gif" >
              <div class="caption">
                <p class="filename">filename.jpg</p>
                <p><a href="#" class="btn btn-primary">Insert</a></p>
              </div>
            </div>
          </li>
          <li class="span2">
            <div class="thumbnail">
              <img src="<?php echo $base_url; ?>/sites/default/files/300x200.gif" >
              <div class="caption">
                <p class="filename">filename.jpg</p>
                <p><a href="#" class="btn btn-primary">Insert</a></p>
              </div>
            </div>
          </li>
          <li class="span2">
            <div class="thumbnail">
              <img src="<?php echo $base_url; ?>/sites/default/files/300x200.gif" >
              <div class="caption">
                <p class="filename">filename.jpg</p>
                <p><a href="#" class="btn btn-primary">Insert</a></p>
              </div>
            </div>
          </li>
          <li class="span2">
            <div class="thumbnail">
              <img src="<?php echo $base_url; ?>/sites/default/files/300x200.gif" >
              <div class="caption">
                <p class="filename">filename.jpg</p>
                <p><a href="#" class="btn btn-primary">Insert</a></p>
              </div>
            </div>
          </li>
          <li class="span2">
            <div class="thumbnail">
              <img src="<?php echo $base_url; ?>/sites/default/files/300x200.gif" >
              <div class="caption">
                <p class="filename">filename.jpg</p>
                <p><a href="#" class="btn btn-primary">Insert</a></p>
              </div>
            </div>
          </li>
          <li class="span2">
            <div class="thumbnail">
              <img src="<?php echo $base_url; ?>/sites/default/files/300x200.gif" >
              <div class="caption">
                <p class="filename">filename.jpg</p>
                <p><a href="#" class="btn btn-primary">Insert</a></p>
              </div>
            </div>
          </li>
          <li class="span2">
            <div class="thumbnail">
              <img src="<?php echo $base_url; ?>/sites/default/files/300x200.gif" >
              <div class="caption">
                <p class="filename">filename.jpg</p>
                <p><a href="#" class="btn btn-primary">Insert</a></p>
              </div>
            </div>
          </li>
          <li class="span2">
            <div class="thumbnail">
              <img src="<?php echo $base_url; ?>/sites/default/files/300x200.gif" >
              <div class="caption">
                <p class="filename">filename.jpg</p>
                <p><a href="#" class="btn btn-primary">Insert</a></p>
              </div>
            </div>
          </li>
          <li class="span2">
            <div class="thumbnail">
              <img src="<?php echo $base_url; ?>/sites/default/files/300x200.gif" >
              <div class="caption">
                <p class="filename">filename.jpg</p>
                <p><a href="#" class="btn btn-primary">Insert</a></p>
              </div>
            </div>
          </li>
          <li class="span2">
            <div class="thumbnail">
              <img src="<?php echo $base_url; ?>/sites/default/files/300x200.gif" >
              <div class="caption">
                <p class="filename">filename.jpg</p>
                <p><a href="#" class="btn btn-primary">Insert</a></p>
              </div>
            </div>
          </li>
          <li class="span2">
            <div class="thumbnail">
              <img src="<?php echo $base_url; ?>/sites/default/files/300x200.gif" >
              <div class="caption">
                <p class="filename">filename.jpg</p>
                <p><a href="#" class="btn btn-primary">Insert</a></p>
              </div>
            </div>
          </li>
        </ul>
      </div><!-- row-fluid -->

  </div><!-- modal-body -->

</div><!-- mymedia-modal -->
