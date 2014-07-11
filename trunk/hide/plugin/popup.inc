<?php
/*
 * popup
 */
$filename = HttpUtil::get('filename');
?>
<html><head><title><?=$filename?></title></head>
<body style="margin:0px;padding:0px;">
<table border="0" cellpadding="0" cellspacing="0" bgcolor="#ffffff">
<tr><td>
<a href="javascript:history.back();"><img src="<?=$filename?>" border="0"></a>
</td></tr>
</table>
</body>
</html>