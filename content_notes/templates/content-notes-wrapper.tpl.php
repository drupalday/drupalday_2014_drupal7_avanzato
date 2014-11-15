<?php
/**
 * Created by PhpStorm.
 * User: adrianocori
 * Date: 14/11/14
 * Time: 12:45
 */
?>
<div id="content-notes">
  <?php if ($title): ?>
  <h3><?php print $title; ?></h3>
  <?php endif; ?>
  <div id="content-notes-wrapper">
    <?php print render($children); ?>
  </div>
</div>