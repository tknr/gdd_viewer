$("[id^=zip_link_]").each(function() {
	$(this).on('click',function(){
		var target_url = $(this).attr("href");
		console.log(target_url);
		if ($(location).attr('search').indexOf('book') == -1){
			window.open(target_url, '_blank');
			return true;
		}
		$.confirm({
		    title: 'confirm',
		    content: 'download or read?',
		    buttons: {
		        download:{
		        	text: 'download',
		        	btnClass: 'btn-blue',
		        	action: function () {
		            	window.open(target_url, '_blank');
		        	}
		        },
		        read:{
		        	text: 'bookreader',
		        	btnClass: 'btn-blue',
		        	action: function () {
		            	window.open('bookreader/?f='+target_url, '_blank');
		        	}
		        },
		        cancel: {
		        	action:function () {
		        	}
		        },
			}
		});
		return false;
	});
});


$("[id^=text_link_]").each(function() {
	$(this).on('click',function(){
		var target_url = $(this).attr("href");
		console.log(target_url);
		$.confirm({
		    title: 'confirm',
		    content: 'download or edit?',
		    buttons: {
		        download:{
		        	text: 'download',
		        	btnClass: 'btn-blue',
		        	action: function () {
		            	window.open(target_url, '_blank');
		        	}
		        },
		        edit:{
		        	text: 'edit',
		        	btnClass: 'btn-blue',
		        	action: function () {
		            	window.open('?mode=edit&f='+target_url, '_blank');
		        	}
		        },
		        cancel: {
		        	action:function () {
		        	}
		        },
			}
		});
		return false;
	});
});
