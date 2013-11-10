

<?php include_once "templates/header.php" ;?>

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
  $loginUrl = $facebook->getLoginUrl(array("scope" => "user_photos","redirect_uri" => "http://localhost:8888/photo_sort/Photo-Sort/"));
}

?>
    <?php if ($user): ?>
      <a href="<?php echo $logoutUrl; ?>">Logout</a>
    <?php else: ?>
      <div>
        <a href="<?php echo $loginUrl; ?>">Login with Facebook</a>
      </div>
    <?php endif ?>

   

    <?php if ($user): ?>
      <h3>You</h3>
      <img src="https://graph.facebook.com/<?php echo $user; ?>/picture">

      <h3>Your User Object (/me)</h3>
     <?php 
     	if(!empty($user_albums['data'])){
     		foreach($user_albums['data'] as $album){
     			$cover_photo = $facebook->api($album['cover_photo']);
     			$album_id = $album['id'];
     			echo $album_id;
     			$html = "<strong>Album: </strong>" . $album['name']. '</br>'."<img class = 'album' id = " . $album_id." src = " . $cover_photo["picture"] . "></img></br>";
     			
     			echo $html;
     		}
     	}
     
     ?>

    <?php else: ?>
      <strong><em>You are not Connected.</em></strong>
    <?php endif ?>
    <div id = "sorted"></div>
    
     





<?php include_once "templates/footer.php";?>

