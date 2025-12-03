<?php
// Author: Thomas Hoerger
// Thomas Hoerger - Copyright © 2025 SkyView Weather App First Build
// 4-17-2025
// Description: Fetches the latitude and longitude for a given city from the Locations table. If not found, attempts to retrieve coordinates using the OpenWeatherMap API.

header('Content-Type: application/json');

$conn = new mysqli('localhost', 'root', 'Sweets@01', 'weather_app');
if ($conn->connect_error) {
    echo json_encode(["error" => "DB connection failed"]);
    exit;
}

$city = $_GET['city'];

// Step 1: Check your database
$stmt = $conn->prepare("SELECT latitude, longitude FROM Locations WHERE city = ?");
$stmt->bind_param("s", $city);
$stmt->execute();
$result = $stmt->get_result();

if ($row = $result->fetch_assoc()) {
    echo json_encode([
        "latitude" => $row['latitude'],
        "longitude" => $row['longitude'],
        "source" => "db"
    ]);
    exit;
}

// Step 2: Fallback — get it from OpenWeatherMap
$apiKey = 'a34bb9d6a46791646f2426d3fada7996';
$url = "http://api.openweathermap.org/geo/1.0/direct?q=" . urlencode($city) . "&limit=1&appid=" . $apiKey;

$response = file_get_contents($url);
$data = json_decode($response, true);

if (isset($data[0]['lat']) && isset($data[0]['lon'])) {
    echo json_encode([
        "latitude" => $data[0]['lat'],
        "longitude" => $data[0]['lon'],
        "source" => "api"
    ]);
} else {
    echo json_encode(["error" => "City not found"]);
}
?>
