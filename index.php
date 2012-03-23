<?php
/////////config//////////
date_default_timezone_set('Asia/Tokyo');
$title=$_SERVER['SCRIPT_NAME'];	//Page title
$home='../'; 	//Home URL
$self = array_reverse( explode("/",$_SERVER["SCRIPT_NAME"]) );
define('SELF_PHP',$self[0]);
define('CHARSET','UTF-8'); //Shift_JIS
define('DATE_FORMAT','Y/m/d H:i:s'); // Y/m/d H:i:s
define('HIDE_FOLDER','hide');
$c = '(c) <a href="http://tknr.com/" target="_blank">tknr.com</a>';
$lock = null;
/////////size config////////////////
require_once HIDE_FOLDER . '/lib/function.inc';
if(is_feature_phone()){
	define('MAX_DIST',32); 	//thumbnail size
	define('DATA_PER_PAGE',10);
	define('PAGING_WIDTH',10);
}else if(is_smart_phone()){
	define('MAX_DIST',80); 	//thumbnail size
	define('DATA_PER_PAGE',50);
	define('PAGING_WIDTH',5);
}else{
	define('MAX_DIST',80); 	//thumbnail size
	define('DATA_PER_PAGE',50);
	define('PAGING_WIDTH',5);
}
/////////request////////////////
$dir = http_get("dir");
$page = floor(http_get("page",1));
$mode = http_get("mode");
/////////function////////////////

/**
 * get_list
 * @param unknown_type $dir_cnt
 * @return multitype:
 */
function get_list($dir_cnt) {

	$dir_handle=opendir($dir_cnt);
	$file_list = null;
	while ($file = readdir($dir_handle)){
		$file_list = "$file_list\t$file";
	}
	closedir($dir_handle);
	$file_list = explode("\t",$file_list);

	foreach($file_list as $_index=>$_value){
		if(strlen($_value)==0){
			unset($file_list[$_index]);
		}
		if(strcmp('.', $_value) == 0){
			unset($file_list[$_index]);
		}
		if(strcmp('..', $_value) == 0){
			unset($file_list[$_index]);
		}
		if(strpos($_value, '.') === 0){
			unset($file_list[$_index]);
		}
		if(strcmp(HIDE_FOLDER, $_value) == 0){
			unset($file_list[$_index]);
		}
	}

	sort($file_list);
	return $file_list;
}


/**
 * get_menu_array
 * @param string $dir
 * @param string $home
 * @param string $lock
 * @return array <string,multitype:>
 */
function get_menu_array($dir,$home,$lock){

	$array = array();

	if (preg_match("/\.\./","$dir")){
		$lock ='1';
	}
	if((!$lock)&&($dir)){
		$array['dir_name'] = $dir;
	}
	if(($lock)&&($dir)){
		$array['error'] = 'Wrong Action !';
	}
	if (!$dir) {
		$array['parent_dir'] = 0;
	} else {
		$dd = explode("/",$dir);
		$array['parent_dir'] = 1;
		if (array_key_exists(2,$dd)){
			$tdir=array_pop($dd);
			$back_dir = explode("/$tdir",$dir);
			$array['upper_dir'] = $back_dir[0];
		}
	}
	$array['home'] = $home;
	return $array;
}


/**
 * get_paging_array
 * @param string $dir
 * @param number $page
 * @return array <string,multitype:>
 */
function get_paging_array($dir,$page){

	$array = array();

	if ($dir){
		$dir_name = "./$dir";
	} else {
		$dir_name = ".";
	}
	$file_list = get_list($dir_name);

	$maxsize = count($file_list);

	$array['max_size'] = $maxsize;

	$maxpage = ceil($maxsize / DATA_PER_PAGE);

	$halfwidth = floor(PAGING_WIDTH /2);
	$from = $page - $halfwidth;
	$to = $page + $halfwidth;
	if($to > $maxpage){
		$to = $maxpage;
	}
	if($maxpage <= PAGING_WIDTH){
		$from = 1;
		$to = $maxpage;
	}else if($page <= $halfwidth){
		$from = 1;
		$to = PAGING_WIDTH;
		if($to > $maxpage){
			$to = $maxpage;
		}
	}else if(($page > ($maxpage - $halfwidth)) && ($maxpage - PAGING_WIDTH > 0)){
		$from = $maxpage - PAGING_WIDTH +1;
		$to = $maxpage;
	}

	$array['dir'] = $dir;
	$array['maxpage'] = $maxpage;
	$array['page'] = $page;
	$array['from'] = $from;
	$array['to'] = $to;

	if($page > $from){
		$_prev_page = $page -1;

		$array['prev'] = $_prev_page;
	}else{
	}

	if($page < $to){
		$_next_page = $page + 1;
		$array['next'] = $_next_page;
	}
	return $array;
}


/**
 * get image property
 * @param string $file_path
 * @param string $filename
 * @return string
 */
function an_file($file_path,$file_name){

	$img= @getimagesize($file_path);
	if (($img[0] < MAX_DIST) and ($img[1] < MAX_DIST)){
		$tw=$img[0]; $th=$img[1];
	} else {
		if ($img[0] < $img[1]){
			$th=MAX_DIST; $tw=$img[0]*$th/$img[1];
		}
		if ($img[0] > $img[1]){
			$tw=MAX_DIST; $th=$img[1]*$tw/$img[0];
		}
		if ($img[0] == $img[1]){
			$tw=MAX_DIST; $th=MAX_DIST;
		}
	}
	$img_type = null;
	$img_prop = "$img[2],$img[0],$img[1],$tw,$th,$img_type,$file_name";
	return $img_prop;
}

/**
 * show files in directory
 * @param string $file_path
 * @param string $file_name
 * @param number $filesize
 * @param number $file_mtime
 * @param string $dir
 * @param number $page
 * @return array <string,multitype:>
 */
function get_dir_array($file_path, $file_name, $filesize, $file_mtime,$dir,$page){
	$array = array();

	$img_prop = an_file($file_path,$file_name);
	$img_prop = explode(",",$img_prop);
	$ext = "$img_prop[0]";
	$ow = "$img_prop[1]";
	$oh = "$img_prop[2]";
	$tw ="$img_prop[3]";
	$th ="$img_prop[4]";

	$web = ("html,htm");
	$zip = ("zip,lzh,tar,rar,7z,cab,lha,bz2,gz,7z");
	$media = ("mp3,rm,rmi,mid,wav,wma,mpeg,avi,3gp,3g2,mp4,flv,mpg");
	$swf = ("swf");
	$txt = ("txt,doc,xls,rtf");
	$pdf = ("pdf");

	$type_list =  explode(",","$web,$zip,$media,$swf,$txt,$pdf");
	$mdate=date(DATE_FORMAT,$file_mtime);
	$show_size = getFileSizeString($filesize);

	$file=".$dir/$file_name";
	$encoded_url = rawurlencode($file);
	
	$array['file'] = $file_name;
	$array['size'] = $show_size;
	$array['mdate'] = $mdate;

	if ($file_name == SELF_PHP){
		$array['type'] = 'self';
		$array['href'] = SELF_PHP;
		$array['src'] = HIDE_FOLDER.'/other.gif';
		$array['alt'] = $file_name;
	}else{
		$array['ext'] = $ext;
		switch($ext){
			case 1:{
				$array['type'] = 'img';
				$array['href'] = $file;
				$array['src'] = $file;
				$array['alt'] = $file_name;
				$array['original_width'] = $ow;
				$array['original_height'] = $oh;
				$array['width'] = $tw;
				$array['height'] = $th;
				break;
			}
			case 2:
			case 3:{
				$array['type'] = 'img';
				$array['href'] = $file;
				$array['src'] = SELF_PHP.'?mode=thumb&ext='.$ext.'&f='.$file.'&ow='.$ow.'&oh='.$oh.'&tw='.$tw.'&th='.$th;
				$array['alt'] = $file_name;
				$array['original_width'] = $ow;
				$array['original_height'] = $oh;
				$array['width'] = $tw;
				$array['height'] = $th;
				break;
			}
			default:{
				$get_ext = explode("." ,$file_name);
				$type = array_reverse($get_ext);
				$icon = null;
				for ($i=0; $i<count($type_list); $i++){
					if (preg_match("/$type_list[$i]$/i",$file_name)){
						if (preg_match("/$type[0]/i","$txt")){
							$icon = 'txt';
						}
						if (preg_match("/$type[0]/i","$media")){
							$icon = 'media';
						}
						if (preg_match("/$type[0]/i","$zip")){
							$icon = 'zip';
						}
						if (preg_match("/$type[0]/i","$web")){
							$icon = 'web';
						}
						if (preg_match("/$type[0]/i","$swf")){
							$icon = 'swf';
						}
						if (preg_match("/$type[0]/i","$pdf")){
							$icon = 'pdf';
						}
					}
				}
				if (!$icon){
					$icon='other';
				}
				$dl_media = explode(',',$media);
				$get_ext_array = explode('.' ,$file_name);
				$get_ext_array = array_reverse($get_ext_array);
				$get_ext = strtolower($get_ext_array[0]);
					
				if(in_array($get_ext,$dl_media)){
					$array['type'] = 'media';
				}else{
					$array['type'] = 'file';
				}
				$array['href'] = $file;
				$array['src'] = HIDE_FOLDER.'/'.$icon.'.gif';
				$array['alt'] = $file_name;
				break;
			}
		}
	}
	return $array;
}

/**
 * get_body_array
 * @param unknown_type $dir
 * @param number $page
 * @return multitype:NULL multitype:string NULL unknown  
 */
function get_body_array($dir,$page){

	$array = array();
	
	$_out = '';
	$lock = null;
	if (preg_match("/\.\./","$dir")){
		$lock ='1';
	}
	if(!$lock){
		if ($dir){
			$dir_name = "./$dir";
		} else {
			$dir_name = ".";
		}
		$file_list = get_list($dir_name);

		$maxsize = count($file_list);

		$from = (($page - 1) * DATA_PER_PAGE)+1;
		$to = (($page * DATA_PER_PAGE)+1);
		if($to > $maxsize){
			$to = $maxsize;
		}

		$dir_list = null;
		for ($count=$from ;$count<$to;$count++) {
			$file_name=$file_list[$count];
			$file_path = "$dir_name/$file_name";
			$file_size = filesize($file_path);
			$file_mtime = filemtime($file_path);

			if (is_file($file_path)){
				$array[] = get_dir_array($file_path, $file_name, $file_size, $file_mtime,$dir,$page);
			} else {
				$dir_list = "$dir_list,$file_name";
			}
		}

		$dir_list = explode(",",$dir_list);
		sort($dir_list);

		for ($count=1;$count<count($dir_list);$count++) {
			$encoded_url = rawurlencode($dir.'/'.$dir_list[$count]);
			$_array = array();
			$_array['file'] = $dir_list[$count];
			$_array['alt'] = $dir_list[$count];
			$_array['type'] = 'dir';
			$_array['href'] = SELF_PHP.'?dir='.$encoded_url;
			$_array['src'] = HIDE_FOLDER.'/dir.gif';
			$_array['size'] = '-';
			$_array['mdate'] = date(DATE_FORMAT,$file_mtime);
			$array[] = $_array;
		}
	}
	return $array;
}
/////////main////////////////
switch($mode){
	case 'popup':{
		require_once HIDE_FOLDER . '/plugin/popup.inc';
		return;
	}
	case 'thumb':{
		require_once HIDE_FOLDER . '/plugin/thumb.inc';
		return;
	}
	case 'dl':{
		require_once HIDE_FOLDER . '/plugin/dl.inc';
		return;
	}
	case 'embed':{
		require_once HIDE_FOLDER . '/plugin/embed.inc';
		return;
	}
	default:{
		break;
	}
}
// doc output
{
	$menu = get_menu_array($dir,$home,$lock);
	$paging = get_paging_array($dir,$page);
	$data = get_body_array($dir,$page);

	ob_start('mb_output_handler');
	if(is_feature_phone()){
		require (HIDE_FOLDER.'/template/fp/index.inc');
	}else{
		require (HIDE_FOLDER.'/template/sp/index.inc');
	}
	$output = ob_get_contents();
	$output = str_replace('%CHARSET%', CHARSET, $output);
	$output = str_replace('%TITLE%', $title, $output);
	$output = str_replace('%SELF%', SELF_PHP, $output);
	$output = str_replace('%HIDE_FOLDER%', HIDE_FOLDER, $output);
	ob_end_clean();

	echo $output;
}
?>