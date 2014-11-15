<?php
/**
 * Created by PhpStorm.
 * User: adrianocori
 * Date: 14/11/14
 * Time: 12:07
 */
?>
<div class="content-note-wrapper">
  <span class="content-info"><?php print t('Created by !author on !date', array('!author' => $author, '!date' => $date)) ?></span>
  <p><?php print $note->note; ?></p>
  <?php print drupal_render($links); ?>
  <div class="clearfix"></div>
</div>