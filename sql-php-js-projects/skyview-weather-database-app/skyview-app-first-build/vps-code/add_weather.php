<?php
// Author: Thomas Hoerger
// Thomas Hoerger - Copyright © 2025 SkyView Weather App First Build
// 4-17-2025
// Description: Inserts a new weather report into the database. If the city does not exist, it adds it to the Locations table with default coordinates.

header('Content-Type: application/json');

// 🔐 Database connection
$conn = new mysqli('localhost', 'root', 'Sweets@01', 'weather_app');
if ($conn->connect_error) {
    echo json_encode(["status" => "error", "message" => "DB connection failed"]);
    exit;
}

// 🧾 Get JSON input
$data = json_decode(file_get_contents("php://input"), true);
$city = $data['city'];
$temperature = $data['temperature'];
$humidity = $data['humidity'];

// 🧠 Geolocation function
function fetchCoordinates($city) {
    $apiKey = 'a34bb9d6a46791646f2426d3fada7996'; // your skyview-key
    $url = "http://api.openweathermap.org/geo/1.0/direct?q=" . urlencode($city) . "&limit=1&appid=" . $apiKey;

    $response = file_get_contents($url);
    if ($response) {
        $data = json_decode($response, true);
        if (isset($data[0]['lat']) && isset($data[0]['lon'])) {
            return [$data[0]['lat'], $data[0]['lon']];
        }
    }
    return [0.0, 0.0]; // fallback if nothing found
}

// 🔍 Step 1: Check if city already exists in Locations
$stmt = $conn->prepare("SELECT location_id FROM Locations WHERE city = ?");
$stmt->bind_param("s", $city);
$stmt->execute();
$result = $stmt->get_result();

if ($row = $result->fetch_assoc()) {
    $location_id = $row['location_id'];
} else {
    // 🌍 Step 2: Fetch coordinates and insert city
    list($lat, $lon) = fetchCoordinates($city);
    $default_country = 'USA';
    $default_user = 1;

    $insertLoc = $conn->prepare("INSERT INTO Locations (city, country, latitude, longitude, user_id) VALUES (?, ?, ?, ?, ?)");
    $insertLoc->bind_param("ssddi", $city, $default_country, $lat, $lon, $default_user);

    if (!$insertLoc->execute()) {
        echo json_encode(["status" => "error", "message" => "Failed to insert location", "details" => $insertLoc->error]);
        exit;
    }

    $location_id = $insertLoc->insert_id;
}

// 🌤️ Step 3: Insert into WeatherReports
$default_condition = 'Clear';
$default_wind = 5;

$insertWeather = $conn->prepare("INSERT INTO WeatherReports (location_id, temperature, humidity, weather_condition, wind_speed) VALUES (?, ?, ?, ?, ?)");
$insertWeather->bind_param("iddsi", $location_id, $temperature, $humidity, $default_condition, $default_wind);

if ($insertWeather->execute()) {
    echo json_encode(["status" => "success"]);
} else {
    echo json_encode(["status" => "error", "message" => "Failed to insert weather report", "details" => $insertWeather->error]);
}

$conn->close();
?>
