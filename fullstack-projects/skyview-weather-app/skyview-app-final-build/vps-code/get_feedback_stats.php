<?php
// Author: Thomas Hoerger
// Thomas Hoerger - Copyright © 2025 SkyView Weather App Final Build
// Solo Group 9
// 4-23-2025
// Description: Returns total count of likes and dislikes from the Feedback table as JSON.

header('Content-Type: application/json'); // Set the response type to JSON

// Establish a connection to the MySQL database
$conn = new mysqli('localhost', 'root', 'Sweets@01', 'weather_app');

// Check for a connection error and return an error message if it occurs
if ($conn->connect_error) {
    echo json_encode(["error" => "DB connection failed"]);
    exit;
}

// SQL query to count likes and dislikes using conditional aggregation
$query = "SELECT 
            SUM(CASE WHEN liked = 1 THEN 1 ELSE 0 END) AS liked,
            SUM(CASE WHEN liked = 0 THEN 1 ELSE 0 END) AS disliked
          FROM Feedback";

// Execute the query
$result = $conn->query($query);

// If the query is successful and returns results, encode them as JSON
if ($result && $row = $result->fetch_assoc()) {
    echo json_encode([
        "liked" => $row['liked'] ?? "0",       // Use 0 as fallback if null
        "disliked" => $row['disliked'] ?? "0"  // Use 0 as fallback if null
    ]);
} else {
    // If the query fails, return an error message with details
    echo json_encode(["error" => "Query failed", "details" => $conn->error]);
}

// Close the database connection
$conn->close();
?>
