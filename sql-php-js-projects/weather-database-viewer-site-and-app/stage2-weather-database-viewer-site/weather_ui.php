<?php
/**
 * Weather Database Interactive Viewer
 * Author: Thomas Hoerger - Group 9
 *
 * Thomas Hoerger - Copyright © 2025 Weather Database Viewer Site Stage 2
 *
 * Description:
 * This program allows users to dynamically select a table from the Weather Database 
 * and display its data in the "Display" tab without needing a submit button.
 */

include 'db_connect.php'; // Include database connection file

// Determine which table is selected from the dropdown. Default is "WeatherReports".
$table = isset($_GET['table']) ? $_GET['table'] : 'WeatherReports';

$displayTableName = preg_replace('/(?<!\ )[A-Z]/', ' $0', $table); // Add spaces before uppercase letters
$displayTableName = ucwords(str_replace('_', ' ', trim($displayTableName))); // Format and capitalize

// Fetch the first 30 rows from the selected table
$sql = "SELECT * FROM $table LIMIT 30";
$result = $conn->query($sql);

// Retrieve column headers dynamically from the selected table
$headers = [];
if ($result && $result->num_rows > 0) {
    $headers = array_keys($result->fetch_assoc()); // Extract column names from the first row
    $result->data_seek(0); // Reset result pointer to fetch rows again
}
?>

<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="author" content="Thomas Hoerger - Group 9">
    <meta name="description" content="Interactive Weather Database Viewer">
    <title>Weather Database - Group 9</title>

    <style>
        /* General styling for the webpage */
        body { 
            font-family: Arial, sans-serif; 
            background-color: #f5f5f5; 
            text-align: center; 
        }

        /* Title styling */
        h1 { 
            font-weight: bold; 
            color: black; 
        }

        /* Navigation tab container */
        .tab-container {
            display: flex;
            justify-content: center;
            margin: 20px 0;
        }

        /* Styling for each tab button */
        .tab {
            padding: 12px 20px;
            cursor: pointer;
            background-color: #007BFF;
            color: white;
            border: 1px solid black;
            margin: 0 5px;
        }

        /* Change tab color on hover */
        .tab:hover {
            background-color: #0056b3;
        }

        /* Highlight the active tab */
        .tab.active {
            background-color: #003f7f;
        }

        /* Hide all content sections by default */
        .content { 
            display: none; 
            margin-top: 20px; 
        }
        
        /* Show the active content section */
        .content.active { 
            display: block; 
        }

        /* Styling for tables */
        table { 
            width: 80%; 
            margin: auto; 
            border-collapse: collapse; 
            background-color: white; 
        }

        /* Styling for table headers and data cells */
        th, td { 
            padding: 12px; 
            border: 1px solid black; 
            text-align: center; 
        }

        /* Styling for table headers */
        th { 
            background-color: #007BFF; 
            color: white; 
        }

        /* Alternate row coloring for readability */
        tr:nth-child(even) { 
            background-color: #f9f9f9; 
        }

        /* Highlight rows when hovered */
        tr:hover { 
            background-color: #ddd; 
        }
    </style>
</head>
<body>

    <!-- Main Title -->
    <h1>Weather Database Viewer</h1>
    <p><strong>Author:</strong> Thomas Hoerger - Group 9</p>

    <!-- Navigation Tabs -->
    <div class="tab-container">
        <div class="tab active" onclick="showTab('selectTab')">Select</div>
        <div class="tab" onclick="showTab('displayTab')">Display</div>
    </div>

    <!-- Select Table Section -->
    <div id="selectTab" class="content active">
        <h2>Select a Table</h2>

        <!-- Dropdown menu to select a table (auto-updates on selection change) -->
        <label for="table">Choose a Table:</label>
        <select name="table" id="table" onchange="changeTable(this.value)">
            <option value="WeatherReports" <?= ($table == 'WeatherReports') ? 'selected' : '' ?>>Weather Reports</option>
            <option value="Locations" <?= ($table == 'Locations') ? 'selected' : '' ?>>Locations</option>
            <option value="Forecasts" <?= ($table == 'Forecasts') ? 'selected' : '' ?>>Forecasts</option>
        </select>
    </div>

    <!-- Display Table Section -->
    <div id="displayTab" class="content">
        <h2><?= htmlspecialchars($displayTableName) ?></h2>  <!-- Display selected table name -->

        <!-- Display table only if data exists -->
        <?php if ($result && $result->num_rows > 0): ?>
        <table>
            <tr>
                <?php 
                // Generate table headers dynamically
                foreach ($headers as $header): ?>
                    <th><?= htmlspecialchars($header); ?></th>
                <?php endforeach; ?>
            </tr>
            
            <?php 
            // Loop through each row and populate table cells
            while ($row = $result->fetch_assoc()): ?>
                <tr>
                    <?php foreach ($headers as $header): ?>
                        <td><?= htmlspecialchars($row[$header]); ?></td>
                    <?php endforeach; ?>
                </tr>
            <?php endwhile; ?>
        </table>
        <?php else: ?>
            <!-- Display message if no data is available -->
            <p>No data available in this table.</p>
        <?php endif; ?>
    </div>

    <script>
        /**
         * Function to switch between tabs dynamically
         * @param {string} tabId - The ID of the tab to be displayed
         */
        function showTab(tabId) {
            // Hide all tab content sections
            document.querySelectorAll('.content').forEach(tab => tab.classList.remove('active'));
            document.querySelectorAll('.tab').forEach(t => t.classList.remove('active'));

            // Show the selected tab's content
            document.getElementById(tabId).classList.add('active');

            // Mark the selected tab as active
            document.querySelector(`.tab[onclick="showTab('${tabId}')"]`).classList.add('active');
        }

        /**
         * Function to update the displayed table automatically when a new one is selected
         * @param {string} tableName - The selected table name
         */
        function changeTable(tableName) {
            window.location.href = "?table=" + tableName; // Update the URL to refresh data dynamically
        }
    </script>

</body>
</html>

<?php
// Close the database connection
$conn->close();
?>
