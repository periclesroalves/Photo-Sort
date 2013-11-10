

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
  $loginUrl = $facebook->getLoginUrl(array("scope" => "user_photos,photo_upload,publish_stream","redirect_uri" => "http://localhost:8888/photo_sort/Photo-Sort/"));
}

?>
	<div id = "login">
	
	<?php if ($user): ?>
	  <h3>You</h3>
      <img src="https://graph.facebook.com/<?php echo $user; ?>/picture"></br>
      <a href="<?php echo $logoutUrl; ?>">Logout</a>
    <?php else: ?>
      <div>
        <a href="<?php echo $loginUrl; ?>">Login with Facebook</a>
      </div>
    <?php endif ?>
    
	</div>

    <?php if ($user): ?>

          
     <?php 
     	if(!empty($user_albums['data'])){
     		$html = "<section id='portfolio' class='clear'><ul>";
     		foreach($user_albums['data'] as $album){
     			$cover_photo = $facebook->api($album['cover_photo']);
     			$album_id = $album['id'];
     			$album_name = $album['name'];
     			$html .= "<li><article><a><figure><img title = '".$album_name."' class = 'album' id = " . $album_id." src = " . $cover_photo["picture"] . "></img></figure></a></article></li>";
     			
     		}
     		$html = $html. "</ul></section>";
     		echo $html;
     	}
     
     ?>

    <?php else: ?>
      <strong><em>You are not Connected.</em></strong>
    <?php endif ?>
    <div id = "sorted"></div>
    
     

  <!-- / Latest Work -->
    </div>
    <!-- / content body -->
  </div>
</div>



<?php include_once "templates/footer.php";?>

