<?php
/**
 * Register heartbeat templates.
 *
 * @see hook_ctools_plugin_api.
 */
function druedu_homework_heartbeat_template_info() {

  $heartbeatmessagetemplates = array();

  $heartbeatmessagetemplate = new HeartbeatMessageTemplate();
  $heartbeatmessagetemplate->disabled = FALSE; /* Edit this to true to make a default heartbeatmessagetemplate disabled initially */
  $heartbeatmessagetemplate->api_version = 1;
  $heartbeatmessagetemplate->message_id = 'heartbeat_first_homework_assignment_activity';
  $heartbeatmessagetemplate->description = 'post an auto message after created an assignment';
  $heartbeatmessagetemplate->message = 'message';
  $heartbeatmessagetemplate->message_concat = '';
  $heartbeatmessagetemplate->perms = 4;
  $heartbeatmessagetemplate->group_type = 'single';
  $heartbeatmessagetemplate->concat_args = array(
    'group_by' => 'none',
    'group_target' => '',
    'group_by_target' => '',
    'group_num_max' => '',
    'merge_separator' => '',
    'merge_end_separator' => '',
    'roles' => array(
      1 => 0,
      2 => 0,
      3 => 0,
      4 => 0,
      5 => 0,
      6 => 0,
    ),
  );
  $heartbeatmessagetemplate->variables = array();
  $heartbeatmessagetemplate->attachments = array(
    'buttons' => array(
      'weight' => array(
        'flagattachment:like' => '0',
        'activitycomments' => '2',
      ),
      'settings' => array(
        'activitycomments' => array(
          'activitycomments_node' => 0,
        ),
      ),
      'enabled' => array(
        'flagattachment:like' => 0,
        'activitycomments' => 0,
      ),
    ),
    'content' => array(
      'weight' => array(
        'flagattachment:like' => '0',
        'activitycomments' => '2',
      ),
      'enabled' => array(
        'flagattachment:like' => 0,
        'activitycomments' => 0,
      ),
    ),
  );
  $heartbeatmessagetemplates['heartbeat_first_homework_assignment_activity'] = $heartbeatmessagetemplate;

  $heartbeatmessagetemplate = new HeartbeatMessageTemplate();
  $heartbeatmessagetemplate->disabled = FALSE; /* Edit this to true to make a default heartbeatmessagetemplate disabled initially */
  $heartbeatmessagetemplate->api_version = 1;
  $heartbeatmessagetemplate->message_id = 'heartbeat_homework_timeline_comment_form';
  $heartbeatmessagetemplate->description = 'save a comment on assignment timeline';
  $heartbeatmessagetemplate->message = '<b>firstname lastname</b> said:
  message';
  $heartbeatmessagetemplate->message_concat = '';
  $heartbeatmessagetemplate->perms = 4;
  $heartbeatmessagetemplate->group_type = 'single';
  $heartbeatmessagetemplate->concat_args = array(
    'group_by' => 'none',
    'group_target' => '',
    'group_by_target' => '',
    'group_num_max' => '',
    'merge_separator' => '',
    'merge_end_separator' => '',
    'roles' => array(
      1 => 0,
      2 => 0,
      3 => 0,
      4 => 0,
      5 => 0,
      6 => 0,
    ),
  );
  $heartbeatmessagetemplate->variables = array();
  $heartbeatmessagetemplate->attachments = array(
    'buttons' => array(
      'weight' => array(
        'flagattachment:like' => '0',
        'activitycomments' => '2',
      ),
      'settings' => array(
        'activitycomments' => array(
          'activitycomments_node' => 0,
        ),
      ),
      'enabled' => array(
        'flagattachment:like' => 0,
        'activitycomments' => 0,
      ),
    ),
    'content' => array(
      'weight' => array(
        'flagattachment:like' => '0',
        'activitycomments' => '2',
      ),
      'enabled' => array(
        'flagattachment:like' => 0,
        'activitycomments' => 0,
      ),
    ),
  );
  $heartbeatmessagetemplates['heartbeat_homework_timeline_comment_form'] = $heartbeatmessagetemplate;

  $heartbeatmessagetemplate = new HeartbeatMessageTemplate();
  $heartbeatmessagetemplate->disabled = FALSE; /* Edit this to true to make a default heartbeatmessagetemplate disabled initially */
  $heartbeatmessagetemplate->api_version = 1;
  $heartbeatmessagetemplate->message_id = 'heartbeat_homework_timeline_submission_form';
  $heartbeatmessagetemplate->description = 'message about files, difficulty, comment of a homework submission';
  $heartbeatmessagetemplate->message = 'name nb_file message';
  $heartbeatmessagetemplate->message_concat = '';
  $heartbeatmessagetemplate->perms = 4;
  $heartbeatmessagetemplate->group_type = 'single';
  $heartbeatmessagetemplate->concat_args = array(
    'group_by' => 'none',
    'group_target' => '',
    'group_by_target' => '',
    'group_num_max' => '',
    'merge_separator' => '',
    'merge_end_separator' => '',
    'roles' => array(
      1 => 0,
      2 => 0,
      3 => 0,
      4 => 0,
      5 => 0,
      6 => 0,
    ),
  );
  $heartbeatmessagetemplate->variables = array();
  $heartbeatmessagetemplate->attachments = array(
    'buttons' => array(
      'weight' => array(
        'flagattachment:like' => '0',
        'activitycomments' => '2',
      ),
      'settings' => array(
        'activitycomments' => array(
          'activitycomments_node' => 0,
        ),
      ),
      'enabled' => array(
        'flagattachment:like' => 0,
        'activitycomments' => 0,
      ),
    ),
    'content' => array(
      'weight' => array(
        'flagattachment:like' => '0',
        'activitycomments' => '2',
      ),
      'enabled' => array(
        'flagattachment:like' => 0,
        'activitycomments' => 0,
      ),
    ),
  );

  $heartbeatmessagetemplates['heartbeat_homework_timeline_submission_form'] = $heartbeatmessagetemplate;

  return $heartbeatmessagetemplates;
}

/**
 * Register default heartbeat streams.
 *
 * @see hook_ctools_plugin_api.
 */
function druedu_homework_heartbeat_stream_info() {
  $export = array();

  $heartbeatstream = new HeartbeatStreamConfig();
  $heartbeatstream->disabled = FALSE; /* Edit this to true to make a default heartbeatstream disabled initially */
  $heartbeatstream->api_version = 1;
  $heartbeatstream->class = 'homework_timeline';
  $heartbeatstream->real_class = 'nodeactivity';
  $heartbeatstream->name = 'Node activity';
  $heartbeatstream->module = 'heartbeat_defaults';
  $heartbeatstream->title = 'Homework Timeline';
  $heartbeatstream->path = 'streams/nodeactivity.inc';
  $heartbeatstream->settings = array(
    'settings__active_tab' => 'edit-settings-fs-perms',
    'messages_denied' => array(
      'heartbeat_add_comment' => 'heartbeat_add_comment',
      'heartbeat_add_node' => 'heartbeat_add_node',
      'heartbeat_edit_account' => 'heartbeat_edit_account',
      'heartbeat_edit_node' => 'heartbeat_edit_node',
      'heartbeat_tweet' => 'heartbeat_tweet',
      'heartbeat_add_grouppost' => 'heartbeat_add_grouppost',
      'heartbeat_become_group_member' => 'heartbeat_become_group_member',
      'heartbeat_first_homework_assignment_activity' => 0,
      'heartbeat_homework_timeline_comment_form' => 0,
      'heartbeat_homework_timeline_submission_form' => 0,
    ),
    'skip_active_user' => 0,
    'show_message_times' => 1,
    'show_message_times_grouped' => 1,
    'poll_messages' => '30',
    'poll_messages_type' => '0',
    'num_load_max' => '20',
    'grouping_seconds' => '300',
    'has_block' => 1,
    'block_items_max' => '5',
    'block_show_pager' => '1',
    'block_view_mode' => 'default',
    'stream_path' => '',
    'stream_profile_path' => '',
    'page_items_max' => '8',
    'page_show_pager' => 0,
    'page_pager_ajax' => 0,
    'page_view_mode' => 'full',
    'exclude_og' => 0,
    'show_status_form' => '0',
  );
  $heartbeatstream->variables = array();
  $export['homework_timeline'] = $heartbeatstream;

  return $export;

}