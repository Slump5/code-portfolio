<?php
// Thomas Hoerger - Copyright © 2025 Weather Database Viewer Site Stage 2
$servername = "localhost";  // Change to VPS IP if accessing remotely
$username = "root";         // Use your MySQL username
$password = "password"; // Use your MySQL root password
$dbname = "weather_app";    // Your database name

// Create connection
$conn = new mysqli($servername, $username, $password, $dbname);

// Check connection
if ($conn->connect_error) {
    die("Connection failed: " . $conn->connect_error);
}
?>
