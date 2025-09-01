<?php
// Thomas Hoerger - Copyright © 2025 Skyview Weather Database Viewer Site-App Final Build
require_once 'vendor/autoload.php';
session_start();

$client = new Google_Client();
$client->setClientId('');
$client->setClientSecret('');
$client->setRedirectUri('http://skyview.work.gd/google-callback.php');  // MUST match Google OAuth settings
$client->addScope("email");
$client->addScope("profile");

if (isset($_GET['code'])) {
    $token = $client->fetchAccessTokenWithAuthCode($_GET['code']);
    $client->setAccessToken($token);

    // Get user info from Google
    $oauth = new Google_Service_Oauth2($client);
    $user = $oauth->userinfo->get();

    // Store user info in session
    $_SESSION['user_email'] = $user->email;
    $_SESSION['user_name'] = $user->name;

    // Redirect to your weather app UI
    header('Location: weather_ui.php');
    exit();
} else {
    echo "Error: No authorization code received.";
}
?>
