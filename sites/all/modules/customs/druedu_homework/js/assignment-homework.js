jQuery(function ($) {
    var ind = 0;
    var indUpload = 0;
    druedu_homework_assignment_init('');

    $.fn.show_homework_submission_form = function(){};

    $.fn.hide_homework_submission_form = function(){};

    $.fn.reset_homework_timeline_comment_form = function(){
        $('#druedu-homework-timeline-comment-form textarea').val('');
    };
    $.fn.initialiseSubmissionId = function(block_id){
        $('input[name="last_submission"]').val($(block_id + ' .submit-info').attr('submission'));
    };
    $.fn.reset_update_last_submission_form = function(){
        var ArrayUploaded = $('input[name="add_files_last_submission"]').val().split(';');
        ArrayUploaded = jQuery.grep(ArrayUploaded, function(value) {
            return value != '';
        });
        $.each(ArrayUploaded, function(index, value) {
            indUpload += 1;
            var file = jQuery.parseJSON(value);
            $('#new_files_uploaded').before(
                '<div class="item item'+indUpload+'" filevault="'+file.id+'" rel="tooltip" data-placement="right" data-original-title="'+ Drupal.t('Minimum one file is required') +'">'      
                    + '<i class="icon-paper-clip icon-small"></i>'
                    + '<a href="'+file.url+'" class="btn btn-link">'+file.filename+'</a>'
                    + '<i class="icon-remove-sign delete-item icon-small hide"></i>'
                + '</div>'
            );
            $('.submit-attch .item'+indUpload+' .delete-item').click(function(){
                RemoveFile(this);
            });
        });
        var ArrayDeleted = $('input[name="delete_files_last_submission"]').val().split(';');
        ArrayDeleted = jQuery.grep(ArrayDeleted, function(value) {
            return value != '';
        });
        $.each(ArrayDeleted, function(index, value) {
            $('div[filevault="'+value+'"]:first').remove();
        });
        $('#nb_file_last_submission').html($('.submit-attch .item').length);
        $('#icon-cancel').click();
        $('#new_files_uploaded_container div').remove();
        $('input[name="delete_files_last_submission"]').val('');
        $('input[name="add_files_last_submission"]').val('');
        ind = 0;
    };

    Drupal.behaviors.druedu_homework_assignment = {
        attach: function (context, settings) {
            druedu_homework_assignment_init(context);
        }
    }

    function druedu_homework_assignment_init(context){

        $('#switch_submissions', context).click(function(){
            if($('#flip .state.flipped').length) {
                $('#flip .state').removeClass('flipped');
            }
            else{
                $('#flip .state').addClass('flipped');
            }
            if($('#icon-cancel').is(':visible')){
                $('.submit-attch .item').tooltip('destroy');
            }
        });

        $('#icon-edit', context).bind('click', function(){
            var parent = '#' + $(this).closest('.face').attr('id');
            $(this).toggleClass('hide');
            $(parent + ' #icon-save').toggleClass('hide');
            $(parent + ' #icon-cancel').toggleClass('hide');
            $(parent + ' #icon-add').toggleClass('hide');
            $(parent + ' .delete-item').toggleClass('hide');
            $('#new_files_uploaded').toggleClass('hide');
            $(parent + ' .submit-attch').toggleClass('editing');
            if($('#submission_form').hasClass('in')) {
                $('#submission_toggle').click();
            }
            lastFileOfSubmission(parent);
            $('#submission_toggle').attr('disabled', 'disabled');
            $('#ui_upload').removeClass('hide');

        });

        $('#icon-save', context).bind('click', function(){
            var parent = '#' + $(this).closest('.face').attr('id');
            var buttonSubmit = $(parent + ' button[type="submit"]').attr('id');
            var submitLastSubmission = Drupal.settings.ajax[buttonSubmit];
            $(submitLastSubmission.element).trigger(submitLastSubmission.event);
        });

        $('#icon-cancel', context).bind('click', function(){
            var parent = '#' + $(this).closest('.face').attr('id');
            $(parent + ' #icon-save').toggleClass('hide');
            $(parent + ' #icon-edit').toggleClass('hide');
            $(parent + ' .delete-item').not('.hide').toggleClass('hide');
            $('#new_files_uploaded').toggleClass('hide');
            $(parent + ' .submit-attch').toggleClass('editing');
            $(this).toggleClass('hide');
            $('input[name="delete_files_last_submission"]').val('');
            $('input[name="add_files_last_submission"]').val('');
            $('#new_files_uploaded_container .file-item').remove();
            $(parent + ' .submit-attch .item').fadeIn('fast');
            $('#submission_toggle').removeAttr('disabled');
            $('#ui_upload').addClass('hide');
            $(parent + ' .submit-attch .item').removeAttr('rel').removeAttr('data-placement').removeAttr('data-original-title');
            $(parent + ' .submit-attch .item').tooltip('destroy');
        });

        $('.submit-attch .delete-item', context).bind('click', function(){
            RemoveFile(this);
        });
    }

    $('#change_status_locked_assignment button').click(function() {
        $('#druedu-homework-status-locked-assignment-form').submit();
    });

    $('input[name="last_submission"]').val($('input[name="last_submission"]').closest('.face').find('.submit-info').attr('submission'));

    $('#filevault_core_block').bind('fv_upload_done', function(e, data) {
        if($('#icon-save:not(.hide)').length) {
            $.each(data.result, function (index, file) {
                ind += 1;
                filesUploaded(ind, file);   
            });
        }
    });

    $('#submission_toggle').bind('click', function(){

        if($('#submission_form').hasClass('in')) {
            $(this).html(Drupal.settings.collapsed_message_close);
            $('#ui_upload').addClass('hide');
        }
        else{
            $(this).html(Drupal.settings.collapsed_message_open);
            $('#ui_upload').removeClass('hide');
        }
    });

    // BIND EVENT
    jQuery('#filevault-modal .insert').live('click', function (e){
        if($('#icon-save:not(.hide)').length) {
            ind += 1;
            $("#filevault-modal").modal("hide");
            var file = jQuery(this).parents('li').data('json');
            filesUploaded(ind, file);
        }
    });

    function RemoveFile(elem){
        var parent = '#' + $(elem).closest('.face').attr('id');
        var items = $('input[name="delete_files_last_submission"]').val();
        var itemToDelete = $(elem).parent().fadeOut('fast', function(){
            lastFileOfSubmission(parent);
        }).attr('filevault');
        $('input[name="delete_files_last_submission"]').val(items + itemToDelete + ';');
    }

    function DeleteFile(elem) {
        var index = $(elem).parent().index();
        var ArrayUploaded = $('input[name="add_files_last_submission"]').val().split(';');
        ArrayUploaded = jQuery.grep(ArrayUploaded, function(value) {
            return value != ArrayUploaded[index];
        });
        ArrayUploaded = jQuery.grep(ArrayUploaded, function(value) {
            return value != '';
        });
        if(ArrayUploaded.length === 0) {
            $('input[name="add_files_last_submission"]').val('');
        }
        else {
            $('input[name="add_files_last_submission"]').val(ArrayUploaded.join(";") + ';');
        }
        $(elem).parent().hide('fast', function(){
            $(elem).parent().remove();
        });
    }

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
        $('#new_files_uploaded_container').append(
            '<div class="file ' + ind + ' file-item clearfix">'
                + '<div class="file_icon span1"><i class="icon-paper-clip icon-large"></i></div>'
                + '<div class="filename span10">' + file.name + '</div>'
                + '<div class="remove_file file' + ind + ' span1"><i class="icon-remove-sign icon-small"></i></div>'
            + '</div>');
            var uploaded = $('input[name="add_files_last_submission"]').val();
            $('input[name="add_files_last_submission"]').val(uploaded + file.entity + ';');
            $('#new_files_uploaded_container .remove_file.file' + ind).click(function(){
            DeleteFile(this);
        });
    }

    function lastFileOfSubmission(parent) {
        if($(parent + " .submit-attch > div.item:visible").size() == 1) {
             $(parent + ' .delete-item').addClass('hide');
             $(parent + ' .submit-attch .item:visible').attr('rel', 'tooltip').attr('data-placement', 'right').attr('data-original-title', Drupal.t('Minimum one file is required'));
             $(parent + ' .submit-attch .item:visible').tooltip('show');
        }
    }
});