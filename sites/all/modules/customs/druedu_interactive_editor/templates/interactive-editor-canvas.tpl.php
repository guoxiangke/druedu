<section id="canvas_container">
  <article id="canvas"></article>
  <button class="btn btn-mini btn-block" type="button" id="enlarge_canvas">Enlarge canvas</button>
</section>

<script id="ieditor_template_image" type="text/x-dot-template">
  <div class="image widget keep_aspect" style="width:auto;">
    <img src="{{=it.embedded}}">
    <div class="handle SE"></div>
    <div class="handle rotate rotate_NE"></div>
    <div class="handle btn-danger delete"></div>
  </div>
</script>

<script id="ieditor_template_video" type="text/x-dot-template">
  <div class="video widget keep_aspect">
      <video width="320" height="240" controls="controls" poster="{{=it.thumbnail}}" preload="metadata">
        <source src="{{=it.original}}" type="{{=it.minetype}">
        Your browser does not support the video tag.
      </video>
    <div class="handle SE"></div>
    <div class="handle rotate rotate_NE"></div>
    <div class="handle btn-danger delete"></div>
  </div>
</script>

<script id="ieditor_template_document" type="text/x-dot-template">
        <img src="{{=it.thumbnail}}">
</script>

<script id="ieditor_template_text" type="text/x-dot-template">
  <div class="text widget" style="width:400px">
    {{=it.text}}
    <div class="handle NN"></div>
    <div class="handle WW"></div>
    <div class="handle EE"></div>
    <div class="handle SS"></div>
    <div class="handle btn-danger delete"></div>
    <div class="handle rotate rotate_NE"></div>
  </div>
</script>
