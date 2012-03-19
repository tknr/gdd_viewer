<?php
$gdv=0; 	//GD Ver. 1.x--'1' 2.x--'0'
/*
 * thumb
 */
$ext = http_get("ext");
$f = http_get("f");
$ow = http_get("ow");
$oh = http_get("oh");
$tw = http_get("tw");
$th = http_get("th");
if($ext == "2"){
	$o = imagecreatefromjpeg($f);
} else {
	$o = imagecreatefrompng($f);
}
if ($gdv){
	$t = imagecreate($tw, $th);
} else {
	$t = imagecreatetruecolor($tw, $th);
}
ImageCopyResized( $t,$o,0,0,0,0,$tw,$th,$ow,$oh);
if($ext == "2"){
	header("content-type: image/jpeg");
	imagejpeg($t);
} else {
	header("content-type: image/png");
	imagepng($t);
}
ImageDestroy($o);
ImageDestroy($t);
?>