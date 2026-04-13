<?php
// Author: Thomas Hoerger
// Thomas Hoerger - Copyright © 2025 SkyView Weather App Final Build
// Solo Group 9
// 4-17-2025
// Description: Searches for weather reports based on a partial city name match
// by joining the Locations and WeatherReports tables, returning recent weather info.

// Enable error reporting for debugging during development
error_reporting(E_ALL);
ini_set('display_errors', 1);

// Set the content type of the response to JSON
header("Content-Type: application/json");

// Connect to the MySQL database
$conn = new mysqli("localhost", "root", "Sweets@01", "weather_app");

// Check for a connection error and return a 500 response if it fails
if ($conn->connect_error) {
  http_response_code(500);
  echo json_encode(["error" => "DB connection failed", "details" => $conn->connect_error]);
  exit();
}

// Retrieve the city search term from the query parameters (default to empty string)
$city = $_GET['city'] ?? '';

// Construct SQL query to fetch weather reports for cities that match the search term
// Joins the WeatherReports and Locations tables on location_id
$sql = "
  SELECT 
    L.city AS City, 
    W.temperature, 
    W.humidity, 
    W.weather_condition, 
    W.wind_speed, 
    W.report_time
  FROM WeatherReports W
  JOIN Locations L ON W.location_id = L.location_id
  WHERE L.city LIKE '%$city%'
";

// Execute the query
$res = $conn->query($sql);

// Handle query failure and return a 500 error with debug info
if (!$res) {
  http_response_code(500);
  echo json_encode([
    "error" => "Query failed", 
    "details" => $conn->error, 
    "sql" => $sql
  ]);
  exit();
}

// Initialize an array to store the results
$data = [];

// Loop through each row of the result set and add it to the array
while ($row = $res->fetch_assoc()) {
  $data[] = $row;
}

// Return the results as a JSON response
echo json_encode($data);
?>

