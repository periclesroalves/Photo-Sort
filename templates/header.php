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

<body>
<script type = "text/javascript">
// Additional JS functions here

	window.fbAsyncInit = function() {
		FB.init({
      		appId      : '643775449019374', // App ID
      		status     : true,    // check login status
      		cookie     : true,    // enable cookies to allow the
                            // server to access the session
      		xfbml      : true     // parse page for xfbml or html5
                            // social plugins like login button below
    	});

	// Put additional init code here
	};
	//Load SDK 
	(function(d, s, id){
     	var js, fjs = d.getElementsByTagName(s)[0];
     	if (d.getElementById(id)) {return;}
     	js = d.createElement(s); js.id = id;
     	js.src = "//connect.facebook.net/en_US/all.js";
     	fjs.parentNode.insertBefore(js, fjs);
   	}(document, 'script', 'facebook-jssdk'));
</script>

<h1>Photo Sort!</h1>
