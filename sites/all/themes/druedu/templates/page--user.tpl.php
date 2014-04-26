<?php
// Both sidebars showing
if ($page['sidebar_left'] && $page['sidebar_right']) {
  $cspan = 7;
}
// Only right showing
if (!$page['sidebar_left'] && $page['sidebar_right']) {
  $cspan = 9;
}
// Only left showing
if ($page['sidebar_left'] && !$page['sidebar_right']) {
  $cspan = 10;
}
// None showing
if (!$page['sidebar_left'] && !$page['sidebar_right']) {
  $cspan = 12;
}
?>

<header>

  <div class="navbar navbar-inverse navbar-fixed-top">
    <div class="navbar-inner">
      <div class="container-fluid">

        <?php if ($logo): ?>
          <a class="brand" href="<?php print $front_page; ?>" title="<?php print t('Home'); ?>">
            <img src="<?php print $logo; ?>" alt="<?php print t('Home'); ?>" />
          </a>
        <?php endif; ?>

        <?php if ($easy_breadcrumb): ?>
          <div class="brand"><?php print $easy_breadcrumb; ?></div>
        <?php endif;?>

        <?php if ($secondary_nav): ?>
          <?php print $secondary_nav; ?>
        <?php endif; ?>

        <?php if ($grades_nav): ?>
          <?php print $grades_nav; ?>
        <?php endif; ?>

        <?php if ($search): ?>
          <div class="pull-right search"><?php print render($search); ?></div>
        <?php endif; ?>

      </div>
    </div>
  </div>

  <?php if ($page['highlighted']): ?>
    <?php print render($page['highlighted']); ?>
  <?php endif; ?>

</header>

<div id="wrapper" class="container-fluid">
  <?php print $messages; ?>

  <?php if ($page['help']): ?>
    <div class="help">
      <div class="alert alert-info">
        <h4><i class="icon-info-sign"></i> Help</h4>
        <?php print render($page['help']); ?>
      </div>
    </div><!-- help -->
  <?php endif; ?>

  <div id="main-menu" class="pull-left">
    <?php print render($page['sidebar_first']); ?>
  </div><!-- main-menu -->
  
<div id="profile">
  <div id="content" class="clearfix">

    <div class="container-fluid">
      <div class="row-fluid">
        <?php if ($page['sidebar_left']): ?>
          <?php print render($page['sidebar_left']); ?>
        <?php endif; ?>
        <span id="main-content" class="span<?php echo $cspan; ?>">
          <div class="main-content">
            <?php print render($page['content']); ?>
          </div>
        </span><!-- main-content.span7/9 -->

        <?php if ($page['sidebar_right']): ?>
          <?php print render($page['sidebar_right']); ?>
        <?php endif; ?>

    </div><!-- row-fluid -->
  </div><!-- container-fluid -->

  <footer>
    <?php print render($page['footer']); ?>
  </footer>

</div><!-- profile -->
</div><!-- content -->


</div><!-- wrapper -->
  <div id="filevault_hidden_blocks">
      <?php print render($page['filevault']); ?>
  </div>

<?php if ($page['dev']): ?>
  <?php print render($page['dev']); ?>
<?php endif; ?>