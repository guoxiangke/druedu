<?php hide($content['links']); ?>

<div class="comment clearfix">

  <span class="span1">
    <?php print $picture; ?>
  </span>

  <span class="span11">
    <div class="arrow-left pull-left"></div>
    <blockquote>

      <div class="submitted">
        <?php print $submitted; ?>
        <?php if ($new): ?>
        <span class="label label-success pull-right"><?php print $new; ?></span>
      <?php endif; ?>
      </div>



      <?php print render($content); ?>

      <div class="actions clearfix">
        <?php print render($content['links']) ?><span class="permalink pull-right"><?php print $permalink; ?></span>
      </div>

    </blockquote>

  </span>

</div>
