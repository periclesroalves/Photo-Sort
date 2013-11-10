<!doctype html>

<html lang="en">
<head>
  <meta charset="utf-8">

  <title>Photo Sort!</title>
  <meta name="description" content="Photo Sort App">
  <meta name="author" content="SitePoint">

  <!--[if lt IE 9]>
  <script src="http://html5shiv.googlecode.com/svn/trunk/html5.js"></script>
  <![endif]-->
</head>
<?php require_once 'facebook-src/facebook.php';

	$facebook = new Facebook(array(
 	 'appId'  => '643775449019374',
 	 'secret' => '082246d3941b60800f031b1731399311',
  	));	
?>

<body>
<script>

  // Additional JS functions here
  window.fbAsyncInit = function() {
    FB.init({
      appId      : '643775449019374', // App ID
      channelUrl : 'http://localhost:8888/photo_sort/Photo-Sort/', // Channel File
      status     : true, // check login status
      cookie     : true, // enable cookies to allow the server to access the session
      xfbml      : true  // parse XFBML
    });

    // Additional init code here
  };

  // Load the SDK asynchronously
  (function(d){
     var js, id = 'facebook-jssdk', ref = d.getElementsByTagName('script')[0];
     if (d.getElementById(id)) {return;}
     js = d.createElement('script'); js.id = id; js.async = true;
     js.src = "//connect.facebook.net/en_US/all.js";
     ref.parentNode.insertBefore(js, ref);
   }(document));
   
    function testAPI() {
    console.log('Welcome!  Fetching your information.... ');
    FB.api('/me', function(response) {
      console.log('Good to see you, ' + response.name + '.');
    });
  }
</script>

<h1>Photo Sort!</h1>
