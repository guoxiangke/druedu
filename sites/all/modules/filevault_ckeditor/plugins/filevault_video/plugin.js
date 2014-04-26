/**
 * Basic sample plugin inserting abbreviation elements into CKEditor editing area.
 *
 * Created out of the CKEditor Plugin SDK:
 * http://docs.ckeditor.com/#!/guide/plugin_sdk_sample_1
 */

// Register the plugin within the editor.
CKEDITOR.plugins.add( 'filevault_video', {

	// The plugin initialization logic goes inside this method.
	init: function( editor ) {

		editor.on( 'doubleclick', function( evt ){
				var element = evt.data.element;

				if ( element.is( 'video' ) ){

          var doc = document;
          var selection = window.getSelection();
          var range = doc.createRange();

          selection.removeAllRanges();

          range.selectNode( evt.data.element.$.parentNode.nextSibling);
          selection.addRange(range);

          range.selectNode( evt.data.element.$.parentNode);
          selection.addRange(range);

          range.selectNode( evt.data.element.$.parentNode.previousSibling);
          selection.addRange(range);

				}
		});

	}
});
