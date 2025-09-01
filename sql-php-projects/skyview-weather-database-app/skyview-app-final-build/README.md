# SkyView Weather App Final Build

## Overview
SkyView is a full-stack, responsive weather tracking application developed using React Native (Expo) for the frontend and PHP/MySQL for the backend. The app allows users to register, log in, add weather reports, search weather by city, view an interactive map, display database tables, and provide feedback visualized in a pie chart. It is hosted on a Google Cloud VPS running Ubuntu with Apache, PHP, and MySQL, and integrates with the OpenWeatherMap API for geolocation data. The project demonstrates skills in frontend design, backend integration, database management, and deployment. This app was made entirely by me as part of a solo group (group 9).

## Features
- **User Authentication:** Secure login and registration system with username, email, and password validation.
- **Weather Data Management:** Users can add weather reports (city, temperature, humidity) to a MySQL database and retrieve them via search.
- **Interactive Map:** Zoom to city locations using react-native-maps, with coordinates fetched from the database or OpenWeatherMap API.
- **Database Display:** Select and view data from any database table (Users, Locations, WeatherReports, Forecasts, Alerts, Feedback) using a dropdown and FlatList.
- **Feedback System:** Users can submit like/dislike feedback, stored in the database and visualized in a real-time pie chart using react-native-chart-kit.
- **Responsive Design:** Supports both mobile and laptop views with scalable components (maps, charts, forms) and Lottie animations for enhanced UI.
- **Navigation:** Utilizes react-native-swiper for smooth screen transitions with custom dot and arrow indicators.
- **Backend API:** PHP scripts handle database operations (CRUD) and API calls, hosted on a VPS with remote access enabled.
- **Live Data Integration:** Real-time database updates and external API usage for dynamic geolocation.
- **Documentation:** Includes a detailed presentation (`powerpoint-skyview-app-final-build.pptx`), demo video (`skyview-app-final-build-demo.mp4`), and design documents.

## File Structure
- **Frontend (React Native / Expo):**
	- `App.js`: Entry point managing navigation and user authentication state.
	- `index.js`: Registers the app with Expo for proper environment setup.
	- `MainSwiper.js`: Swiper navigation for core app screens with welcome/logout header.
	- `AnimatedHeader.js`: Reusable header with SkyView title and Lottie animation.
	- `LoginScreen.js`: Handles user login with server-side validation.
	- `RegisterScreen.js`: Manages user registration with duplicate username checks.
	- `AddScreen.js`: Form for submitting weather reports to the database.
	- `SearchScreen.js`: Searches weather by city using FlatList to display results.
	- `DisplayScreen.js`: Displays database table data with dropdown selection.
	- `MapScreen.js`: Interactive map with city-based zoom functionality.
	- `FeedbackScreen.js`: Submits like/dislike feedback with Lottie animation.
	- `ChartScreen.js`: Displays feedback statistics in a pie chart with refresh capability.
- **Backend (PHP/MySQL):**
	- `db_connect.php`: Establishes MySQL database connection.
	- `add_weather.php`: Inserts weather reports and adds new cities to Locations table.
	- `search_weather.php`: Retrieves weather reports by partial city name match.
	- `get_coords.php`: Fetches city coordinates from database or OpenWeatherMap API.
	- `submit_feedback.php`: Stores user feedback (like/dislike) in the database.
	- `get_feedback_stats.php`: Returns like/dislike counts for pie chart visualization.
	- `get_all_weather.php`: Retrieves all records from WeatherReports table.
	- `get_table_data.php`: Returns rows from any specified database table.
	- `get_table_list.php`: Lists all table names in the database.
	- `login_user.php`: Validates user login credentials (plain-text for demo).
	- `register_user.php`: Registers new users with duplicate username checks.
- **Documentation and Media:**
	- `documentation-skyview-app-final-build.pdf`: Step-by-step implementation guide.
	- `powerpoint-skyview-app-final-build.pptx`: Presentation summarizing the project.
	- `skyview-app-final-build-demo.mp4`: Demo video showcasing app functionality.
	- `presentation-skyview-app-final-build.mkv`: Additional presentation video.
	- `instructions.pdf`: Instructor details (partial).

## Requirements
- **Frontend:**
	- Node.js and npm for Expo project setup.
	- Expo CLI (`npm install -g expo-cli`).
	- React Native dependencies: `react-native-swiper`, `react-native-maps`, `react-native-chart-kit`, `lottie-react-native`, `@react-navigation/native`, `@react-navigation/native-stack`, `react-native-dropdown-picker`.
	- Expo Go app for mobile testing.
- **Backend:**
	- Google Cloud VPS (Ubuntu) with Apache, PHP, and MySQL installed.
	- MySQL database named `weather_app` with tables: Users, Locations, WeatherReports, Forecasts, Alerts, Feedback.
	- OpenWeatherMap API key for geolocation (`a34bb9d6a46791646f2426d3fada7996` in scripts).
- **Development/Testing:**
	- A code editor (VS Code).
	- Browser or PDF viewer for documentation.
	- Media player for `.mp4` and `.mkv` files.

## Setup and Installation
1. **Backend Setup:**
	- Deploy an Ubuntu server on Google Cloud VPS.
	- Install Apache, PHP, and MySQL:
		```bash
		sudo apt update
		sudo apt install apache2 php mysql-server php-mysql```
	- Create the weather_app database and tables (Users, Locations, WeatherReports, Forecasts, Alerts, Feedback).
	- Place PHP scripts (add_weather.php, search_weather.php, etc.) in the Apache web root ('/var/www/html').
	- Configure MySQL credentials in PHP scripts (root, password or update as needed).
	- Enable remote access for PHP scripts (update firewall and Apache settings).
2. Frontend Setup:
	- Clone the repository (if applicable):
		```bash
		git clone <repository-url>
		cd <repository-directory>```
	- Install Expo CLI:
		```bash
		npm install -g expo-cli```
	- Create Expo project:
		```bash
		npx create-expo-app weather-swiper-blank
		cd weather-swiper-blank```
	- Install dependencies:
		```bash
		npm install react-native-swiper react-native-maps react-native-chart-kit lottie-react-native @react-navigation/native @react-navigation/native-stack react-native-dropdown-picker```
	- Add provided frontend files (App.js, MainSwiper.js, etc.) to the project directory.
	- Update API endpoints in frontend files to match VPS IP ('http://34.123.143.201').
3. Running the App:
	- Start the Expo development server:
		```bash
		npx expo start```
	- Use Expo Go app to scan the QR code for mobile testing, or run in a simulator.
	- Ensure the VPS is running and accessible for backend API calls.
	
## How to Use
1. **Launch the App:**
	- Open Expo Go on a mobile device or use a simulator.
	- Scan the QR code from the Expo development server to load the app.
2. **User Authentication:**
	- On first launch, register a new account (RegisterScreen) or log in (LoginScreen) with existing credentials.
	- After login, access the main app via MainSwiper.
3. **App Features:**
	- **Add Weather:** Use AddScreen to submit city, temperature, and humidity data.
	- **Search Weather:** Enter a city name in SearchScreen to view matching weather reports.
	- **Display Data:** Select a database table in DisplayScreen to view its contents.
	- **Map View:** Enter a city in MapScreen to zoom to its location with a marker.
	- **Feedback:** Submit like/dislike feedback in FeedbackScreen.
	- **Chart:** View like/dislike statistics in a pie chart on ChartScreen (refresh to update).
4. **Navigation:**
	- Swipe between screens using custom dot/arrow indicators.
	- Use the logout button in the header to return to the login screen.
5. **View Outputs:**
	- Check the MySQL database (weather_app) for stored data.
	- Review generated feedback statistics or weather reports via ChartScreen or DisplayScreen.
	
## License
This project is for personal/educational use. Retain the copyright notice: "Thomas Hoerger - Copyright © 2025 SkyView Weather App Final Build".