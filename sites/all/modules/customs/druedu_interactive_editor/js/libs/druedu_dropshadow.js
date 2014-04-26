

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
        //plugin name - dropshadow
        dropshadow: function(options) {

            this.obj = null;

            var size = 0;
            var blur = 0;
            var opacity = 0;
            var distance = 0;
            var color = "#000000"; // Black is the default

            function cutHex(h) {return (h.charAt(0)=="#") ? h.substring(1,7):h}
            function hexToR(h) {return parseInt((cutHex(h)).substring(0,2),16)}
            function hexToG(h) {return parseInt((cutHex(h)).substring(2,4),16)}
            function hexToB(h) {return parseInt((cutHex(h)).substring(4,6),16)}

            function update_drop_shadow(){

              
              var R = hexToR(color);
              var G = hexToG(color);
              var B = hexToB(color);

              $('#canvas .selected').css('-webkit-box-shadow','0 ' + distance +'px ' +  blur + 'px ' +   size + 'px rgba(' + R +","+ G + ',' + B + ',' + opacity + ')');
              console.log( '0 ' + distance +'px ' +  blur + 'px ' +   size + 'px rgba(' + R +","+ G + ',' + B + ',' + opacity + ')');
            }

            function init(element){

              console.log('init');

              $('#dropshadow_container select[name="select03"]').change(function() {
                  color = $('#dropshadow_container select[name="select03"]').val();
                  update_drop_shadow();
              });

              $("#dropshadow_container #opacity").slider({
                from: 0,
                to: 1,
                step: 0.1,
                round: 1,
                onstatechange: function( value ){
                  opacity = value;

                  var R = hexToR(color);
                  var G = hexToG(color);
                  var B = hexToB(color);

                  $('#canvas .selected').css('-webkit-box-shadow','0 ' + distance +'px ' +  blur + 'px ' +   size + 'px rgba(' + R +","+ G + ',' + B + ',' + opacity + ')');
                }
              });

              $("#dropshadow_container #distance").slider({
                from: 0,
                to: 50,
                step: 1,
                round: 0,
                onstatechange: function( value ){
                  distance = value;
                  
                  var R = hexToR(color);
                  var G = hexToG(color);
                  var B = hexToB(color);

                  $('#canvas .selected').css('-webkit-box-shadow','0 ' + distance +'px ' +  blur + 'px ' +   size + 'px rgba(' + R +","+ G + ',' + B + ',' + opacity + ')');
                }

              });

              $("#dropshadow_container #blur").slider({
                from: 0,
                to: 100,
                step: 1,
                round: 0,
                onstatechange: function( value ){
                  blur = value;
                  
                  var R = hexToR(color);
                  var G = hexToG(color);
                  var B = hexToB(color);

                  $('#canvas .selected').css('-webkit-box-shadow','0 ' + distance +'px ' +  blur + 'px ' +   size + 'px rgba(' + R +","+ G + ',' + B + ',' + opacity + ')');
                }

              });

              $("#dropshadow_container #size").slider({
                from: 0,
                to: 50,
                step: 1,
                round: 0,
                onstatechange: function( value ){
                  size = value;

                  var R = hexToR(color);
                  var G = hexToG(color);
                  var B = hexToB(color);

                  $('#canvas .selected').css('-webkit-box-shadow','0 ' + distance +'px ' +  blur + 'px ' +   size + 'px rgba(' + R +","+ G + ',' + B + ',' + opacity + ')');
 
                }
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
