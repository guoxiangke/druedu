<section class="canvas_container clear-block">

<div id="add_toolbar">
  <ul class="nav nav-tabs">
    <li class="active"><a href="#media" data-toggle="tab">Media</a></li>
    <li><a href="#upload" data-toggle="tab">Upload</a></li>
    <li><a href="#text" data-toggle="tab">Text</a></li>
  </ul>

  <div class="tab-content">
    <div class="tab-pane active" id="text">
    </div>
    <div class="tab-pane active" id="media">
       <?php print views_embed_view("my_media"); ?>
    </div>
    <div class="tab-pane active" id="upload">
       <?php
              $block = module_invoke('jquery_file_upload','block_view', 'jquery_file_uploader');
              print render($block);

       ?>
    </div>
  </div>
</div>

<div id="widget_toolbar">

  <ul class="nav nav-tabs">
    <li class="active"><a href="#dropshadow" data-toggle="tab">Drop Shadow</a></li>
    <li><a href="#innershadow" data-toggle="tab">Inner Shadow</a></li>
    <li><a href="#background" data-toggle="tab">Background</a></li>
    <li><a href="#border" data-toggle="tab">Border</a></li>
    <li><a href="#borderradius" data-toggle="tab">Border Radius</a></li>
  </ul>

  <div class="tab-content">
    <div class="tab-pane active" id="dropshadow">
      <div id="dropshadow_container">

        <section id="controls1">
          <label>Opacity:</label>
          <input class="slider" type="number" name="opacity" min="0" max="10" value="0" id="opacity">
          <label>Distance:</label>
          <input class="slider" type="number" name="distance" min="0" max="20" value="0" id="distance">
        </section>

        <section id="controls2">
          <label>Blur:</label>
          <input class="slider" type="number" name="blur" min="0" max="30" value="0" id="blur">
          <label>Size:</label>
          <input class="slider" type="number" name="size" min="0" max="40" value="0" id="size">
        </section>

        <section id="color_picker">
          <select name="select03">
            <option value="#000000" selected="selected">#000000</option>
            <option value="#ffffff">#ffffff</option>
            <option value="#ac725e">#ac725e</option>
            <option value="#d06b64">#d06b64</option>
            <option value="#f83a22">#f83a22</option>
            <option value="#fa573c">#fa573c</option>
            <option value="#ff7537">#ff7537</option>
            <option value="#ffad46">#ffad46</option>
            <option value="#42d692">#42d692</option>
            <option value="#16a765">#16a765</option>
            <option value="#7bd148">#7bd148</option>
            <option value="#b3dc6c">#b3dc6c</option>
            <option value="#fbe983">#fbe983</option>
            <option value="#fad165">#fad165</option>
            <option value="#92e1c0">#92e1c0</option>
            <option value="#9fe1e7">#9fe1e7</option>
            <option value="#9fc6e7">#9fc6e7</option>
            <option value="#4986e7">#4986e7</option>
            <option value="#9a9cff">#9a9cff</option>
            <option value="#b99aff">#b99aff</option>
            <option value="#c2c2c2">#c2c2c2</option>
            <option value="#cabdbf">#cabdbf</option>
            <option value="#cca6ac">#cca6ac</option>
            <option value="#f691b2">#f691b2</option>
            <option value="#cd74e6">#cd74e6</option>
            <option value="#a47ae2">#a47ae2</option>
          </select>
        </section>

        <section id="light_position">
          <label class="checkbox"><input type="checkbox">Global Light </label>
          <div class="knob_container">
            <input class="knob" data-width="100" data-cursor=true data-fgColor="#222222" data-thickness=.3 value="29" data-min="0"
data-max="360">
          </div>
        </section>

      </div><!-- dropshadow_container end -->
    </div><!-- tab-pane end -->
    <div class="tab-pane" id="innershadow">
      <div id="innershadow_container">

        <section id="controls1">
          <label>Opacity:</label>
          <input class="slider" type="number" name="opacity" min="0" max="1" value="1" id="opacity">
          <label>Distance:</label>
          <input class="slider" type="number" name="distance" min="0" max="50" value="0" id="distance">
        </section>

        <section id="controls2">
          <label>Blur:</label>
          <input class="slider" type="number" name="blur" min="0" max="50" value="0" id="blur">
          <label>Size:</label>
          <input class="slider" type="number" name="size" min="0" max="50" value="0" id="size">
        </section>

        <section id="color_picker">
          <select name="select03">
            <option value="#000000" selected="selected">#000000</option>
            <option value="#ffffff">#ffffff</option>
            <option value="#ac725e">#ac725e</option>
            <option value="#d06b64">#d06b64</option>
            <option value="#f83a22">#f83a22</option>
            <option value="#fa573c">#fa573c</option>
            <option value="#ff7537">#ff7537</option>
            <option value="#ffad46">#ffad46</option>
            <option value="#42d692">#42d692</option>
            <option value="#16a765">#16a765</option>
            <option value="#7bd148">#7bd148</option>
            <option value="#b3dc6c">#b3dc6c</option>
            <option value="#fbe983">#fbe983</option>
            <option value="#fad165">#fad165</option>
            <option value="#92e1c0">#92e1c0</option>
            <option value="#9fe1e7">#9fe1e7</option>
            <option value="#9fc6e7">#9fc6e7</option>
            <option value="#4986e7">#4986e7</option>
            <option value="#9a9cff">#9a9cff</option>
            <option value="#b99aff">#b99aff</option>
            <option value="#c2c2c2">#c2c2c2</option>
            <option value="#cabdbf">#cabdbf</option>
            <option value="#cca6ac">#cca6ac</option>
            <option value="#f691b2">#f691b2</option>
            <option value="#cd74e6">#cd74e6</option>
            <option value="#a47ae2">#a47ae2</option>
          </select>
        </section>

        <section id="light_position">
          <label class="checkbox"><input type="checkbox">Global Light </label>
          <div class="knob_container">
            <input class="knob" data-width="100" data-cursor=true data-fgColor="#222222" data-thickness=.3 value="29" data-min="0"
data-max="360">
          </div>
        </section>
      </div>
    </div>

    <div class="tab-pane" id="background">
      <div id="background_container">

        <section id="color_picker">
          <select name="select03">
            <option value="#000000" selected="selected">#000000</option>
            <option value="#ffffff">#ffffff</option>
            <option value="#ac725e">#ac725e</option>
            <option value="#d06b64">#d06b64</option>
            <option value="#f83a22">#f83a22</option>
            <option value="#fa573c">#fa573c</option>
            <option value="#ff7537">#ff7537</option>
            <option value="#ffad46">#ffad46</option>
            <option value="#42d692">#42d692</option>
            <option value="#16a765">#16a765</option>
            <option value="#7bd148">#7bd148</option>
            <option value="#b3dc6c">#b3dc6c</option>
            <option value="#fbe983">#fbe983</option>
            <option value="#fad165">#fad165</option>
            <option value="#92e1c0">#92e1c0</option>
            <option value="#9fe1e7">#9fe1e7</option>
            <option value="#9fc6e7">#9fc6e7</option>
            <option value="#4986e7">#4986e7</option>
            <option value="#9a9cff">#9a9cff</option>
            <option value="#b99aff">#b99aff</option>
            <option value="#c2c2c2">#c2c2c2</option>
            <option value="#cabdbf">#cabdbf</option>
            <option value="#cca6ac">#cca6ac</option>
            <option value="#f691b2">#f691b2</option>
            <option value="#cd74e6">#cd74e6</option>
            <option value="#a47ae2">#a47ae2</option>
          </select>
        </section>

      </div>
    </div>

    <div class="tab-pane" id="border">
      <div id="border_container">
        <section id="controls2">
          <label>Opacity:</label>
          <input class="slider" type="number" name="blur" min="0" max="50" value="0" id="opacity">
          <label>Size:</label>
          <input class="slider" type="number" name="size" min="0" max="50" value="0" id="size">
        </section>

        <section id="color_picker">
          <select name="select03">
            <option value="#000000" selected="selected">#000000</option>
            <option value="#ffffff">#ffffff</option>
            <option value="#ac725e">#ac725e</option>
            <option value="#d06b64">#d06b64</option>
            <option value="#f83a22">#f83a22</option>
            <option value="#fa573c">#fa573c</option>
            <option value="#ff7537">#ff7537</option>
            <option value="#ffad46">#ffad46</option>
            <option value="#42d692">#42d692</option>
            <option value="#16a765">#16a765</option>
            <option value="#7bd148">#7bd148</option>
            <option value="#b3dc6c">#b3dc6c</option>
            <option value="#fbe983">#fbe983</option>
            <option value="#fad165">#fad165</option>
            <option value="#92e1c0">#92e1c0</option>
            <option value="#9fe1e7">#9fe1e7</option>
            <option value="#9fc6e7">#9fc6e7</option>
            <option value="#4986e7">#4986e7</option>
            <option value="#9a9cff">#9a9cff</option>
            <option value="#b99aff">#b99aff</option>
            <option value="#c2c2c2">#c2c2c2</option>
            <option value="#cabdbf">#cabdbf</option>
            <option value="#cca6ac">#cca6ac</option>
            <option value="#f691b2">#f691b2</option>
            <option value="#cd74e6">#cd74e6</option>
            <option value="#a47ae2">#a47ae2</option>
          </select>
        </section>

        <section id="border_style">
          <div id="broderstyle_container">
            <div id="solid" class="broderstyle" style="border:#333333 1px solid"></div>
            <div id="dashed" class="broderstyle" style="border:#333333 1px dashed"></div>
            <div id="dotted" class="broderstyle" style="border:#333333 1px dotted"></div>
            <div id="double" class="broderstyle" style="border:#333333 1px double"></div>
            <div id="groove" class="broderstyle" style="border:#333333 1px groove"></div>
            <div id="inset" class="broderstyle" style="border:#333333 1px inset"></div>
            <div id="outset" class="broderstyle" style="border:#333333 1px outset"></div>
            <div id="ridge" class="broderstyle" style="border:#333333 1px ridge"></div>
          </div>
        </section>
        </div>
      </div>

    <div class="tab-pane" id="borderradius">
      <div id="borderradius_container">
        <section id="controls2">
          <label>Radius:</label>
          <input class="slider" type="number" name="radius" min="0" max="50" id="radius">
        </section>

        <section id="corners">
          <div class="cornersborder" id="NW"></div>
          <div class="cornersborder" id="NE"></div>
          <div class="cornersborder" id="SE"></div>
          <div class="cornersborder" id="SW"></div>
        </section>
      </div>
    </div>
  </div><!-- tab-content end -->
  </div><!-- widget_toolbar end -->


  <article id="canvas">
    <div class="image widget" id="W2">
      <div class="handle NE"></div>
      <div class="handle NN"></div>
      <div class="handle NW"></div>
      <div class="handle WW"></div>
      <div class="handle EE"></div>
      <div class="handle SW"></div>
      <div class="handle SS"></div>
      <div class="handle SE"></div>
      <div class="handle rotate rotate_NE"></div>
    </div>

    <div class="movie widget" id="W3">
      <div class="handle NE"></div>
      <div class="handle NN"></div>
      <div class="handle NW"></div>
      <div class="handle WW"></div>
      <div class="handle EE"></div>
      <div class="handle SW"></div>
      <div class="handle SS"></div>
      <div class="handle SE"></div>
      <div class="handle rotate rotate_NE"></div>
    </div>
  </article>
</section>


<div id="form-footer">
  <?php if(isset($form) && $form ): ?>
  <?php print drupal_render_children($form); ?>
  <?php endif; ?>
</div>
</div>
