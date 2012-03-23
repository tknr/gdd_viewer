<?php
/*
 * popup
 */
$filename = http_get('filename');
$dir = http_get('dir');
if (!$dir){
	$dir='.';
}
?>
<html><head><title><?=$filename?></title></head>
<body style="margin:0px;padding:0px;">
<table border="0" cellpadding="0" cellspacing="0" bgcolor="#ffffff">
<tr><td>
<a href="javascript:void(0)" onclick="window.close()"><img src="<?=$dir.'/'.$filename ?>" border="0"></a>
</td></tr>
</table>
</body>
</html>