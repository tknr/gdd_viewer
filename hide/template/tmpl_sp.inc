<!DOCTYPE html>
<html>
<head>
<meta charset="%CHARSET%">
<title>%TITLE%</title>
<meta name="viewport" content="width = device-width, initial-scale=1.0,minimum-scale=1.0,maximum-scale=1.0,user-scalable=0" />
<script type="text/javascript" src="http://code.jquery.com/jquery.min.js"></script>
<script type="text/javascript" src="http://code.jquery.com/mobile/latest/jquery.mobile.min.js"></script>
<link href="http://code.jquery.com/mobile/latest/jquery.mobile.min.css" rel="stylesheet" type="text/css" />
<link href="%HIDE_FOLDER%/css/reset.css" rel="stylesheet" type="text/css" />
<link href="%HIDE_FOLDER%/css/base.css" rel="stylesheet" type="text/css" />
<meta name="apple-mobile-web-app-capable" content="yes" />
<meta name="apple-mobile-web-app-status-bar-style" content="black-translucent">
</head>
<body onload="setTimeout('scrollTo(0,1)',100)">
<div data-role="page" id="home">
<div data-role="header">
<div data-role="controlgroup" data-type="horizontal">
<!-- menu -->
<?php if(array_key_exists('dir_name',$menu)){?>
Index of <b><?=$menu['dir_name']?></b><br />
<?php }?>
<?php if(array_key_exists('error',$menu)){?>
<b style=\"color:crimson;\"><?=$menu['error']?></b>
<?php }?>
<?php if($menu['parent_dir'] == 0){?>
<b>! Parent Dir</b>
<?php }else{?>
<a data-role="button" data-inline="true" href="%SELF%">Parent Dir</a>
<?php if(array_key_exists('upper_dir',$menu)){?>
<a data-role="button" data-inline="true" href="%SELF%?dir=<?=$menu['upper_dir']?>">Upper Dir</a>
<?php }?>
<?php }?>
<a data-role="button" data-inline="true" href="<?=$menu['home']?>">Home</a>
<!-- menu -->
</div>
<div data-role="controlgroup" data-type="horizontal">
<!-- paging -->
<?php if($paging['page'] > $paging['from']){?>
<a data-role="button" data-inline="true" href="%SELF%?page=1&dir=<?=$paging['dir']?>">&lt;&lt;</a><a data-role="button" data-inline="true" href="%SELF%?page=<?=$paging['prev']?>&dir=<?=$paging['dir']?>">&lt;</a>
<?php }else{?>
<span data-role="button">&lt;&lt;</span><span data-role="button">&lt;</span>
<?php }?>
<?php for($count = $paging['from'] ; $count <= $paging['to'] ; $count++){
	if($count == $paging['page']){?><span data-role="button" data-inline="true"><?=$count?>/<?=$paging['maxpage']?></span><?php ;
	}else{
		?><a data-role="button" data-inline="true" href="%SELF%?page=<?=$count?>&dir=<?=$paging['dir']?>"><?=$count?></a><?php 
	}
 }?>
<?php if($paging['page'] < $paging['to']){?>
<a data-role="button" data-inline="true" href="%SELF%?page=<?=$paging['next']?>&dir=<?=$paging['dir']?>">&gt;</a><a data-role="button" data-inline="true" href="%SELF%?page=<?=$paging['maxpage']?>&dir=<?=$paging['dir']?>">&gt;&gt;</a>
<?php }else{?>
<span data-role="button">&gt;</span><span data-role="button">&gt;&gt;</span>
<?php }?>
<!-- paging -->
</div>
</div>
<div data-role="content">

<div class="content-primary main-content">
<ul data-role="listview"> 
<?php foreach($data as $index=>$datum){?>
	<?php if(strcmp('img',$datum['type'])==0){?>
	<li>
		<a href="<?=$datum['href']?>" target="_blank"><img src="<?=$datum['src']?>" width="<?=$datum['width']?>" height="<?=$datum['height']?>" border="0" alt="<?=$datum['alt']?>" /></a>
		<p><a href="<?=$datum['href']?>"><?=$datum['file']?></a></p>
		<p><?=$datum['original_width']?>x<?=$datum['original_height']?></p>
		<p><?=$datum['size']?></p>
		<p><?=$datum['mdate']?></p>
	</li>
	<?php }else{?>
	<li>
		<a href="<?=$datum['href']?>" target="_blank"><img src="<?=$datum['src']?>" width="<?=MAX_DIST?>" height="<?=MAX_DIST?>" border="0" alt="<?=$datum['alt']?>"  /></a>
		<p><a href="<?=$datum['href']?>"><?=$datum['file']?></a></p>
		<p><?=$datum['size']?></p>
		<p><?=$datum['mdate']?></p>
	</li>
	<?php }?>
<?php }?>
</ul>
</div>

</div>
<div data-role="footer">
<div data-role="controlgroup" data-type="horizontal">
<!-- paging -->
<?php if($paging['page'] > $paging['from']){?>
<a data-role="button" data-inline="true" href="%SELF%?page=1&dir=<?=$paging['dir']?>">&lt;&lt;</a><a data-role="button" data-inline="true" href="%SELF%?page=<?=$paging['prev']?>&dir=<?=$paging['dir']?>">&lt;</a>
<?php }else{?>
<span data-role="button">&lt;&lt;</span><span data-role="button">&lt;</span>
<?php }?>
<?php for($count = $paging['from'] ; $count <= $paging['to'] ; $count++){
	if($count == $paging['page']){?><span data-role="button" data-inline="true"><?=$count?>/<?=$paging['maxpage']?></span><?php ;
	}else{
		?><a data-role="button" data-inline="true" href="%SELF%?page=<?=$count?>&dir=<?=$paging['dir']?>"><?=$count?></a><?php 
	}
 }?>
<?php if($paging['page'] < $paging['to']){?>
<a data-role="button" data-inline="true" href="%SELF%?page=<?=$paging['next']?>&dir=<?=$paging['dir']?>">&gt;</a><a data-role="button" data-inline="true" href="%SELF%?page=<?=$paging['maxpage']?>&dir=<?=$paging['dir']?>">&gt;&gt;</a>
<?php }else{?>
<span data-role="button">&gt;</span><span data-role="button">&gt;&gt;</span>
<?php }?>
<!-- paging -->
</div>
<div data-role="controlgroup" data-type="horizontal">
<!-- menu -->
<?php if(array_key_exists('dir_name',$menu)){?>
Index of <b><?=$menu['dir_name']?></b><br />
<?php }?>
<?php if(array_key_exists('error',$menu)){?>
<b style=\"color:crimson;\"><?=$menu['error']?></b>
<?php }?>
<?php if($menu['parent_dir'] == 0){?>
<b>! Parent Dir</b>
<?php }else{?>
<a data-role="button" data-inline="true" href="%SELF%">Parent Dir</a>
<?php if(array_key_exists('upper_dir',$menu)){?>
<a data-role="button" data-inline="true" href="%SELF%?dir=<?=$menu['upper_dir']?>">Upper Dir</a>
<?php }?>
<?php }?>
<a data-role="button" data-inline="true" href="<?=$menu['home']?>">Home</a>
<!-- menu -->
</div>
</div>
</div>
</body>
</html>