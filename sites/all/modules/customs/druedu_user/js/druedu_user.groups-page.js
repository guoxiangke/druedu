jQuery(function($){
	var count = 0;
	$.each($('.'+Drupal.t('my_public_groups')+' .public.group') , function(index, obj) {
		initializeHover(obj);
	});

	Drupal.behaviors.druedu_user = {
		attach: function(context, settings) {
		  //user subscribe a group	
		  $('body').bind('ajaxSuccess', function(data, status, xhr){
		    if(xhr.url.indexOf('groups') >= 0 && xhr.url.indexOf('add-user') >= 0 && context.find('.group-unsubscribe').length > 0) {
		     	initializeHover(context);
		    }
		  });
		}
	}

	$.fn.prepareModal = function() {
		$('#groups-modal').modal('show');

		$('#groups-modal .modal-footer #edit-cancel-validation').click(function(){
			$('#groups-modal').modal('hide');
		});

		$('#groups-modal .modal-header button.close').click(function(){
			$('#groups-modal').modal('hide');
		});

		$('#groups-modal .modal-footer a.btn.no').click(function(){
			$('#groups-modal').modal('hide');
			return false;
		});
			
		$('#groups-modal').on('hidden', function () {
			$('#groups-modal').remove();
		});
	};

	$.fn.prepareGroupSubscribed = function() {
		$('#groups-modal').modal('hide');
		if(checkEmptyList($('li.' + Drupal.t('subscribe') + '.group'))) {
		 	$('.view-id-og_user_groups.view-display-id-all_public_groups_block .view-content').addClass('hide');
		}
		// inferior to 2 because user have necessary a grade, we check only if he has public groups
		if(checkEmptyList($('.view-id-og_user_groups.view-display-id-user_group_page .view-content ul.'+Drupal.t('my_public_groups')))) {
		 	$('.view-id-og_user_groups.view-display-id-user_group_page .view-content ul.'+Drupal.t('my_private_groups')).after('<h3>' 
		 		+ Drupal.t('My public groups') + '</h3><ul class="'+Drupal.t('my_public_groups')+'"></ul>');
		}

		//if have 0 element now, we will Have 1 after inserting so show
		if(checkEmptyList($('li.' + Drupal.t('public') + '.group'))) {
		 	$('.view-id-og_user_groups.view-display-id-user_group_page .view-content > h3:eq(1)').removeClass('hide');
		 	$('.view-id-og_user_groups.view-display-id-user_group_page .view-content > ul:eq(1)').removeClass('hide');
		}
	};

	$.fn.prepareGroupUnsubscribed = function() {
		if(checkEmptyList($('li.' + Drupal.t('public') + '.group'))) {
		 	$('.view-id-og_user_groups.view-display-id-user_group_page .view-content > h3:eq(1)').addClass('hide');
		 	$('.view-id-og_user_groups.view-display-id-user_group_page .view-content > ul:eq(1)').addClass('hide');
		}
		if(!checkEmptyList($('li.' + Drupal.t('subscribe') + '.group'))) {
		 	$('.view-id-og_user_groups.view-display-id-all_public_groups_block .view-content').removeClass('hide');
	}
	};

	function checkEmptyList(list) {
		if(list.length == 0) {
		 	return true;
		}
		return false;
	}

	function initializeHover(context) {
		//add delay tooltip
		/*
			$(context).tooltip({
				delay : { show: 0, hide: 5000 },
			});
		*/
		$(context).hover(
			function () {
				$(this).find('.group-unsubscribe').removeClass('hide');
			}, 
			function () {
				$(this).find('.group-unsubscribe').addClass('hide');
			}
		);
	}
});
