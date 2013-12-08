<?php

header('Access-Control-Allow-Origin: *');

include 'DB.php';

echo "test";

// class userData
// {
// 	public $userid;
// 	public $name;
// 	public $title;
// 	public $location;
// 	public $objective;
// 	public $email;
// 	public $linkedin;
// 	public $cood;
// 	public $phone;
// }

// if(isset($_GET[GETVAR_USERID])) 
//    	$userid=$_GET[GETVAR_USERID];
// else exit;

// // echo "aa";

// $CONNECTION=getSQLConnection();
// if(!$CONNECTION){
// 	endSQLConnection($CONNECTION);
// 	echo "(DBERROR) Database error";
// }

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