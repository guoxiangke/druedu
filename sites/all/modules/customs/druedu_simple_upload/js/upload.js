$(document).ready(function() {

	// Makes sure the dataTransfer information is sent when we
	// Drop the item in the drop box.
	jQuery.event.props.push('dataTransfer');

	$('#loading').css({'display' : 'none'});

	var z = -40;
	// The number of images to display
	var maxFiles = 5;
	var errMessage = 0;

	// Get all of the data URIs and put them in an array
	var dataArray = [];

  document.addEventListener("dragenter", function(e) { e.stopPropagation(); e.preventDefault(); }, false);
  document.addEventListener("dragexit", function(e) { e.stopPropagation(); e.preventDefault(); }, false);
  document.addEventListener("dragover", function(e) { e.stopPropagation(); e.preventDefault(); }, false);
  document.addEventListener("drop", drop, false);

  CKEDITOR.on('instanceReady', function(e){

  	var iframe = document.getElementsByTagName('iframe')[0]
    var doc = iframe.contentWindow.document

  	doc.addEventListener("dragenter", function(e) { e.stopPropagation(); e.preventDefault(); }, false);
  	doc.addEventListener("dragexit", function(e) { e.stopPropagation(); e.preventDefault(); }, false);
  	doc.addEventListener("dragover", function(e) { e.stopPropagation(); e.preventDefault(); }, false);
  	doc.addEventListener("drop", drop, false);

  });

	// Bind the drop event to the dropzone.
	function drop(e){

		// Stop the default action, which is to redirect the page
		// To the dropped file

		e.stopPropagation();
  	e.preventDefault();

  	dataArray.length = 0;

		var files = e.dataTransfer.files;

		// Show the upload holder
		$('#uploaded-holder').show();

		// For each file
		$.each(files, function(index, file) {

			// Start a new instance of FileReader
			var fileReader = new FileReader();

				// When the filereader loads initiate a function
				fileReader.onload = (function(file) {

					return function(e) {

						// Push the data URI into an array
						dataArray.push({name : file.name, value : this.result});

						// Move each image 40 more pixels across
						z = z+40;
						var image = this.result;
						upload();


					};

				})(files[index]);

			// For data URI purposes
			fileReader.readAsDataURL(file);


		});


	}

	function restartFiles() {

		// This is to set the loading bar back to its default state
		$('#loading-bar .loading-color').css({'width' : '0%'});
		$('#loading').css({'display' : 'none'});
		$('#loading-content').html(' ');
		// --------------------------------------------------------

		// And finally, empty the array/set z to -40
		dataArray.length = 0;
		z = -40;

		return false;

	}

	function upload(){

		$("#loading").show();
		var totalPercent = 100 / dataArray.length;
		var x = 0;
		var y = 0;

		//$('#loading-content').html('Uploading '+dataArray[0].name);

		$.each(dataArray, function(index, file) {

			$.post(druedu_simple_upload_path, dataArray[index], function(data) {

				var fileName = dataArray[index].name;
				++x;


				// Change the bar to represent how much has loaded
				$('#loading-bar .loading-color').css({'width' : totalPercent*(x)+'%'});

				if(totalPercent*(x) == 100) {
					// Show the upload is complete
					$('#loading-content').html('Uploading Complete!');

					// Reset everything when the loading is completed
					setTimeout(restartFiles, 500);

				} else if(totalPercent*(x) < 100) {

					// Show that the files are uploading
					$('#loading-content').html('Uploading '+fileName);

				}

				// Show a message showing the file URL.
				var dataSplit = data.split('#%#');
				if(dataSplit[1] == 'uploaded successfully') {


				if(dataSplit[2].toLowerCase() == 'png' || dataSplit[2].toLowerCase() == 'jpg' || dataSplit[2].toLowerCase() == 'jpeg' || dataSplit[2].toLowerCase() == 'gif' ) {
						var media = '<img src="' + dataSplit[0] +'"  style="margin:15px;"/>';
				}else if ( dataSplit[2].toLowerCase() == 'mp4'){
						var media = '<video width="320" height="240" controls="controls"  style="margin:15px;" ><source src="'+ dataSplit[0] +'" type="video/mp4" />Your browser does not support the video tag.</video>';
				}else{
						var media = '<a href="' + dataSplit[0] +'"  style="margin:15px;"/>'+ dataSplit[3] + '</a>';
				}

					 Drupal.insert.insertIntoActiveEditor(media);

				}

			});
		});


		return false;
	}

});
