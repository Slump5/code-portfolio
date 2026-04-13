<?php
// Author: Thomas Hoerger
// Thomas Hoerger - Copyright © 2025 SkyView Weather App Final Build
// Solo Group 9
// 4-24-2025
// Description: Returns all records from WeatherReports table as JSON.

header('Content-Type: application/json'); // Set the response content type to JSON

// Establish a connection to the MySQL database
$conn = new mysqli('localhost', 'root', 'Sweets@01', 'weather_app');

// Check if the database connection failed
if ($conn->connect_error) {
    echo json_encode(["error" => "DB connection failed"]); // Return error as JSON
    exit; // Terminate the script if connection fails
}

// Execute a SQL query to retrieve all records from the WeatherReports table
$result = $conn->query("SELECT * FROM WeatherReports");

// Initialize an empty array to store the results
$data = [];

// Loop through each row in the result set and add it to the array
while ($row = $result->fetch_assoc()) {
    $data[] = $row;
}

// Encode the array of records into JSON and return it
echo json_encode($data);

// Close the database connection
$conn->close();
?>
