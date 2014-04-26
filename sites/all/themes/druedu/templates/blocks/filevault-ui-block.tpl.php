<div id="filevault_ui_block" class="inner">

  <h2>
    <a href="#filevault-modal" role="button" class="btn btn-info btn-mini" data-toggle="modal" id="big-media">
      <i class="icon-fullscreen"></i> Fullscreen
    </a> My file vault
  </h2>

  <div class="progress progress-info progress-striped" id="progress_all" style="display: none;">
    <div class="bar" style="width: 0%;"></div>
  </div>

  <div class="dropzone">
    <p>Drag'n'drop to upload files <br /> or click here to choose a file</p>
  </div>

  <div class="filelist">
    <!-- <button class="btn btn-mini disabled" type="button" id="prev">Prev</button>
    <button class="btn btn-mini" type="button" id="next">Next</button> -->
    <p class="help">Click on a file to insert it</p>
    <ul class="files"></ul>
  </div>

  <script id="filevault_block_template_image" type="text/x-dot-template">
    <li>
      <span class="payload">
          <img src="{{=it.embedded}}" style="float:left; margin:10px;"/>
      </span>
      <a href="{{=it.thumbnail}}" class="thumbnail hover-info image" rel="tooltip" title="{{=it.fullname}}">
        <img src="{{=it.thumbnail}}" />
        <span class="filename">{{=it.filename}}</span>
      </a>
    </li>
  </script>

  <script id="filevault_block_template_video" type="text/x-dot-template">
    <li>
      <span class="payload">
          <p style="height:0px; margin:0; padding:0;">&nbsp;</p>
          <div>
            <video width="480" height="320" controls="controls" style="margin:10px;"><source src="{{=it.original}}" type="video/mp4"></video>
          </div>
          <p style="height:0px; margin:0; padding:0;">&nbsp;</p>

      </span>
      <a href="{{=it.filename}}" class="thumbnail hover-info video" rel="tooltip" title="{{=it.fullname}}">
        <img src="/sites/default/files/icon-video.png" />
        <span class="filename">{{=it.filename}}</span>
      </a>
    </li>
  </script>

  <script id="filevault_block_template_document" type="text/x-dot-template">
    <li>
      <span class="payload">
        <a href="{{=it.original}}" class="document" rel="tooltip" title="{{=it.fullname}}">{{=it.fullname}}</a>
      </span>
      <a href="{{=it.filename}}" class="thumbnail hover-info document" rel="tooltip" title="{{=it.fullname}}">
        <img src="/sites/default/files/icon-file.png" />
        <span class="filename">{{=it.filename}}</span>
      </a>
    </li>
  </script>

</div>
