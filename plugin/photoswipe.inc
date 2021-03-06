<!DOCTYPE html>
<html>
<head>
<meta charset="%CHARSET%">
<title>%TITLE%</title>
<meta name="viewport" content="width=device-width, initial-scale=1.0,minimum-scale=1.0,maximum-scale=1.0,user-scalable=0" />
<meta name="apple-mobile-web-app-status-bar-style" content="black-translucent">
<link rel="stylesheet" href="//code.jquery.com/mobile/1.4.3/jquery.mobile-1.4.3.min.css" />
<link rel="stylesheet" href="//cdnjs.cloudflare.com/ajax/libs/photoswipe/3.0.5/photoswipe.min.css" />
</head>

<body>
	<div data-role="page" id="home">
		<div data-role="content">
			<div class="content-primary main-content">
				<ul data-role="listview" id="Gallery"> 
	<?php foreach($data as $index=>$datum){?>
	<?php if(strcmp('img',$datum['type'])==0){?>
	<li><a target="_blank" id="image" href="<?=$datum['href']?>"> <img src="<?=$datum['src']?>" width="<?=$datum['width']?>" height="<?=$datum['height']?>" border="0" alt="<?=$datum['alt']?>" />
							<h3>
								<?=$datum['file']?>
							</h3>
							<p>
								<?=$datum['original_width']?>
								x
								<?=$datum['original_height']?>
								<br />
								<?=$datum['size']?>
								<br />
								<?=$datum['mdate']?>
								<br />
							</p>
					</a></li>
	<?php }?>
	<?php }?>
</ul>
			</div>
		</div>
	</div>
	<script type="text/javascript" src="//code.jquery.com/jquery-1.11.1.min.js"></script>
	<script type="text/javascript" src="//code.jquery.com/mobile/1.4.3/jquery.mobile-1.4.3.min.js"></script>
	<script type="text/javascript" src="//cdn.jsdelivr.net/jquery.animate-enhanced/1.07/jquery.animate-enhanced.min.js"></script>
	<script type="text/javascript" src="//cdnjs.cloudflare.com/ajax/libs/photoswipe/3.0.5/klass.min.js"></script>
	<script type="text/javascript" src="//cdnjs.cloudflare.com/ajax/libs/photoswipe/3.0.5/code.photoswipe.jquery.min.js"></script>
	<script type="text/javascript">
    $(document).ready(function(){  
        var myPhotoSwipe = $("ul#Gallery a#image").photoSwipe({ enableMouseWheel: true , enableKeyboard: true });  
    });  
    </script>
</body>
</html>