

<?php include_once "templates/header.php" ;?>

<div class="wrapper row3">
  <div id="container" class="clear">
    <div id="homepage">
    
</br>
<?php
$user = $facebook->getUser();
if ($user) {
  try {
    
    $user_profile = $facebook->api('/me');
	
    $user_albums = $facebook->api('/me/albums');
    
  } catch (FacebookApiException $e) {
    error_log($e);
    $user = null;
  }
}

if ($user) {
  $logoutUrl = $facebook->getLogoutUrl();
} else {
  $loginUrl = $facebook->getLoginUrl(array("scope" => "read_stream, publish_stream, photo_upload, user_photos, user_photo_video_tags","redirect_uri" => "http://localhost:8888/photo_sort/Photo-Sort/"));
}

?>
    <table style="border:0px !important"><tr>
    <td style="text-decoration : none; color:#ffffff; font-size:550%; vertical-align: middle; border: medium none;">
        <b>photo sort</b>
	</td>
    <td style="vertical-align: middle; border: medium none;">
    <center>
    <div id = "login">
	<?php if ($user): ?>
      <img style="border-radius:4px; border: 2px solid #FFFFFF;" src="https://graph.facebook.com/<?php echo $user; ?>/picture"></br>
    <div style="height:7%; width:38%;border-radius:4px; border: 2px solid #FFFFFF;">
    <center>
      <a style="text-decoration : none; color:#ffffff;" href="<?php echo $logoutUrl; ?>"><b>logout</b></a>
    </center>
    </div>
    <?php else: ?>
      <div style="height:7%; width:60%;border-radius:4px; border: 2px solid #FFFFFF;">
        <a style="text-decoration : none; color:#ffffff;" href="<?php echo $loginUrl; ?>">Login with Facebook</a>
      </div>
    <?php endif ?>
	</div></center></td>
    </tr></table>

    <?php if ($user): ?>

          
     <?php 
     	if(!empty($user_albums['data'])){
     		$html = "<section id='portfolio' class='clear'><ul>";
     		foreach($user_albums['data'] as $album){
     			$cover_photo = $facebook->api($album['cover_photo']);
     			$album_id = $album['id'];
     			$album_name = $album['name'];
     			$html .= "<li id = ".$album_id." class = 'album'><article><a><figure><img style='border-radius:4px; border: 2px solid #FFFFFF;' title = '".$album_name."'  src = " . $cover_photo["picture"] . "></img></figure><center><div style='height:7%; width:85%;border-radius:4px; border: 2px solid #FFFFFF; color:#ffffff;'><b>".$album_name."</b></div></center></a></article></li>";
     			
     		}
     		$html = $html. "</ul></section>";
     		echo $html;
     	}
     
     ?>

    <?php endif ?>
    <div id = "sorted"></div>
    
     

  <!-- / Latest Work -->
    </div>
    <!-- / content body -->
  </div>
</div>
<div id="dialog-confirm" title="Choose sorting type"></div>
<div class="modal"><!-- Place at bottom of page --></div>


<?php include_once "templates/footer.php";?>

