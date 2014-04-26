jQuery(function($) {
	ToggleSlide('');
	$('#answer-node-form button[type="submit"]').attr('disabled', 'disabled');

	function CKupdate(){
		for ( instance in CKEDITOR.instances )
	    CKEDITOR.instances[instance].updateElement();
	    CKEDITOR.instances[instance].setData('');
	}
	function CKcheck(instance){
	  if (instance.getData() != '' 
	  	|| ( instance.document.getBody().getChild(0) !== null && instance.document.getBody().getChild(0).getText() !='')){
			$('#answer-node-form button[type="submit"]').removeAttr('disabled');
			return true;
		}else{
			$('#answer-node-form button[type="submit"]').attr('disabled', 'disabled');
			return false;
		}
	}

	for ( instance in CKEDITOR.instances ) {
	  CKEDITOR.instances[instance].on( 'key', function( e ){
	   setTimeout(CKcheck, 200, CKEDITOR.instances[instance]);
	  });
	 }
 	//Upload a file or insert on ckeditor enabled submit button
 	$('#files_uploaded_container .insert').live('click',function(){ 
       	$('#answer-node-form button[type="submit"]').removeAttr('disabled');
    });

   	$('#filevault_core_block').bind('fileuploaddone', function() {
        	$('#answer-node-form button[type="submit"]').removeAttr('disabled');
    });

	Drupal.behaviors.druedu_qa = {
     attach: function (context, settings) {
			// $('.comments-wrapper .has-comment').after('<b class="triangle_top"></b>');
			ToggleSlide(context);
			var temp = $(context).html();
			if(temp.indexOf('answer_node_form') != -1) {
				CKupdate();//Always ckeditor not $('#edit-body-und-0-value').val(' ');
			}
			var checked = false;
			$(document).bind('flagGlobalAfterLinkUpdate', function(event, data) {
			  if (data.flagName == 'accepted' && data.flagStatus == 'flagged') {
			  	$(data.link).parents('#answers').find('a.unflag-action').not('.view-wrapper-'+data.contentId+' a.flag').click()
			  	$("#answers").prepend($(data.link).parents('.view-wrapper-'+data.contentId));
			  }
			});

		}
	}

	$.fn.insertComment = function(args) {
		$(args.selector).append(args.data);
	};


	$.fn.disableSubmitButton = function() {
		$('#answer-node-form button[type="submit"]').attr('disabled', 'disabled');
		$('#files_uploaded_container .remove_file').each(function(){
			$(this).click();
		});
		$('#files_uploaded').attr('class','hide');
	};
});

function ToggleSlide(context) {
	$('.fed_button').popover();

			$('.comment_button', context).click(function(){
				$(this).parents('.comments_answer').children('.comment_textarea').slideToggle('1000');
				$(this).parents('.comments_question').children('.comment_textarea').slideToggle('1000');
			});

			$('.comment_textarea a', context).click(function(e){
				e.preventDefault();
				$(this).parent().hide();
			});

	// Change the color of vote number when can not vote
	$('span.rate-button').next('.rate-number-up-down-rating').css('color',"#919191");

	$('.rate-widget-yesno').hover(function(){
		$(this).children('.qa-userful-buttons').show();
	} ,function(){
		$(this).children('.qa-userful-buttons').hide();
	});

}