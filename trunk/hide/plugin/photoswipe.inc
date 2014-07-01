<?php
$dir = http_get('dir');
?>
<!DOCTYPE html>
<html>
<head>
<title><?=$dir?></title>
<meta name="viewport" content="width=device-width, initial-scale=1.0,minimum-scale=1.0,maximum-scale=1.0,user-scalable=0" />
<meta name="apple-mobile-web-app-capable" content="yes" />
<meta name="apple-mobile-web-app-status-bar-style" content="black-translucent">
<link rel="stylesheet" href="http://code.jquery.com/mobile/1.0.1/jquery.mobile-1.0.1.min.css" />
</head>
<body>
<div data-role="page" id="home">
<div data-role="content">

<div class="content-primary main-content">
<ul data-role="listview"> 
</ul>
</div>


</div>
</div>
<script type="text/javascript" src="http://code.jquery.com/jquery-1.6.4.min.js"></script>
<script type="text/javascript" src="http://code.jquery.com/mobile/1.0.1/jquery.mobile-1.0.1.min.js"></script>
<script type="text/javascript" src="hide/js/jquery.animate-enhanced.min.js"></script>
<script type="text/javascript" src="hide/js/klass.min.js"></script>
<script type="text/javascript" src="hide/js/code.photoswipe-3.0.4.min.js"></script>
<script type="text/javascript">
		$(document).ready(function(){
			$('div.gallery-page').live('pageshow', function(e){
				$("div.gallery a", e.target).photoSwipe();
				return true;
			})
		});
</script>

</body>
</html>
