<div class="group-image">
	<?php print render($content_group['image']); ?>
</div>
<?php if($content_group['subscribe']) : ?>
<div class="group-unsubscribe hide">
    <?php print render($content_group['unsubscribe_link']); ?>
</div>
<?php endif; ?>
<div class="group-title">
	<?php print render($content_group['title']); ?>
</div>
