<?php
// Thomas Hoerger - Copyright © 2025 Skyview Weather Database Viewer Site-App Final Build
require_once 'vendor/autoload.php';
session_start();

$client = new Google_Client();
$client->setClientId(''); 
$client->setClientSecret('');  
$client->setRedirectUri('http://skyview.work.gd/google-callback.php');
$client->addScope("email");
$client->addScope("profile");

$auth_url = $client->createAuthUrl();
header('Location: ' . filter_var($auth_url, FILTER_SANITIZE_URL));
?>
