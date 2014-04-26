<h1><i class="icon-comments-alt"></i><?php print t('What\'s happening in'). ' ' . $group->title; ?></h1>
<table>
<?php foreach ($rows as $id => $row): ?>
	<?php print $row; ?>
<?php endforeach; ?>
</table>