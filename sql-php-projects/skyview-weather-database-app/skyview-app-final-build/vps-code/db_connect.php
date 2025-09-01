<?php
// Author: Thomas Hoerger
// Thomas Hoerger - Copyright © 2025 SkyView Weather App Final Build
// Solo Group 9
// 4-17-2025
// Description: Establishes a connection to the MySQL database for the weather_app system.
// If the connection fails, the script stops and displays an error message.

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
