<?php
/**
 * @param string $key
 * @param string $default
 * @return unknown
 */
function http_get($key,$default = ''){
	if(!array_key_exists($key, $_GET)){
		return $default;
	}
	return $_GET[$key];
}
/**
 * get if smart phone or not
 * @return boolean
 */
function is_smart_phone(){
	$ua=$_SERVER['HTTP_USER_AGENT'];
	return ((strpos($ua,'iPhone')!==false)||(strpos($ua,'iPod')!==false)||(strpos($ua,'Android')!==false));
}
/**
 * get if feature phone or not
 * @return boolean
 */
function is_feature_phone(){
	$ua=$_SERVER['HTTP_USER_AGENT'];
	return ((strpos($ua,'DoCoMo')!==false)||(strpos($ua,'UP.Browser')!==false)||(strpos($ua,'J-PHONE')!==false)||(strpos($ua,'J-Vodafone')!==false)||(strpos($ua,'SoftBank')!==false)||(strpos($ua,'WILLCOM')!==false));
}

/**
 * get file size
 * @param number $filesize
 * @return string
 */
function getFileSizeString($filesize){
	if($filesize < 1000){
		return $filesize . " b";
	}
	$file_kb = round(($filesize / 1024), 2); // bytes to KB
	$file_mb = round(($filesize / 1048576), 2); // bytes to MB
	$file_gb = round(($filesize / 1073741824), 2); // bytes to GB
	// PHP does funny thing for files larger than 2GB
	if($file_gb > 1){
		return $file_gb . " Gb";
	}
	if($file_mb > 1){
		return $file_mb . " Mb";
	}
	return $file_kb." Kb";
}

/**
 * get extension
 * @param string $filename
 * @return string
 */
function get_extension($filename){
	$get_ext = explode("." ,$filename);
	$type = array_reverse($get_ext);
	return $type[0];
}
?>