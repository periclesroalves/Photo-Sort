$('.album').click(function(){
	var album_id = $(this).attr('id');
	$('#sorted').load('download.php?album_id='+album_id);		
});
$('.album').hover(function() {
        $(this).css('cursor','pointer');
    });