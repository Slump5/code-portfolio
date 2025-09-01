<?php
// Author: Thomas Hoerger
// Thomas Hoerger - Copyright © 2025 SkyView Weather App Final Build
// Solo Group 9
// 4-24-2025
// Description: Returns all rows from any valid table as JSON.

header('Content-Type: application/json'); // Set response type to JSON

// Establish a connection to the MySQL database
$conn = new mysqli('localhost', 'root', 'Sweets@01', 'weather_app');

// Check for connection errors and return an error response if one occurs
if ($conn->connect_error) {
    echo json_encode(["error" => "DB connection failed"]);
    exit;
}

// Sanitize the 'table' query parameter to prevent SQL injection
// Only allow alphanumeric characters and underscores
$table = preg_replace('/[^a-zA-Z0-9_]/', '', $_GET['table'] ?? '');

// If the table name is invalid or empty, return an error
if (!$table) {
    echo json_encode(["error" => "Invalid table"]);
    exit;
}

// Construct and run a SQL query to retrieve all rows from the specified table
$result = $conn->query("SELECT * FROM `$table`");

// If the query fails, return an error message with details
if (!$result) {
    echo json_encode(["error" => "Query failed", "details" => $conn->error]);
    exit;
}

// Initialize an array to store each row of the result
$rows = [];
while ($row = $result->fetch_assoc()) {
    $rows[] = $row;
}

// Return the table name and all rows as a JSON response
echo json_encode(["table" => $table, "rows" => $rows]);

// Close the database connection
$conn->close();
?>
