
<!-- menu -->
<?php if(array_key_exists('dir_name',$menu)){?>
<span data-role="button" data-inline="true" data-mini="true"><b><?=$menu['dir_name']?></b></span>
<?php }?>
<?php if(array_key_exists('error',$menu)){?>
<span data-role="button" data-inline="true" data-mini="true" data-icon="info"><b style=\"color:crimson;\"><?=$menu['error']?></b></span>
<?php }?>
<div data-role="controlgroup" data-type="horizontal">
<?php if($menu['parent_dir'] == 0){?>
<span data-role="button" data-inline="true" data-mini="true" data-icon="arrow-u"><b>! Parent Dir</b></span>
<?php }else{?>
<a data-role="button" data-inline="true" data-mini="true" data-icon="arrow-u" href="%SELF%">Parent Dir</a>
<?php if(array_key_exists('upper_dir',$menu)){?>
<a data-role="button" data-inline="true" data-mini="true" data-icon="arrow-u" href="%SELF%?dir=<?=$menu['upper_dir']?>">Upper Dir</a>
<?php }?>
<?php }?>
<a data-role="button" data-inline="true" data-mini="true" data-icon="home" href="<?=$menu['home']?>">Home</a>
<!-- menu -->
</div>