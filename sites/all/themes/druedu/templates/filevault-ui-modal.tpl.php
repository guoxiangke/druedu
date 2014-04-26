<div class="modal hide fade large" id="filevault-modal" role="dialog" aria-labelledby="filevaultLabel" aria-hidden="true">

  <div class="modal-header">
    <button type="button" class="close" data-dismiss="modal" aria-hidden="true">×</button>
    <h3 id="filevaultLabel">My Media</h3><i class="modal-refresh icon-refresh"><?php print t('Refresh'); ?></i>
  </div>

  <div class="modal-body">
      <div class="row-fluid">
        <div class="modal-filelist">
            <?php print views_embed_view('filevault_modal', 'filevault_modal_block'); ?>
        </div>
      </div><!-- row-fluid -->
  </div><!-- modal-body -->

</div><!-- filevault-modal -->
<!--
  <script id="filevault_modal_template_image" type="text/x-dot-template">
    <li class="image">
      <span class="payload">
          <img src="{{=it.embedded}}">
      </span>
      <div class="thumbnail">
        <img src="{{=it.thumbnail}}">
        <div class="caption">
          <p class="filename">{{=it.filename}}</p>
          <p><a href="#" class="btn btn-inverse btn-mini insert">Insert</a></p>
        </div>
      </div>
    </li>
  </script>

  <script id="filevault_modal_template_video" type="text/x-dot-template">
    <li class="video">
      <span class="payload">
          <video controls="controls" poster="">
            <source src="{{=it.original}}" type="video/mp4">
            Your browser does not support the video tag.
          </video>
      </span>
      <div class="thumbnail">
        <img src="/sites/default/files/icon-video.png" />
        <div class="caption">
          <p class="filename">{{=it.filename}}</p>
          <p><a href="#" class="btn btn-inverse btn-mini insert">Insert</a></p>
        </div>
      </div>
    </li>
  </script>

  <script id="filevault_modal_template_document" type="text/x-dot-template">
    <li class="file">
      <span class="payload">
        <a href="{{=it.original}}" class="document" rel="tooltip" title="{{=it.filename}}">{{=it.filename}}</a>
      </span>
      <div class="thumbnail">
        <img src="/sites/default/files/icon-file.png" />
        <div class="caption">
          <p class="filename">{{=it.filename}}</p>
          <p><a href="#" class="btn btn-inverse btn-mini insert">Insert</a></p>
        </div>
      </div>
    </li>
  </script>
-->

