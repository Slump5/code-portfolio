# SkyView Weather App First Build

## Overview
This is a full-stack mobile weather tracking application built with React Native and Expo for the frontend, PHP for the backend APIs, and MySQL for data storage. The app, named SkyView, allows users to add weather reports for cities, search and view weather data, display city locations on an interactive map (with fallback to OpenWeatherMap API), submit feedback (like/dislike), and view feedback statistics in a pie chart. It features swipe-based navigation between screens for a user-friendly experience. The backend is hosted on a Google Cloud VPS running Ubuntu, Apache, PHP, and MySQL. The project includes setup documentation, a PowerPoint presentation, video demos, and fulfills requirements for a software development project (database integration, API usage, responsive UI). It supports real-time data interactions and is designed for both mobile (via Expo Go) and desktop views. The app was made entirely by me as part of a solo group (group 9).

## Features
- **Swipe Navigation:** Uses react-native-swiper for seamless transitions between 5 screens: Add Weather, Search Weather, Map View, Feedback, and Chart.
- **Add Weather Reports:** Users submit city, temperature, and humidity via a form; data is inserted into the MySQL database, with automatic city coordinate fetching from OpenWeatherMap if needed.
- **Search Weather:** Retrieves and displays weather reports by city, showing temperature, humidity, condition, wind speed, and report time in a FlatList.
- **Interactive Map:** Zooms to city coordinates on a map using react-native-maps; fetches coords from database or OpenWeatherMap API.
- **Feedback System:** Users submit like/dislike feedback, stored in the database.
- **Feedback Chart:** Displays a pie chart of likes vs. dislikes using react-native-chart-kit, with a refresh button for live updates.
- **Database Integration:** MySQL with tables for Users, Locations, WeatherReports, Forecasts, Alerts, and Feedback; PHP scripts handle CRUD operations.
- **API Fallbacks:** Uses OpenWeatherMap Geo API for coordinates if not in the database.
- **Responsive Design:** UI scales for mobile and laptop views; custom pagination dots and arrows in swiper.
- **Documentation and Demos:** Includes step-by-step implementation docs (PDF), PowerPoint presentation, and video files for demo and presentation.
- **Error Handling:** Alerts for failed submissions, invalid data, or network issues; debugging enabled in PHP scripts.

## File Structure
- **App.js:** Entry point for the React Native app; renders the main swiper navigation.
- **index.js:** Registers the root component with Expo for proper environment setup.
- **MainSwiper.js:** Controls swipe-based navigation between app screens with custom dots and arrows.
- **screens/AddScreen.js:** Form screen for submitting new weather reports.
- **screens/SearchScreen.js:** Screen for searching and displaying weather by city using FlatList.
- **screens/MapScreen.js:** Interactive map screen with city search and zoom using react-native-maps.
- **screens/FeedbackScreen.js:** UI for submitting like/dislike feedback.
- **screens/ChartScreen.js:** Displays pie chart of feedback stats with refresh functionality.
- **add_weather.php:** PHP script to insert weather reports; adds new locations if needed with OpenWeatherMap coords.
- **search_weather.php:** PHP script to retrieve weather reports by city via SQL join.
- **get_coords.php:** PHP script to fetch city coordinates from DB or OpenWeatherMap API.
- **submit_feedback.php:** PHP script to store user feedback in the database.
- **get_feedback_stats.php:** PHP script to return aggregated likes/dislikes for charting.
- **documentation-skyview-app-first-build.pdf:** Step-by-step implementation guide (26 pages, truncated in upload).
- **powerpoint-skyview-app-first-build.pptx:** Presentation slides detailing setup, features, and summary (includes image placeholders like image1.png to image32.PNG).
- **instructions.pdf:** Project instructions document (10 pages, truncated; covers documentation, submission, and demo requirements).
- **presentation-skyview-app-first-build.mkv:** Video file for project presentation.
- **skyview-app-first-build-demo.MP4:** Short video demo (3-5 minutes) of the app in action.

## Requirements
- **Frontend:** Node.js (v18+), Expo CLI (install via `npm install -g expo-cli`), React Native libraries (react-native-swiper, react-native-maps, react-native-chart-kit).
- **Backend:** PHP 7+, MySQL 8+, Apache server; OpenWeatherMap API key (hardcoded in scripts as 'a34bb9d6a46791646f2426d3fada7996').
- **Hosting:** Google Cloud VPS or similar with Ubuntu; remote MySQL access enabled.
- **Development Tools:** Expo Go app for mobile testing (iOS/Android); web browser for desktop view.
- **Database Setup:** Create 'weather_app' database with tables: Users, Locations, WeatherReports, Forecasts, Alerts, Feedback.
- **No Additional Installs Needed:** All libraries are imported in code; assume standard Expo environment.
- **Optional:** Video player for .mkv and .MP4 files; PDF viewer for docs; PowerPoint viewer for .pptx.

## Compilation and Running
1. Clone the repository (if applicable):
	```bash
	git clone <repository-url>
	cd <repository-directory>```
2. Install dependencies (in the Expo project directory):
	```bash
	npm install```
	- Ensure react-native-swiper, react-native-maps, react-native-chart-kit are installed via npm if not in package.json.
3. Set up the backend:
	- Deploy Ubuntu on Google Cloud VPS.
	- Install Apache, PHP, MySQL: sudo apt update && sudo apt install apache2 php mysql-server libapache2-mod-php php-mysql.
	- Create MySQL database and tables as per documentation.
	- Upload PHP scripts to VPS ('/var/www/html/') and enable remote access.
	- Replace IP in frontend fetches ('http://34.123.143.201/') with your VPS IP.
4. Run the Expo app:
	- Start the development server:
		```bash
		npx expo start```
	- Scan the QR code with Expo Go app on mobile, or press 'w' for web view in browser.
5. For production: Build with npx expo build (requires Expo account).

## How to Use
1. Ensure backend VPS is running with MySQL database populated (add initial locations via PHPMyAdmin).
2. Start the Expo app as described above.
3. Swipe between screens:
	- **Add Screen:** Enter city, temperature, humidity; submit to add to DB.
	- **Search Screen:** Enter city; view results in list (temperature, humidity).
	- **Map Screen:** Enter city; zoom to location on map (marker shown).
	- **Feedback Screen:** Select like/dislike; submit (shows thank you message).
	- **Chart Screen:** View pie chart of feedback; refresh for updates.
4. Test with sample data: Add reports for cities like "Minneapolis"; search and map them.
5. View docs: Open documentation-skyview-app-first-build.pdf for steps; play demo.MP4 for app walkthrough; view .pptx for presentation.
6. Interactive Testing: Use Expo Go to scan QR; ensure internet for API calls.
7. Troubleshooting: Check console for errors; enable PHP error reporting as in scripts.

## License
This project is for personal use. Retain the copyright notice: "Thomas Hoerger - Copyright © 2025 SkyView Weather App First Build".