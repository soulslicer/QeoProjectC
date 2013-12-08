<?php

header('Access-Control-Allow-Origin: *');

include 'DB.php';


//Get Variables
$room=null;
$count=null;
if(isset($_GET[ROOM])) 
   	$room=$_GET[ROOM];
if(isset($_GET[COUNT])) 
   	$count=$_GET[COUNT];
if(is_null($room) || is_null($count))
	exit;

//SQL Connection
$CONNECTION=getSQLConnection();
if(!$CONNECTION){
	endSQLConnection($CONNECTION);
	echo "(DBERROR) Database error";
}

//Get current room count
$sql=
"
SELECT count FROM roomcount
WHERE room=\"".$room."\"
";
$result = mysqli_query($CONNECTION,$sql)  or die ("(DBERROR)");
while($row = mysqli_fetch_array($result)){
	$currCount=$row["count"];
}

//Get type
if(($count-$currCount)>0)
	$type="increment";
else if(($count-$currCount)<0)
	$type="decrement";
else
	$type="same";

//Set the current count
$sql=
"
UPDATE roomcount
SET count=".$count." 
WHERE room=\"".$room."\"
";
$result = mysqli_query($CONNECTION,$sql)  or die ("(DBERROR)");

//Insert date
$sql=
"
INSERT INTO roomhistory (room, timing, type)
VALUES ("."\"".$room."\"".","."NOW()".","."\"".$type."\"".")
";
$result = mysqli_query($CONNECTION,$sql)  or die (mysqli_error($CONNECTION));

//Insert into timestamp table

// $sql="SELECT * FROM userbio where user_id=".$userid;
// $result = mysqli_query($CONNECTION,$sql)  or die ("(DBERROR)");
// while($row = mysqli_fetch_array($result)){
// 	$userData=new userData();
// 	$userData->userid=$row["user_id"];
// 	$userData->name=$row["name"];
// 	$userData->title=$row["title"];
// 	$userData->location=$row["location"];
// 	$userData->objective=$row["objective"];
// 	$userData->email=$row["email"];
// 	$userData->linkedin=$row["linkedin"];
// 	$userData->cood=$row["cood"];
// 	$userData->phone=$row["phone"];
// }

// endSQLConnection($CONNECTION);

// //echo json_encode($userData);

// class rawcard
// {
// 	public $userid;
// 	public $header;
// 	public $bullet;
// 	public $date;
// 	public $image;
// }

// class header
// {
// 	public $userid;
// 	public $header;
// 	public $bullets=array();
// }

// class bullet
// {
// 	public $bullet;
// 	public $date;
// 	public $image;
// 	public $link;
// }

// $FINALARRAY=array();
// $RETURNARRAY=array();

// $CONNECTION=getSQLConnection();
// if(!$CONNECTION){
// 	endSQLConnection($CONNECTION);
// 	echo "(DBERROR) Database error";
// }

// $sql="SELECT * FROM cards where user_id=".$userid;
// $result = mysqli_query($CONNECTION,$sql)  or die ("(DBERROR)");
// while($row = mysqli_fetch_array($result)){
// 	$rawcard=new rawcard();
// 	$rawcard->userid=$row["user_id"];
// 	$rawcard->header=$row["header"];
// 	$rawcard->bullet=$row["bullet"];
// 	$rawcard->date=$row["date"];
// 	$rawcard->image=$row["image"];
// 	$rawcard->link=$row["link"];
// 	array_push($RETURNARRAY, $rawcard);
// }

// // //find for everything with that header

// foreach ($RETURNARRAY as $card) {
// 	$header=$card->header;
// 	if(arrayContainsHeader($FINALARRAY,$header)){

// 		$bullet=new bullet();
// 		$bullet->bullet=$card->bullet;
// 		$bullet->date=$card->date;
// 		$bullet->image=$card->image;
// 		$bullet->link=$card->link;

// 		addBullet($FINALARRAY,$header,$bullet);
// 	}else{
// 		$header=new header();
// 		$header->userid=$card->userid;
// 		$header->header=$card->header;

// 		$bullet=new bullet();
// 		$bullet->bullet=$card->bullet;
// 		$bullet->date=$card->date;
// 		$bullet->image=$card->image;
// 		$bullet->link=$card->link;

// 		$header->bullets[]=$bullet;
// 		array_push($FINALARRAY, $header);
// 	}

// }

// function arrayContainsHeader($array,$headercompare){
// 	foreach ($array as $header){
// 		if($header->header==$headercompare) return true;
// 	}
// 	return false;
// }

// function addBullet(&$array,$headercompare,$bullet){
// 	foreach ($array as &$header){
// 		if($header->header==$headercompare){
// 			$header->bullets[]=$bullet;
// 		}
// 	}
// }

// $OUTPUTARRAY=array(
//     "cards" => $FINALARRAY,
//     "userbio" => $userData,
// );


// echo json_encode($OUTPUTARRAY);

?>