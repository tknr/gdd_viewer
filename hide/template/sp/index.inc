<!DOCTYPE html>
<html>
<head>
<meta charset="%CHARSET%">
<title>%TITLE%</title>
<meta name="viewport" content="width=device-width, initial-scale=1.0,minimum-scale=1.0,maximum-scale=1.0,user-scalable=0" />
<meta name="apple-mobile-web-app-status-bar-style" content="black-translucent">
<link rel="stylesheet" href="%HIDE_FOLDER%/css/minireset.css" />
<link rel="stylesheet" href="//code.jquery.com/mobile/1.4.5/jquery.mobile-1.4.5.min.css" />
<link rel="stylesheet" href="%HIDE_FOLDER%/css/jquery-confirm.min.css" />
<link rel="stylesheet" href="%HIDE_FOLDER%/css/main.css" />
</head>
<body>
	<div data-role="page" id="home">

		<div data-role="header" data-position="fixed">
<?php require (HIDE_FOLDER.'/template/sp/dir.inc');?>
<?php require (HIDE_FOLDER.'/template/sp/menu.inc');?>
<?php require (HIDE_FOLDER.'/template/sp/paging.inc');?>
</div>

		<div data-role="content">

			<div class="content-primary main-content">
				<ul data-role="listview" id="Gallery"> 
	<?php foreach($data as $index=>$datum){?>
	<?php if(strcmp('img',$datum['type'])==0){?>
	<li><a target="_blank" id="image" href="<?=$datum['href']?>">
<?php /*?>	
	<img src="<?=$datum['src']?>" width="<?=$datum['width']?>" height="<?=$datum['height']?>" border="0" alt="<?=$datum['alt']?>" />
*/?>
							<h3>
								<?=$datum['icon']?>&nbsp;<?=$datum['file']?>
							</h3>
							<p>
								<?=$datum['original_width']?>&nbsp;x&nbsp;<?=$datum['original_height']?>&nbsp;<?=$datum['size']?>
								<br />
								<?=$datum['mdate']?>
								<br />
							</p>
					</a></li>
	<?php }else if(strcmp('media',$datum['type'])==0){?>
	<li><a target="_blank" href="<?=$datum['href']?>">
							<h3>
								<?=$datum['icon']?>&nbsp;<?=$datum['file']?>
							</h3>
							<p>
								<?=$datum['extension']?>&nbsp;<?=$datum['size']?>
								<br />
								<?=$datum['mdate']?>
							</p>
					</a></li>
	<?php }else if(strcmp('zip',$datum['type'])==0){?>
	<li><a id="zip_link_<?=$index?>" target="_blank" href="<?=$datum['href']?>" data-ajax="false">
							<h3>
								<?=$datum['icon']?>&nbsp;<?=$datum['file']?>
							</h3>
							<p>
								<?=$datum['extension']?>&nbsp;<?=$datum['size']?>
								<br />
								<?=$datum['mdate']?>
							</p>
					</a></li>
	<?php }else if(strcmp('text',$datum['type'])==0){?>
	<li><a id="text_link_<?=$index?>" target="_blank" href="<?=$datum['href']?>" data-ajax="false">
							<h3>
								<?=$datum['icon']?>&nbsp;<?=$datum['file']?>
							</h3>
							<p>
								<?=$datum['extension']?>&nbsp;<?=$datum['size']?>
								<br />
								<?=$datum['mdate']?>
							</p>
					</a></li>
	<?php }else if(strcmp('dir',$datum['type'])==0){?>
	<li><a href="<?=$datum['href']?>">
							<h3>
								<?=$datum['icon']?>&nbsp;<?=$datum['file']?>
							</h3>
							<p>
								<?=$datum['mdate']?>
							</p>
					</a></li> 
	<?php }else{?>
	<li><a target="_blank" href="<?=$datum['href']?>">
							<h3>
								<?=$datum['icon']?>&nbsp;<?=$datum['file']?>
							</h3>
							<p>
								<?=$datum['extension']?>&nbsp;<?=$datum['size']?>
								<br />
								<?=$datum['mdate']?>
							</p>
					</a></li>
	<?php }?>
	<?php }?>
</ul>
			</div>

		</div>

	</div>
	
	<script type="text/javascript" src="%HIDE_FOLDER%/js/console.ie.js"></script>
	<script type="text/javascript" src="//code.jquery.com/jquery-1.12.4.min.js"></script>
	<script type="text/javascript" src="//use.fontawesome.com/2b63a6d468.js"></script>
	<script type="text/javascript" src="%HIDE_FOLDER%/js/jquery-confirm.min.js"></script>
	<script type="text/javascript" src="%HIDE_FOLDER%/js/main.js"></script>
	<script type="text/javascript" src="//code.jquery.com/mobile/1.4.5/jquery.mobile-1.4.5.min.js"></script>
</body>
</html>
