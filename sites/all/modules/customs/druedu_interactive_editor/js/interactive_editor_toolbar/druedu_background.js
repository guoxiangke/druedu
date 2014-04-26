

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
        //plugin name - background
        background: function(options) {

            obj = null;
            var color = "#FFFFFF"

            function init(element){

              console.log('init');


              $('#background_container select[name="select03"]').change(function() {
                  color = $('#background_container select[name="select03"]').val();
                  $('#canvas .selected').css('background-color',color);
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
