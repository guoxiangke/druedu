

/**
 * Drop Shadow
 *
 * Dependencies : jQuery v1.7+
 *
 * Version: 1.0.0 (4/09/2012)
 * Auther: Jens H. Nielsen
 *
 */

 (function($){
    $.fn.extend({
        //plugin name - video
        video_image: function(options) {

            this.obj = null;

            var videotmpl = '<div class="movie widget"></div>'

            var imagetmpl = '<div class="image widget"></div>'

            var footer    = '   <div class="handle NE"></div>
                                <div class="handle NN"></div>
                                <div class="handle NW"></div>
                                <div class="handle WW"></div>
                                <div class="handle EE"></div>
                                <div class="handle SW"></div>
                                <div class="handle SS"></div>
                                <div class="handle SE"></div>
                                <div class="handle rotate rotate_NE"></div>
                                <div class="handle btn-danger delete"></div>
                            ';

            function init(element){

              $('.views-field-field-jquery-uploader-file img').click(function(e) {

                  var widget =  $('<div class="image_widget widget">').append( $(this).clone() );
                      widget.append(footer);
                      widget.appendTo( $('#canvas') );
              });

              $('.views-field-field-jquery-uploader-file video').click(function(e) {

                  var widget =  $('<div class="movie_widget widget">').append( $(this).clone() );
                      widget.append(footer);
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
