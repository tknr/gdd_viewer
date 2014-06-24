<!DOCTYPE html>
<html>
<head>
<meta charset="%CHARSET%">
<title>%TITLE%</title>
<meta name="viewport" content="width=device-width, initial-scale=1.0,minimum-scale=1.0,maximum-scale=1.0,user-scalable=0" />
<link rel="stylesheet" href="http://code.jquery.com/mobile/latest/jquery.mobile.min.css" />
<script type="text/javascript" src="http://code.jquery.com/jquery.min.js"></script>
<script type="text/javascript" src="http://code.jquery.com/mobile/latest/jquery.mobile.min.js"></script>
<meta name="apple-mobile-web-app-status-bar-style" content="black-translucent">
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
<ul data-role="listview"> 
	<?php foreach($data as $index=>$datum){?>
	<?php if(strcmp('img',$datum['type'])==0){?>
	<li>
		<a target="_blank" href="<?=$datum['href']?>">
		<img src="<?=$datum['src']?>" width="<?=$datum['width']?>" height="<?=$datum['height']?>" border="0" alt="<?=$datum['alt']?>" />
		<h3><?=$datum['file']?></h3>
		<p>
		<?=$datum['original_width']?>x<?=$datum['original_height']?><br />
		<?=$datum['size']?><br />
		<?=$datum['mdate']?>
		</p>
		</a>
	</li>
	<?php }else if(strcmp('media',$datum['type'])==0){?>
	<li>
		<a target="_blank" href="<?=$datum['href']?>">
		<img src="<?=$datum['src']?>" width="<?=MAX_DIST?>" height="<?=MAX_DIST?>" border="0" alt="<?=$datum['alt']?>" />
		<h3><?=$datum['file']?></h3>
		<p>
		<?=$datum['extension']?><br />
		<?=$datum['size']?><br />
		<?=$datum['mdate']?>
		</p>
		</a>
	</li>
	<?php }else if(strcmp('text',$datum['type'])==0){?>
	<li>
		<a target="_blank" href="<?=$datum['href']?>">
		<img src="<?=$datum['src']?>" width="<?=MAX_DIST?>" height="<?=MAX_DIST?>" border="0" alt="<?=$datum['alt']?>" />
		<h3><?=$datum['file']?></h3>
		<p>
		<?=$datum['extension']?><br />
		<?=$datum['size']?><br />
		<?=$datum['mdate']?>
		</p>
		</a>
	</li>
	<?php }else if(strcmp('dir',$datum['type'])==0){?>
	<li>   
		<a href="<?=$datum['href']?>">              
		<img src="<?=$datum['src']?>" width="<?=MAX_DIST?>" height="<?=MAX_DIST?>" border="0" alt="<?=$datum['alt']?>" />
		<h3><?=$datum['file']?></h3>                
		<p>
		<?=$datum['mdate']?>        
		</p>     
		</a>     
	</li> 
	<?php }else{?>
	<li>
		<a target="_blank" href="?mode=dl&f=<?=$datum['href']?>">
		<img src="<?=$datum['src']?>" width="<?=MAX_DIST?>" height="<?=MAX_DIST?>" border="0" alt="<?=$datum['alt']?>"  />
		<h3><?=$datum['file']?></h3>
		<p>
		<?=$datum['extension']?><br />
		<?=$datum['size']?><br />
		<?=$datum['mdate']?>
		</p>
		</a>
	</li>
	<?php }?>
	<?php }?>
</ul>
</div>

</div>

</div>
</body>
</html>
