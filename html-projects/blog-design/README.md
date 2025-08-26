# Static Blog Website Design

## Overview
This project is a static blog website titled "Web Stuff," created by Thomas Hoerger as part of a web design assignment. It utilizes HTML for structure, CSS for fixed styling, and includes a JavaScript script for image handling. The design is based on a provided wireframe with a fixed pixel-based layout, featuring a header with logo, navigation, a feature section, a blog area with two columns, and a footer.

## Features
- **Static Layout**: Uses fixed pixel measurements for widths, heights, margins, and padding to maintain a consistent design across screen sizes.
- **Multi-Page Structure**: Includes an index page and additional pages (page2 to page5) that may represent variations or development stages of the layout.
- **Custom Styling**: Incorporates colors, fonts from Google Fonts (e.g., 'Open Sans' and 'Roboto Slab'), and background images for visual appeal.
- **Image Handling**: JavaScript script (imgSizer.js) for managing images, including IE-specific alpha transparency support.
- **Semantic HTML**: Utilizes elements like `<header>`, `<nav>`, `<article>`, `<figure>`, and `<footer>` for better accessibility and SEO.
- **Commented Code**: CSS includes comments for clarity (e.g., pixel measurements), and HTML/CSS are organized with closing tag comments for readability.

## File Structure
- **index.html**: The main homepage with the full blog layout.
- **page2.html**, **page3.html**, **page4.html**, **page5.html**: Additional pages with similar structures, possibly for testing or extensions.
- **style.css**: External stylesheet containing all CSS rules, organized alphabetically by section and class.
- **imgSizer.js**: JavaScript file for collating and resizing images to maintain proportions based on original dimensions.
- **Project2_Requirements.pdf**: Project specification document outlining requirements for the static design.

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
2. Open index.html (or any other .html file) in a web browser to view the site.

## Usage
- Navigate the site using the links in the navigation bar (Link 1 to Link 5).
- The feature section displays a prominent image with caption and paragraph text.
- The blog section is divided into left and right columns for articles, with headings and paragraphs.
- Footer includes copyright information.
- Note: The layout is designed for a specific resolution; resizing the browser may not adjust content proportionally.

## License
This project is for educational purposes. Retain the copyright notice: "Copyright Thomas Hoerger © 2023".