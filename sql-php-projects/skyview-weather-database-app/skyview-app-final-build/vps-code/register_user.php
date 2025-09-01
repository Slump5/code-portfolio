<?php
// Author: Thomas Hoerger
// Thomas Hoerger - Copyright © 2025 SkyView Weather App Final Build
// Solo Group 9
// 4-23-2025
// Description: Handles user registration. Checks for duplicate username 
// and inserts plain-text password (for demo use only).

header('Content-Type: application/json'); // Set response type to JSON

// Connect to the MySQL database
$conn = new mysqli('localhost', 'root', 'password', 'weather_app');

// Decode JSON data from the request body
$data = json_decode(file_get_contents("php://input"), true);

// Extract user-submitted fields
$username = $data['username'];
$password = $data['password'];
$email = $data['email'];
$created_at = date('Y-m-d H:i:s'); // Get current timestamp

// Check if the username already exists in the database
$check = $conn->prepare("SELECT user_id FROM Users WHERE username = ?");
$check->bind_param("s", $username);
$check->execute();
$check->store_result();

// If the username is already taken, return an error response
if ($check->num_rows > 0) {
    echo json_encode([
        "status" => "error",
        "message" => "Username already exists"
    ]);
    $check->close();
    $conn->close();
    exit; // Terminate script
}

$check->close(); // Close the prepared statement for the username check

// Insert new user into the Users table
// Note: Password is stored in plain-text here for demonstration purposes only
$stmt = $conn->prepare("INSERT INTO Users (username, password, email, created_at) VALUES (?, ?, ?, ?)");
$stmt->bind_param("ssss", $username, $password, $email, $created_at);

// If insertion is successful, return success response
if ($stmt->execute()) {
    echo json_encode([
        "status" => "success",
        "message" => "User registered successfully"
    ]);
} else {
    // Return an error if the insertion fails
    echo json_encode([
        "status" => "error",
        "message" => "Database insert failed"
    ]);
}

// Close the statement and database connection
$stmt->close();
$conn->close();
?>
