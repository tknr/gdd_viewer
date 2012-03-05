<?php
/*
 * dl
 */
mb_http_output("pass");
$f = http_get('f');
$ff = split('/',$f);
$ff = array_reverse($ff);
$filename= $ff[0];
$filename_array = split('.',$filename);
$filename_array = array_reverse($filename_array);
$ext = strtoupper($filename_array[0]);

if($ext == "3GP"){
	header("Content-type: video/3gpp"); //3gp
}else if ($ext == "3G2"){
	header("Content-type: video/3gpp2"); //3g2
}else if ($ext == "MP3"){
	header("Content-type: audio/mpeg3"); //mp3
}else if ($ext == "MP4"){
	header("Content-type: video/mpeg4"); //mp4
}else{
	header("Content-type: application/octet-stream"); //other
}
$inline_filename=str_replace(" ","_",$filename);
header("Content-Disposition: inline; filename=".$inline_filename);
header("Content-length: " . filesize($f));
readfile($f);
?>