

<?php include_once "templates/header.php" ;?>
<fb:login-button show-faces="true" width="200" max-rows="1"></fb:login-button>

</br>
<?php
$user = $facebook->getUser();
if ($user) {
  try {
    
    $user_profile = $facebook->api('/me');
	
    $user_album = $facebook->api('/me/albums');
    var_dump($user_album);
    
  } catch (FacebookApiException $e) {
    error_log($e);
    $user = null;
  }
}
else{

 $params = array('scope' => 'publish_stream, user_photos,friends_photos ','redirect_url' => 'http://localhost:8888/photo_sort/Photo-Sort/');   //Requesting User Permissions through Facebook App
                                    
 $login_url = $facebook->getLoginUrl( $params );//Login URL
 echo '<a href="' . $login_url . '"><div class="fb-login-button" data-width="200"></div></a>';
} 


?>





<?php include_once "templates/footer.php";?>

