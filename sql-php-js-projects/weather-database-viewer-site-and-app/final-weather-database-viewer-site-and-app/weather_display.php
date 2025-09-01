<?php
// Thomas Hoerger - Copyright © 2025 Skyview Weather Database Viewer Site-App Final Build
include 'db_connect.php';

// Fetch weather reports with locations
$sql = "SELECT Locations.city, Locations.country, WeatherReports.temperature, WeatherReports.weather_condition
        FROM WeatherReports
        INNER JOIN Locations USING(location_id)
        ORDER BY WeatherReports.temperature ASC";

// Execute query
$result = $conn->query($sql);

// Check for errors
if (!$result) {
    die("Query failed: " . $conn->error);
}
?>

<!DOCTYPE html>
<html lang="en">
<head>
    <title>Weather Reports</title>
    <style>  
    	body { font-family: Arial, sans-serif; text-align: center; background-color: #f5f5f5; }
    	h2 { font-weight: bold; color: black; }
    	table { width: 80%; margin: auto; border-collapse: collapse; background-color: white; }
    	th, td { padding: 12px; border: 1px solid black; text-align: center; }
    	th { background-color: #007BFF; color: white; }
    	tr:nth-child(even) { background-color: #f9f9f9; }
    	tr:hover { background-color: #ddd; }
    </style>
</head>
<body>
    <h2>All Weather Reports Coldest to Warmest</h2>

    <?php if ($result->num_rows > 0): ?>
    <table>
        <tr>
            <th>City</th>
            <th>Country</th>
            <th>Temperature (°F)</th>
            <th>Condition</th>
        </tr>
        <?php while ($row = $result->fetch_assoc()): ?>
        <tr>
            <td><?php echo htmlspecialchars($row['city']); ?></td>
            <td><?php echo htmlspecialchars($row['country']); ?></td>
            <td><?php echo htmlspecialchars($row['temperature']); ?></td>
            <td><?php echo htmlspecialchars($row['weather_condition']); ?></td>
        </tr>
        <?php endwhile; ?>
    </table>
    <?php else: ?>
        <p>No weather reports found.</p>
    <?php endif; ?>

</body>
</html>

<?php
$conn->close();
?>

