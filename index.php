<?php
date_default_timezone_set('Asia/Tokyo');

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
 * get if smart phone nor not
 * @return boolean
 */
function is_smart_phone(){
	$ua=$_SERVER['HTTP_USER_AGENT'];
	return ((strpos($ua,'iPhone')!==false)||(strpos($ua,'iPod')!==false)||(strpos($ua,'Android')!==false));
}
/**
 * get if feature phone nor not
 * @return boolean
 */
function is_feature_phone(){
	$ua=$_SERVER['HTTP_USER_AGENT'];
	return ((strpos($ua,'DoCoMo')!==false)||(strpos($ua,'UP.Browser')!==false)||(strpos($ua,'J-PHONE')!==false)||(strpos($ua,'J-Vodafone')!==false)||(strpos($ua,'SoftBank')!==false)||(strpos($ua,'WILLCOM')!==false));
}


/////////config//////////
$gdv=0; 	//GD Ver. 1.x--'1' 2.x--'0'
$title=$_SERVER['SCRIPT_NAME'];	//Page title
$home='../'; 	//Home URL
define('CHARSET','UTF-8'); //Shift_JIS
define('DATE_FORMAT','Y/m/d H:i:s'); // Y/m/d H:i:s
$c = '(c) <a href="http://tknr.com/" target="_blank">tknr.com</a>';
define('HIDE_FOLDER','hide');
$self = array_reverse( explode("/",$_SERVER["SCRIPT_NAME"]) );
define('SELF_PHP',$self[0]);
$lock = null;
/////////size config////////////////
if(is_feature_phone()){
	define('MAX_DIST',32); 	//thumbnail size
	define('DATA_PER_PAGE',10);
	define('PAGING_WIDTH',10);
}else if(is_smart_phone()){
	define('MAX_DIST',80); 	//thumbnail size
	define('DATA_PER_PAGE',30);
	define('PAGING_WIDTH',5);
}else{
	define('MAX_DIST',32); 	//thumbnail size
	define('DATA_PER_PAGE',30);
	define('PAGING_WIDTH',10);
}
/////////request////////////////
$dir = http_get("dir");
$page = floor(http_get("page",1));
$mode = http_get("mode");
/////////function////////////////
/**
 * get list
 * @param unknown_type $dir_cnt
 * @return multitype:
 */
function get_list($dir_cnt,$dir,$page) {

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
		if(strpos($_value, '.', 0) === 0){
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
 * show menu
 * @return string
 */
function showmenu($dir,$home,$lock){

	$_out = '';

	if (preg_match("/\.\./","$dir")){
		$lock ='1';
	}
	if((!$lock)&&($dir)){
		$_out .= "Index of <b>$dir</b><br />";
	}
	if(($lock)&&($dir)){
		$_out .= "<b style=\"color:crimson;\">Wrong Action !</b>";
	}
	if (!$dir) {
		$_out .= "<b>! Parent Dir</b>";
	} else {
		$dd = explode("/",$dir);
		$_out .= "<a data-role=\"button\" data-inline=\"true\" href=\"".SELF_PHP."\" directkey=\"*\" accesskey=\"*\" nonumber>[*]Parent Dir</a>";
		if (array_key_exists(2,$dd)){
			$tdir=array_pop($dd);
			$back_dir = explode("/$tdir",$dir);
			$_out .= " | <a data-role=\"button\" data-inline=\"true\" href=\"".SELF_PHP."?dir=$back_dir[0]\" directkey=\"#\" accesskey=\"#\" nonumber>[#]Upper Dir</a>";
		}
	}
	$_out .= " | <a data-role=\"button\" data-inline=\"true\" href=\"$home\" accesskey=\"0\">[0]Home</a>\n";
	if(is_feature_phone()){
		$_out = str_replace(" data-role=\"button\" data-inline=\"true\"", '', $_out);
		$_out = str_replace('<span>', '', $_out);
		$_out = str_replace('</span>', '', $_out);
	}else{
		$_out = str_replace('|','',$_out);
		$_out = str_replace('[*]','',$_out);
		$_out = str_replace('[#]','',$_out);
		$_out = str_replace('[0]','',$_out);
	}
	return $_out;
}

/**
 * show paging
 * @return string
 */
function showpaging($dir,$page){

	$_out = '';

	if ($dir){
		$dir_name = "./$dir";
	} else {
		$dir_name = ".";
	}
	$file_list = get_list($dir_name,$dir,$page);

	$maxsize = count($file_list);

	//	$_out .= "<span data-role=\"button\">count:$maxsize</span> | ";

	//width
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

	if($page > $from){
		$_prev_page = $page -1;
		$_out .= "<a data-role=\"button\" data-inline=\"true\" href=\"".SELF_PHP."?page=1&dir=$dir\">&lt;&lt;</a>|";
		$_out .= "<a data-role=\"button\" data-inline=\"true\" href=\"".SELF_PHP."?page=$_prev_page&dir=$dir\">&lt;</a>|";
	}else{
		//		$_out .= "<span data-role=\"button\">&lt;&lt;</span>|<span data-role=\"button\">&lt;</span>|";
	}
	for($count = $from ; $count <= $to ; $count++){
		$_out .= "";
		if($count !=$from){
			$_out .= "|";

		}
		if($count == $page){
			$_out .= "<span data-role=\"button\" data-inline=\"true\">$count/$maxpage</span>";
		}else{
			$accesskey = "";
			if(is_feature_phone() && $count > 0 && $count < 10){
				$accesskey = " directkey=\"$count\" accesskey=\"$count\" nonumber";
			}
			$_out .= "<a data-role=\"button\" data-inline=\"true\" href=\"$self[0]?page=$count&dir=$dir\"$accesskey>$count</a>";
		}
	}
	if($page < $to){
		$_next_page = $page + 1;
		$_out .= "|<a data-role=\"button\" data-inline=\"true\" href=\"$self[0]?page=$_next_page&dir=$dir\">&gt;</a>";
		$_out .="|<a data-role=\"button\" data-inline=\"true\" href=\"$self[0]?page=$maxpage&dir=$dir\">&gt;&gt;</a>";
	}else{
		//		$_out .= "|<span data-role=\"button\">&gt;</span>|<span data-role=\"button\">&gt;&gt;</span>";
	}
	if(is_feature_phone()){
		$_out = str_replace(" data-role=\"button\" data-inline=\"true\"", '', $_out);
		$_out = str_replace('<span>', '', $_out);
		$_out = str_replace('</span>', '', $_out);
	}else{
		$_out = str_replace('|','',$_out);
	}
	return $_out;
}

/**
 * get image property
 * @param string $file_path
 * @return string
 */
function an_file($file_path,$dir,$page,$file_name){

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
 * @return string
 */
function show_dir($file_path, $file_name, $filesize, $file_mtime,$dir,$page){
	
	$_out = '';

	$img_prop = an_file($file_path,$dir,$page,$file_name);
	$img_prop = explode(",",$img_prop);
	$ext = "$img_prop[0]";
	$ow = "$img_prop[1]";
	$oh = "$img_prop[2]";
	$tw ="$img_prop[3]";
	$th ="$img_prop[4]";

	$web = ("html,htm");
	$zip = ("zip,lzh,tar,rar,7z,cab,lha");
	$media = ("mp3,rm,rmi,mid,wav,wma,mpeg,avi,3gp,3g2,mp4");
	$swf = ("swf");
	$txt = ("txt,doc,xls,rtf");
	$pdf = ("pdf");

	$type_list =  explode(",","$web,$zip,$media,$swf,$txt,$pdf");
	$mdate=date(DATE_FORMAT,$file_mtime);
	$show_size = getFileSizeString($filesize);

	if ($file_name != SELF_PHP){
		$file=".$dir/$file_name";
		$_out .= "<tr><td class=\"td\">";
		switch($ext){
			case 1:
				{
					$_out .= "<a href=\"javascript:void(0)\" onclick=\"picspop('.$dir','$file_name','$ow','$oh')\">";
					$_out .= "<img src=\".$dir/$file_name\" width=\"$tw\" height=\"$th\" border=\"0\"></a>";
					break;
				}
			case 2:
			case 3:
				{
					$_out .= "<a href=\"javascript:void(0)\" onclick=\"picspop('.$dir','$file_name','$ow','$oh');\">";
					$_out .= "<img src=\"".SELF_PHP."?mode=thumb&ext=$ext&f=$file&ow=$ow&oh=$oh&tw=$tw&th=$th\" width=\"$tw\" height=\"$th\" border=\"0\"></a>";
					break;
				}
			default:
				{
					$get_ext = explode("." ,$file_name);
					$type = array_reverse($get_ext);
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
					$dl_media = array("MP3","MP4","3GP","3G2");
					$get_ext_array = explode("." ,$file_name);
					$get_ext_array = array_reverse($get_ext_array);
					$get_ext = strtoupper($get_ext_array[0]);
					if(in_array($get_ext,$dl_media)){
						$encoded_url = rawurlencode($file);
						$_out .= "<a href=\"?mode=dl&f=$file\" target=\"_blank\"><img src=\"".HIDE_FOLDER."/$icon.gif\" border=\"0\" alt=\"$file_name\"></a>";
					}else{
						$_out .= "<a href=\"$file\" target=\"_blank\"><img src=\"".HIDE_FOLDER."/$icon.gif\" border=\"0\" alt=\"$file_name\"></a>";
					}
					break;
				}
		}
		$dl_media = array("MP3","MP4","3GP","3G2");
		$get_ext_array = explode("." ,$file_name);
		$get_ext_array = array_reverse($get_ext_array);
		$get_ext = strtoupper($get_ext_array[0]);
		if(is_feature_phone()){
			if(in_array($get_ext,$dl_media)){
				$_out .= "</td><td class=\"td\"><a href=\"".SELF_PHP."?mode=dl&f=$file\" target=\"_blank\">$file_name</a></td>";
			}else{
				$_out .= "</td><td class=\"td\"><a href=\"$file\" target=\"_blank\">$file_name</a></td>";
			}
			if (($ow) AND ($oh)){
				$_out .= "<td class=\"td\">$ow x $oh</td>";
			} else {
				$_out .= "<td class=\"td\">-</td>";
			}
			$_out .= "<td class=\"td\">$show_size</td><td class=\"td\">$mdate</td></tr>\n";
		}else{
			if(in_array($get_ext,$dl_media)){
				$_out .= "</td><td class=\"td\"><a href=\"".SELF_PHP."?mode=dl&f=$file\" target=\"_blank\">$file_name</a>";
			}else{
				$_out .= "</td><td class=\"td\"><a href=\"$file\" target=\"_blank\">$file_name</a>";
			}
			if (($ow) AND ($oh)){
				$_out .= "<br />$ow x $oh<br />";
			} else {
				$_out .= "<br />-<br />";
			}
			$_out .= "$show_size</td><td class=\"td\">$mdate</td></tr>\n";
		}
	}
	return $_out;
}
/**
 * show index
 * @param unknown_type $dir_cnt
 */
function show_indx($dir_cnt){
	global $dir;
	global $self;
	show_indx($_SERVER["SCRIPT_NAME"]);
	ereg ( "([^/]*)$",$dir_cnt,$temp);
	$td_name = ereg_replace( "$temp[1]$","", $dir_cnt);
}

function show_body($dir,$page){

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
		$file_list = get_list($dir_name,$dir,$page);

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
				$_out .= show_dir($file_path, $file_name, $file_size, $file_mtime,$dir,$page);
			} else {
				$dir_list = "$dir_list,$file_name";
			}
		}

		$dir_list = explode(",",$dir_list);
		sort($dir_list);

		for ($count=1;$count<count($dir_list);$count++) {
			$mdate=date(DATE_FORMAT,$file_mtime);
			if(is_feature_phone()){
				$_out .= "<tr><td class=\"td\">";
				$_out .= "<a href=\"".SELF_PHP."?dir=$dir/$dir_list[$count]\">";
				$_out .= "<img src=\"".HIDE_FOLDER."/dir.gif\" border=\"0\" width=\"32\" height=\"26\"></a></td>";
				$_out .= "<td class=\"td\"><a href=\"".SELF_PHP."?dir=$dir/$dir_list[$count]\">$dir_list[$count]</a></td><td class=\"td\">-</td><td class=\"td\">-</td><td class=\"td\">$mdate</td></tr>\n";
			}else{
				$_out .= "<tr><td class=\"td\">";
				$_out .= "<a href=\"".SELF_PHP."?dir=$dir/$dir_list[$count]\">";
				$_out .= "<img src=\"".HIDE_FOLDER."/dir.gif\" border=\"0\" width=\"32\" height=\"26\"></a></td>";
				$_out .= "<td class=\"td\"><a href=\"".SELF_PHP."?dir=$dir/$dir_list[$count]\">$dir_list[$count]</a></td><td class=\"td\">$mdate</td></tr>\n";
			}
		}
	}
	return $_out;
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
	default:{
		break;
	}
}
$tmpl = '';
if(is_feature_phone()){
	$tmpl = file_get_contents(HIDE_FOLDER.'/template/tmpl_fp.html');
}else{
	$tmpl = file_get_contents(HIDE_FOLDER.'/template/tmpl_sp.html');
}
$tmpl = str_replace('%CHARSET%', CHARSET, $tmpl);
$tmpl = str_replace('UTF-8', CHARSET, $tmpl);
$tmpl = str_replace('%TITLE%', $title, $tmpl);
$tmpl = str_replace('%SELF%', SELF_PHP, $tmpl);
$tmpl = str_replace('%SHOWMENU%', showmenu($dir,$home,$lock), $tmpl);
$tmpl = str_replace('%SHOWPAGING%', showpaging($dir,$page), $tmpl);
$tmpl = str_replace('%SHOWBODY%', show_body($dir,$page), $tmpl);
echo $tmpl;
?>