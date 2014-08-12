<?php
/*
 * thumb
 */
$f = HttpUtil::get("f");
$tw = HttpUtil::getInt("tw");
$th = HttpUtil::getInt("th");

$iu = new ImageUtil($f);
$iu->image_resize($tw, $th);

$expires = 60 * 60 * 23;
header('Last-Modified: Fri Jan 01 2010 00:00:00 GMT');
header('Expires: ' . gmdate('D, d M Y H:i:s T', time() + $expires));
header('Cache-Control: private, max-age=' . $expires);
header('Pragma: ');
$iu->outImage();
?>