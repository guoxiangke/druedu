jQuery(function($){
	var fieldName = Drupal.settings.field_name;
	$('.field-name-'+fieldName+' .controls').first().before('<input type="checkbox" value="check_all" id="check_all_feature" class="form-checkbox"><label>Select all</label>');

	$('#check_all_feature').click(function(){
		if($('#check_all_feature').is(':checked')) {
			$('.field-name-'+fieldName+' .form-type-checkbox input').not(':checked').click();
		}
		else {
			$('.field-name-'+fieldName+' .form-type-checkbox input:checked').click();
		}
	});
});
