<?php
/*
 * embed
 */
$filename = HttpUtil::get('filename');
?>
<html>
<head>
<meta charset="<?=CHARSET?>">
<title><?=$filename?></title>
<meta name="viewport" content="width=device-width, initial-scale=1.0,minimum-scale=1.0,maximum-scale=1.0,user-scalable=0" />
</head>
<body style="margin:0px;padding:0px;">
<table border="0" cellpadding="0" cellspacing="0" bgcolor="#ffffff">
<tr><td>
<embed src="<?=$filename?>" width="100%" height="auto" airplay="allow" control="console" controller="true" autostart="true" /> 
</td></tr>
</table>
</body>
</html>