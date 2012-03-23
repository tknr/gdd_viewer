<?php echo '<?xml version="1.0" encoding="'.CHARSET.'"?>'?>
<!DOCTYPE html PUBLIC "-//WAPFORUM//DTD XHTML Mobile 1.0//EN" "http://www.wapforum.org/DTD/xhtml-mobile10.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
<head>
<meta http-equiv="Content-Type" content="text/html; charset=%CHARSET%" />
<title>%TITLE%</title>
<style type="text/css">
<!--
body { 	font-size: 13; background-color: white; }
a { color: royalblue; font-size: 13;}
a:hover { color: lightcoral; text-decoration: underline; }
.td { font-size: 13; 	background-color: #ffffff; text-align: left;}
-->
</style>
</head>
<body>

<p>

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
<a href="%SELF%" directkey="*" accesskey="*" nonumber>[*]Parent Dir</a>
<?php if(array_key_exists('upper_dir',$menu)){?>
 | <a href="%SELF%?dir=<?=$menu['upper_dir']?>" directkey="#" accesskey="#" nonumber>[#]Upper Dir</a>
<?php }?>
<?php }?>
 | <a href="<?=$menu['home']?>" directkey="0" accesskey="0" nonumber>[0]Home</a>
 <br />
<!-- menu -->

<!-- paging -->
<?php if($paging['page'] > $paging['from']){?>
<a href="%SELF%?page=1&dir=<?=$paging['dir']?>">&lt;&lt;</a>|<a href="%SELF%?page=<?=$paging['prev']?>&dir=<?=$paging['dir']?>">&lt;</a>|
<?php }else{?>
<span >&lt;&lt;</span>|<span >&lt;</span>|
<?php }?>
<?php for($count = $paging['from'] ; $count <= $paging['to'] ; $count++){
	if($count != $paging['from']){?>|<?php ;}
	if($count == $paging['page']){?><span data-role="button" data-inline="true"><?=$count?>/<?=$paging['maxpage']?></span><?php ;
	}else{
		$accesskey = "";
		if($count > 0 && $count < 10){
			$accesskey = " directkey=\"$count\" accesskey=\"$count\" nonumber";
		}
		?><a href="%SELF%?page=<?=$count?>&dir=<?=$paging['dir']?>"<?=$accesskey?>><?=$count?></a><?php 
	}
 }?>
<?php if($paging['page'] < $paging['to']){?>
|<a href="%SELF%?page=<?=$paging['next']?>&dir=<?=$paging['dir']?>">&gt;</a>|<a href="%SELF%?page=<?=$paging['maxpage']?>&dir=<?=$paging['dir']?>">&gt;&gt;</a>
<?php }else{?>
|<span >&gt;</span>|<span >&gt;&gt;</span>
<?php }?>
<br />
<!-- paging -->

</p>

<table border="0" cellpadding="3" cellspacing="1" bgcolor="gray">
	<tr>
		<td class="td"><b>icon</b></td>
		<td class="td"><b>filename</b></td>
		<td class="td"><b>image</b></td>
		<td class="td"><b>size</b></td>
		<td class="td"><b>date</b></td>
	</tr>

<?php foreach($data as $index=>$datum){?>
	<?php if(strcmp('img',$datum['type'])==0){?>
	<tr>
		<td class="td"><b><a href="<?=$datum['href']?>"><img src="<?=$datum['src']?>" width="<?=$datum['width']?>" height="<?=$datum['height']?>" border="0" alt="<?=$datum['alt']?>" /></a></b></td>
		<td class="td"><b><a href="<?=$datum['href']?>"><?=$datum['file']?></a></b></td>
		<td class="td"><b><?=$datum['original_width']?>x<?=$datum['original_height']?></b></td>
		<td class="td"><b><?=$datum['size']?></b></td>
		<td class="td"><b><?=$datum['mdate']?></b></td>
	</tr>
	<?php }else if(strcmp('media',$datum['type'])==0){?>
	<tr>
		<td class="td"><b><a href="%SELF%?mode=dl&f=<?=$datum['href']?>"><img src="<?=$datum['src']?>" width="<?=$datum['width']?>" height="<?=$datum['height']?>" border="0" alt="<?=$datum['alt']?>" /></a></b></td>
		<td class="td"><b><a href="%SELF%?mode=dl&f=<?=$datum['href']?>"><?=$datum['file']?></a></b></td>
		<td class="td"><b>-</b></td>
		<td class="td"><b><?=$datum['size']?></b></td>
		<td class="td"><b><?=$datum['mdate']?></b></td>
	</tr>
	<?php }else{?>
	<tr>
		<td class="td"><b><a href="<?=$datum['href']?>"><img src="<?=$datum['src']?>" /></a></b></td>
		<td class="td"><b><a href="<?=$datum['href']?>"><?=$datum['file']?></a></b></td>
		<td class="td"><b>-</b></td>
		<td class="td"><b><?=$datum['size']?></b></td>
		<td class="td"><b><?=$datum['mdate']?></b></td>
	</tr>
	<?php }?>
<?php }?>
</table>

<p>

<!-- paging -->
<?php if($paging['page'] > $paging['from']){?>
<a href="%SELF%?page=1&dir=<?=$paging['dir']?>">&lt;&lt;</a>|<a href="%SELF%?page=<?=$paging['prev']?>&dir=<?=$paging['dir']?>">&lt;</a>|
<?php }else{?>
<span >&lt;&lt;</span>|<span >&lt;</span>|
<?php }?>
<?php for($count = $paging['from'] ; $count <= $paging['to'] ; $count++){
	if($count !=$paging['from']){?>|<?php ;}
	if($count == $paging['page']){?><span data-role="button" data-inline="true"><?=$count?>/<?=$paging['maxpage']?></span><?php ;
	}else{
		$accesskey = "";
		if($count > 0 && $count < 10){
			$accesskey = " directkey=\"$count\" accesskey=\"$count\" nonumber";
		}
		?><a href="%SELF%?page=<?=$count?>&dir=<?=$paging['dir']?>"<?=$accesskey?>><?=$count?></a><?php 
	}
 }?>
<?php if($paging['page'] < $paging['to']){?>
|<a href="%SELF%?page=<?=$paging['next']?>&dir=<?=$paging['dir']?>">&gt;</a>|<a href="%SELF%?page=<?=$paging['maxpage']?>&dir=<?=$paging['dir']?>">&gt;&gt;</a>
<?php }else{?>
|<span >&gt;</span>|<span >&gt;&gt;</span>
<?php }?>
<br />
<!-- paging -->

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
<a href="%SELF%" directkey="*" accesskey="*" nonumber>[*]Parent Dir</a>
<?php if(array_key_exists('upper_dir',$menu)){?>
 | <a href="%SELF%?dir=<?=$menu['upper_dir']?>" directkey="#" accesskey="#" nonumber>[#]Upper Dir</a>
<?php }?>
<?php }?>
 | <a href="<?=$menu['home']?>" directkey="0" accesskey="0" nonumber>[0]Home</a>
 <br />
<!-- menu -->

</p>
</body>
</html>