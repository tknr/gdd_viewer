<!DOCTYPE html>
<html>
<head>
<meta charset="%CHARSET%">
<title>%TITLE%</title>
<meta name="viewport" content="width=device-width, initial-scale=1.0,minimum-scale=1.0,maximum-scale=1.0,user-scalable=0" />
<meta name="apple-mobile-web-app-status-bar-style" content="black-translucent">
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
<script type="text/javascript" src="//code.jquery.com/jquery.min.js"></script>
<script type="text/javascript" src="//code.jquery.com/mobile/latest/jquery.mobile.min.js"></script>
<script type="text/javascript" src="//alexgorbatchev.com/pub/sh/current/scripts/shCore.js"></script>
<script type="text/javascript" src="//alexgorbatchev.com/pub/sh/current/scripts/shAutoloader.js"></script>
<script type="text/javascript">
$(document).bind("mobileinit", function(){
   $.mobile.ajaxFormsEnabled = false;
});
</script>
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
