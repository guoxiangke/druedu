<section id="filevault_core_block" class="block">

  <?php print render($filevault_form); ?>

  <script id="filevault_core_template_image" type="text/x-dot-template">
    <img src="{{=it.embedded}}" style="float:left; margin:10px;"/>
  </script>

  <script id="filevault_core_template_video" type="text/x-dot-template">
    <video height="240px" width="320px" controls="controls" style="float:left; margin:10px;">
      <source src="{{=it.original}}" type="video/mp4">
      Your browser does not support the video tag.
    </video>
  </script>

  <script id="filevault_core_template_document" type="text/x-dot-template">
    <a href="{{=it.original}}" class="document" rel="tooltip" title="{{=it.filename}}">{{=it.filename}}</a>
  </script>

</section>
