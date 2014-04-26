

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
        //plugin name - borderradius
        borderradius: function(options) {

            this.obj = null;
            var radius = 0;

            function update_drop_shadow(){

              //radius = parseInt( $('#borderradius_container #radius').slider("value") );



              //$('#canvas .selected').css("borderradius",'rgba(' + R +","+ G + ',' + B + ',' + opacity + ') '+ style + ' ' + size + 'px');
              //console.log( 'rgba(' + R +","+ G + ',' + B + ',' + opacity + ') '+ style + ' ' + size + 'px');
            }

            function init(element){

              console.log('borderradius');


              $('.cornersborder').click(function(e) {
                  $(this).toggleClass('deselected');
              });

              $("#borderradius_container #radius").slider({
                from: 0,
                to: 50,
                step: 1,
                round: 0,
                onstatechange: function( value ){

                  var type= "%";
                  if($(".btn-group .active").attr("id") == "px"){
                    type = "px";
                  }



                  if( !$('#corners #NE').hasClass('deselected') ) {
                    $('#canvas .selected').css('border-top-right-radius', value + type);
                    $('#canvas .selected').find('video, img').css('border-top-right-radius', value + type);
                  }

                  if( !$('#corners #NW').hasClass('deselected') ) {
                    $('#canvas .selected').css('border-top-left-radius', value +type);
                    $('#canvas .selected').find('video, img').css('border-top-left-radius', value +type);
                  }

                  if( !$('#corners #SE').hasClass('deselected') ) {
                    $('#canvas .selected').css('border-bottom-left-radius', value +type);
                    $('#canvas .selected').find('video, img').css('border-bottom-left-radius', value +type);
                  }

                  if( !$('#corners #SW').hasClass('deselected') ) {
                    $('#canvas .selected').css('border-bottom-right-radius', value +type);
                    $('#canvas .selected').find('video, img').css('border-bottom-right-radius', value +type);
                  }
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
