

/**
 * Drop Shadow
 *
 * Dependencies : jQuery v1.7+
 *
 * Version: 1.0.0 (4/09/2012)
 * Auther: Jens H. Nielsen
 *
 *
 */

 (function($){
    $.fn.extend({
        //plugin name - video
        video_image: function(options) {

            this.obj = null;

            var videotmpl = '<div class="movie widget"></div>';

            var imagetmpl = '<div class="image widget"></div>';

            var footer = '<div class="handle SE"></div><div class="handle rotate rotate_NE"></div><div class="handle btn-danger delete"></div>';

            //<div class="handle NE"></div><div class="handle NN"></div><div class="handle NW"></div><div class="handle WW"></div><div class="handle EE"></div><div class="handle SW"></div><div class="handle SS"></div>

            //'

            function init(element){

              $('.views-field-field-jquery-uploader-file img').click(function(e) {

                  var data = $(this).data();
                  var h = data['orgHeight'];
                  var w = data['orgWidth'];

                  if( h > 400 || w > 400 ){
                      while(h > 400 || w > 400  ){
                        h = h/2;
                        w = w/2;
                    }
                  }

                  var widget = $('<div class="image_widget keep_aspect widget">');
                  var img = $(this).clone();

                  $(img).css('height','auto');
                  $(img).css('width',w);
                  widget.append(img);

                  $(widget).css('height','auto');
                  $(widget).css('width',w);


                  widget.append(footer);
                  $(widget).find('.delete').click(function(e) {
                          $(this).parent().remove();
                  });

                  widget.appendTo( $('#canvas') );

              });

              $('.views-field-field-jquery-uploader-file video').click(function(e) {

                  var widget =  $('<div class="movie_widget keep_aspect widget">');
                  var video = $(this).clone();

                  var h = $(video).attr('height');
                  var w = $(video).attr('width');

                  //$(video).css('max-width','100%');
                  $(video).css('height','auto');
                  $(video).attr('data-orgHeight', h);
                  $(video).attr('data-orgWidth', w);

                  $(widget).css('height','auto');
                  $(widget).css('width',w);

                  widget.append($(video));
                  widget.append(footer);

                  $(widget).find('.delete').click(function(e) {
                    $(this).parent().remove();
                  });
                  widget.appendTo( $('#canvas') );
              });

            }

            return this.each(function() {
                  var o =options;
                  obj = this;
                  init(this);

            });
        }
    });
})(jQuery);
