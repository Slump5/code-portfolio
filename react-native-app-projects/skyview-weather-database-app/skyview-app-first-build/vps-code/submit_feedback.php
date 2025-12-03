<?php
// Author: Thomas Hoerger
// Thomas Hoerger - Copyright © 2025 SkyView Weather App First Build
// 4-17-2025
// Description: Returns the total number of likes and dislikes from the feedback table in JSON format for use in a chart visualization.

header("Content-Type: application/json");

$conn = new mysqli("localhost", "root", "Sweets@01", "weather_app");

if ($conn->connect_error) {
  echo json_encode(["error" => "DB error"]);
  exit();
}

$data = json_decode(file_get_contents('php://input'), true);
$username = $conn->real_escape_string($data['username'] ?? 'anonymous');
$liked = intval($data['liked'] ?? 0);

$conn->query("INSERT INTO Feedback (username, liked) VALUES ('$username', $liked)");

echo json_encode(["status" => "ok"]);
?>
