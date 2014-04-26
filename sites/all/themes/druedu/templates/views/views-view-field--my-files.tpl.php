<?php

/**
 * @file
 * This template is used to print a single field in a view.
 *
 * It is not actually used in default Views, as this is registered as a theme
 * function which has better performance. For single overrides, the template is
 * perfectly okay.
 *
 * Variables available:
 * - $view: The view object
 * - $field: The field handler object that can process the input
 * - $row: The raw SQL result that can be used
 * - $output: The processed output that will normally be used.
 *
 * When fetching output from the $row, this construct should be used:
 * $data = $row->{$field->field_alias}
 *
 * The above will guarantee that you'll always get the correct data,
 * regardless of any changes in the aliasing that might happen if
 * the view is modified.
 */
?>

<?php

  $dom = new DOMDocument;
  $dom->loadHTML($output);

  foreach ($dom->getElementsByTagName('a') as $node) {
    $output = $node->getAttribute( 'href' );
  }


	if( strpos($output, "mp4") ){
			print '<video width="100" height="75" controls="controls"><source src="'.$output.'" type="video/mp4" />Your browser does not support the video tag.</video>';
	}else{

      $parsedURL = parse_url($output);
      $path = $_SERVER['DOCUMENT_ROOT'].urldecode( $parsedURL['path']);
      if(file_exists($path)) {
        $size = getimagesize( $path );
      }else{
        $size[0] = 0;
        $size[1] = 0;
      }

      $original = $output;

      global $base_url;
      $ds = file_default_scheme();
      $sw = file_stream_wrapper_get_instance_by_scheme($ds);
      //check that url is from this site and from default stream wrapper
      if (preg_match('`^' . preg_quote($base_url . '/' . $sw->getDirectoryPath() . '/') . '`', $output)) {
        $uri = $ds . '://' . preg_replace('`^' . preg_quote($base_url . '/' . $sw->getDirectoryPath() . '/') . '`', '', $output);
        $output = $uri;
      }
      else {
        $output = "";
      }

      $large = image_style_url("large", $output);

      print '<img src="'.image_style_url("my_media_thumbnails", $output).'" height="100px" data-org-height="'. $size[1] .'" data-org-width="'. $size[0].'" data-original="'. $original .'" data-large="'. $large .'" />';


	}

 ?>
