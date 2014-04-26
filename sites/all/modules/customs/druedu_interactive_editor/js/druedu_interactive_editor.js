/**
 * Notes: http://jsfiddle.net/m4ubj/ Get current rotation in degreed
 *
 *
 *
 */

jQuery(function($){


  $(".knob").knob({ 'min':0,'max':360});

  // toolbars
    $('#widget_toolbar').dropshadow();
    $('#widget_toolbar').innershadow();
    $('#widget_toolbar').border();
    $('#widget_toolbar').borderradius();
    $('#widget_toolbar').background();
    $('#widget_toolbar').druedutext();

  // init global color module
  $('select[name="select03"]').simplecolorpicker();

  // delete widget
    $('.widget .delete').click(function(e) {
      $(this).parent().remove();
    });


    $('#saveall').click(function(e) {
      $('#canvas .widget').css('position','absolute');
      $('#canvas .widget .handle').remove();

      var html = $('.canvas_container');
      $(html).find('#grid_checkbox').remove();
      $(html).find('#enlarge_canvas').remove();
      $(html).find('#canvas').css('height', $('#canvas').height() );
      $(html).find('#canvas').css('width', $('#canvas').width() );


      $('#edit-title').val( $('#title').val() );

      $('#edit-body-und-0-value').val( $(html).html() );
      $('#edit-field-keywords-und').val( $('#tags').val() );

    });



    $('#enlarge_canvas').click(function(e) {
      $('#canvas').css('height', parseInt($('#canvas').css('height'))+300 + 'px');
    });

  // add WYSIWYG text editor
    $('#add_toolbar .textarea').wysihtml5();

  // Handle insertion of Video and Images
  $('#widget_toolbar').video_image();

  // Container
    var $div = $('#canvas');


  $("#canvas").on("click", ".widget", function(event){
      // Select widget
      $( this ).toggleClass("selected");

      // hide toolbar
      if($('#canvas .selected').size() == 0){
        $('#widget_toolbar').hide();
        $('#add_toolbar').show();
      }

      // show toolbar
      if($('#canvas .selected').size() > 0){
        $('#widget_toolbar').show();
        $('#add_toolbar').hide();
      }

  $(this).drag("init",function(){
      if ( $( this ).is('.selected') )
        return $('.selected');
    },{ relative:true });

    $(this).drag("start",function( ev, dd ){

      dd.limit = $div.offset();

      dd.limit.bottom = dd.limit.top + $div.outerHeight() - $( this ).outerHeight();
      dd.limit.right = dd.limit.left + $div.outerWidth() - $( this ).outerWidth();


      dd.attr = $( ev.target ).prop("className");
      dd.width = $( this ).width();
      dd.height = $( this ).height();
    },{ relative:true })

    $(this).drag(function( ev, dd ){

      var props = {};
      var handle = false;
      if ( dd.attr.indexOf("EE") > -1 ){
        $( this ).css('-webkit-transform-origin', '0px 0px');
        props.width = Math.max( 32, dd.width + dd.deltaX );
        handle = true;
      }
      if ( dd.attr.indexOf("SS") > -1 ){
        $( this ).css('-webkit-transform-origin', '0px 0px');
        props.height = Math.max( 32, dd.height + dd.deltaY );
        handle = true;

      }
      if ( dd.attr.indexOf("WW") > -1 ){
        $( this ).css('-webkit-transform-origin', 'right bottom');
        props.width = Math.max( 32, dd.width - dd.deltaX );
        props.left = dd.originalX + dd.width - props.width;
        handle = true;

      }
      if ( dd.attr.indexOf("NN") > -1 ){
        $( this ).css('-webkit-transform-origin', 'right bottom');
        props.height = Math.max( 32, dd.height - dd.deltaY );
        props.top = dd.originalY + dd.height - props.height;
        handle = true;
      }

      if ( dd.attr.indexOf("SE") > -1 ){
        $( this ).css('-webkit-transform-origin', 'left top');

        if( $(this).hasClass('keep_aspect') ){
          $(this).css('width', Math.max( 32, dd.width + dd.deltaX ));
          $(this).find('video, img').css('width', Math.max( 32, dd.width + dd.deltaX ));
        }

        handle = true;
      }


      if ( dd.attr.indexOf("rotate") > -1 ){
        handle = true;

        var $this = $(this);
        var offset = $this.offset();

        var center_x = (offset.left) + ($this.outerWidth()/2);
        var center_y = (offset.top) + ($this.outerHeight()/2);
        var mouse_x = ev.clientX;
        var mouse_y = ev.clientY;
        var radians = Math.atan2(mouse_x - center_x, mouse_y - center_y);
        var degree = (radians * (180 / Math.PI) * -1) + 90;

        var last_degree = $this.data('degree');

        var diff = Math.abs( last_degree - degree)

        $this.data('degree', degree);
        $( this ).css('-webkit-transform-origin', '50% 50%');
        $( this ).css('-webkit-transform','rotate(' + degree + 'deg)' );
      }


      if( !handle ){
          if( $('#grid').get(0).checked ) {
            $( this ).css({
              top: Math.min( dd.limit.bottom, Math.max( dd.limit.top, Math.round( dd.offsetY / 20 ) * 20 ) ),
              left: Math.min( dd.limit.right, Math.max( dd.limit.left, Math.round( dd.offsetX / 20 ) * 20 ) )
            });
          }else{
            $( this ).css({
              top: dd.offsetY ,
              left:dd.offsetX
            });
          }
      }

      if ( dd.attr.indexOf("drag") > -1 ){
        props.top = dd.offsetY;
        props.left = dd.offsetX;
      }
      $( this ).css( props );
    });



    })

});
