<?php

/**
 * @file
 * Default theme implementation to display a node.
 *
 * Available variables:
 * - $title: the (sanitized) title of the node.
 * - $content: An array of node items. Use render($content) to print them all,
 *   or print a subset such as render($content['field_example']). Use
 *   hide($content['field_example']) to temporarily suppress the printing of a
 *   given element.
 * - $user_picture: The node author's picture from user-picture.tpl.php.
 * - $date: Formatted creation date. Preprocess functions can reformat it by
 *   calling format_date() with the desired parameters on the $created variable.
 * - $name: Themed username of node author output from theme_username().
 * - $node_url: Direct url of the current node.
 * - $display_submitted: Whether submission information should be displayed.
 * - $submitted: Submission information created from $name and $date during
 *   template_preprocess_node().
 * - $classes: String of classes that can be used to style contextually through
 *   CSS. It can be manipulated through the variable $classes_array from
 *   preprocess functions. The default values can be one or more of the
 *   following:
 *   - node: The current template type, i.e., "theming hook".
 *   - node-[type]: The current node type. For example, if the node is a
 *     "Blog entry" it would result in "node-blog". Note that the machine
 *     name will often be in a short form of the human readable label.
 *   - node-teaser: Nodes in teaser form.
 *   - node-preview: Nodes in preview mode.
 *   The following are controlled through the node publishing options.
 *   - node-promoted: Nodes promoted to the front page.
 *   - node-sticky: Nodes ordered above other non-sticky nodes in teaser
 *     listings.
 *   - node-unpublished: Unpublished nodes visible only to administrators.
 * - $title_prefix (array): An array containing additional output populated by
 *   modules, intended to be displayed in front of the main title tag that
 *   appears in the template.
 * - $title_suffix (array): An array containing additional output populated by
 *   modules, intended to be displayed after the main title tag that appears in
 *   the template.
 *
 * Other variables:
 * - $node: Full node object. Contains data that may not be safe.
 * - $type: Node type, i.e. story, page, blog, etc.
 * - $comment_count: Number of comments attached to the node.
 * - $uid: User ID of the node author.
 * - $created: Time the node was published formatted in Unix timestamp.
 * - $classes_array: Array of html class attribute values. It is flattened
 *   into a string within the variable $classes.
 * - $zebra: Outputs either "even" or "odd". Useful for zebra striping in
 *   teaser listings.
 * - $id: Position of the node. Increments each time it's output.
 *
 * Node status variables:
 * - $view_mode: View mode, e.g. 'full', 'teaser'...
 * - $teaser: Flag for the teaser state (shortcut for $view_mode == 'teaser').
 * - $page: Flag for the full page state.
 * - $promote: Flag for front page promotion state.
 * - $sticky: Flags for sticky post setting.
 * - $status: Flag for published status.
 * - $comment: State of comment settings for the node.
 * - $readmore: Flags true if the teaser content of the node cannot hold the
 *   main body content.
 * - $is_front: Flags true when presented in the front page.
 * - $logged_in: Flags true when the current user is a logged-in member.
 * - $is_admin: Flags true when the current user is an administrator.
 *
 * Field variables: for each field instance attached to the node a corresponding
 * variable is defined, e.g. $node->body becomes $body. When needing to access
 * a field's raw values, developers/themers are strongly encouraged to use these
 * variables. Otherwise they will have to explicitly specify the desired field
 * language, e.g. $node->body['en'], thus overriding any language negotiation
 * rule that was previously applied.
 *
 */
//HELP
//Use dpm($content); Outputs the content variable for inspection.
//General principle to alter classes: access $content['field_name']['#attributes']['class'];
//Example - add a classe to a field wrapper: $content['body']['#attributes']['class'][] = 'my_class';
//Please place the class alteration at the beginning of this template - eventually, they will belong to druedu_layout_alter_node_view()
//Adding a variation of this template: create a node--content_type_machine_name.tpl.php file
?>
<article id="node-<?php print $node->nid; ?>" class="<?php print $classes; ?> clearfix"<?php print $attributes; ?>>
	<header>
    <?php print render($title_prefix); ?>
    <?php if ($title): ?>
      <h2<?php print $title_attributes; ?>><?php print $title; ?></h2>
    <?php endif; ?>
    <?php print render($title_suffix); ?>
    <?php print render($variables['status_locked_form']) ; ?>
    <?php if (isset($variables['status_marked_form'])) : ?>
      <?php print render($variables['status_marked_form']) ; ?>
    <?php else : ?>
        <?php if(!empty($marked_date)) : ?>
          <div class="marked"><?php print t('This assignment has been marked'). ' : ' . $marked_date; ?> </div>
        <?php endif; ?>
    <?php endif; ?>
        <div class="due_info">
          <span class="due label label-important"> <?php print render($due_date); ?></span>
          <?php print t('On') . ' ' . render($limit_date); ?>
          <span class="subject"> <?php print l(t(render($subject)), $subject_link, array('attributes' => array('class' => array('btn', 'btn-link')))); ?></span>
          <span class="separator"> / </span>
          <span class="teacher"> <?php print l($variables['teacher_assignment_set'], 'user/'.$variables['teacher_uid'], array('attributes' => array('class' => array('btn', 'btn-link')))); ?></span>
        </div>
    <?php if (!is_null($in_class)) : ?>
      <?php print render($in_class); ?>
    <?php endif; ?>
  </header>
  <button id="switch_submissions" class="btn btn-link btn-mini"><i class="icon-retweet"></i> <?php print t('Switch'); ?></button>
  <div id="last_submission_block">
    <div id="flip">
      <div class="state">
    <?php print theme('last_submission_student_block', array('last_submission_block' => $variables['last_submission_student_block'])); ?>
    <?php print theme('last_submission_teacher_block', array('last_submission_block' => $variables['last_submission_teacher_block'])); ?>
      </div>
    </div>
  </div>
  <!-- SUBMISSION FORM -->
  <div id="submission_block" class="<?php print $variables['submission_block_class']; ?>">
    <div id="ui_upload" class="<?php print $variables['hide_close']; ?>">
      <div id="dragndrop-area">
        <p class="dragndrop"><?php print t("Drag'n'drop to upload files or")?></p>
        <span class="pc_files"><a class="btn btn-success" href="#"><?php print t('Upload new files'); ?></a></span>
        <span class="server_files"><a class="btn btn-success" href="#filevault-modal" role="button" data-toggle="modal" id="big-media"><?php print t('Files on server'); ?></a></span>
      </div>
      <section id="filevault_ui_block" class="block">
          <div class="progress_bars">
            <div class="progress" id="progress_all">
              <div class="bar" style="width: 0%;"></div>
            </div>
          </div>
      </section>
    </div>
    <div id="submission_form" class="<?php print $variables['collapsed']; ?>">
      <div class="inner-form img-polaroid img-rounded">
<!-- 		    <b class="triangle_top"></b> -->
        
        <div id="files_uploaded">
          <h4><?php print t('Files uploaded'); ?></h4>
           <div id="files_uploaded_container"></div>
        </div>
        <?php print render($variables['submission_form']) ; ?>
      </div>
    <?php $temp = block_get_blocks_by_region('Filevault'); print render($temp); ?>
    </div>
    <button id="submission_toggle" type="button" class="btn btn-small" data-toggle="collapse" data-target="#submission_form"><?php print $variables['collapsed_default_message']; ?></button>
  </div>
  <!-- -->
  <div class="sub_content">
  <?php print render($variables['body_assignment_set']); ?>
  <?php if (!empty($attachments_assignment_set)) : ?>
  <div class="field field-name-field-attachments field-type-filevault-field field-label-above">
    <div class="field-label"><?php print t('Attachments').' :';?></div>
       <?php foreach($attachments_assignment_set as $file) : ?>
        <?php print render($file); ?>
        <div class="field-item"> </div>
       <?php endforeach; ?>
    </div>
  </div>
<?php endif; ?>
  <!-- NEED HELP -->
  <h3><?php print t('Need Help').' ?'; ?></h3>
   <?php if (module_exists('druedu_qa')) : ?>
   <?php global $base_url; ?>
   <span class="btn btn-inverse"><i class="icon-external-link"></i><?php print l(t('Ask a question in Q&A'), 'questions'); ?></span>
  <?php endif; ?>
  <span class="btn btn-inverse"><i class="icon-external-link"></i><?php print l(t('Go to learning support'), $subject_link); ?></span>


</article> <!-- /.node -->
