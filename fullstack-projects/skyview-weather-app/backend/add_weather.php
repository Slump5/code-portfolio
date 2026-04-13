<?php
// Author: Thomas Hoerger
// Thomas Hoerger - Copyright © 2025 SkyView Weather App Final Build
// Solo Group 9
// 4-17-2025
// Description: Inserts a new weather report into the database. If the city does not exist, it adds it to the Locations table with default coordinates.

header('Content-Type: application/json'); // Set response content type to JSON

// Establish a connection to the MySQL database
$conn = new mysqli('localhost', 'root', 'Sweets@01', 'weather_app');

// Check if connection to the database failed
if ($conn->connect_error) {
    echo json_encode(["status" => "error", "message" => "DB connection failed"]);
    exit;
}

// Retrieve the JSON data sent in the POST request
$data = json_decode(file_get_contents("php://input"), true);

// Extract individual values from the decoded data
$city = $data['city'];
$temperature = $data['temperature'];
$humidity = $data['humidity'];

// Function to fetch geographical coordinates for a city using OpenWeatherMap API
function fetchCoordinates($city) {
    $apiKey = 'a34bb9d6a46791646f2426d3fada7996'; // OpenWeatherMap API key
    $url = "http://api.openweathermap.org/geo/1.0/direct?q=" . urlencode($city) . "&limit=1&appid=" . $apiKey;

    $response = file_get_contents($url); // Make API call to get location data
    if ($response) {
        $data = json_decode($response, true);
        // If valid coordinates are returned, use them
        if (isset($data[0]['lat']) && isset($data[0]['lon'])) {
            return [$data[0]['lat'], $data[0]['lon']];
        }
    }
    return [0.0, 0.0]; // Return default coordinates if not found
}

// Step 1: Check if the city already exists in the Locations table
$stmt = $conn->prepare("SELECT location_id FROM Locations WHERE city = ?");
$stmt->bind_param("s", $city);
$stmt->execute();
$result = $stmt->get_result();

// If city exists, retrieve its location_id
if ($row = $result->fetch_assoc()) {
    $location_id = $row['location_id'];
} else {
    // Step 2: If city does not exist, fetch coordinates and insert into Locations
    list($lat, $lon) = fetchCoordinates($city);
    $default_country = 'USA';
    $default_user = 1;

    $insertLoc = $conn->prepare("INSERT INTO Locations (city, country, latitude, longitude, user_id) VALUES (?, ?, ?, ?, ?)");
    $insertLoc->bind_param("ssddi", $city, $default_country, $lat, $lon, $default_user);

    // If location insertion fails, return an error
    if (!$insertLoc->execute()) {
        echo json_encode(["status" => "error", "message" => "Failed to insert location", "details" => $insertLoc->error]);
        exit;
    }

    $location_id = $insertLoc->insert_id; // Get ID of newly inserted location
}

// Step 3: Insert the weather report into the WeatherReports table
$default_condition = 'Clear'; // Default weather condition
$default_wind = 5; // Default wind speed

$insertWeather = $conn->prepare("INSERT INTO WeatherReports (location_id, temperature, humidity, weather_condition, wind_speed) VALUES (?, ?, ?, ?, ?)");
$insertWeather->bind_param("iddsi", $location_id, $temperature, $humidity, $default_condition, $default_wind);

// If insertion is successful, return success status
if ($insertWeather->execute()) {
    echo json_encode(["status" => "success"]);
} else {
    // If weather report insertion fails, return an error
    echo json_encode(["status" => "error", "message" => "Failed to insert weather report", "details" => $insertWeather->error]);
}

$conn->close(); // Close the database connection
?>
