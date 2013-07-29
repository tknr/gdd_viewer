<?php
/**
 * @param string $key
 * @return mixed|boolean
 */
function get_apc_value($key) {
	if (function_exists ( 'apc_fetch' )) {
		return apc_fetch ( $key );
	}
	return false;
}
/**
 * @param string $key
 * @param mixed $value
 * @return boolean
 */
function put_apc_value($key, $value) {
	if (function_exists ( 'apc_store' )) {
		return apc_store ( $key, $value );
	}
	return false;
}
?>