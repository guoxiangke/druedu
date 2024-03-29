<?php

/**
 * @file
 * This class represents an ldap_authentication module's configuration
 * It is extended by LdapAuthenticationConfAdmin for configuration and other admin functions
 */

module_load_include('php', 'ldap_user', 'LdapUserConf.class');

class LdapAuthenticationConf {

  /**
   * server configuration ids being used for authentication
   *
   * @var array
   *
   * @see LdapServer::sid()
   */
  public $sids = array();

  /**
   * server configuration ids being used for authentication
   *
   * @var associative array of LdapServer objects keyed on sids
   *
   * @see LdapServer::sid
   * @see LdapServer
   */
  public $enabledAuthenticationServers = array();


  /**
   * LdapUser configuration object
   *
   * @var LdapUser object
   */
  public $ldapUser = NULL; // ldap_user configuration object

  /**
   * Has current object been saved to the database?
   *
   * @var boolean
   */
  public $inDatabase = FALSE;

  /**
    * Choice of authentication modes
    *
    * @var integer
    *   LDAP_AUTHENTICATION_MODE_DEFAULT (LDAP_AUTHENTICATION_MIXED)
    *   LDAP_AUTHENTICATION_MIXED - signifies both LDAP and Drupal authentication are allowed
    *     Drupal authentication is attempted first.
    *   LDAP_AUTHENTICATION_EXCLUSIVE - signifies only LDAP authenication is allowed
    */
  public $authenticationMode = LDAP_AUTHENTICATION_MODE_DEFAULT;

  /**
   * The following are used to alter the logon interface to direct users
   * to local LDAP specific authentication help
   */

  /**
   * Text describing username to use, such as "Hogwarts Username"
   *  which will be inserted on logon forms to help users figure out which
   *  username to use
   *
   * @var string
   */
  public $loginUIUsernameTxt;

  /**
   * Text describing password to use, such as "Hogwards LDAP Password"
   *  which will be inserted on logon forms.  Useful in organizations with
   *  multiple account types for authentication
   *
   * @var string
   */
  public $loginUIPasswordTxt;

  /**
   * Text and Url to provide help link for password such as:
   *   ldapUserHelpLinkUrl:    https://passwords.hogwarts.edu
   *   ldapUserHelpLinkText:  Hogwarts IT Password Support Page
   *
   * @var string
   */
  public $ldapUserHelpLinkUrl;
  public $ldapUserHelpLinkText = LDAP_AUTHENTICATION_HELP_LINK_TEXT_DEFAULT;

  /**
   * Email handling option
   *   LDAP_AUTHENTICATION_EMAIL_FIELD_REMOVE -- don't show email on user forms
   *   LDAP_AUTHENTICATION_EMAIL_FIELD_DISABLE (default) -- disable email on user forms
   *   LDAP_AUTHENTICATION_EMAIL_FIELD_ALLOW -- allow editing of email on user forms
   *
   * @var int
   */
  public $emailOption = LDAP_AUTHENTICATION_EMAIL_FIELD_DEFAULT;

   /**
   * Email handling option
   *   LDAP_AUTHENTICATION_EMAIL_UPDATE_ON_LDAP_CHANGE_ENABLE_NOTIFY -- (default) Update stored email if LDAP email differs at login and notify user
   *   LDAP_AUTHENTICATION_EMAIL_UPDATE_ON_LDAP_CHANGE_ENABLE  -- Update stored email if LDAP email differs at login but don\'t notify user
   *   LDAP_AUTHENTICATION_EMAIL_UPDATE_ON_LDAP_CHANGE_DISABLE -- Don\'t update stored email if LDAP email differs at login
   *
   * @var int
   */
  public $emailUpdate = LDAP_AUTHENTICATION_EMAIL_UPDATE_ON_LDAP_CHANGE_DEFAULT;

  public $ssoEnabled = FALSE;
  public $ssoRemoteUserStripDomainName = FALSE;
  public $ssoExcludedPaths = NULL;
  public $ssoExcludedHosts = NULL;
  public $seamlessLogin = FALSE;
  public $ldapImplementation = FALSE;
  public $cookieExpire = LDAP_AUTHENTICATION_COOKIE_EXPIRE;

  public $apiPrefs = array();

  /**
   * Advanced options.   whitelist / blacklist options
   *
   * these are on the fuzzy line between authentication and authorization
   * and determine if a user is allowed to authenticate with ldap
   *
   */

  /**
   * text which must be present in user's LDAP entry's DN for user to authenticate with LDAP
   *   e.g. "ou=people"
   *
   * @var string
   */
  public $allowOnlyIfTextInDn = array(); // eg ou=education that must be met to allow ldap authentication

  /**
   * text which prohibits logon if found in user's LDAP entry's DN for user to authenticate with LDAP
   *   e.g. "ou=guest accounts"
   *
   * @var string
   */
  public $excludeIfTextInDn = array();

  /**
   * code that prints 1 or 0 signifying if user is allowed
   *   should not start with <?php
   *
   * @var string of php
   */
  public $allowTestPhp = NULL;

  /**
   * if at least 1 ldap authorization must exist for user to be allowed
   *   True signfies disallow if no authorizations.
   *   False signifies don't consider authorizations.
   *
   * @var boolean.
   */
  public $excludeIfNoAuthorizations = LDAP_AUTHENTICATION_EXCL_IF_NO_AUTHZ_DEFAULT;

  public $saveable = array(
    'sids',
    'authenticationMode',
    'loginUIUsernameTxt',
    'loginUIPasswordTxt',
    'ldapUserHelpLinkUrl',
    'ldapUserHelpLinkText',
    'emailOption',
    'emailUpdate',
    'allowOnlyIfTextInDn',
    'excludeIfTextInDn',
    'allowTestPhp',
    'excludeIfNoAuthorizations',
    'ssoRemoteUserStripDomainName',
    'ssoExcludedPaths',
    'ssoExcludedHosts',
    'seamlessLogin',
    'ldapImplementation',
    'cookieExpire',
  );

  public function hasEnabledAuthenticationServers() {
    return !(count($this->enabledAuthenticationServers) == 0);
  }

  public function enabled_servers() {
    return $this->hasEnabledAuthenticationServers();
  }

  function __construct() {
    $this->load();
  }

  function load() {

    if ($saved = variable_get("ldap_authentication_conf", FALSE)) {
      $this->inDatabase = TRUE;
      foreach ($this->saveable as $property) {
        if (isset($saved[$property])) {
          $this->{$property} = $saved[$property];
        }
      }
      $this->enabledAuthenticationServers = array(); // reset in case reloading instantiated object
      $enabled_ldap_servers = ldap_servers_get_servers(NULL, 'enabled');
      foreach ($this->sids as $sid => $enabled) {
        if ($enabled && isset($enabled_ldap_servers[$sid])) {
          $this->enabledAuthenticationServers[$sid] = $enabled_ldap_servers[$sid];
        }
      }

    }
    else {
      $this->inDatabase = FALSE;
    }

    $this->ldapUser = new LdapUserConf();
    $this->ssoEnabled = module_exists('ldap_sso');
    $this->apiPrefs['requireHttps'] = variable_get('ldap_servers_require_ssl_for_credentails', 1);
    $this->apiPrefs['encryption'] = variable_get('ldap_servers_encryption', LDAP_SERVERS_ENC_TYPE_CLEARTEXT);

  }

  /**
   * Destructor Method
   */
  function __destruct() { }


 /**
   * decide if a username is excluded or not
   *
   * @param string $name as proposed drupal username
   * @param array $ldap_user where top level keys are 'dn','attr','mail'
   * @return boolean FALSE means NOT allow; TRUE means allow
   *
   * @todo.  this function should simply invoke hook_ldap_authentication_allowuser_results_alter
   *   and most of this function should go in ldap_authentication_allowuser_results_alter
   */
  public function allowUser($name, $ldap_user, $account_exists = NULL) {

    /**
     * do one of the exclude attribute pairs match
     */
    $ldap_user_conf = ldap_user_conf();
    // if user does not already exists and deferring to user settings AND user settings only allow
    $user_register = variable_get('user_register', USER_REGISTER_VISITORS_ADMINISTRATIVE_APPROVAL);
    if (!$account_exists && $ldap_user_conf->acctCreation == LDAP_AUTHENTICATION_ACCT_CREATION_USER_SETTINGS_FOR_LDAP && $user_register == USER_REGISTER_ADMINISTRATORS_ONLY) {
      return FALSE;
    }

    foreach ($this->excludeIfTextInDn as $test) {
      if (stripos($ldap_user['dn'], $test) !== FALSE) {
        return FALSE;//  if a match, return FALSE;
      }
    }

    /**
     * evaluate php if it exists
     */

    if ($this->allowTestPhp) {
      if (module_exists('php')) {
        global $_name, $_ldap_user_entry;
        $_name = $name;
        $_ldap_user_entry = $ldap_user;
        $code = '<?php ' . "global \$_name; \n  global \$_ldap_user_entry; \n" . $this->allowTestPhp . ' ?>';
        $code_result = php_eval($code);
        $_name = NULL;
        $_ldap_user_entry = NULL;
        if ((boolean)($code_result) == FALSE) {
          return FALSE;
        }
      }
      else {
        drupal_set_message(t(LDAP_AUTHENTICATION_DISABLED_FOR_BAD_CONF_MSG), 'warning');
        $tokens = array('!ldap_authentication_config' => l(t('LDAP Authentication Configuration'), 'admin/config/people/ldap/authentication'));
        watchdog('ldap_authentication', 'LDAP Authentication is configured to deny users based on php execution with php_eval function, but php module is not enabled. Please enable php module or remove php code at !ldap_authentication_config .', $tokens);
        return FALSE;
      }
    }

    /**
     * do one of the allow attribute pairs match
     */
    if (count($this->allowOnlyIfTextInDn)) {
      $fail = TRUE;
      foreach ($this->allowOnlyIfTextInDn as $test) {
        if (stripos($ldap_user['dn'], $test) !== FALSE) {
          $fail = FALSE;
        }
      }
      if ($fail) {
        return FALSE;
      }

    }
    /**
     * is excludeIfNoAuthorizations option enabled and user not granted any groups
     */

    if ($this->excludeIfNoAuthorizations) {

      if (!module_exists('ldap_authorization')) {
        drupal_set_message(t(LDAP_AUTHENTICATION_DISABLED_FOR_BAD_CONF_MSG), 'warning');
        $tokens = array('!ldap_authentication_config' => l(t('LDAP Authentication Configuration'), 'admin/config/people/ldap/authentication'));
        watchdog('ldap_authentication', 'LDAP Authentication is configured to deny users without LDAP Authorization mappings, but LDAP Authorization module is not enabled.  Please enable and configure LDAP Authorization or disable this option at !ldap_authentication_config .', $tokens);
        return FALSE;
      }

      $user = new stdClass();
      $user->name = $name;
      $user->ldap_authenticated = TRUE; // fake user property added for query
      $consumers = ldap_authorization_get_consumers();
      $has_enabled_consumers = FALSE;
      $has_ldap_authorizations = FALSE;

      foreach ($consumers as $consumer_type => $consumer_config) {
        $consumer_obj = ldap_authorization_get_consumer_object($consumer_type);
        if ($consumer_obj->consumerConf->status) {
          $has_enabled_consumers = TRUE;
          list($authorizations, $notifications) = ldap_authorizations_user_authorizations($user, 'query', $consumer_type, 'test_if_authorizations_granted');
          if (
            isset($authorizations[$consumer_type]) &&
            count($authorizations[$consumer_type]) > 0
            ) {
            $has_ldap_authorizations = TRUE;
          }
        }
      }

      if (!$has_enabled_consumers) {
        drupal_set_message(t(LDAP_AUTHENTICATION_DISABLED_FOR_BAD_CONF_MSG), 'warning');
        $tokens = array('!ldap_consumer_config' => l(t('LDAP Authorization Configuration'), 'admin/config/people/ldap/authorization'));
        watchdog('ldap_authentication', 'LDAP Authentication is configured to deny users without LDAP Authorization mappings, but 0 LDAP Authorization consumers are configured:  !ldap_consumer_config .', $tokens);
        return FALSE;
      }
      elseif (!$has_ldap_authorizations) {
        return FALSE;
      }

    }

    // allow other modules to hook in and refuse if they like
    $hook_result = TRUE;
    drupal_alter('ldap_authentication_allowuser_results', $ldap_user, $name, $hook_result);

    if ($hook_result === FALSE) {
      watchdog('ldap_authentication', "Authentication Allow User Result=refused for %name", array('%name' => $name), WATCHDOG_NOTICE);
      return FALSE;
    }

    /**
     * default to allowed
     */
    return TRUE;
  }


}
