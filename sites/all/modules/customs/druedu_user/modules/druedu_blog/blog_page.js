$(function() {

	$('.views-field.read_more').live('click', function(){
		var parent = $(this).parent().attr('class');
		parent = '.' + parent.replace(/ /g, ".");
		$(this).toggleClass('hide');
		$(parent + ' .views-field.views-field-body').toggleClass('hide');
		$(parent + ' .views-field.collapse_it').toggleClass('hide');
		$(parent + ' .views-field.views-field-field-summary').toggleClass('hide');
	});

	$('.views-field.collapse_it').live('click', function(){
		var parent = $(this).parent().attr('class');
		parent =  '.' + parent.replace(/ /g, ".");
		$(this).toggleClass('hide');
		$(parent + ' .views-field.views-field-body').toggleClass('hide');
		$(parent + ' .views-field.read_more').toggleClass('hide');
		$(parent + ' .views-field.views-field-field-summary').toggleClass('hide');
	});
	$('.views-field.btn-comments').live('click', function(){
		var parent = $(this).parent().attr('class');
		parent =  '.' + parent.replace(/ /g, ".");
		$(parent + ' .views-field.comments').toggleClass('hide');
		$(parent + ' .views-field.comment-form').toggleClass('hide');
	
	});

	
	$.fn.insertComment = function(args) {
		$(args.selector).append(args.data);
	};

});