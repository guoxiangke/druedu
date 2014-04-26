// Click shemaphore to handle single and double clicks
var alreadyclicked = false;
var timer;


/**
 * File Object Single Click Handler
 */
function single_click(e){

  // Set the shemaphore
  alreadyclicked = false

  // Get json
  var fileobject = $(e.target).parents('.fileobject');
  var json = $(fileobject).find('.json').html();
  var file = $.parseJSON(json);

  // Set focus on the fileobject
  $(fileobject).focus();

  $('.fileinfo').data('activefile',file);

  // Set value in the meta box
  $('.fileinfo .filename').val(file[0].filename);
  $('.fileinfo .filesize').text(file[0].size);

  // If the click did not happen on the play button. Stop the video.
  var video_id = $(fileobject).find('video').attr('id');
  var myPlayer = _V_(video_id);
  myPlayer.currentTime(0); // 2 minutes into the video
  myPlayer.pause();
  myPlayer.posterImage.el.style.display = 'block';
  myPlayer.bigPlayButton.show();
}


/**
 * File Object Double Click Handler
 */
function double_click(){

}


/**
 * Document ready
 *
 */
$(function() {

  // Share Autocompleter
  $("body.page-filevault-navi #shareuser").typeahead({
      minLength: 3,
      source: function(query, process) {
        $.post('filevault/ajax/user_autocomplete', { q: query, limit: 8 }, function(data) {
                process(JSON.parse(data));
        });
      }
  });

	// Debug info
	$('video').bind('loadstart',function(e){
		console.log( "Video started loading: " + e.target.id);
		e.preventDefault();
	});



  $("body.page-filevault-navi .type-selector").click(function(e) {

    var active_type = $('.type-selector button.active');
    var selector ="";

    for (var i = active_type.length - 1; i >= 0; i--) {
       selector += "."+$(active_type[i]).data('type') +",";
    };

    console.log(selector);


    // Hide all
    $( ".fileobject").hide();

    // Show selected
    $(selector).show();

  });

  $("body.page-filevault-navi #shareuser").typeahead({});

  $("body.page-filevault-navi .fileobject").click(function(e) {

    if(!alreadyclicked){

      // don't go to the link
      e.preventDefault();

      // set the shemaphore
      alreadyclicked = true;

      // Set the timer
      timer = setTimeout( function(){ single_click(e) }, 200);
      return false;

    }

    // stop the single click function to be run
    clearTimeout(timer);

    // Set the shemaphore
    alreadyclicked = false

    // Does not preventDefault, so the link get's activate.
    double_click();

  });

  $("body.page-filevault-navi .fileobject .delete").click(function(e) {
    var path = "";
    var file = $('.fileinfo').data('activefile');

    $.post('filevault/ajax/delete', { path: path, file: file }, function(data) {
    });
  });

});
