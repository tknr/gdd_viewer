<?php
// ///////config//////////
date_default_timezone_set('Asia/Tokyo');
define('SCRIPT_TITLE', 'gdd_viewer');
$title = SCRIPT_TITLE; // Page title
$home = '../'; // Home URL
$self = array_reverse(explode("/", $_SERVER["SCRIPT_NAME"]));
define('SELF_PHP', $self[0]);
define('CHARSET', 'UTF-8'); // Shift_JIS
define('DATE_FORMAT', 'Y/m/d H:i:s'); // Y/m/d H:i:s
define('HIDE_FOLDER', 'hide');
$c = '(c) <a href="http://tknr.com/" target="_blank">tknr.com</a>';
$lock = null;
// ///////size config////////////////
require_once HIDE_FOLDER . '/lib/function.inc';
$user_agent = new UserAgent($_SERVER['HTTP_USER_AGENT']);
if ($user_agent->is_feature_phone()) {
    define('MAX_DIST', 32); // thumbnail size
    define('DATA_PER_PAGE', 10);
    define('PAGING_WIDTH', 10);
    define('TEMPLATE_FOLDER', HIDE_FOLDER . '/template/fp/');
} else 
    if ($user_agent->is_smart_phone()) {
        define('MAX_DIST', 80); // thumbnail size
        define('DATA_PER_PAGE', 40);
        define('PAGING_WIDTH', 5);
        define('TEMPLATE_FOLDER', HIDE_FOLDER . '/template/sp/');
    } else {
        define('MAX_DIST', 80); // thumbnail size
        define('DATA_PER_PAGE', 50);
        define('PAGING_WIDTH', 5);
        define('TEMPLATE_FOLDER', HIDE_FOLDER . '/template/sp/');
    }
define('ICON_FOLDER', TEMPLATE_FOLDER . 'icon/');
// ///////request////////////////
$dir = HttpUtil::get("dir");
$page = floor(HttpUtil::get("page", 1));
$mode = HttpUtil::get("mode");
// ///////function////////////////

/**
 * get_list
 *
 * @param unknown_type $dir_cnt            
 * @return multitype:
 */
function get_list($dir_cnt)
{
    $file_list = null;
    
    $file_list = APCUtil::get(SCRIPT_TITLE . '_' . $dir_cnt);
    if (! $file_list) {
        
        $command = 'export IFS=$\'\n\';list=\'\';for dir in `ls -1r "' . $dir_cnt . '"`;do list=${dir}"\t"${list};done;echo -e ${list}';
        // echo $command;
        $file_list = exec($command);
        if ($file_list) {
            $file_list = explode("\t", $file_list);
            APCUtil::put(SCRIPT_TITLE . '_' . $dir_cnt, $file_list);
            return $file_list;
        }
        
        $dir_handle = opendir($dir_cnt);
        while ($file = readdir($dir_handle)) {
            $file_list = "$file_list\t$file";
        }
        closedir($dir_handle);
        
        $file_list = explode("\t", $file_list);
        
        foreach ($file_list as $_index => $_value) {
            if (strlen($_value) == 0) {
                unset($file_list[$_index]);
            }
            if (strcmp('.', $_value) == 0) {
                unset($file_list[$_index]);
            }
            if (strcmp('..', $_value) == 0) {
                unset($file_list[$_index]);
            }
            if (strcmp(HIDE_FOLDER, $_value) == 0) {
                unset($file_list[$_index]);
            }
        }
        
        sort($file_list);
        
        APCUtil::put(SCRIPT_TITLE . '_' . $dir_cnt, $file_list);
    }
    
    return $file_list;
}

/**
 * get_menu_array
 *
 * @param string $dir            
 * @param string $home            
 * @param string $lock            
 * @return array <string,multitype:>
 */
function get_menu_array($dir, $home, $lock)
{
    $array = array();
    
    if (preg_match("/\.\./", "$dir")) {
        $lock = '1';
    }
    if ((! $lock) && ($dir)) {
        $array['dir_name'] = $dir;
    }
    if (($lock) && ($dir)) {
        $array['error'] = 'Wrong Action !';
    }
    if (! $dir) {
        $array['parent_dir'] = 0;
    } else {
        $dd = explode("/", $dir);
        $array['parent_dir'] = 1;
        if (array_key_exists(2, $dd)) {
            $tdir = array_pop($dd);
            $back_dir = explode("/$tdir", $dir);
            $array['upper_dir'] = $back_dir[0];
        }
    }
    $array['home'] = $home;
    return $array;
}

/**
 * get_paging_array
 *
 * @param string $dir            
 * @param number $page            
 * @return array <string,multitype:>
 */
function get_paging_array($dir, $page)
{
    $array = array();
    
    if ($dir) {
        $dir_name = "./$dir";
    } else {
        $dir_name = ".";
    }
    $file_list = get_list($dir_name);
    
    $maxsize = count($file_list);
    
    $array['max_size'] = $maxsize;
    
    $maxpage = ceil($maxsize / DATA_PER_PAGE);
    
    $halfwidth = floor(PAGING_WIDTH / 2);
    $from = $page - $halfwidth;
    $to = $page + $halfwidth;
    if ($to > $maxpage) {
        $to = $maxpage;
    }
    if ($maxpage <= PAGING_WIDTH) {
        $from = 1;
        $to = $maxpage;
    } else 
        if ($page <= $halfwidth) {
            $from = 1;
            $to = PAGING_WIDTH;
            if ($to > $maxpage) {
                $to = $maxpage;
            }
        } else 
            if (($page > ($maxpage - $halfwidth)) && ($maxpage - PAGING_WIDTH > 0)) {
                $from = $maxpage - PAGING_WIDTH + 1;
                $to = $maxpage;
            }
    
    $array['dir'] = $dir;
    $array['maxpage'] = $maxpage;
    $array['page'] = $page;
    $array['from'] = $from;
    $array['to'] = $to;
    
    if ($page > $from) {
        $_prev_page = $page - 1;
        
        $array['prev'] = $_prev_page;
    } else {}
    
    if ($page < $to) {
        $_next_page = $page + 1;
        $array['next'] = $_next_page;
    }
    return $array;
}

/**
 * get image property
 *
 * @param string $file_path            
 * @param string $filename            
 * @return string
 */
function an_file($file_path, $file_name)
{
    $img = @getimagesize($file_path);
    if (($img[0] < MAX_DIST) and ($img[1] < MAX_DIST)) {
        $tw = $img[0];
        $th = $img[1];
    } else {
        if ($img[0] < $img[1]) {
            $th = MAX_DIST;
            $tw = floor($img[0] * $th / $img[1]);
        }
        if ($img[0] > $img[1]) {
            $tw = MAX_DIST;
            $th = floor($img[1] * $tw / $img[0]);
        }
        if ($img[0] == $img[1]) {
            $tw = MAX_DIST;
            $th = MAX_DIST;
        }
    }
    $img_type = null;
    $img_prop = "$img[2],$img[0],$img[1],$tw,$th,$img_type,$file_name";
    return $img_prop;
}

/**
 * show files in directory
 *
 * @param string $file_path            
 * @param string $file_name            
 * @param number $filesize            
 * @param number $file_mtime            
 * @param string $dir            
 * @param number $page            
 * @return array <string,multitype:>
 */
function get_dir_array($file_path, $file_name, $filesize, $file_mtime, $dir, $page)
{
    $array = array();
    
    $img_prop = an_file($file_path, $file_name);
    $img_prop = explode(",", $img_prop);
    $img_ext = "$img_prop[0]";
    $ow = "$img_prop[1]";
    $oh = "$img_prop[2]";
    $tw = "$img_prop[3]";
    $th = "$img_prop[4]";
    
    $web = explode(',', 'html,htm,xhtml,php,phps,inc,cgi,pl,pm,tt,tmpl,py,xml,css,js');
    $zip = explode(',', 'zip,lzh,tar,rar,7z,cab,lha,bz2,gz,7z');
    $sound = explode(',', 'mp3,rm,rmi,mid,wav,aiff');
    $video = explode(',', 'wma,mpeg,avi,3gp,3g2,mp4,mpg,m4a,mov');
    $swf = explode(',', 'swf,flv');
    $txt = explode(',', 'txt,sh,ini,conf,properties,java,c,cpp,h,cs,sql');
    $doc = explode(',', 'doc,xls,rtf,docx,xslx');
    $pdf = explode(',', 'pdf');
    
    $mdate = date(DATE_FORMAT, $file_mtime);
    $show_size = FileUtil::getFileSizeString($filesize);
    
    $file = ".$dir/$file_name";
    
    $array['file'] = $file_name;
    $array['size'] = $show_size;
    $array['mdate'] = $mdate;
    $extension = strtolower(FileUtil::getExtension($file_name));
    $array['extension'] = $extension;
    
    if ($file_name == SELF_PHP) {
        $array['type'] = 'self';
        $array['href'] = SELF_PHP;
        $array['src'] = ICON_FOLDER . 'other.gif';
        $array['alt'] = $file_name;
    } else {
        switch ($img_ext) {
            case 1:
                {
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
            case 3:
                {
                    $array['type'] = 'img';
                    $array['href'] = $file;
                    $array['src'] = SELF_PHP . "?mode=thumb&ext=" . $img_ext . "&f=" . $file . "&ow=" . $ow . "&oh=" . $oh . "&tw=" . $tw . "&th=" . $th;
                    $array['alt'] = $file_name;
                    $array['original_width'] = $ow;
                    $array['original_height'] = $oh;
                    $array['width'] = $tw;
                    $array['height'] = $th;
                    break;
                }
            default:
                {
                    $icon = 'other';
                    if (in_array($extension, $txt) || in_array($extension, $doc)) {
                        $icon = 'text';
                    }
                    if (in_array($extension, $sound)) {
                        $icon = 'sound';
                    }
                    if (in_array($extension, $video)) {
                        $icon = 'movie';
                    }
                    if (in_array($extension, $zip)) {
                        $icon = 'package';
                    }
                    if (in_array($extension, $web)) {
                        $icon = 'web';
                    }
                    if (in_array($extension, $swf)) {
                        $icon = 'swf';
                    }
                    if (in_array($extension, $pdf)) {
                        $icon = 'pdf';
                    }
                    
                    if (in_array($extension, $sound) || in_array($extension, $video) || in_array($extension, $swf)) {
                        $array['type'] = 'media';
                        $array['href'] = $file;
                    } else 
                        if (in_array($extension, $txt) || in_array($extension, $web)) {
                            $array['type'] = 'text';
                            $array['href'] = SELF_PHP . "?mode=edit&f=" . $file;
                        } else {
                            $array['type'] = 'file';
                            $array['href'] = $file;
                        }
                    $array['src'] = ICON_FOLDER . $icon . '.gif';
                    $array['alt'] = $file_name;
                    break;
                }
        }
    }
    return $array;
}

/**
 * get_body_array
 *
 * @param unknown_type $dir            
 * @param number $page            
 * @return multitype:NULL multitype:string NULL unknown
 */
function get_body_array($dir, $page)
{
    $array = array();
    
    $lock = null;
    if (preg_match("/\.\./", "$dir")) {
        $lock = '1';
    }
    if ($lock) {
        return $array;
    }
    if ($dir) {
        $dir_name = "./$dir";
    } else {
        $dir_name = ".";
    }
    $file_list = get_list($dir_name);
    
    $maxsize = count($file_list);
    
    $from = (($page - 1) * DATA_PER_PAGE);
    $to = (($page * DATA_PER_PAGE));
    if ($to > $maxsize) {
        $to = $maxsize;
    }
    
    $dir_list = null;
    for ($count = $from; $count < $to; $count ++) {
        $file_name = $file_list[$count];
        $file_path = "$dir_name/$file_name";
        $file_size = filesize($file_path);
        $file_mtime = filemtime($file_path);
        
        if (is_dir($file_path)) {
            $dir_list = "$dir_list\t$file_name";
        } else {
            $array[] = get_dir_array($file_path, $file_name, $file_size, $file_mtime, $dir, $page);
        }
    }
    
    $dir_list = explode("\t", $dir_list);
    sort($dir_list);
    
    $count_dir_list = count($dir_list);
    for ($count = 1; $count < $count_dir_list; $count ++) {
        $encoded_url = rawurlencode($dir . '/' . $dir_list[$count]);
        $_array = array();
        $_array['file'] = $dir_list[$count];
        $_array['alt'] = $dir_list[$count];
        $_array['type'] = 'dir';
        $_array['href'] = SELF_PHP . '?dir=' . $encoded_url;
        $_array['src'] = ICON_FOLDER . 'folder.gif';
        $_array['size'] = '-';
        $_array['mdate'] = date(DATE_FORMAT, $file_mtime);
        $array[] = $_array;
    }
    return $array;
}
// ///////main////////////////

header("Content-type: text/html; charset=utf-8");
switch ($mode) {
    case 'popup':
        {
            require_once HIDE_FOLDER . '/plugin/popup.inc';
            return;
        }
    case 'thumb':
        {
            require_once HIDE_FOLDER . '/plugin/thumb.inc';
            return;
        }
    case 'dl':
        {
            require_once HIDE_FOLDER . '/plugin/dl.inc';
            return;
        }
    case 'embed':
        {
            require_once HIDE_FOLDER . '/plugin/embed.inc';
            return;
        }
    case 'stream':
        {
            require_once HIDE_FOLDER . '/plugin/stream.inc';
            return;
        }
    case 'edit':
        {
            require_once HIDE_FOLDER . '/plugin/editor.inc';
            return;
        }
    default:
        {
            break;
        }
}
// doc output
{
    $menu = get_menu_array($dir, $home, $lock);
    $paging = get_paging_array($dir, $page);
    $data = get_body_array($dir, $page);
    
    ob_start('mb_output_handler');
    require (TEMPLATE_FOLDER . 'index.inc');
    
    $output = ob_get_contents();
    $output = str_replace('%CHARSET%', CHARSET, $output);
    $output = str_replace('%TITLE%', $title, $output);
    $output = str_replace('%SELF%', SELF_PHP, $output);
    $output = str_replace('%HIDE_FOLDER%', HIDE_FOLDER, $output);
    ob_end_clean();
    
    echo $output;
}
?>
