<?php
/*
 * popup
 */
$filename = http_get("filename");
global $dir;
if (!$dir){
	$d='.';
}
$_out = '';
$_out .= "<html>\n<head>\n<title>$filename</title>\n</head>\n";
$_out .= "<body style=\"margin:0px;\">\n";
$_out .= "<table border=\"0\" cellpadding=\"0\" cellspacing=\"0\" bgcolor=\"#ffffff\">\n";
$_out .= "<tr><td><a href=\"javascript:void(0)\" onclick=\"window.close()\"><img src=\"$d$dir/$filename\" border=\"0\"></a></td></tr>\n</table>\n</body>\n</html>\n";
echo $_out;
?>