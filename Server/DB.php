<?php


// //getSearch
define("ROOM", "room");
define("COUNT", "count");
define("TIME", "time");

// define("GETVAR_EVENTID", "eventid");


function getSQLConnection(){
	$host="localhost";
	$user="root";
	$password="root";
	$database="qeo";
	$link = mysqli_connect($host,$user,$password,$database);
	return $link;
}

function endSQLConnection($CONNECTION){
	mysqli_close($CONNECTION);
}

function beginTransaction($CONNECTION){
	if(mysqli_connect_errno($CONNECTION)){
		return FALSE;
	}else{
		mysqli_autocommit($CONNECTION, FALSE);
		return TRUE;
	}
}

function endTransaction($success,$CONNECTION){
	if($success){
		mysqli_commit($CONNECTION);
	}else{
		mysqli_rollback($CONNECTION);
	}
}

?>