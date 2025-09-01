<?php
// Author: Thomas Hoerger
// Thomas Hoerger - Copyright © 2025 SkyView Weather App Final Build
// Solo Group 9
// 4-17-2025
// Description: Handles POST requests to record whether a user liked or disliked the app,
// storing the result in the Feedback table.

header("Content-Type: application/json"); // Set the response type to JSON

// Establish a connection to the MySQL database
$conn = new mysqli("localhost", "root", "Sweets@01", "weather_app");

// Handle database connection errors
if ($conn->connect_error) {
  echo json_encode(["error" => "DB error"]);
  exit();
}

// Decode JSON data from the POST request body
$data = json_decode(file_get_contents('php://input'), true);

// Sanitize and extract the username; default to 'anonymous' if not provided
$username = $conn->real_escape_string($data['username'] ?? 'anonymous');

// Get the liked value and ensure it is an integer (1 for like, 0 for dislike)
$liked = intval($data['liked'] ?? 0);

// Insert the feedback entry into the database
$conn->query("INSERT INTO Feedback (username, liked) VALUES ('$username', $liked)");

// Return a success response
echo json_encode(["status" => "ok"]);
?>
