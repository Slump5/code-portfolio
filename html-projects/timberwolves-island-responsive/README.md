# Timberwolves Island

## Overview
This project is a static fan website titled "Timberwolves Island," created by Thomas Hoerger to support the Minnesota Timberwolves NBA team and inform fans about its players and history. It utilizes HTML for structure, Bootstrap v3.3.7 for responsive layout and components, custom CSS for styling, and JavaScript for interactive elements like modals and dropdowns. The design features a navigation bar with dropdowns, player profiles, team history, and a contact modal, with a color scheme inspired by the Timberwolves (navy blues, greens, and grays).

## Features
- **Responsive Layout**: Uses Bootstrap's grid system and media queries for mobile-friendly design, unlike fixed layouts.
- **Multi-Page Structure**: Includes a home page and additional pages for team history and player profiles.
- **Custom Styling**: Incorporates team-themed colors (e.g., #0C2340 for body background, #78BE20 for articles), fonts from Google Fonts (e.g., 'Open Sans' and 'Roboto Slab'), and hover effects for thumbnails and buttons.
- **Player Information**: Detailed biographies and early life sections for Anthony Edwards, Karl-Anthony Towns, and Rudy Gobert.
- **Team Data**: Includes playoff history, top 10 players list, and personal goals from the creator.
- **Interactive Elements**: Bootstrap-powered navigation dropdown for players, contact modal, and button styles with hover states.
- **Semantic HTML**: Utilizes elements like `<nav>`, `<article>`, and `<footer>` for better accessibility and SEO.
- **Commented Code**: Custom CSS includes comments organized alphabetically by element/class, and HTML pages are structured for readability.

## File Structure
- **index.html**: Main homepage featuring top 10 Timberwolves players, personal goals, and playoff history.
- **about.html**: Team history overview and about the creator (interests in technology, basketball, and fitness).
- **ant.html**: Player profile for Anthony Edwards (early life, career highlights).
- **kat.html**: Player profile for Karl-Anthony Towns (early life, career highlights, awards).
- **rudy.html**: Player profile for Rudy Gobert (early life, career highlights, defensive awards).
- **bootstrap.css**: Full Bootstrap CSS stylesheet.
- **bootstrap.min.css**: Minified Bootstrap CSS.
- **bootstrap-theme.css**: Bootstrap theme CSS for gradients and shadows.
- **bootstrap-theme.min.css**: Minified Bootstrap theme CSS.
- **custom.css**: Custom stylesheet overriding Bootstrap with team-specific styles.
- **bootstrap.js**: Full Bootstrap JavaScript for components like modals and dropdowns.
- **bootstrap.min.js**: Minified Bootstrap JavaScript.
- **npm.js**: CommonJS loader for Bootstrap JavaScript modules.

## Requirements
- A modern web browser (Chrome, Firefox) to view the site.
- jQuery library (required for Bootstrap JavaScript; assume it's linked externally or locally).
- No server-side dependencies; the site is fully static and can be opened locally.
- Google Fonts API access (linked in HTML for 'Open Sans' and 'Roboto Slab').

## How to Run
1. Clone or download the repository:
   ```bash
   git clone <repository-url>
   cd <repository-directory>```
2. Open index.html (or any other .html file) in a web browser to view the site.

## Usage
- Navigate the site using the top navigation bar (Home, About, Players dropdown with links to individual profiles, Contact).
- The homepage displays top players, goals, and playoff history up to 2021-2022.
- About page provides team history and creator info.
- Player profiles offer biographical details sourced from public info (e.g., Wikipedia-style references).
- Contact modal allows emailing the creator.
- Note: Content is from 2023 and may be outdated as of 2025; the layout adjusts responsively but is optimized for desktop.

## License
This project is for personal and fan use. Retain the copyright notice: "Thomas Hoerger - Copyright © 2023 Timberwolves Island".