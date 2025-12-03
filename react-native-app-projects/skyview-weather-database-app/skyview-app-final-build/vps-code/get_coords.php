<?php
// Author: Thomas Hoerger
// Thomas Hoerger - Copyright © 2025 SkyView Weather App Final Build
// Solo Group 9
// 4-17-2025
// Description: Fetches the latitude and longitude for a given city from the Locations table. 
// If not found, attempts to retrieve coordinates using the OpenWeatherMap API.

header('Content-Type: application/json'); // Set response content type to JSON

// Establish a connection to the MySQL database
$conn = new mysqli('localhost', 'root', 'Sweets@01', 'weather_app');

// Check for a failed database connection
if ($conn->connect_error) {
    echo json_encode(["error" => "DB connection failed"]); // Return error as JSON
    exit; // Terminate the script
}

// Retrieve the city parameter from the URL query string
$city = $_GET['city'];

// Step 1: Attempt to find coordinates in the local database
$stmt = $conn->prepare("SELECT latitude, longitude FROM Locations WHERE city = ?");
$stmt->bind_param("s", $city); // Bind the city parameter to the query
$stmt->execute();
$result = $stmt->get_result();

// If the city is found in the database, return the coordinates
if ($row = $result->fetch_assoc()) {
    echo json_encode([
        "latitude" => $row['latitude'],
        "longitude" => $row['longitude'],
        "source" => "db" // Indicate the source is the database
    ]);
    exit;
}

// Step 2: If not found in the database, attempt to get coordinates from the OpenWeatherMap API
$apiKey = 'a34bb9d6a46791646f2426d3fada7996'; // OpenWeatherMap API key
$url = "http://api.openweathermap.org/geo/1.0/direct?q=" . urlencode($city) . "&limit=1&appid=" . $apiKey;

// Make the API request
$response = file_get_contents($url);
$data = json_decode($response, true);

// If valid coordinates are returned from the API, output them
if (isset($data[0]['lat']) && isset($data[0]['lon'])) {
    echo json_encode([
        "latitude" => $data[0]['lat'],
        "longitude" => $data[0]['lon'],
        "source" => "api" // Indicate the source is the API
    ]);
} else {
    // If the city is not found in the API response, return an error message
    echo json_encode(["error" => "City not found"]);
}
?>
