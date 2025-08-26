# Minnesota Timberwolves Fan Page Responsive

## Overview
This project is a responsive fan website titled "Minnesota Timberwolves Fan Page," created by Thomas Hoerger as part of a web design assignment focused on responsive design. It utilizes HTML for structure, CSS with media queries for adaptive styling across devices (mobile, tablet, desktop), and includes a JavaScript script for image handling. The design features a header with logo, navigation, main content sections for best players and goals, a gallery with images, and a footer. It incorporates flexible grids, tiled background images, and media queries to ensure compatibility with various screen sizes.

## Features
- **Responsive Layout:** Uses media queries to adjust styles for mobile (default), tablet (min-width: 45em), and desktop (min-width: 80em) views, including font sizes, margins, and grid displays.
- **Flexible Design:** Employs relative units, flexible images, and background images to simulate faux columns and maintain proportionality.
- **Multi-Section Structure:** Includes sections for best players, team goals, and a gallery with player images.
- **Custom Styling:** Incorporates Timberwolves team colors in hex, Google Fonts (e.g., 'Open Sans' and 'Roboto Slab'), and background images for visual appeal.
- **Image Handling:** JavaScript script (imgSizer.js) for resizing images while maintaining proportions, with IE-specific alpha transparency support.
- **Semantic HTML:** Utilizes elements like <header>, <nav>, <article>, <figure>, and <footer> for better accessibility and SEO.
- **Commented Code:** CSS includes organization in alphabetical order and media query specifics for clarity.

## File Structure
- **index.html:** The main homepage with sections for best players, goals, and gallery.
- **default.css:** Base stylesheet for mobile devices, including default styles for layout, fonts, and backgrounds.
- **screen_min_45em.css:** Media query stylesheet for tablet devices (min-width: 45em).
- **screen_min_80em.css:** Media query stylesheet for desktop devices (min-width: 80em).
- **imgSizer.js:** JavaScript file for collating and resizing images to maintain proportions.
- **Project3.pdf:** Project specification document outlining requirements for the responsive design.

## Requirements
- A modern web browser (Chrome, Firefox) to view the site.
- No server-side dependencies; the site is fully static and can be opened locally.
- Google Fonts API access (linked in HTML for 'Open Sans' and 'Roboto Slab').
- Note: The imgSizer.js script references a spacer image path ("/path/to/your/spacer.gif") which may need updating for production.

## How to Run
1. Clone or download the repository:
   ```bash
   git clone <repository-url>
   cd <repository-directory>```
2. Open index.html in a web browser to view the site.

## Usage
- Navigate the site using the links in the navigation bar (currently only "Home").
- The main content displays lists of best players and team goals.
- The gallery section shows player images with a basketball court background.
- Resize the browser window to see responsive changes: mobile view by default, tablet adjustments at wider screens, and desktop grid layout at larger sizes.
- Note: The layout adapts to screen size; test on different devices or use browser developer tools to emulate.

## License
This project is for personal and fan use. Retain the copyright notice: "Copyright Thomas Hoerger © 2023- Minnesota Timberwolves Fan Page".