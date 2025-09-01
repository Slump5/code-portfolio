# Weather Database Viewer Site Stage 2

## Overview
This is a PHP-based web application designed to provide an interactive interface for viewing data from a weather database. It allows users to select a table from a dropdown menu and dynamically display its contents (up to 30 rows) in a tabbed interface without requiring a submit button. The application fulfills the requirements of a CSCI411/511 Database Theory & Design project, supporting at least three tables (WeatherReports, Locations, Forecasts) and updating the display automatically upon table selection. The project includes source code, documentation, a PowerPoint presentation, and a video demo.

## Features
- **Dynamic Table Selection:** Users can choose from three tables (WeatherReports, Locations, Forecasts) via a dropdown menu in the "Select" tab.
- **Automatic Display Update:** The "Display" tab updates instantly when a new table is selected, showing up to 30 rows of data without a submit button.
- **Tabbed Interface:** Two tabs ("Select" and "Display") provide a clean, user-friendly navigation experience.
- **Responsive Table Styling:** Data is displayed in a formatted HTML table with alternating row colors, hover effects, and centered text for readability.
- **Dynamic Column Headers:** Column names are extracted dynamically from the selected table for flexible display.
- **Error Handling:** Displays a "No data available" message if the selected table is empty.
- **Database Integration:** Connects to a MySQL database via a `db_connect.php` file to fetch table data.
- **Documentation Support:** Includes a midterm documentation PDF, PowerPoint presentation, and a video demo (5-10 minutes).

## File Structure
- **weather_ui.php:** Main PHP file containing the web application logic, HTML structure, CSS styling, and JavaScript for tab navigation and table updates.
- **documentation-stage2-weather-database-viewer-site.pdf:** Midterm documentation describing implementation steps (6 pages).
- **powerpoint-stage2-weather-database-viewer-site.pptx:** PowerPoint presentation outlining the project steps, including screenshots and server status checks.
- **video-stage2-weather-database-viewer-site.mkv:** Video demo (5-10 minutes) showcasing the application's functionality.
- **instructions.pdf:** Project requirements and guidelines from Dr. Adriano Cavalcanti (12 pages).
- **db_connect.php:** Database connection file for MySQL integration (adjust as needed).

## Requirements
- **PHP 7.4 or later:** For server-side scripting and MySQL integration.
- **MySQL Database:** A running MySQL instance with at least three tables (WeatherReports, Locations, Forecasts).
- **Web Server:** Apache (or compatible) to serve PHP files.
- **Browser:** Any modern browser (Chrome, Firefox, Safari, etc.) for viewing the web interface.
- **Dependencies:** MySQLi PHP extension for database connectivity.
- **Input Files:** A configured `db_connect.php` file with valid MySQL credentials.
- **Optional:** PDF viewer for documentation, PowerPoint viewer for presentation, and media player for video demo.

## Setup and Running
1. **Set up the Database:**
   - Ensure a MySQL database is running with the tables `WeatherReports`, `Locations`, and `Forecasts`.
   - Create or configure `db_connect.php` with appropriate database credentials (e.g., host, user, password, database name).
2. **Configure the Web Server:**
   - Place `weather_ui.php` in the web server's root directory (`/var/www/html/` for Apache on Linux).
   - Ensure `db_connect.php` is in the same directory and accessible.
3. **Restart Apache:**
	- On Unix-like systems:
		```bash
		sudo systemctl restart apache2```
	- On Windows (with XAMPP or similar): Restart Apache via the control panel.
4. Access the Application:
	- Navigate to http://<External-IP>/weather_ui.php in a browser (replace <External-IP> with your server's IP or localhost).
5. Verify Server Status:
	- Ensure MySQL is running:
		```bash
		sudo systemctl status mysql```
	- Ensure Apache is running:
		```bash
		sudo systemctl status apache2```
		
## How to Use
1. Open the application in a browser (http://<External-IP>/weather_ui.php).
2. On the "Select" tab, choose a table (WeatherReports, Locations, or Forecasts) from the dropdown menu.
3. The page will automatically refresh and switch to the "Display" tab, showing up to 30 rows of data from the selected table.
4. Switch between tabs using the "Select" and "Display" buttons to navigate.
5. If no data is available, a "No data available in this table" message will appear in the "Display" tab.
6. Watch the video for a live demo

## Notes
- The application assumes a MySQL database with the specified tables. Ensure the table names match exactly (WeatherReports, Locations, Forecasts).
- The db_connect.php needs to be adjusted for a valid MySQL connection (e.g., using mysqli_connect).
- The project meets the requirements outlined in instructions.pdf, including dynamic table selection, automatic updates, and support for at least 30 rows across three tables.

## License
This project is for educational and personal use. Retain the copyright notice: "Thomas Hoerger - Copyright © 2025 Weather Database Viewer Site Stage 2".
	

	