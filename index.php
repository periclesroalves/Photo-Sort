<fb:login-button show-faces="true" width="200" max-rows="1"></fb:login-button>


<?php include_once "templates/header.php" ;
  	echo "test";

	$facebook = new Facebook(array(
 	 'appId'  => '643775449019374',
 	 'secret' => '76b91ccb3a4880dbdceaded8f7454095',
 	 'cookie' => true,
  	));	
  	 echo "test";

  	$access_token = $facebook->getAccessToken();
  	echo "test";
	echo $access_token;
  	$albums = $facebook->api('/me/albums');
   	var_dump($albums);
?>
<p>test</p>


<?php include_once "templates/footer.php" ?>

