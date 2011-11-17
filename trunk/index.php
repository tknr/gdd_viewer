<?php
/////////config//////////
$gdv=0; 	//GD Ver. 1.x--'1' 2.x--'0'
$title='gdd viewer';	//Page title
$home='../'; 	//Home URL
$maxdist=32; 	//thumbnail size
$charset='UTF-8'; //Shift_JIS
$date_format="Y/m/d H:i:s"; // Y/m/d H:i:s
$home_link = '<a href="http://tknr.com/" target="_blank">tknr.com</a>';
/////////////////////////
$dir = $_GET["dir"];
$self = array_reverse( explode("/",$_SERVER["SCRIPT_NAME"]) );

$page = floor($_GET["page"]);
if(!$page){ $page = 1;}
$size = floor($_GET["size"]);
if(!$size){ $size = 10;}
$width = floor($_GET["width"]);
if(!$width){ $width = 10;}

function get_list($dir_cnt) {
	$dir_handle=opendir($dir_cnt);
	while ($file = readdir($dir_handle)){
		$file_list = "$file_list\t$file";
	}
	closedir($dir_handle);
	
	$file_list = explode("\t",$file_list);
	sort($file_list);

	return $file_list;
}

function showmenu(){
	global $dir;
	global $self;
	global $home;
	global $size;
	global $width;
		
	if (preg_match("/\.\./","$dir")){ $lock ='1';}
	if((!$lock)&&($dir)){echo "Index of <b>$dir</b><br />";}
	if(($lock)&&($dir)){echo "<b style=\"color:crimson;\">Wrong Action !</b>";}
	if (!$dir) {echo "<b>! Parent Dir</b>";} else {
		$dd = explode("/",$dir);
		echo "<a href=\"$self[0]?size=$size&width=$width\" directkey=\"*\" accesskey=\"*\" nonumber>[*]Parent Dir</a>";
		if ($dd[2]){
			$tdir=array_pop($dd);
			$back_dir = explode("/$tdir",$dir);
			echo " | <a href=\"$self[0]?size=$size&width=$width&dir=$back_dir[0]\" directkey=\"#\" accesskey=\"#\" nonumber>[#]Upper Dir</a>";
		}
	}
	echo " | <a href=\"$home?size=$size&width=$width\" accesskey=\"0\">[0]Home</a><p>\n";
	
}

function showpaging(){
	global $dir;
	global $self;
	global $size;
	global $page;
	global $width;

	if ($dir){$dir_name = "./$dir";} else {$dir_name = ".";}
	$file_list = get_list($dir_name);
	$maxsize = count($file_list);

	echo "count : $maxsize | ";

	//width
	$maxpage = floor($maxsize / $size);
	if($maxsize % $size !=0){
		$maxpage ++;
	}
	$halfwidth = floor($width /2);
	$from = $page - $halfwidth;
	$to = $page + $halfwidth;
	if($maxpage <= $width){
		$from = 1;
		$to = $maxpage;
	}else if($page <= $halfwidth){
		$from = 1;
		$to = $width;
	}else if(($page > ($maxpage - $halfwidth)) && ($maxpage - $width > 0)){
		$from = $maxpage - $width;
		$to = $maxpage;
	}

	for($count = $from ; $count <= $to ; $count++){
		if($count !=$from){ echo "|";	}
		if($count == $page){
			echo " $count / $maxpage ";
		}else{
			$accesskey = "";
			if($count > 0 && $count < 10){
				$accesskey = " directkey=\"$count\" accesskey=\"$count\" nonumber";
			}
			echo " <a href=\"$self[0]?size=$size&width=$width&page=$count&dir=$dir\"$accesskey>$count</a>";
		}
	}
	echo "<br />\n";
}

global $self;
$c = $home_link;
$mode = $_GET["mode"];

if ($mode == "popup"){
	$filename = $_GET["filename"];
	global $dir;
	if (!$dir){ $d='.'; }
	echo "<html>\n<head>\n<title>$filename</title>\n</head>\n";
	echo "<body style=\"margin:0px;\">\n";
	echo "<table border=\"0\" cellpadding=\"0\" cellspacing=\"0\" bgcolor=\"#ffffff\">\n";
	echo "<tr><td><a href=\"javascript:void(0)\" onclick=\"window.close()\"><img src=\"$d$dir/$filename\" border=\"0\"></a></td></tr>\n</table>\n</body>\n</html>\n";
} elseif (($mode == "thumb") AND ($c)){
	$ext = $_GET["ext"];
	$f = $_GET["f"];
	$ow = $_GET["ow"];
	$oh = $_GET["oh"];
	$tw = $_GET["tw"];
	$th = $_GET["th"];
	if($ext == "2"){ $o = imagecreatefromjpeg($f); } else { $o = imagecreatefrompng($f); }
	if ($gdv){
	$t = imagecreate($tw, $th);} else { $t = imagecreatetruecolor($tw, $th); }
	ImageCopyResized( $t,$o,0,0,0,0,$tw,$th,$ow,$oh);
	if($ext == "2"){ header("content-type: image/jpeg"); imagejpeg($t); } else { header("content-type: image/png");imagepng($t); }
	ImageDestroy($o);
	ImageDestroy($t);
} else {
	if ($c){
		echo "<html>\n<head>\n<meta http-equiv=\"content-type\" content=\"text/html; charset=$charset\">\n";
		echo "<title>$title</title>\n";
	
?>
<style type="text/css">
<!--
body{font-size:13; background-color:white;}
a{color:royalblue; font-size:13;}
a:hover{color:lightcoral; text-decoration:underline;}
.td{font-size:13; background-color:#ffffff; text-align:left;}
-->
</style>
<script type="text/javascript">
<!--
function picspop(d,f,w,h){
var l=(screen.width-w)/2;
var t=(screen.height-h)/2;
<?
		echo "window.open(\"$self[0]?mode=popup&dir=\"+d+\"&filename=\"+f,\"popup\",\"width=\"+w+\",height=\"+h+\",left=\"+l+\",top=\"+t);\n";
?>
}
//-->
</script>
</head>
<body>
<?

		showmenu();
		showpaging();
		
		echo "<table border=\"0\" cellpadding=\"3\" cellspacing=\"1\" bgcolor=\"gray\">\n";
		echo "<tr><td class=\"td\"><b>icon</b></td><td class=\"td\"><b>filename</b></td><td class=\"td\"><b>image</b></td><td class=\"td\"><b>size</b></td><td class=\"td\"><b>date</b></td></tr>\n";
	
		function an_file($file_path){
			global $maxdist;
			$img= @getimagesize($file_path);
			if (($img[0] < $maxdist) and ($img[1] < $maxdist)){$tw=$img[0]; $th=$img[1];} else {
				if ($img[0] < $img[1]){$th=$maxdist; $tw=$img[0]*$th/$img[1];}
				if ($img[0] > $img[1]){$tw=$maxdist; $th=$img[1]*$tw/$img[0];}
				if ($img[0] == $img[1]){$tw=$maxdist; $th=$maxdist;}
			}
			$img_prop = "$img[2],$img[0],$img[1],$tw,$th,$img_type,$file_name";
			return $img_prop;
		}
	
		function show_dir($file_path, $file_name, $filesize, $file_mtime){
			global $dir;
			$img_prop = an_file($file_path);
			$img_prop = explode(",",$img_prop);
			$ext = "$img_prop[0]";
			$ow = "$img_prop[1]";
			$oh = "$img_prop[2]";
			$tw ="$img_prop[3]";
			$th ="$img_prop[4]";
		
			$web = ("html,htm");
			$zip = ("zip,lzh");
			$media = ("mp3,rm,rmi,mid,wav,wma,mpeg,avi");
			$swf = ("swf");
			$txt = ("txt,doc,xls,rtf");
			$pdf = ("pdf");
		
			$type_list =  explode(",","$web,$zip,$media,$swf,$txt,$pdf");
			global $date_format;
			$mdate=date($date_format,$file_mtime);
			$ts_1 = round($filesize/1000,1);
			$ts_2 = round($filesize/1000000,2);
			if ($ts_1 < 1) { $show_size = 1; $t = 'KB'; $m = 1; }
			if ($ts_2 > 1) { $show_size = $ts_2; $t = 'MB'; $m = 1; }
			if (!$m){ $show_size = $ts_1; $t = 'KB'; }
			global $self;
			if ($file_name != $self[0]){
				$file=".$dir/$file_name";
				echo "<tr><td class=\"td\">";
				if ($ext==1){
					echo "<a href=\"javascript:void(0)\" onclick=\"picspop('.$dir','$file_name','$ow','$oh')\">";
					echo "<img src=\".$dir/$file_name\" width=\"$tw\" height=\"$th\" border=\"0\"></a>";
				} elseif (($ext==2) or ($ext==3)){
					echo "<a href=\"javascript:void(0)\" onclick=\"picspop('.$dir','$file_name','$ow','$oh');\">";
					echo "<img src=\"$self[0]?mode=thumb&ext=$ext&f=$file&ow=$ow&oh=$oh&tw=$tw&th=$th\" width=\"$tw\" height=\"$th\" border=\"0\"></a>";
				} else {
					$get_ext = explode("." ,$file_name);
					$type = array_reverse($get_ext);
					for ($i=0; $i<count($type_list); $i++){
						if (preg_match("/$type_list[$i]$/i",$file_name)){
						if (preg_match("/$type[0]/i","$txt")){ $icon = 'txt'; }
						if (preg_match("/$type[0]/i","$media")){ $icon = 'media'; }
						if (preg_match("/$type[0]/i","$zip")){ $icon = 'zip'; }
						if (preg_match("/$type[0]/i","$web")){ $icon = 'web'; }
						if (preg_match("/$type[0]/i","$swf")){ $icon = 'swf'; }
						if (preg_match("/$type[0]/i","$pdf")){ $icon = 'pdf'; }
					}
				}
				if (!$icon){ $icon='other'; }
				echo "<a href=\"$file\" target=\"_blank\"><img src=\"hide/$icon.gif\" border=\"0\" alt=\"$file_name\"></a>";
			}
			echo "</td><td class=\"td\"><a href=\"$file\" target=\"_blank\">$file_name</a></td>";
			if (($ow) AND ($oh)){ echo "<td class=\"td\">$ow x $oh</td>"; } else { echo "<td class=\"td\">-</td>"; }
				echo "<td class=\"td\">$show_size $t</td><td class=\"td\">$mdate</td></tr>\n";
			}
			return;
		}
	
		if (preg_match("/\.\./","$dir")){ $lock ='1';}
		if(!$lock){
	
			function show_indx($dir_cnt){
				global $dir;
				global $self;
				show_indx(${script_name}); 
				ereg ( "([^/]*)$",$dir_cnt,$temp); 
				$td_name = ereg_replace( "$temp[1]$","", $dir_cnt);
			}
	
			if ($dir){$dir_name = "./$dir";} else {$dir_name = ".";}
			$file_list = get_list($dir_name);
	
			$maxsize = count($file_list);
				
			$from = (($page - 1) * $size)+1;
			$to = (($page * $size)+1);
			if($to > $maxsize){ $to = $maxsize; }
					
			for ($count=$from ;$count<$to;$count++) {
				$file_name=$file_list[$count];
				$file_path = "$dir_name/$file_name";
				$file_size = filesize($file_path);
				$file_mtime = filemtime($file_path);
			
				if (is_file($file_path)){
					show_dir($file_path, $file_name, $file_size, $file_mtime);
				} elseif(("." != $file_name) && (".." != $file_name) && (".htaccess" !=$file_name)&&(".htpasswd" !=$file_name)&&("php.ini" !=$file_name)) {
					$dir_list = "$dir_list,$file_name";
				}
			}
			
			$dir_list = explode(",",$dir_list);
			sort($dir_list); 
	
			for ($count=1;$count<count($dir_list);$count++) {
				if ($dir_list[$count] != 'hide'){
					global $date_format;
					$mdate=date($date_format,$file_mtime);
					echo "<tr><td class=\"td\">";
					echo "<a href=\"$self[0]?size=$size&width=$width&dir=$dir/$dir_list[$count]\">";
					echo "<img src=\"hide/dir.gif\" border=\"0\" width=\"32\" height=\"26\"></a></td>";
					echo "<td class=\"td\"><a href=\"$self[0]?size=$size&width=$width&dir=$dir/$dir_list[$count]\">$dir_list[$count]</a></td><td class=\"td\">-</td><td class=\"td\">-</td><td class=\"td\">$mdate</td></tr>\n";
				}
			}
		}
		echo "</table>\n<p>\n";
		showpaging();
		showmenu();
		echo "$c\n</body>\n</html>\n";
	}
}
?>