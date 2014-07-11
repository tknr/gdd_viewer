<?php
$gdv=0; 	//GD Ver. 1.x--'1' 2.x--'0'
/*
 * thumb
 */
$ext = HttpUtil::get("ext");
$f = HttpUtil::get("f");
$ow = HttpUtil::get("ow");
$oh = HttpUtil::get("oh");
$tw = HttpUtil::get("tw");
$th = HttpUtil::get("th");


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
APCUtil::put(SCRIPT_TITLE.'_'.$ext.'_'.$f.'_'.$ow.'_'.$oh.'_'.$tw.'_'.$th, $t);
ImageDestroy($o);
ImageDestroy($t);
?>