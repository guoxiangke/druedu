<?php foreach ($content as $key => $value){ $$key = $value; } ?>

<tr class="heartbeat-activity">
  <td class="heartbeat-group-left">
    <?php print render($avatar); ?>
  </td>
  <td>
    <?php print render($message); ?>
    <?php print render($time); ?>
  </td>
</tr>
