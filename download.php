<?php require_once 'config.php';
echo 'hello';
$album_id = $_GET['album_id'];


$album = $facebook->api($album_id.'/photos');
$data = $album['data'];
$photos = array();
foreach($data as $photo){
	$id = $photo['id'];
	$source = $photo['source'];
	echo $source . '</br>';
	$path = 'photos/'.$id.'.jpg';
	file_put_contents($path, file_get_contents($source));
	//echo $id . ' downloaded</br>';
    array_push($photos,$path);
	//echo '<img src = '.$source.'></img>';	
}
$paths = implode($photos,' ');
echo $paths;


?>