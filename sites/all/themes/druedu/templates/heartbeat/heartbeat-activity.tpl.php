<?php 
//<div class="<?php print $classes;? >"<?php print $attributes; ? >>
  //< ?php print render($content); ? s>
  //tes123564564
//</div>
?>
<?php foreach ($content as $key => $value){ $$key = $value; } ?>
<div class="heartbeat-activity clearfix">
  <div class="heartbeat-group-left">
    <?php print render($avatar); ?>
  </div>
  <div class="hearbeat-group-right">
    <?php print render($message); ?>
    <?php print render($time); ?>
  </div>
</div>