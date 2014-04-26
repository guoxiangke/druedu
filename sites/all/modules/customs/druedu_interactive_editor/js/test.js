
jQuery(function($){

    $('#toggle_i_editor').toggleButtons({
        width: 200,
        label: {
            enabled: "Interactive",
            disabled: "Standard"
        },
        onChange: function ($el, status, e) {

            if(status){
              $('.druedu_interactive').show();
              $('.canvas_container').show();
              $(".filter-wrapper .filter-list").val("pure").change();
              window.druedu_interactive = true;

              //if there is content from the standard editor, put it in a text widget

              if( $('#edit-body-und-0-value').val().indexOf('<article id="canvas"') == -1 ){

                var footer = '<div class="handle NN"></div><div class="handle WW"></div><div class="handle EE"></div><div class="handle SS"></div><div class="handle btn-danger delete"></div><div class="handle rotate rotate_NE"></div>';
                var widget =  $('<div class="text widget">');
                var text = $('#edit-body-und-0-value').val();
                widget.append(text);
                widget.append(footer);

                $(widget).find('.delete').click(function(e) {
                  $(this).parent().remove();
                });

                $(widget).css('width',500);

                widget.appendTo( $('#canvas') );

                $('.field-name-body').hide();
              }



            }else {
              $('.field-name-body').show();

              $('.druedu_interactive').hide();
              $('.canvas_container').hide();
              $(".filter-wrapper .filter-list").val("full_html").change();
              window.druedu_interactive = false;
            }
        }
    });

  // remove padding from the iframe
  $("iframe").contents().find("body").css('padding-top','0px');


  $(".knob").knob({ 'min':0,'max':360});

  // toolbars
  $('.druedu_interactive').dropshadow();
  $('.druedu_interactive').innershadow();
  $('.druedu_interactive').border();
  $('.druedu_interactive').borderradius();
  $('.druedu_interactive').background();
  $('.druedu_interactive').druedutext();
  $('.druedu_interactive').video_image();

  // init global color module
  $('select[name="select03"]').simplecolorpicker();

  // delete widget
  $('.widget .delete').click(function(e) {
      $(this).parent().remove();
  });

  // Enlarge canvas
  $('#enlarge_canvas').click(function(e) {
      $('#canvas').css('height', parseInt($('#canvas').css('height'))+300 + 'px');
  });

  // add WYSIWYG text editor
  $('.add_content .textarea').wysihtml5();

  // Save button
  $('#edit-submit').click(function(e) {
    
    // If the interactive editor is in use, copy the HTML to the textarea
    if(window.druedu_interactive){

      $('#canvas .widget').css('position','absolute');
      $('#canvas').css('position','relative');
      $('#canvas .widget .handle').remove();

      var html = $('.canvas_container');
      $(html).find('#grid_checkbox').remove();
      $(html).find('#enlarge_canvas').remove();
      $(html).find('#canvas').css('height', $('#canvas').height() );
      $(html).find('#canvas').css('width', '100%' );
      $('#edit-body-und-0-value').val( $(html).html() );

    }
  });


  if( $('#edit-body-und-0-value').val().indexOf('<article id="canvas"') > -1 ){ 

      $('.druedu_interactive').show();
      $('.canvas_container').show();
      $(".filter-wrapper .filter-list").val("pure").change();
      window.druedu_interactive = true;

      var footer_text = '<div class="handle NN"></div><div class="handle WW"></div><div class="handle EE"></div><div class="handle SS"></div><div class="handle btn-danger delete"></div><div class="handle rotate rotate_NE"></div>';
      var footer_media = '<div class="handle SE"></div><div class="handle rotate rotate_NE"></div><div class="handle btn-danger delete"></div>';

      var html = $('#edit-body-und-0-value').val();
      $('#canvas').css('height', $(html).find('#canvas').height() );

      $(html).find('.movie_widget').append(footer_media);
      $(html).find('.image_widget').append(footer_media);
      $(html).find('.text_widget').append(footer_text);
      var widgets = $(html).children();

      $('#canvas').html(widgets);
  }


});