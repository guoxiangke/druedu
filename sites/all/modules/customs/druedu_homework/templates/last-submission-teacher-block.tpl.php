<div id="last_submission_teacher_block" class="face back">
  <?php if (isset($last_submission_block['has_submission'])) : ?>
    <p class="no-submission"><?php print t('No submission record.'); ?></p>
  <?php else : ?>
  <!-- LAST SUBMISSION -->
  <div class="submit-block img-polaroid img-rounded">
    <div class="submit-info" submission="<?php print $last_submission_block['field_collection_entity_id'] ?>">
      <?php print render($last_submission_block['last_submissions']['firstname']); ?>
      <?php print render($last_submission_block['last_submissions']['lastname']); ?>
      <?php print t('submitted') . ' <span id="nb_file_last_submission">' . render($last_submission_block['last_submissions']['nb_file']) . '</span> ' . t('files for this homework'); ?> 
       <?php //if (!is_null($last_submission_block['on_time'])) : ?>
          <?php //print render($last_submission_block['on_time']); ?>
        <?php //endif; ?>
      <?php if (!is_null($last_submission_block['last_submissions']['field_submission_date'])) : ?>
        <?php print '( '. render($last_submission_block['last_submissions']['field_submission_date']) . ' )'; ?>
      <?php endif; ?>
       <?php //if (!is_null($last_submission_block['difficulty'])) : ?>
      <!-- <span class="level"><?php //print t('This assignment is') . ' ' . '<span class="difficulty ' . strtolower(str_replace(' ', '_', $last_submission_block['difficulty'])) .'">' . t($last_submission_block['difficulty']) . '</span>'; ?></span> -->
      <?php //endif; ?>
      <?//php if (!is_null($last_submission_block['last_submissions']['field_submission_comment'])) : ?>
      <?//php print render($last_submission_block['last_submissions']['field_submission_comment']); ?>
      <?//php endif; ?>
    </div>
    <div class="submit-attch clearfix">
    <?php if (isset($last_submission_block['can_edit']) && $last_submission_block['can_edit']) : ?>
      <div class="options">
          <i id="icon-save" class="icon-check hide icon-small"><span><?php print  t('Save'); ?></span></i> 
          <i id="icon-cancel" class="icon-remove-circle hide icon-small"><span><?php print t('Cancel'); ?></span></i>
          <i id="icon-edit" class="icon-edit icon-small"><span><?php print t('Edit'); ?></span></i>
      </div>
    <?php endif; ?>

    <?php foreach($last_submission_block['last_submissions']['field_submission_filevault'] as $file) : ?>
        <div class="item" filevault="<?php print $file['fid']; ?>">      
        <i class="icon-paper-clip icon-small"></i><?php print $file['link']; ?> <i class="icon-remove-sign delete-item hide icon-small"></i>
          </div>
    <?php endforeach; ?>
    <?php if (isset($last_submission_block['can_edit']) && $last_submission_block['can_edit']) : ?>
      <div id="new_files_uploaded" class="hide">
            <h4><?php print t('New Files') ?></h4>
            <div id="new_files_uploaded_container"></div>
      </div>
      <?php if (isset($last_submission_block['form'])) : ?>
        <?php print render($last_submission_block['form']); ?>
      <?php endif; ?>
    <?php endif; ?>
    </div>
  </div>
  <?php endif; ?>
</div>