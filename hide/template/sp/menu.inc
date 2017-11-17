<!-- menu -->
<div data-role="controlgroup" data-type="horizontal">
<?php if($menu['parent_dir'] == 0){?>
<!-- 
<a data-role="button" data-inline="true" data-mini="true" data-icon="home" href="%SELF%">home</a>
-->
<?php }else{?>
<a data-role="button" data-inline="true" data-mini="true" data-icon="home" href="%SELF%">home</a>
<?php if(array_key_exists('upper_dir',$menu)){?>
<a data-role="button" data-inline="true" data-mini="true" data-icon="arrow-u" href="%SELF%?dir=<?=$menu['upper_dir']?>">upper</a>
<?php }?>
<?php }?>
<a target="_blank" data-role="button" data-inline="true" data-mini="true" data-icon="search" href="%SELF%?mode=photoswipe&dir=<?=$dir?>">photoswipe</a>
<!-- 
<a data-role="button" data-inline="true" data-mini="true" data-icon="home" href="<?=$menu['home']?>">Home</a>
-->
<!-- menu -->
</div>