$('#likes').click(function(){
	var catid;
	catid=$(this).attr('data-catid');
	$.get(
		'/rango/like_category/',
		{
			category_id:catid
		},
		function(data){
			$('#like_count').html(data);
			$('#likes').hide();
	});
});
$('#suggestion').keyup(function(){
	var query;
	query=$(this).val();
	$.get('/rango/suggest_category/',
	{
		suggestion:query,
	},
	function(data){
		$('#cats').html(data);
	});
});

$('button[name=add_page_from_link]').click(function(){

	var title=$(this).attr('data-pagetitle');
	var url=$(this).attr('data-pageurl');
	var category=$(this).attr('data-catid');
	$.get('/rango/auto_add_page/',
	{
		title:title,
		url:url,
		category:category,
	},
	function(data){
		if(data=='SUCCESS')
		{
			location.reload();
		}
		else
		{

		}

	});
});