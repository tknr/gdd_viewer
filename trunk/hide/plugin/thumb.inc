<?php
$gdv = 0; // GD Ver. 1.x--'1' 2.x--'0'
/*
 * thumb
 */
$ext = HttpUtil::getInt("ext");
$f = HttpUtil::get("f");
$ow = HttpUtil::getInt("ow");
$oh = HttpUtil::getInt("oh");
$tw = HttpUtil::getInt("tw");
$th = HttpUtil::getInt("th");
/*
if ($ext == 2) {
    $o = imagecreatefromjpeg($f);
} else {
    $o = imagecreatefrompng($f);
}
if ($gdv) {
    $t = imagecreate($tw, $th);
} else {
    $t = imagecreatetruecolor($tw, $th);
}
ImageCopyResampled($t, $o, 0, 0, 0, 0, $tw, $th, $ow, $oh);
*/

$iu = new ImageUtil($f);
$iu->image_resize($tw, $th);

$expires = 60 * 60 * 23;
header('Last-Modified: Fri Jan 01 2010 00:00:00 GMT');
header('Expires: ' . gmdate('D, d M Y H:i:s T', time() + $expires));
header('Cache-Control: private, max-age=' . $expires);
header('Pragma: ');
/*
if ($ext == 2) {
    header("content-type: image/jpeg");
    imagejpeg($t);
} else {
    header("content-type: image/png");
    imagepng($t);
}

ImageDestroy($o);
ImageDestroy($t);
*/
$iu->outImage();
?>