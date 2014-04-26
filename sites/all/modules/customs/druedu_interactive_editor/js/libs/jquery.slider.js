/**
 * Touch/mouse based slider
 *
 * Dependencies : jquery.event.drag.js, jQuery v1.7+
 *
 * Version: 1.0.0 (31/08/2012)
 * Auther: Jens H. Nielsen
 *
 *
 */

 (function($){
    $.fn.extend({
        //plugin name - animatemenu
        druedu_slider: function(options) {

      this.obj = null;
      this.obj_parent = null;

      this.min = 0;
      this.max = 100;
      this.surfix = "";

      function buildHTML(){
        $(obj).wrap('<div class="druedu_slide_container" />');
        obj_parent = $(obj).parent();
        $(obj).wrap('<div class="druedu_slide_input" />');
        $(obj_parent).append('<div class="druedu_slider_rail" />');
        $(obj_parent).find('.druedu_slider_rail').append('<div class="druedu_slider_handle" />');
        $(obj_parent).find('.druedu_slider_rail').append('<div class="druedu_slider_line" />');
      }

      function addCSS(){
        $(obj_parent).find(".druedu_slide_input").css({'width':'15%','height':'20px','float':'right','margin-left':'5%','margin-left':'-9px'});
        $(obj_parent).find(".druedu_slider_rail").css({'width':'75%','height':'26px'});
        $(obj_parent).find(".druedu_slider_line").css({'width':'100%','height':'10px','margin-top':'8px'});
        $(obj_parent).find(".druedu_slider_handle").css({'width':'20px','height':'24px', 'position':'absolute','margin-top':'-8px'});
      }


      function update_value(element){
        var obj_rail_lenght = $(element).parent().find(".druedu_slider_line").outerWidth();
        var obj_handle = $(element).parent().find(".druedu_slider_handle");
        var input_obj = $(element).parent().find("input");
        var abs_max = max - min;
        var value = parseInt($(obj_handle).css('left'));
        var position = $(element).parent().position();

        var cssLeft = ((value - position.left) / (obj_rail_lenght - $(obj_handle).outerWidth())) * abs_max + min + 1;


        if(max > 1) {
            $(element).parents('.druedu_slide_container').find('input').val( Math.round(cssLeft) ).change();
        }else{
            $(element).parents('.druedu_slide_container').find('input').val(cssLeft ).change();
        }
      }


      function update_handle(){

        var input_obj = $(obj_parent).find("input");

        $(input_obj).change(function () {
          var value = $(input_obj).val();

          if(value > max){
            $(input_obj).val(max);
          }

          if(value < min){
            $(input_obj).val(min);
          }

          var obj_handle = $(obj_parent).find(".druedu_slider_handle");
          var obj_rail_lenght = $(obj_parent).find(".druedu_slider_rail").width();
          var abs_max = max - min;
          var abs_value = $(input_obj).val() - min;

          $(obj_handle).css('left', (abs_value/abs_max)*obj_rail_lenght);
        });
      }


      function init(){

        var self = this;

        $(obj_parent).find(".druedu_slider_handle").drag("start",function( ev, dd ){
          dd.limit = $(this).parent().offset();
          dd.limit.bottom = dd.limit.top + $(this).parent().outerHeight() - $( this ).outerHeight();
          dd.limit.right = dd.limit.left + $(this).parent().outerWidth() - $( this ).outerWidth();
        });

        $(obj_parent).find(".druedu_slider_handle").drag(function( ev, dd ){
          $( this ).css({
            left: Math.min( dd.limit.right, Math.max( dd.limit.left, dd.offsetX ) )
          });
          update_value(this);
        });

        min = parseInt( $(obj).attr('min') );
        max = parseInt( $(obj).attr('max') );
        surfix = $(obj).attr('surfix');
        update_handle();

      }

            return this.each(function() {
                  var o =options;
                  obj = this;
          buildHTML();
          addCSS();
          init();

            });
        }
    });
})(jQuery);
