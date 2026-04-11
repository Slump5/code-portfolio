# Finance Portfolio App

## Overview

This project is a full-stack financial portfolio management application developed as part of a **collaborative group project**. The system allows users to track stocks and cryptocurrencies, manage personal assets, and monitor portfolio performance in real time.

The application consists of a frontend built with HTML, CSS, and JavaScript, and a backend implemented using Flask with SQLite and MongoDB integration. It supports authentication, asset tracking, favorites management, real-time price updates, and interactive data visualization using external APIs such as Finnhub and CoinGecko.

## Features

- **User Authentication**
  - Secure login and signup system
  - Session handling using localStorage
  - Route protection and redirect logic

- **Portfolio Management**
  - Add, edit, and remove assets
  - Track quantity and purchase price
  - Automatic gain/loss calculations
  - Portfolio summary (total value, gains/losses, asset count)
  - Portfolio allocation chart

- **Favorites System**
  - Add/remove favorite assets
  - Dropdown asset selector
  - Mini charts with 24H / 7D toggle
  - Cached price history

- **Dashboard**
  - User welcome and account data
  - Total balance and gains/losses
  - Trending assets with charts
  - Community comments system (MongoDB)

- **Market Data Integration**
  - Stock data via Finnhub API
  - Crypto data via CoinGecko API
  - Auto-seeded trending assets
  - Smart caching system

- **UI / UX**
  - Responsive design
  - Dark mode toggle
  - Navbar with profile dropdown
  - Modal-based interactions
  - Chart.js visualizations

## File Structure

### Frontend (client)

- **pages/**
  - `index.html` – Landing page
  - `login.html` – Login page
  - `signup.html` – Registration page
  - `dashboard.html` – Dashboard
  - `portfolio.html` – Portfolio management
  - `favorites.html` – Favorites tracking
  - `profile.html` – User profile

- **scripts/**
  - `main.js` – Core frontend logic and API calls
  - `dark-mode.js` – Theme toggle functionality

- `styles.css` – Global styling

### Backend (server)

- `app.py` – Flask application and API endpoints

#### Database

- `assets.db` – SQLite database
- `script.sql` – Database schema

### Configuration / Misc

- `requirements.txt` – Python dependencies
- `ENV_TEMPLATE.txt` – Environment variables template
- `QUICKSTART.md` – Setup guide
- `.vscode/settings.json` – Deployment config

## Requirements

- Python 3.10+
- Flask and related libraries
- SQLite
- MongoDB
- Finnhub API key
- CoinGecko API (optional)

## Setup and Installation

1. Clone the repository:
   ```bash
   git clone <repository-url>
   cd <project-folder>
   ```

2. Install dependencies:
   ```bash
   cd server
   pip install -r requirements.txt
   ```

3. Create `.env` file in server folder:
   ```env
   FH_API_KEY=your_finnhub_key
   CG_API_KEY=optional
   MONGO_DB_URI=your_mongo_uri
   ```

4. Run the server:
   ```bash
   python app.py
   ```

5. Open in browser:
   `http://127.0.0.1:5000`

## How to Use

1. **Register a new account**
2. **Login** to access the dashboard
3. **Add assets** to your portfolio
4. **Track favorites** and view charts
5. **Monitor gains/losses** and trending assets
6. Use the **Profile page** to manage account and logout

## Project Notes

- Uses SQLite for structured data and MongoDB for comments
- Implements caching for price history
- Supports both stock and cryptocurrency assets
- Trending assets are auto-seeded and updated
- Portfolio values update dynamically

## My Contribution

### 11/12/2025 – Backend
- Implemented Login API endpoint in `app.py`

### 11/18/2025 – Authentication / Routing
- Added login/session protection to all pages
- Redirect logic for logged-in and logged-out users
- Prevented account creation while logged in

### Navigation / Layout
- Dynamic navbar behavior based on login state
- Added consistent Logout button across all pages
- Standardized navigation structure

### 11/19/2025 – Portfolio
- Built Add Asset modal
- Built Edit Asset modal (save/remove/cancel)
- Connected frontend to backend APIs
- Implemented dynamic portfolio table
- Added portfolio summary (value, gain/loss, count)
- Implemented pie chart visualization
- Added empty-state handling

### Favorites
- Replaced manual inputs with dropdown selector
- Implemented modal functionality
- Connected dropdown to API
- Fixed SQL query for price change rendering
- Cleaned up JavaScript logic

### 11/20/2025 – Enhancements
- Added 24H / 7D chart toggle
- Integrated mini charts
- Implemented percent change recalculation
- Synced chart colors with trends
- Added caching for charts
- Improved UI styling

## Future Improvements

- Implement password hashing for security
- Add real-time updates (WebSockets)
- Improve analytics and chart features
- Add transaction history tracking
- Deploy to cloud hosting
- Enhance UI/UX further

## License

This project is for personal and educational use only.  
Please retain the following copyright notice:

© 2024 G7 Finance. All rights reserved.