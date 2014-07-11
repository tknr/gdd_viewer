<!-- menu -->
<div data-role="controlgroup" data-type="horizontal">
<?php if($menu['parent_dir'] == 0){?>
<span data-role="button" data-inline="true" data-mini="true"><b>! Parent Dir</b></span>
<?php }else{?>
<a data-role="button" data-inline="true" data-mini="true" data-icon="arrow-u" href="%SELF%">Parent Dir</a>
<?php if(array_key_exists('upper_dir',$menu)){?>
<a data-role="button" data-inline="true" data-mini="true" data-icon="arrow-u" href="%SELF%?dir=<?=$menu['upper_dir']?>">Upper Dir</a>
<?php }?>
<?php }?>
<a data-role="button" data-inline="true" data-mini="true" data-icon="home" href="<?=$menu['home']?>">Home</a>
<a data-role="button" data-inline="true" data-mini="true" target="_blank" href="%SELF%?page=<?=$page?>&amp;dir=<?php echo rawurlencode($dir);?>&amp;mode=photoswipe">photoswipe</a>
<!-- menu -->
</div>