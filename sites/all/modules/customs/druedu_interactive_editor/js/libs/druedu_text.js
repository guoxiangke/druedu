

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
        //plugin name - druedutext
        druedutext: function(options) {

            this.obj = null;

            var footer = '<div class="handle NN"></div><div class="handle WW"></div><div class="handle EE"></div><div class="handle SS"></div><div class="handle btn-danger delete"></div><div class="handle rotate rotate_NE"></div>';

            function init(element){

              $('#addtext').click(function(e) {

                var widget =  $('<div class="text widget">');
                var text = $('.add_content .textarea').val();

                widget.append(text);
                widget.append(footer);

                $(widget).find('.delete').click(function(e) {
                  $(this).parent().remove();
                });

                $(widget).css('width',500);

                widget.appendTo( $('#canvas') );

                $('.add_content .textarea').val("");
                $('.add_content .nav a:first').tab('show');
                $('#canvas').css('margin-top','0px')
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
