# Skyview Weather Database Viewer Site and App Final Build

## Overview
Skyview is a PHP-based web application designed for interactively viewing weather data from a MySQL database. It features a user-friendly interface with login functionality, including Google OAuth 2.0 support, and allows users to dynamically select and display weather-related tables (WeatherReports, Locations, Forecasts). The application supports responsive design for both desktop and mobile platforms, ensuring accessibility across devices. It fulfills the requirements of Project 2 for CSCI411/511 Database Theory & Design, including secure session management, dynamic table rendering, and a clean UI/UX.

## Features
- **Login System:** Supports email/password authentication and Google OAuth 2.0 for secure user access.
- **Session Management:** Redirects unauthenticated users to the login page and maintains user sessions.
- **Dynamic Table Selection:** Users can select from WeatherReports, Locations, or Forecasts tables via a dropdown, with data auto-refreshing without a submit button.
- **Responsive UI/UX:** Optimized for laptop and mobile platforms with a clean, modern design using CSS media queries.
- **Tab Navigation:** Two tabs (Select and Display) for intuitive table selection and data viewing.
- **Data Display:** Fetches and displays up to 30 rows from the selected table with dynamically generated headers.
- **Logout Functionality:** Allows users to securely end their session and return to the login page.
- **Database Integration:** Connects to a MySQL database (`weather_app`) to retrieve and display weather data.
- **Error Handling:** Handles database connection errors, empty result sets, and invalid logins gracefully.
- **Google OAuth Integration:** Uses the Google API Client Library for seamless third-party authentication.

## File Structure
- **auth.php:** Handles email/password login authentication and session creation.
- **db_connect.php:** Establishes connection to the MySQL `weather_app` database.
- **google-callback.php:** Processes Google OAuth 2.0 login responses and sets user session data.
- **google-login.php:** Initiates Google OAuth 2.0 authentication flow.
- **index.html:** Simple redirect page to `login.php`.
- **info.php:** Displays PHP configuration details (for debugging).
- **login.php:** Renders the login interface with email/password and Google login options.
- **logout.php:** Destroys user sessions and redirects to the login page.
- **weather_display.php:** Displays weather reports sorted by temperature, joining WeatherReports and Locations tables.
- **weather_ui.php:** Main application interface for dynamic table selection and display, with session-based access control.
- **weather_ui.php.save:** Backup version of `weather_ui.php` with slightly different styling.
- **composer.json / composer.lock:** Manages dependencies for the Google API Client Library.
- **powerpoint-final-weather-database-viewer-site-and-app.pptx:** Presentation outlining project development steps.
- **documentation-final-weather-database-viewer-site-and-app.pdf:** Documentation summarizing project implementation.
- **instructions.pdf:** Project requirements and objectives from Dr. Adriano Cavalcanti.
- **presentation-final-weather-database-viewer-site-and-app.mkv:** Video presentation of the project (not included in code but referenced).

## Requirements
- **PHP:** Version 7.4 or later (compatible with Google API Client Library).
- **MySQL:** Database server with `weather_app` database and tables (Users, WeatherReports, Locations, Forecasts).
- **Web Server:** Apache or similar with PHP support.
- **Composer:** For installing Google API Client Library dependencies.
- **Google OAuth Credentials:** Client ID and secret configured in `google-login.php` and `google-callback.php`.
- **Dependencies:** Google API Client Library (`google/apiclient:^2.0`) as specified in `composer.json`.
- **Browser:** Modern web browser (Chrome, Firefox, Safari) for testing.
- **Input Files:** Database must be populated with relevant tables and data.

## Setup and Installation
1. **Clone the Repository (if applicable):**
	```bash
	git clone <repository-url>
	cd <repository-directory>```
2. Set Up MySQL Database:
	- Create a MySQL database named weather_app.
	- Create tables: Users, WeatherReports, Locations, Forecasts with appropriate schema.
	- Update db_connect.php with your MySQL credentials (replace root and password with your username and password).
3. Install Dependencies:
	- Install Composer if not already installed: getcomposer.org.
	- Run the following command in the project directory to install the Google API Client Library:
		```bash
		composer install```
4. Configure Google OAuth:
	- Create a project in the Google Cloud Console.
	- Enable the Google+ API and create OAuth 2.0 credentials.
	- Update google-login.php and google-callback.php with your Client ID, Client Secret, and Redirect URI (http://skyview.work.gd/google-callback.php).
5. Deploy to Web Server:
	- Copy all files to your web server’s document root (e.g., /var/www/html for Apache).
	- Ensure the server has PHP and MySQL modules enabled.
6. Set File Permissions:
	- Ensure the web server has read/write access to the project directory and vendor/ folder.
	
## How to Use
1. Access the Application:
	- Navigate to http://<your-domain>/index.html or directly to login.php.
	- You will be redirected to the login page if not authenticated.
2. Log In:
	- Use email/password credentials (stored in the Users table) or click "Login with Google" for OAuth authentication.
3. Select and View Data:
	- On the weather_ui.php page, use the "Select" tab to choose a table (WeatherReports, Locations, Forecasts) from the dropdown.
	- The page auto-refreshes to display the selected table’s data in the "Display" tab (up to 30 rows).
4. View Weather Reports:
	- Access weather_display.php to see weather reports sorted by temperature, joined with location data.
5. Log Out:
	- Click the logout link in weather_ui.php to end the session and return to the login page.
6. Test on Multiple Platforms:
	- Open the application on a laptop and mobile device to verify responsive design.
7. Debugging (Optional):
	- Access info.php to view PHP configuration details if issues arise.

## Notes
- **Security:** The auth.php file uses plain text passwords for simplicity. In production, implement password hashing (e.g., password_hash() and password_verify()) for security.
- **DNS Propagation:** If using a custom domain like skyview.work.gd, ensure DNS is fully propagated for Google OAuth to work.
- **Database Schema:** Ensure the weather_app database has the required tables (Users, WeatherReports, Locations, Forecasts) with appropriate columns.
- **Responsive Design:** The CSS in weather_ui.php and login.php includes media queries for mobile compatibility.

## License
This project is for personal use. Retain the copyright notice: "Thomas Hoerger - Copyright © 2025 Skyview Weather Database Viewer Site-App Final Build".