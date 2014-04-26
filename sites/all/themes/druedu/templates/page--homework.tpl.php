<?php 
	$showRight = ($page['sidebar_right']) ? TRUE : FALSE ; 
	if($page['sidebar_right'] && $sidebarRight) {
		$cspan = 9;
	}
	else {
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
<?php 
  //page level id for specific theme 
  //use case:if you have a page like this: http://example.com/mypage,
  //and you want add a css ID on that page:<div id="mypage">..</div>,
  //you can push the "mypage" to $specific_pages.
  //@see template.php druedu_preprocess_page()
  //-guo
if (isset($page_id)): ?>
<div id="<?php echo $page_id; ?>">
<?php endif; ?>

	<div id="content" class="clearfix">

		<div class="container-fluid">
			<div class="row-fluid">

				<span id="main-content" class="span<?php echo $cspan; ?>">
					<?php if ($showRight): ?>
						<div class="seperator-right pull-right" id="hide-sidebar"><i class="icon-columns"></i></div>
					<?php endif; ?>
					<div class="main-content">
						<div><?php print render($page['content']); ?></div>
					</div>
				</span><!-- main-content.span7/9 -->

				<?php if ($page['sidebar_right']): ?>
					<?php print render($page['sidebar_right']); ?>
				<?php endif; ?>

			</span>
		</div><!-- row-fluid -->
	</div><!-- container-fluid -->

	<footer>
		<?php print render($page['footer']); ?>
	</footer>

</div><!-- content -->
<?php if (isset($page_id)): ?>
</div>
<?php endif; //end of page_id ?>

</div><!-- wrapper -->

<?php if ($page['dev']): ?>
	<?php print render($page['dev']); ?>
<?php endif; ?>
