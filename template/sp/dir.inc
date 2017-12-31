<div class="ws-normal">
<?php if(array_key_exists('dir_name',$menu)){?>
<a data-role="button" data-mini="true"><b><?=$menu['dir_name']?></b></a>
<?php }?>
<?php if(array_key_exists('error',$menu)){?>
<a data-role="button" data-mini="true" data-icon="info"><b style=\"color:crimson;\"><?=$menu['error']?></b></a>
<?php }?>
</div>