<section class="canvas_container clear-block">
  <div id="grid_checkbox"><label class="checkbox"><input type="checkbox" id="grid"> Grid</label> </div>


  <article id="canvas"></article>
  <button class="btn btn-large btn-block" type="button" id="enlarge_canvas">Enlarge canvas</button>
</section>

<div class="modal hide fade" id="saveModal">
  <div class="modal-header">
    <button type="button" class="close" data-dismiss="modal" aria-hidden="true">&times;</button>
    <h3>Give your creation a title</h3>
  </div>
  <div class="modal-body">
    <p><div class="control-group">
        <label class="control-label" for="title">title</label>
        <div class="controls">
              <input type="text" id="title" placeholder="Title">
        </div>
      </div>
      <div class="control-group">
        <label class="control-label" for="keywords">Keywords</label>
        <div class="controls">
          <input type="text" id="tags" placeholder="Keywords">
          <span class="help-inline">Keyword, Keyword, Keyword, etc</span>
        </div>
  </div>
</p>
  </div>
  <div class="modal-footer">
    <button class="btn" data-dismiss="modal" aria-hidden="true">Close</button>
    <button type="submit" class="btn btn-primary" id="saveall">Save changes</button>
  </div>
</div>



<div id="form-footer">
  <?php if(isset($form) && $form ): ?>
  <?php print drupal_render_children($form); ?>
  <?php endif; ?>
</div>
</div>
