<?php
// Author: Thomas Hoerger
// Thomas Hoerger - Copyright © 2025 SkyView Weather App First Build
// 4-17-2025
// Description: Returns the total number of likes and dislikes from the feedback table in JSON format for use in a chart visualization.

header("Content-Type: application/json");

$conn = new mysqli("localhost", "root", "Sweets@01", "weather_app");

$res = $conn->query("SELECT liked, COUNT(*) as total FROM Feedback GROUP BY liked");

$data = ["liked" => 0, "disliked" => 0];
while ($row = $res->fetch_assoc()) {
  if ($row['liked'] == 1) {
    $data['liked'] = $row['total'];
  } else {
    $data['disliked'] = $row['total'];
  }
}

echo json_encode($data);
?>
