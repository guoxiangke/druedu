jQuery(function($){

	function drueduNotificationsAjaxSubmit() {
		$( ".notifications-ajax li a" ).each(function(){
			if($(this).hasClass('btn-small')) {
				$(this).removeClass('btn-small');
			}
			$(this).addClass('btn btn-mini');
		});

		$( ".notifications-ajax li[class*='notifications-']" ).each(function(){
			//$(this).addClass('use-ajax');
			//ajax-processed btn btn-small
			if($(this).children('a').hasClass('ajax-processed')) {
				return; //continue
			}
			$(this).children('a').addClass('ajax-processed');
			url = $(this).children('a').attr('href');
			//$(this).children('a').attr('href','/nojs'+url);

			var element_settings = {};
		    // Ajax submits specified in this manner automatically submit to the
		    // normal form action.
		    element_settings.url = url ;
		    // Form submit button clicks need to tell the form what was clicked so
		    // it gets passed in the POST request.
		    element_settings.setClick = true;
		    // Form buttons use the 'click' event rather than mousedown.
		    element_settings.event = 'click';
		    // Clicked form buttons look better with the throbber than the progress bar.
		    element_settings.progress = { 'type': 'throbber' };

		    var base = $(this).attr('id');
		    Drupal.ajax[base] = new Drupal.ajax(base, this, element_settings);
		});
	//end
	}

	drueduNotificationsAjaxSubmit();

	Drupal.behaviors.druedu_notifications = {
		attach: function (context, settings) {
		//your code here
			drueduNotificationsAjaxSubmit();
		}
	}

});
