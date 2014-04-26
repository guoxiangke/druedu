(function ($) {
	if($('.container-classes-students-settings-form .fieldset-wrapper .form-checkboxes').length > 0){
		alert('test');
		$('.container-classes-students-settings-form .fieldset-wrapper .form-checkboxes').each(function(){
			var value = $(this).parent().parent().parent().parent().find('.vertical-tab-button strong').html();
			$(this).before('<label><input class="select_all" type="checkbox" value="all"> ' + Drupal.t('Select all students of') + ' ' + value + '</label>');
		});
	}
})(jQuery);
