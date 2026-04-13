<?php
// Author: Thomas Hoerger
// Thomas Hoerger - Copyright © 2025 SkyView Weather App Final Build
// Solo Group 9
// 4-23-2025
// Description: Logs a user in by checking the username and plain-text password
// from the Users table. This version skips hashing for demo/testing purposes.

header('Content-Type: application/json'); // Set response content type to JSON

// Connect to the MySQL database
$conn = new mysqli('localhost', 'root', 'password', 'weather_app');

// Decode the JSON payload from the request body
$data = json_decode(file_get_contents("php://input"), true);
$username = $data['username'];
$password = $data['password'];

// Prepare a SQL statement to select the password for the given username
$stmt = $conn->prepare("SELECT password FROM Users WHERE username = ?");
$stmt->bind_param("s", $username);
$stmt->execute();
$res = $stmt->get_result();

// Check if a matching user was found
if ($row = $res->fetch_assoc()) {
    // Compare the provided plain-text password with the stored password
    if ($password === $row['password']) {
        // Login successful
        echo json_encode(["status" => "success", "username" => $username]);
    } else {
        // Password did not match
        echo json_encode(["status" => "error", "message" => "Incorrect password"]);
    }
} else {
    // No user found with the provided username
    echo json_encode(["status" => "error", "message" => "User not found"]);
}

// Close the database connection
$conn->close();
?>
