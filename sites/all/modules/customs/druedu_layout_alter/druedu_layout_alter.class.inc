<?php
// Singleton to transmit node fields render.
class RenderNodeFields {
	private static $classInstance;
	private static $content_information = NULL;
	private static $content_nid = NULL;
	// The constructor must be private like this:
	private function __construct() {

	}

	public static function getInstance(){
		if (!self::$classInstance)
		{
			self::$classInstance = new RenderNodeFields();
		}
		return self::$classInstance;
	}

	public static function get_content_information() {
		return self::$content_information;
	}

	public static function set_content_information($fields) {
		if(isset($fields) && !empty($fields)) {
			self::$content_information = $fields;
		}
	}

	public static function get_nid() {
		return self::$content_nid;
	}

	public static function set_nid($nid) {
		if(isset($nid) && !empty($nid)) {
			self::$content_nid = $nid;
		}
	}
}

// Singleton to transmit node fields render.
class RenderUserFields {
	private static $classInstance;
	private static $user_information = NULL;
	private static $user_nid = NULL;
	// The constructor must be private like this:
	private function __construct() {

	}

	public static function getInstance(){
		if (!self::$classInstance)
		{
			self::$classInstance = new RenderUserFields();
		}
		return self::$classInstance;
	}

	public static function get_user_information() {
		return self::$user_information;
	}

	public static function set_user_information($fields) {
		if(isset($fields) && !empty($fields)) {
			self::$user_information = $fields;
		}
	}
}