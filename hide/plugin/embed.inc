<?php
/*
 * embed
 */
$filename = http_get('filename');
?>
<html><head><title><?=$filename?></title></head>
<body style="margin:0px;padding:0px;">
<table border="0" cellpadding="0" cellspacing="0" bgcolor="#ffffff">
<tr><td>
<embed src="<?=$filename?>" width="320" height="240" airplay="allow" allowfullscreen="true"> 
</td></tr>
</table>
</body>
</html>