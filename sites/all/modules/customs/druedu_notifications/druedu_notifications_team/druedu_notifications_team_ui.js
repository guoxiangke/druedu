jQuery(function($){
	function drueduNotificationsNoSelected() {
		if(!$('#notifications-options-all .users').length &&!$('#notifications_user_selected_container').length) {
			$('#notifications-options-all').append('<div id="notifications_user_selected_container"><div class="no_selected_wrapper"> No users selected <div></div>');
		}else{
			$('#notifications_user_selected_container').remove();
		}
	}
	function drueduNotificationsUI() {
		//ajax for filter of group grade.
		$('.delete-item').live('click',function(){
			uid = $(this).parents('.controls').find('input').attr('value');
			$(this).parents('#edit-notifications').find('.form-item-notifications-team-all-'+ uid ).hide().find('input').removeAttr('checked');
			$(this).parents('#edit-notifications').find('.form-item-notifications-team-filter-'+ uid ).find('input').removeAttr('checked');
		});
		drueduNotificationsNoSelected();
	// drueduNotificationsUI end
	}
	drueduNotificationsUI();
	
	// checkboxs check begin
	var all_users = jQuery.parseJSON($('input[name="users_potential_selected"]').val());
	// init ui append
	$('#notifications-options-all input').each(function(){
		$(this).parents('.control-group').hide();
		if($(this).is(":checked")) {
			uid = $(this).attr('value');
			var username = all_users[uid];
			if(!$('#notifications-options-all .users.user_'+ uid).length) {
				$('#notifications-options-all').append('<div class="users user_'+ uid +'">'+ username +' <i class="icon-remove-sign delete-item icon-small"></i></div>');
			}
		}
	});

	function drueduNotificationsFilter() {
		$('#wrapper_filter_user').find('input').each(function(){
			$(this).live('click',function(){
				uid = $(this).attr('value');
				var username = all_users[uid];
				if($(this).attr("checked")){
					$(this).parents('#edit-notifications').find('#notifications-options-all .form-item-notifications-team-all-'+ uid ).each(
						function(){
							$(this).find('input[value='+ uid +']').attr("checked", 1);
							//$(this).fadeIn('fast');
							if(!$('#notifications-options-all .users.user_'+ uid).length) {
								$('#notifications-options-all').append('<div class="users user_'+ uid +'">'+ username +' <i class="icon-remove-sign delete-item icon-small"></i></div>');
							}
						});
				}else{
					$(this).parents('#edit-notifications').find('#notifications-options-all .form-item-notifications-team-all-'+ uid ).each(
						function(){
							//$(this).fadeOut('fast');
							$('#edit-team-checkall').removeAttr("checked");
							$(this).find('input[value='+ uid +']').removeAttr("checked");
							$('#notifications-options-all .users.user_'+ uid).remove();
						});
				}

				drueduNotificationsNoSelected();
			});
		});
	}
	drueduNotificationsFilter();

	function checkCheckBox(){
		if($('#edit-team-checkall').is(":checked")){
			 	$('#edit-team-checkall').parents('#edit-notifications').find('#wrapper_filter_user input').each(
					function(){
						$(this).attr("checked", 1);
						uid = $(this).attr('value');
						$('#notifications-options-all input[value='+ uid +']').attr("checked", 1);
						var username = all_users[uid];
						$('#notifications-options-all .users.user_'+ uid).remove();
						if(!$('#notifications-options-all .users.user_'+ uid).length) {
							$('#notifications-options-all').append('<div class="users user_'+ uid +'">'+ username +' <i class="icon-remove-sign delete-item icon-small"></i></div>');
						}//$(this).parents('#edit-notifications').find('.form-item-notifications-team-all-'+ uid ).fadeOut('fast');
					});
		}else{
			 	$('#edit-team-checkall').parents('#edit-notifications').find('#wrapper_filter_user input').each(
					function(){
						$(this).removeAttr("checked");
						uid = $(this).attr('value');
						$('#notifications-options-all input[value='+ uid +']').removeAttr("checked");
						$('#notifications-options-all .users.user_'+ uid).remove();
						//$(this).parents('#edit-notifications').find('.form-item-notifications-team-all-'+ uid ).fadeIn('fast');
					});
		}
	};

	function drueduNotificationsCheckAll() {
		$('#edit-team-checkall').live('click',function(){
			checkCheckBox();
			if ($(this).is(":checked")) {
				$('#edit-notifications-content-disable').removeAttr("checked");
			};
			drueduNotificationsNoSelected();
		});

		$('#edit-notifications-content-disable').live('click',function(){
			console.log('clicked');
			if($('#edit-notifications-content-disable:checked').length){
				if($('#edit-team-checkall').is(":checked")){
					$('#edit-team-checkall').click();
					$(this).attr("checked", 1);
					setTimeout(checkCheckBox, 100);
				}else{
					$('#notifications-options-all .users .delete-item').each(function(){
						$(this).click();
					});
				}
			}
			// if($(this).is(":checked")){
			// 	$('#notifications-options-all .users').slideUp('fast');
			// }else{
			// 	$('#notifications-options-all .users').slideDown('fast');
			// }
		});
		//click on delete
		$('#notifications-options-all .users .delete-item').live('click',function(){
			//var classes = $(this).parent().attr('class');
			var uid = $(this).parent().attr('class').split('_');
			uid = uid[1];
			$('#edit-team-checkall').removeAttr("checked");
			$('#wrapper_filter_user input[value='+ uid +']').removeAttr("checked");
			$('#notifications-options-all input[value='+ uid +']').removeAttr("checked");
			$('#notifications-options-all .users.user_'+ uid).remove();
			drueduNotificationsNoSelected();
		});
	}
	drueduNotificationsCheckAll();	
	// checkboxs check end

	Drupal.behaviors.druedu_notifications = {
		attach: function (context, settings) {
			drueduNotificationsUI();
			drueduNotificationsCheckAll();
			drueduNotificationsFilter();
		}
	}

});
