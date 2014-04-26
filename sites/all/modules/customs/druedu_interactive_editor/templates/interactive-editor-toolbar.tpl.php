
<!-- Interactive editor toolbar -->
<div class="row-fluid" id="druedu_interactive_editor_toolbar">
  <div class="span12 add_content">

    <!-- nav tabs -->
    <ul class="nav nav-tabs">
      <li class="active"><a href="#text" data-toggle="tab">Text</a></li>
      <li><a href="#dropshadow" data-toggle="tab">Drop Shadow</a></li>
      <li><a href="#background" data-toggle="tab">Background</a></li>
      <li><a href="#border" data-toggle="tab">Border</a></li>
      <li><a href="#borderradius" data-toggle="tab">Border Radius</a></li>
      <li><a href="#maps" data-toggle="tab">Maps</a></li>
      <li><a href="#graphs" data-toggle="tab">Graphs</a></li>
    </ul>

    <!-- nav tabs content -->
    <div class="tab-content">
      <!-- add text -->
      <div class="tab-pane" id="text">
        <div class="wysiwyg">
          <textarea class="textarea" placeholder="Enter text ..." style="width:95%; height: 60px"></textarea>
        </div>
        <button class="btn btn-success" type="button" id="addtext"><i class="icon-plus icon-white"></i>Add text...</button>
      </div>

      <!-- Maps tab -->
      <div class="tab-pane" id="maps">
        <p>Coming soon</p>
      </div>

      <!-- Graphs tab -->
      <div class="tab-pane" id="graphs">
        <p>Coming soon</p>
      </div>

      <div class="tab-pane active" id="dropshadow">
        <div id="dropshadow_container">
          <section id="controls1">

            <label>Opacity:</label>
            <div class="layout-slider">
              <input id="opacity" type="slider" name="opacity" value="0" />
            </div>

            <label>Distance:</label>
            <div class="layout-slider">
              <input id="distance" type="slider" name="distance" value="0" />
            </div>
          </section>

          <section id="controls2">

            <label>Blur:</label>
            <div class="layout-slider">
              <input id="blur" type="slider" name="blur" value="0" />
            </div>

            <label>Size:</label>
            <div class="layout-slider">
              <input id="size" type="slider" name="size" value="0" />
            </div>
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

<!--
          <section id="light_position">
            <label class="checkbox"><input type="checkbox">Global Light </label>
            <div class="knob_container">
              <input class="knob" data-width="100" data-cursor=true data-fgColor="#222222" data-thickness=.3 value="29" data-min="0" data-max="360">
            </div>
          </section>
-->
      </div><!-- dropshadow_container end -->
    </div>


    <!-- tab-pane end -->
    <div class="tab-pane" id="innershadow">
      <div id="innershadow_container">
        <section id="controls1">

          <label>Opacity:</label>
          <div class="layout-slider">
            <input id="opacity" type="slider" name="opacity" value="0" />
          </div>

          <label>Distance:</label>
          <div class="layout-slider">
            <input id="distance" type="slider" name="distance" value="0" />
          </div>

        </section>

        <section id="controls2">

          <label>Blur:</label>
          <div class="layout-slider">
            <input id="blur" type="slider" name="blur" value="0" />
          </div>

          <label>Size:</label>
          <div class="layout-slider">
            <input id="size" type="slider" name="size" value="0" />
          </div>

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
            <input class="knob" data-width="100" data-cursor=true data-fgColor="#222222" data-thickness=.3 value="29" data-min="0" data-max="360">
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
          <div class="layout-slider">
            <input id="opacity" type="slider" name="opacity" value="0" />
          </div>

          <label>Size:</label>
          <div class="layout-slider">
            <input id="size" type="slider" name="size" value="0" />
          </div>

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
          <div class="layout-slider">
            <input id="radius" type="slider" name="radius" value="0" />
          </div>

          <div class="btn-group" data-toggle="buttons-radio">
            <button type="button" class="btn" id="px">px</button>
            <button type="button" class="btn" id="percent">%</button>
          </div>

        </section>

        <section id="corners">
          <div class="cornersborder" id="NW"></div>
          <div class="cornersborder" id="NE"></div>
          <div class="cornersborder" id="SE"></div>
          <div class="cornersborder" id="SW"></div>
        </section>

      </div>
    </div>
  </div>
  <!-- tab-content end -->
</div>
<!-- widget_toolbar end -->

</div>

