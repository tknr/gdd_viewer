<!DOCTYPE html>
<html>
<head>
<meta charset="%CHARSET%">
<title>%TITLE%</title>
<meta name="viewport" content="width=device-width, initial-scale=1.0,minimum-scale=1.0,maximum-scale=1.0,user-scalable=0" />
<meta name="apple-mobile-web-app-status-bar-style" content="black-translucent">
<link rel="stylesheet" href="%HIDE_FOLDER%/css/minireset.css" />
<link rel="stylesheet" href="//code.jquery.com/mobile/latest/jquery.mobile.min.css" />
<link href="//alexgorbatchev.com/pub/sh/current/styles/shThemeDefault.css" rel="stylesheet" type="text/css" />
</head>
<body style="margin: 0px; padding: 0px;">
	<div data-role="page" id="home">
		<div data-role="content">
			<div class="content-primary main-content">
				<form method="post" action="%SELF%?mode=edit&f=%FILENAME%" data-ajax="false">
					<table border="0" cellpadding="0" cellspacing="0" bgcolor="#ffffff">
						<tr>
							<td><a data-role="button" target="_blank" href="%SELF%?mode=dl&f=%FILENAME%">%FILENAME%</a></td>
						</tr>
						<tr>
							<td>%RESULT%</td>
						</tr>
						<tr>
							<td><textarea name="contents" class="brush: %EXT%;" cols="32" rows="20" wrap="off">%TEXT%</textarea></td>
						</tr>
						<tr>
							<td><input type="reset" name="reset" value="reset" data-role="button" /> <input type="submit" name="save" value="save" data-role="button" /></td>
						</tr>
					</table>
				</form>
			</div>
		</div>
	</div>
<script type="text/javascript" src="%HIDE_FOLDER%/js/console.ie.js"></script>
<script type="text/javascript" src="//code.jquery.com/jquery-1.12.4.min.js"></script>
<script type="text/javascript" src="//alexgorbatchev.com/pub/sh/current/scripts/shCore.js"></script>
<script type="text/javascript" src="//alexgorbatchev.com/pub/sh/current/scripts/shAutoloader.js"></script>
<script type="text/javascript" src="%HIDE_FOLDER%/js/editor.js"></script>
<script type="text/javascript" src="//code.jquery.com/mobile/latest/jquery.mobile.min.js"></script>
</body>
</html>
