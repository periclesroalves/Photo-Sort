<?php require_once 'config.php';
echo 'hello';
$album_id = $_GET['album_id'];
$type = '';
if($_GET['type'] == 1){
	$type = 'c';
}
else{
	$type = 'o';
}
$album = $facebook->api($album_id.'/photos', 'get' , array('limit' => 400));
$data = $album['data'];
$photos = array();
foreach($data as $photo){
	$id = $photo['id'];
	$source = $photo['source'];
	$path = 'photos/'.$id.'.jpg';
	file_put_contents($path, file_get_contents($source));
	chmod($path,0777);
	//echo $id . ' downloaded</br>';
    array_push($photos,$path);
	//echo '<img src = '.$source.'></img>';	
}

$paths = implode($photos,' ');

//echo $paths;
$pathToSort = './src/img-core/sort '.$type;

echo exec('unset DYLD_LIBRARY_PATH ; '. $pathToSort.' '.$paths);

// Create a new Album, and upload the sorted photos into that

$facebook->setFileUploadSupport(true);
$album_details = array('message'=>'Album Description','name' => 'Sorted Album');
$create_album = $facebook->api('/me/albums', 'post', $album_details);
  
//Get album ID of the album you've just created
$album_uid = $create_album['id'];
  

$file = fopen("order.txt", "r") or exit("Unable to open file!");
//Output a line of the file until the end is reached
try{
while(!feof($file))
  {//Upload a photo to album of ID...
	$photo_file=fgets($file); 
	$photo_details = array(
    	'message'=> 'Photo message', 
   		'source' => trim('@/Applications/MAMP/htdocs/photo_sort/Photo-Sort/'.$photo_file)  
	);
	$upload_photo = $facebook->api('/'.$album_uid.'/photos', 'post', $photo_details);
	unlink(trim($photo_file));
  }
  }
  catch(Exception  $e){
  	var_dump($e);
  }
  
fclose($file);
unlink('order.txt');
?>
<script type = 'text/javascript'>
alert('Album was sorted and is now available on Facebook');
</script>