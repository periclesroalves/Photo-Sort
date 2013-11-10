$(document).ready(function() {
	$('.album').click(function(){
		var album_id = $(this).attr('id');
	
    $( "#dialog-confirm" ).dialog({
        resizable: false,
      	height:100,
      	modal: true,
      	buttons: {
        	"Color": function() {
         		$( this ).dialog( "close" );
         		$('#sorted').load('download.php?album_id='+album_id+'&type=1');
        	},
			"Object": function() {
         		$( this ).dialog( "close" );
         		$('#sorted').load('download.php?album_id='+album_id+'&type=2');
       	 	},
        Cancel: function() {
          	$( this ).dialog( "close" );
        }
      }
    });
	});		

	$('.album').hover(function() {
     	   $(this).css('cursor','pointer');
	});

});