<?php require_once 'config.php';
echo 'hello';
$album_id = $_GET['album_id'];

$album = $facebook->api($album_id.'/photos');
$data = $album['data'];
$photos = array();
foreach($data as $photo){
	$id = $photo['id'];
	$source = $photo['source'];
	$path = 'photos/'.$id.'.jpg';
	file_put_contents($path, file_get_contents($source));
	//echo $id . ' downloaded</br>';
    array_push($photos,$path);
	//echo '<img src = '.$source.'></img>';	
}
$paths = implode($photos,' ');

//echo $paths;
$pathToSort = './src/img-core/sort';
echo exec('unset DYLD_LIBRARY_PATH ; '. $pathToSort.' '.$paths);

$facebook->setFileUploadSupport(true);
$album_details = array('message'=>'Album Description','name' => 'Sorted Album');
$create_album = $facebook->api('/me/albums', 'post', $album_details);
  
//Get album ID of the album you've just created
$album_uid = $create_album['id'];
  

$file = fopen("order.txt", "r") or exit("Unable to open file!");
//Output a line of the file until the end is reached
while(!feof($file))
  {//Upload a photo to album of ID...
	$photo_details = array(
    	'message'=> 'Photo message'
	);
	$photo_file=fgets($file); //Example image file
	echo $photo_file;
	$photo_details['image'] = '@' . realpath($photo_file);
	$upload_photo = $facebook->api('/'.$album_uid.'/photos', 'post', $photo_details);
  }
  
fclose($file);

?>