<?php

class views_handler_area_link extends views_handler_area {

  function option_definition() {
    $options = parent::option_definition();
    $options['text'] = array('default' => '', 'translatable' => TRUE);
    $options['path'] = array('default' => '');
    $options['html'] = array('default' => 0);
    $options['querystring'] = array('default' => '');
    $options['anchor'] = array('default' => '');
    $options['class'] = array('default' => '');
    return $options;
  }

  function options_form(&$form, &$form_state) {
    parent::options_form($form, $form_state);
    $form['text'] = array(
      '#type' => 'textfield',
      '#title' => t('Link text'),
      '#default_value' => $this->options['text'],
      '#description' => t('The text of the link'),
    );
    $form['html'] = array(
      '#type' => 'checkbox',
      '#title' => t('html text?'),
      '#default_value' => $this->options['html'],
      '#description' => t('The text of the link must be displayed as html'),
    );
    $form['path'] = array(
      '#type' => 'textfield',
      '#title' => t('Link path'),
      '#default_value' => $this->options['path'],
      '#description' => t('The Drupal path or full URL to which to link'),
    );
    $form['querystring'] = array(
      '#type' => 'textfield',
      '#title' => t('Link querystring'),
      '#default_value' => $this->options['querystring'],
      '#description' => t('The query parameters that follow the full path'),
    );
    $form['anchor'] = array(
      '#type' => 'textfield',
      '#title' => t('Link anchor'),
      '#default_value' => $this->options['anchor'],
      '#description' => t('The anchor data that follows the full path and query parameters'),
    );
    $form['class'] = array(
      '#type' => 'textfield',
      '#title' => t('Link CSS class'),
      '#default_value' => $this->options['class'],
      '#description' => t('A custom CSS class to add to the link'),
    );

    $count = 0; // This lets us prepare the key as we want it printed.
    foreach ($this->view->display_handler->get_handlers('argument') as $arg => $handler) {
      $options[t('Arguments')]['%' . ++$count] = t('@argument title', array('@argument' => $handler->ui_name()));
      $options[t('Arguments')]['!' . $count] = t('@argument input', array('@argument' => $handler->ui_name()));
    }

    if (!empty($options)) {
      $output = t('<p>The following substitution patterns are available for this display based on the arguments for this view. Use the pattern shown on the left to display the value indicated on the right.</p>');
      foreach (array_keys($options) as $type) {
        if (!empty($options[$type])) {
          $vars = array('title' => $type);
          foreach ($options[$type] as $key => $value) {
            $vars['items'][] = $key . ' == ' . $value;
          }
          $output .= theme('item_list', $vars);
        }
      }

      $form['help'] = array(
        '#type' => 'fieldset',
        '#title' => t('Replacement patterns'),
      );
      $form['help']['help'] = array(
        '#type' => 'markup',
        '#markup' => $output,
      );
    }
  }

  function options_submit(&$form, &$form_state) {
    parent::options_submit($form, $form_state);
  }

  function render($empty = FALSE) {
    if (!$empty || !empty($this->options['empty'])) {

      $tokens = $this->get_render_tokens();

      // Replace any tokens in the path.
      $path = strtr($this->options['path'], $tokens);

      // Check that the user has access to the menu router item, but only if the
      // path is for a valid menu router item, so that external URLs or paths not
      // handled by Drupal's menu router are always permitted.
      $router_item = menu_get_item($path);
      if ($router_item && !$router_item['access']) {
        return '';
      }

      $link_options = array();
      if (!empty($this->options['querystring'])) {
        // This is an ugly way to do it, but Drupal 7 now takes an array for
        // query instead of a string.  That's good, but makes our string field
        // not work.  This should get switched to a multi-value interface of
        // some kind instead of ugly string parsing. @todo
        $querystring = strtr($this->options['querystring'], $tokens);
        $link_options['query'] = drupal_get_query_array($querystring);
      }
      if (!empty($this->options['anchor'])) {
        $link_options['anchor'] = strtr($this->options['anchor'], $tokens);
      }
      if (!empty($this->options['class'])) {
        $link_options['attributes'] = array('class' => explode(' ', strtr($this->options['class'], $tokens)));
      }
      if($this->options['html']) {
        $link_options['html'] = TRUE;
      }
      return l(strtr($this->options['text'], $tokens), $path, $link_options);
    }
    return '';
  }

  /**
   * Gets appropriate views replacement tokens for this handler.
   *
   * This code is largely based on views_handler_field's token rendering, but
   * we only care about arguments.  The render() method's link generation
   * handles XSS for us.
   */
  function get_render_tokens() {
    $tokens = array();
    if (!empty($this->view->build_info['substitutions'])) {
      $tokens = $this->view->build_info['substitutions'];
    }
    $count = 0;
    foreach ($this->view->display_handler->get_handlers('argument') as $arg => $handler) {
      $token = '%' . ++$count;
      if (!isset($tokens[$token])) {
        $tokens[$token] = '';
      }

      $tokens['!' . $count] = isset($this->view->args[$count - 1]) ? check_plain($this->view->args[$count - 1]) : '';
    }
    return $tokens;
  }
}
