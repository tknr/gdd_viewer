<?php
/*
 * embed
 */
$filename = http_get('filename');
?>
<html>
<head>
<title><?=$filename?></title>
<style type="text/css">
embed { width:100% !important; max-width: 100% !important; height: auto !important; }
</style>
</head>
<body style="margin:0px;padding:0px;">
<table border="0" cellpadding="0" cellspacing="0" bgcolor="#ffffff">
<tr><td>
<embed src="<?=$filename?>" airplay="allow" control="console" controller="true" autostart="true" /> 
</td></tr>
</table>
</body>
</html>