<div data-role="controlgroup" data-type="horizontal">
<!-- paging -->
<?php if($paging['page'] > $paging['from']){?>
<a data-role="button" data-inline="true" data-mini="true" href="%SELF%?page=1&amp;dir=<?=$paging['dir']?>">&lt;&lt;</a>
<a data-role="button" data-inline="true" data-mini="true" href="%SELF%?page=<?=$paging['prev']?>&amp;dir=<?=$paging['dir']?>">&lt;</a>
<?php }?>
<?php for($count = $paging['from'] ; $count <= $paging['to'] ; $count++){
	if($count == $paging['page']){?><a data-role="button" data-inline="true" data-mini="true"><?=$count?>/<?=$paging['maxpage']?></a><?php ;
	}else{
		?><a data-role="button" data-inline="true" data-mini="true" href="%SELF%?page=<?=$count?>&amp;dir=<?=$paging['dir']?>"><?=$count?></a><?php 
	}
 }?>
<?php if($paging['page'] < $paging['to']){?>
<a data-role="button" data-inline="true" data-mini="true" href="%SELF%?page=<?=$paging['next']?>&amp;dir=<?=$paging['dir']?>">&gt;</a>
<a data-role="button" data-inline="true" data-mini="true" href="%SELF%?page=<?=$paging['maxpage']?>&amp;dir=<?=$paging['dir']?>">&gt;&gt;</a>
 <?php }?>
<!-- paging -->
</div>