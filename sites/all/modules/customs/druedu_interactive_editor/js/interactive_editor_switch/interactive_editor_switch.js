// Global Interactive Flag
var interactive_editor_enabled = false;

jQuery(function($){

  $('#advanced_editor_switch').click(function(e) {

    interactive_editor_enabled = true;

    $('.widget .delete').on('click',function(e){
          $(this).parent().remove();
    });


    // Diable the wysiwyg and hide the text area
    for(var i in CKEDITOR.instances) {

        Drupal.myWysiwygControl.detach(CKEDITOR.instances[i].name);
        $('#'+i).hide();
        // Insert the canvas after the title
        $('.node-form .body').prepend( $('#canvas_container') );

        // Insert the toolbar
        $('.node-form .body').prepend( $('#druedu_interactive_editor_toolbar') );

        //druedu_interactive_editor_edit_widget
        $('.node-form .body').prepend( $('#druedu_interactive_editor_edit_widget') );


        $('#druedu_interactive_editor_toolbar').dropshadow();
        $('#druedu_interactive_editor_toolbar').border();
        $('#druedu_interactive_editor_toolbar').borderradius();
        $('#druedu_interactive_editor_toolbar').background();
        $('#druedu_interactive_editor_toolbar').druedutext();
        $('select[name="select03"]').simplecolorpicker();


        if( $('#edit-body-und-0-value').val().indexOf('<article id="canvas"') == -1 ){

                var footer = '<div class="handle NN"></div><div class="handle WW"></div><div class="handle EE"></div><div class="handle SS"></div><div class="handle btn-danger delete"></div><div class="handle rotate rotate_NE"></div>';
                var widget =  $('<div class="text widget">');
                var text = $('#edit-body-und-0-value').val();
                widget.append(text);
                widget.append(footer);

                $('.widget').find('.delete').click(function(e) {
                  $(this).parent().remove();
                });

                $(widget).css('width',500);

                widget.appendTo( $('#canvas') );

                $('.field-name-body').hide();
        }

        $('.widget .delete').on('click',function(e){
          $(this).parent().remove();
        });

        // add WYSIWYG text editor
        $('.add_content .textarea').wysihtml5();

        // Save button
        $('#edit-submit').click(function(e) {

        // If the interactive editor is in use, copy the HTML to the textarea
          if(interactive_editor_enabled){

            $('#canvas .widget').css('position','absolute');
            $('#canvas').css('position','relative');
            $('#canvas .widget .handle').remove();

            var html = $('#canvas_container');
            $(html).find('#enlarge_canvas').remove();
            $(html).find('#canvas').css('height', $('#canvas').height() );
            $(html).find('#canvas').css('width', '100%' );
            $('#edit-body-und-0-value').val( $(html).html() );

          }
        }); }
  });

  if( $('#edit-body-und-0-value').val().indexOf('<article id="canvas"') > -1 ){

     if (typeof CKEDITOR == 'object') {
      CKEDITOR.on('instanceReady', function(e) {

        for(var i in CKEDITOR.instances) {
          Drupal.myWysiwygControl.detach(CKEDITOR.instances[i].name);
          $('#'+i).hide();
        }
      });
    }

    interactive_editor_enabled = true;

    // Diable the wysiwyg and hide the text area
    for(var i in CKEDITOR.instances) {
      Drupal.myWysiwygControl.detach(CKEDITOR.instances[i].name);
      $('#'+i).hide();
      // Insert the canvas after the title
      $('.node-form .body').prepend( $('#canvas_container') );

      // Insert the toolbar
      $('.node-form .body').prepend( $('#druedu_interactive_editor_toolbar') );

      //druedu_interactive_editor_edit_widget
      $('.node-form .body').prepend( $('#druedu_interactive_editor_edit_widget') );


      $('#druedu_interactive_editor_toolbar').dropshadow();
      $('#druedu_interactive_editor_toolbar').border();
      $('#druedu_interactive_editor_toolbar').borderradius();
      $('#druedu_interactive_editor_toolbar').background();
      $('#druedu_interactive_editor_toolbar').druedutext();
      $('select[name="select03"]').simplecolorpicker();


      $('.widget .delete').on('click',function(e){
          $(this).parent().remove();
      });



      var footer_text = '<div class="handle NN"></div><div class="handle WW"></div><div class="handle EE"></div><div class="handle SS"></div><div class="handle btn-danger delete"></div><div class="handle rotate rotate_NE"></div>';
      var footer_media = '<div class="handle SE"></div><div class="handle rotate rotate_NE"></div><div class="handle btn-danger delete"></div>';

      var html = $('#edit-body-und-0-value').val();
      $('#canvas').css('height', $(html).find('#canvas').height() );

      $(html).find('.movie').append(footer_media);
      $(html).find('.image').append(footer_media);
      $(html).find('.text').append(footer_text);

      var widgets = $(html).children();
      $('#body-add-more-wrapper').hide();
      $('#canvas').html(widgets);
    }
  }
});


