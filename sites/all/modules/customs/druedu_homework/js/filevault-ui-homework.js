function getStatutFilevaultField() {
    return true;
}

jQuery(function ($) {

    $.fn.reset_homework_submission_form = function(){
        $('#files_uploaded_container div').remove();
        ind = 0;
        $('#edit-submission-comment').val('');
        $('input[name="uploaded_file"]').val('');
        $('#druedu-homework-submission-form button[type="submit"]').attr('disabled','disabled');
    };

    //INITIALIZE
    $('#edit-submission-submit').attr('disabled','disabled');
    var ind = 0;
    if( $('input[name="uploaded_file"]').val() != '' ){
        var ArrayUploaded = $('input[name="uploaded_file"]').val().split(';');
        ArrayUploaded = jQuery.grep(ArrayUploaded, function(value) {
            return value != '';
        });
        $('#ui_upload').removeClass('hide');
        $('#edit-submission-submit').removeAttr('disabled');
        $('input[name="uploaded_file"]').val();
        $.each(ArrayUploaded, function(index, value) {
            var file = jQuery.parseJSON(value);
            ind += 1;
            filesUploaded(ind, file);
        });
    }
    // BIND EVENT
    $('#filevault_core_block').bind('fv_upload_done', function(e, data) {
        if($('#icon-save').length == 0 || $('#icon-save.hide').length) {
            ind += 1;
            $.each(data.result, function (index, file) {
                filesUploaded(ind, file);
            });
        }
    });

    $('#filevault_core_block').bind('fileuploadstart', function() {
        if($('#submission_form:not(.in)').length) {
            $('#submission_toggle').click();
            $('#ui_upload').removeClass('hide');
        }
    });

    // BIND EVENT
    jQuery('#filevault-modal .insert').live('click', function (e){
        if($('#icon-save').length == 0 || $('#icon-save.hide').length) {
            ind += 1;
            $("#filevault-modal").modal("hide");
            var file = jQuery(this).parents('li').data('json');
            filesUploaded(ind, file);
        }
    });

    $('#ui_upload #dragndrop-area .pc_files').click(function() {
        $('#edit-file').click();
    });

    function filesUploaded(ind, file) {
        if(typeof(file.name) == "undefined") {
            file.name = file.filename;   
        }
        if(typeof(file.type) == "undefined") {
            file.type = file.mime_type;   
        }
        if(typeof(file.entity) == "undefined") {
            file.entity = JSON.stringify(file);
        }
        $('#files_uploaded_container').append(
                '<div class="file ' + ind + ' file-item clearfix">'
                    + '<div class="file_icon span1"><i class="icon-paper-clip icon-large"></i></div>'
                    + '<div class="filename span10">' + file.name + '</div>'
                    + '<div class="remove_file file' + ind + ' span1"><i class="icon-remove-sign icon-small"></i></div>'
                + '</div>');
        var uploaded = $('input[name="uploaded_file"]').val();
        $('input[name="uploaded_file"]').val(uploaded + file.entity + ';');
        $('#files_uploaded_container .remove_file.file' + ind).click(function(){
            DeleteFile(this);
        });
        $('#edit-submission-submit').removeAttr('disabled');
    }

    function DeleteFile(elem) {
        var index = $(elem).parent().index();
        console.log(index);
        console.log($(elem).parent());
        var ArrayUploaded = $('input[name="uploaded_file"]').val().split(';');
        ArrayUploaded = jQuery.grep(ArrayUploaded, function(value) {
            return value != ArrayUploaded[index];
        });
        ArrayUploaded = jQuery.grep(ArrayUploaded, function(value) {
            return value != '';
        });
        if(ArrayUploaded.length === 0) {
            $('input[name="uploaded_file"]').val('');
            $('#edit-submission-submit').attr('disabled','disabled');
        }
        else {
            $('input[name="uploaded_file"]').val(ArrayUploaded.join(";") + ';');
        }
        $(elem).parent().hide('fast', function(){
            $(elem).parent().remove();
        });
    }
});