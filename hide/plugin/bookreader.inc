<?php
/*
 * bookreader
 */
$filename = HttpUtil::get("f");
$page = HttpUtil::getInt("p");

$arr = explode('.', $filename);
$ext = end($arr);

switch ($ext){
	case 'zip':
	{
		$zip = new \ZipArchive;
		if (!$zip->open($filename)) {
			    throw new \Exception("open error");
		}
		if ( $page > $zip->numFiles ) {
			throw new \Exception("page error");
		}


		break;
	}
	case 'rar':
	{

		break;
	}
}


$iu = new ImageUtil($f);
if ($iu->resize($tw, $th) === false) {
    echo 'resize error';
}

$expires = 60 * 60 * 23;
header('Last-Modified: Fri Jan 01 2000 00:00:00 GMT');
header('Expires: ' . gmdate('D, d M Y H:i:s T', time() + $expires));
header('Cache-Control: private, max-age=' . $expires);
//header('Pragma: ');
if ($iu->printOut() === false) {
    echo 'printOut error';
}

?>
<!DOCTYPE html>
<html>
<head>
<meta charset="%CHARSET%">
<title>%FILENAME%</title>
</head>
<body style="margin: 0px; padding: 0px;">
	<table border="0" cellpadding="0" cellspacing="0" bgcolor="#ffffff">
		<tr>
			<td><a href="javascript:history.back();"><img src="%FILENAME%" border="0"></a></td>
		</tr>
	</table>
</body>
</html>
