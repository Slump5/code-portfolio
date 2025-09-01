<?php
// Thomas Hoerger - Copyright © 2025 Skyview Weather Database Viewer Site-App Final Build
session_start();
include 'db_connect.php'; // Reuse your existing DB connection

// Get email and password from the form submission
$email = $_POST['email'];
$password = $_POST['password'];

// In production, hash and verify passwords securely
$sql = "SELECT * FROM Users WHERE email = '$email' AND password = '$password'";
$result = $conn->query($sql);

// Check if login is valid
if ($result->num_rows > 0) {
    $row = $result->fetch_assoc();
    $_SESSION['user_email'] = $row['email'];
    $_SESSION['user_name'] = $row['username'];
    header("Location: weather_ui.php");
} else {
    echo "Invalid login. <a href='login.php'>Try again</a>";
}
?>
