<?php if(array_key_exists('dir_name',$menu)){?>
<span data-role="button" data-inline="true" data-mini="true"><b><?=$menu['dir_name']?></b></span>
<?php }?>
<?php if(array_key_exists('error',$menu)){?>
<span data-role="button" data-inline="true" data-mini="true" data-icon="info"><b style=\"color:crimson;\"><?=$menu['error']?></b></span>
<?php }?>