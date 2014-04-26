jQuery(function ($) {
	//click on delete
			$('#share_user_selected_container .users .delete-item').live('click',function(){
				//var classes = $(this).parent().attr('class');
				var userId = $(this).parent().attr('class').split('_');
				userId = userId[1];
				var string = userId + ';';
				var user_selected_new_value = $('input[name="users_selected"]').val().replace(string, '');
				$('input[name="users_selected"]').val(user_selected_new_value);
				$('#wrapper_potential_user input[name="potential_users['+ userId +']"]:checked').click();
				$('#share_user_selected_container .users.user_'+ userId).remove();
				if(!$.trim($('input[name="users_selected"]').val()).length){
					$('#share_user_selected_container .no_selected_wrapper').fadeIn('fast');
				}
			});

	Drupal.behaviors.druedu_notification_share = {
		attach: function(context, settings) {
			var all_users = jQuery.parseJSON($('input[name="users_potential_selected"]').val());
			$('#wrapper_action_submit button').attr('disabled', 'disabled');
			$('#wrapper_potential_user .form-checkboxes').append('<div id="edit-no-potential-users" style="display:none">'+ Drupal.t('No users available.') +'</div>');
			//filter by username
			$('#edit-username').keyup(function(){
				//get value user tap
				var value = $(this).val();
				//if filter is not empty
				if($.trim(value).length > 0){
					//check all username from the list
					$('#wrapper_potential_user input[type="checkbox"]').each(function(){
						var user = $(this).parent().text();
						//if doesnt match hide checkbox and if all checkbox is hidden disabled button submit and display message "No user available"
						if(user.indexOf(value) == -1) {
							$(this).parent().parent().parent().fadeOut('fast', function() {
								if($('#wrapper_potential_user input[type="checkbox"]:visible').length == 0) {
									$('#edit-no-potential-users').fadeIn('fast');
									$('#wrapper_action_submit button').attr('disabled', 'disabled');
								}
							});
						}
						//else remove the text and if have a checkbox checked previously, enabled submit button
						else{
							$(this).parent().parent().parent().fadeIn('fast', function() {
								$('#edit-no-potential-users').fadeOut('fast');
								if($('#wrapper_potential_user input[type="checkbox"]:checked').length > 0 && $('#wrapper_action_validate input[name="confirm"]:checked').length > 0) {
									$('#wrapper_action_submit button').removeAttr('disabled');
								}
							});
						}
					});
				}
				//if filter is empty
				else{
					$('#edit-no-potential-users').fadeOut('fast', function(){
						$('#wrapper_potential_user input[type="checkbox"]').parent().parent().parent().fadeIn('fast');
					});
					if($('#wrapper_potential_user input[type="checkbox"]:checked').length > 0 && $('#wrapper_action_validate input[name="confirm"]:checked').length > 0) {
						$('#wrapper_action_submit button').removeAttr('disabled');
					}	
				}
			});

			//After checked or unchecked a selecbox
			$('#wrapper_potential_user input[type="checkbox"]').change(function(){
				var userId = $(this).val();
				var user_selected_value = $('input[name="users_selected"]').val();
				if($('#wrapper_potential_user input[type="checkbox"]:checked').length > 0) {
					if($('#wrapper_action_validate input[name="confirm"]:checked').length > 0) {
						$('#wrapper_action_submit button').removeAttr('disabled');
					}
				}
				else{
					$('#wrapper_action_submit button').attr('disabled', 'disabled');
				}
				if($(this).is(':checked')) {
					if(user_selected_value.indexOf(userId + ';') == -1) {
						$('input[name="users_selected"]').val(user_selected_value + $(this).val() + ';');
						var username = all_users[userId];
						$('#share_user_selected_container .no_selected_wrapper').fadeOut('fast', function(){
							$('#share_user_selected_container').append('<div class="users user_'+ userId +'">'+ username +'<i class="icon-remove-sign delete-item icon-small"></i></div>');
						});
					}
				}
				else {
					var string = userId + ';';
					//if exist
					if(user_selected_value.indexOf(string) >= 0) {
						var user_selected_new_value = $('input[name="users_selected"]').val().replace(string, '');
						$('input[name="users_selected"]').val(user_selected_new_value);
						$('#share_user_selected_container .users.user_'+ userId).remove();
						if(!$.trim($('input[name="users_selected"]').val()).length){
							$('#share_user_selected_container .no_selected_wrapper').fadeIn('fast');
						}
					}
				}
			});

			// after check or uncheck validate 
			$('#wrapper_action_validate input').change(function(){
				if($('#wrapper_action_validate input:checked').length > 0) {
					if($('#wrapper_potential_user input[type="checkbox"]:checked').length > 0) {
						$('#wrapper_action_submit button').removeAttr('disabled');
					}
					else{
						$('#wrapper_action_submit button').attr('disabled', 'disabled');
					}
				}
				else {
					$('#wrapper_action_submit button').attr('disabled', 'disabled');
				}
			});


			if($.trim($('input[name="users_selected"]').val()).length > 0 && $('#wrapper_action_validate input[name="confirm"]:checked').length > 0) {
				$('#wrapper_action_submit button').removeAttr('disabled');
			}
		}
	};

	$.fn.druedu_notification_default_checkboxes = function(){
		default_checkboxes = $('input[name="users_selected"]').val();
		if($.trim(default_checkboxes).length > 0) {
			default_checkboxes = default_checkboxes.split(';');
			default_checkboxes = jQuery.grep(default_checkboxes, function(value) {
	            return value != '';
	        });
			$.each(default_checkboxes, function(index, userId) {
				$('#wrapper_potential_user input[name="potential_users['+ userId +']"]').not(':checked').click();
			});
		}
		$('#edit-username').val('');
	};	

});
