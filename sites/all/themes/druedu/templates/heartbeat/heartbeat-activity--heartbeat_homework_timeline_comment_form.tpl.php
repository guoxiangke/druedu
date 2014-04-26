<div class="<?php print $classes;?> clearfix"<?php print $attributes; ?>>
<?php if(in_array('student', $content['avatar']['class'])) : ?>
	<?php print render($content['avatar']); ?>
<?php else : ?>
	<?php hide($content['avatar']); ?>
<?php endif; ?>

<?php if(in_array('teacher', $content['avatar']['class'])) : ?>
	<?php print render($content['avatar']); ?>
<?php endif; ?>
	<div class="comment-content">
		<?php print render($content); ?>
	</div>
</div>