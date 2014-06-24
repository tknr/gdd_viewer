<?php
/*
 * editor
 */
$filename = http_get ( 'f' );
$text = file_get_contents ( $filename );
// $text = htmlspecialchars($text);
$ext = substr ( $filename, strrpos ( $filename, '.' ) + 1 );
$result = '';
if (array_key_exist ( 'save', $_POST ) && $_POST ['save']) {
    $fp = @fopen ( $filename, 'w' );
    if (! $fp) {
        $result = 'cannot write';
    } else {
        $contents = htmlspecialchars ( $_POST ['contents'] );
        fwrite ( $fp, $contents );
        fclose ( $fp );
        $result = 'write succeded.';
    }
}
?>
<html>
<head>
<meta charset="<?=CHARSET?>">
<title><?=$filename?></title>
<meta name="viewport" content="width=device-width, initial-scale=1.0,minimum-scale=1.0,maximum-scale=1.0,user-scalable=0" />
<link rel="stylesheet" href="http://code.jquery.com/mobile/latest/jquery.mobile.min.css" />
<script type="text/javascript" src="http://code.jquery.com/jquery.min.js"></script>
<script type="text/javascript" src="http://code.jquery.com/mobile/latest/jquery.mobile.min.js"></script>
<link href="http://alexgorbatchev.com/pub/sh/current/styles/shThemeDefault.css" rel="stylesheet" type="text/css" />
<script src="http://alexgorbatchev.com/pub/sh/current/scripts/shCore.js" type="text/javascript"></script>
<script src="http://alexgorbatchev.com/pub/sh/current/scripts/shAutoloader.js" type="text/javascript"></script>
<meta name="apple-mobile-web-app-status-bar-style" content="black-translucent">
</head>
<body style="margin: 0px; padding: 0px;">
	<div data-role="page" id="home">
		<div data-role="content">
			<div class="content-primary main-content">
				<form method="post" action="<?=$_SERVER ["PHP_SELF"]?>">
					<table border="0" cellpadding="0" cellspacing="0" bgcolor="#ffffff">
						<tr>
							<td><a data-role="button" target="_blank" href="<?=$_SERVER ["PHP_SELF"]?>?mode=dl&f=<?=$filename?>"><?=$filename?></a></td>
						</tr>
						<tr>
							<td>
								<?=$result?>
							</td>
						</tr>
						<tr>
							<td><textarea name="contents" class="brush: <?=$ext?>;" cols="32" rows="20" wrap="off"><?=$text?></textarea></td>
						</tr>
						<tr>
							<td><input type="reset" name="reset" value="reset" data-role="button" /> <input type="submit" name="save" value="save" data-role="button" /></td>
						</tr>
					</table>
				</form>
			</div>
		</div>
	</div>
	<script type="text/javascript">
function path()
{
	var args = arguments,
	result = []
	;
	
	for(var i = 0; i < args.length; i++){
		result.push(args[i].replace('@', '/pub/sh/current/scripts/'));
	}
	return result;
};
 
SyntaxHighlighter.autoloader.apply(null, path(
	'applescript	@shBrushAppleScript.js',
	'actionscript3 as3	@shBrushAS3.js',
	'bash shell	@shBrushBash.js',
	'coldfusion cf	@shBrushColdFusion.js',
	'cpp c	@shBrushCpp.js',
	'c# c-sharp csharp	@shBrushCSharp.js',
	'css	@shBrushCss.js',
	'delphi pascal	@shBrushDelphi.js',
	'diff patch pas	@shBrushDiff.js',
	'erl erlang	@shBrushErlang.js',
	'groovy	@shBrushGroovy.js',
	'java	@shBrushJava.js',
	'jfx javafx	@shBrushJavaFX.js',
	'js jscript javascript @shBrushJScript.js',
	'perl pl	@shBrushPerl.js',
	'php	@shBrushPhp.js',
	'text plain	@shBrushPlain.js',
	'py python	@shBrushPython.js',
	'ruby rails ror rb	@shBrushRuby.js',
	'sass scss	@shBrushSass.js',
	'scala	@shBrushScala.js',
	'sql	@shBrushSql.js',
	'vb vbnet	@shBrushVb.js',
	'xml xhtml xslt html @shBrushXml.js'
));
SyntaxHighlighter.config.tagName="textarea";
SyntaxHighlighter.defaults['toolbar'] = false;
SyntaxHighlighter.all('contents')
</script>
</body>
</html>
