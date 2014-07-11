<?php
$data = get_body_array($dir, $page, 65535);
?>
<!DOCTYPE html>
<html>
<head>
<title><?=$dir?></title>
<meta name="viewport" content="width=device-width, initial-scale=1.0,minimum-scale=1.0,maximum-scale=1.0,user-scalable=0" />
<meta name="apple-mobile-web-app-capable" content="yes" />
<meta name="apple-mobile-web-app-status-bar-style" content="black-translucent">
<link rel="stylesheet" href="//code.jquery.com/mobile/latest/jquery.mobile.min.css" />
<link rel="stylesheet" href="//cdnjs.cloudflare.com/ajax/libs/photoswipe/3.0.5/photoswipe.min.css" />

</head>
<body>
	<div data-role="page" id="home">
		<div data-role="content">
			<div class="content-primary main-content">
				<ul data-role="listview" id="Gallery">
				<?php foreach($data as $index=>$datum){?>
	<?php if(strcmp('img',$datum['type'])==0){?>
	<li><a href="<?=$datum['href']?>"><img src="<?=$datum['src']?>" alt="<?=$datum['alt']?>" />
					</a></li>
	<?php }}?>
				</ul>
			</div>
		</div>
	</div>
	<script type="text/javascript" src="//code.jquery.com/jquery-1.6.4.min.js"></script>
		<script type="text/javascript" src="//cdn.jsdelivr.net/jquery.animate-enhanced/1.07/jquery.animate-enhanced.min.js"></script>
	<script type="text/javascript" src="//cdnjs.cloudflare.com/ajax/libs/photoswipe/3.0.5/klass.min.js"></script>
	<script type="text/javascript" src="//cdnjs.cloudflare.com/ajax/libs/photoswipe/3.0.5/code.photoswipe.jquery.min.js"></script>
	<script type="text/javascript">
	(function(window, PhotoSwipe){
			document.addEventListener('DOMContentLoaded', function(){
				var
					options = {},
					instance = PhotoSwipe.attach( window.document.querySelectorAll('#Gallery a'), options );
			}, false);
		}(window, window.Code.PhotoSwipe));
    </script>

</body>
</html>
