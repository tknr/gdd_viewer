<?php echo '<?xml version="1.0" encoding="'.CHARSET.'"?>'?>
<!DOCTYPE html PUBLIC "-//WAPFORUM//DTD XHTML Mobile 1.0//EN" "http://www.wapforum.org/DTD/xhtml-mobile10.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
<head>
<meta http-equiv="Content-Type" content="text/html; charset=%CHARSET%" />
<title>%TITLE%</title>
<style type="text/css">
<!--
body { 	font-size: 13; background-color: white; }
a { color: royalblue; font-size: 13;}
a:hover { color: lightcoral; text-decoration: underline; }
.td { font-size: 13; 	background-color: #ffffff; text-align: left;}
-->
</style>
<script type="text/javascript">
<!--
function picspop(d,f,w,h){
var l=(screen.width-w)/2;
var t=(screen.height-h)/2;
window.open("%SELF%?mode=popup&dir="+d+"&filename="+f,"popup","width="+w+",height="+h+",left="+l+",top="+t);
}
//-->
</script>
</head>
<body>
%SHOWMENU%<br />
%SHOWPAGING%<br />
	<table border="0" cellpadding="3" cellspacing="1" bgcolor="gray">
		<tr>
			<td class="td"><b>icon</b></td>
			<td class="td"><b>filename</b></td>
			<td class="td"><b>image</b></td>
			<td class="td"><b>size</b></td>
			<td class="td"><b>date</b></td>
		</tr>
%SHOWBODY%
</table>
<p>
%SHOWMENU%<br />
%SHOWPAGING%<br />
</p>
</body>
</html>