jQuery(function ($) {

  	$('.sticky-header').remove();

    var defaultValueTextfield = Drupal.t('Search by name...');

    if($('input[name="name"]').val() == '') {
      $('input[name="name"]').val(defaultValueTextfield);
    }

    $('input[name="name"]').focus(function(){
      if($(this).val() == defaultValueTextfield) {
        $(this).val('');
      }
    });

    $('input[name="name"]').blur(function(){
      if($(this).val() == '') {
        $(this).val(defaultValueTextfield);
      }
    });

  //MODAL PART
	$.fn.prepareModal = function() {
    $('#submission-modal').modal('show');

    $('.modal-header button').click(function(){
			$('#submission-modal').modal('hide');
		});

    $('#submission-modal').on('hidden', function () {
      $('#submission-modal').remove();
    });
  };
  //END MODAL PART
});