<?php
// Author: Thomas Hoerger
// Thomas Hoerger - Copyright © 2025 SkyView Weather App First Build
// 4-17-2025
// Description: Returns the total number of likes and dislikes from the feedback table in JSON format for use in a chart visualization.

// Show errors for debugging
error_reporting(E_ALL);
ini_set('display_errors', 1);
header("Content-Type: application/json");

// Connect to MySQL
$conn = new mysqli("localhost", "root", "Sweets@01", "weather_app");

// Handle connection error
if ($conn->connect_error) {
  http_response_code(500);
  echo json_encode(["error" => "DB connection failed", "details" => $conn->connect_error]);
  exit();
}

// Get the search term
$city = $_GET['city'] ?? '';

// SQL query: join WeatherReports with Locations using location_id
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

// Run the query
$res = $conn->query($sql);

// Handle query failure
if (!$res) {
  http_response_code(500);
  echo json_encode([
    "error" => "Query failed", 
    "details" => $conn->error, 
    "sql" => $sql
  ]);
  exit();
}

// Format results as JSON
$data = [];
while ($row = $res->fetch_assoc()) {
  $data[] = $row;
}

echo json_encode($data);
?>
