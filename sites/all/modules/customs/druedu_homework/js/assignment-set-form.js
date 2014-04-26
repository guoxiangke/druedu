jQuery(function ($) {
	druedu_homework_assignment_set('');
	Drupal.behaviors.druedu_homework = {
    	attach: function (context, settings) {
			druedu_homework_assignment_set(context);
		}
	}

	function druedu_homework_assignment_set(context) {
		$('#container_classes_students input:checkbox', context).not('.select_all').change( function(){
				var students = $('input[name="hidden_student"]').val();
				var idfieldset = $(this).closest('fieldset.vertical-tabs-pane').attr('id');	
				if(!$(this).is(':checked')) {
					var newVal = students.replace($(this).val() + ';', '') ;
					$('input[name="hidden_student"]').val(newVal);
					hasStudentinClass(idfieldset);
				}
				else if($(this).is(':checked') && students.search($(this).val()) == -1) {
					$('input[name="hidden_student"]').val(students + $(this).val() +';');
					hasStudentinClass(idfieldset);
				}
			});

			$('#edit-field-assignment-grade select', context).change( function(){
				$('input[name="hidden_student"]').val('');
				$('input[name="hidden_classes"]').val('');
				$('#list_field_assignment_subject').hide();
				$('#list_field_structure_unit').hide();
				$('#container_classes_students').hide();
				$('.no_student').remove();
				$('#select_all_student_wrapper').remove();
			});
			$('#edit-field-assignment-subject select', context).change( function(){
				$('input[name="hidden_student"]').val('');
				$('input[name="hidden_classes"]').val('');
				$('#list_field_structure_unit').hide();
				$('#container_classes_students').hide();
				$('.no_student').remove();
				$('#select_all_student_wrapper').remove();
			});

			$('input.select_all[value="all"]').click(function(){
				var idfieldset = $(this).closest('fieldset.vertical-tabs-pane').attr('id');	
				if($(this).is(':checked')) {
					$('#' + idfieldset + ' .form-checkboxes input').not(':checked').click();
				}
				else{
					$('#' + idfieldset + ' .form-checkboxes input:checked').click();
				}
			});

			$('input#select_all_student').click(function(){
				$('input.select_all[value="all"]').not(this).click();
				if($(this).is(':checked')) {
					$('input.select_all[value="all"]').not(this).attr('checked','checked');
				}
				else{
					$('input.select_all[value="all"]').not(this).removeAttr('checked');
				}
			});
	}

	$('#edit-container-classes-students input:checked').attr('disabled', 'disabled');

	function hasStudentinClass(domClass) {
		var classes = $('input[name="hidden_classes"]').val();
		var idClass = domClass.replace('edit-', '').replace(/--+[0-9]/g, '');
		var n = $('#' + domClass + ' input:checked').length;
		if(n > 0 && classes.search(idClass) != 0) {
			$('input[name="hidden_classes"]').val(classes + idClass +';');
		}
		else if(n == 0) {
			var newVal = classes.replace(idClass + ';', '') ;
			$('input[name="hidden_classes"]').val(newVal);
		}
	}

});