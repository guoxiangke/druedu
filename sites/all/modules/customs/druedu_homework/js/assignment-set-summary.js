jQuery(function ($) {
    druedu_homework_summeries('');

  	Drupal.behaviors.drueduHomeworkFieldsetSummeries = {
    	attach: function (context) {
    		druedu_homework_summeries(context);
    	}
  	}

    function druedu_homework_summeries(context){
      $('fieldset.container-classes-students-settings-form', context).each(function(){
          var classes = $(this).attr('class');
          classes = classes.replace(' ', '.').replace(' ', '.').replace(' ', '.').replace(' ', '.');
          $('fieldset.' + classes, context).drupalSetSummary(function (context) {
            var n = $('fieldset.' + classes + ' input:checked').not('.select_all').length;
          if(n > 0){
                 return Drupal.t('@count student(s) selected', {'@count' : n});
            }
            else {
                return Drupal.t('No student selected.');
            }
        }); 
      });
    }


});