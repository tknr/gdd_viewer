<div data-role="controlgroup" data-type="horizontal">
<!-- menu -->
<?php if(array_key_exists('dir_name',$menu)){?>
<span data-role="button" data-inline="true"><b><?=$menu['dir_name']?></b></span>
<?php }?>
<?php if(array_key_exists('error',$menu)){?>
<span data-role="button" data-inline="true"><b style=\"color:crimson;\"><?=$menu['error']?></b></span>
<?php }?>
<?php if($menu['parent_dir'] == 0){?>
<span data-role="button" data-inline="true"><b>! Parent Dir</b></span>
<?php }else{?>
<a data-role="button" data-inline="true" href="%SELF%">Parent Dir</a>
<?php if(array_key_exists('upper_dir',$menu)){?>
<a data-role="button" data-inline="true" href="%SELF%?dir=<?=$menu['upper_dir']?>">Upper Dir</a>
<?php }?>
<?php }?>
<a data-role="button" data-inline="true" href="<?=$menu['home']?>">Home</a>
<!-- menu -->
</div>