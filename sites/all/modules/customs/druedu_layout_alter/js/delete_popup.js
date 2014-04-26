jQuery(function($){
	var message = 'No result...'; //@TODO recup default message of the view
	$.fn.prepareModal = function() {
		$('#validationDelete-modal').modal('show');

		$('#validationDelete-modal button[value="Cancel"]').click(function(){
			$('#validationDelete-modal').modal('hide');
		});

		$('#validationDelete-modal .modal-header button.close').click(function(){
			$('#validationDelete-modal').modal('hide');
		});
			
		$('#validationDelete-modal').on('hidden', function () {
			$('#validationDelete-modal').remove();
		});
	};

	$.fn.hideModal = function() {
		$('#validationDelete-modal').modal('hide');
	};
	$.fn.checkViews = function() {
		var countNode = $('div[nid]').length;
		if(countNode == 0){
			$('#main-content .view-content > div:first').append(message);
		}
	};

	$.fn.checkhasComment = function(warpper_nid) {
		if(!$(warpper_nid + ' .ajax-comment-wrapper').length){
			$(warpper_nid +' .has-comment').remove();
		}
	};

	Drupal.behaviors.ajax_comment_form  = {
		attach: function(context, settings) {
  			$('#comment-form-wrapper textarea').val('');
		}
	}

});


