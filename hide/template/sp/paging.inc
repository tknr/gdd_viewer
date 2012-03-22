<div data-role="controlgroup" data-type="horizontal">
<!-- paging -->
<?php if($paging['page'] > $paging['from']){?>
<a data-role="button" data-inline="true" data-mini="true" href="%SELF%?page=1&dir=<?=$paging['dir']?>">&lt;&lt;</a><a data-role="button" data-inline="true" data-mini="true" href="%SELF%?page=<?=$paging['prev']?>&dir=<?=$paging['dir']?>">&lt;</a>
<?php }else{?>
<span data-role="button" data-inline="true" data-mini="true">&lt;&lt;</span><span data-role="button" data-inline="true" data-mini="true">&lt;</span>
<?php }?>
<?php for($count = $paging['from'] ; $count <= $paging['to'] ; $count++){
	if($count == $paging['page']){?><span data-role="button" data-inline="true" data-mini="true"><?=$count?>/<?=$paging['maxpage']?></span><?php ;
	}else{
		?><a data-role="button" data-inline="true" data-mini="true" href="%SELF%?page=<?=$count?>&dir=<?=$paging['dir']?>"><?=$count?></a><?php 
	}
 }?>
<?php if($paging['page'] < $paging['to']){?>
<a data-role="button" data-inline="true" data-mini="true" href="%SELF%?page=<?=$paging['next']?>&dir=<?=$paging['dir']?>"></a><a data-role="button" data-inline="true" data-mini="true" href="%SELF%?page=<?=$paging['maxpage']?>&dir=<?=$paging['dir']?>"></a>
<?php }else{?>
<span data-role="button" data-inline="true" data-mini="true">&gt;</span><span data-role="button" data-inline="true" data-mini="true">&gt;&gt;</span>
<?php }?>
<!-- paging -->
</div>