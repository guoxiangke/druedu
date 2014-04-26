<?php global $base_url; ?>
<div id="wrapper" class="container-fluid">
  <div class="row-fluid">
      <div class="main-content" class="span12">
        <center><img src="<?php print $base_url.'/'.path_to_theme(); ?>/img/BCISLogo.png" class="logo" /></center>
        <center><?php print $messages; ?></center>
        <?php print render($page['content']); ?>
      </div>
  </div>
</div>