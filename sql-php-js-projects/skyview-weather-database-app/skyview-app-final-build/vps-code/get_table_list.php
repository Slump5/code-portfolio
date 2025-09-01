<?php
// Author: Thomas Hoerger
// Thomas Hoerger - Copyright © 2025 SkyView Weather App Final Build
// Solo Group 9
// 4-24-2025
// Description: Returns a list of all table names in the weather_app database.

header('Content-Type: application/json'); // Set the response type to JSON

// Establish a connection to the MySQL database
$conn = new mysqli('localhost', 'root', 'Sweets@01', 'weather_app');

// Check for connection errors and return an error if the connection fails
if ($conn->connect_error) {
    echo json_encode(["error" => "DB connection failed"]);
    exit;
}

// Initialize an array to store the table names
$tables = [];

// Execute SQL command to list all tables in the database
$result = $conn->query("SHOW TABLES");

// Loop through the result set and add each table name to the array
while ($row = $result->fetch_array()) {
    $tables[] = $row[0];
}

// Encode the list of tables as JSON and return it
echo json_encode($tables);

// Close the database connection
$conn->close();
?>
