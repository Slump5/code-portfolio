/*
  G7 Finance Database Site
  © 2024 G7 Finance. All rights reserved.
*/

// Dark Mode Toggle Functionality
(function () {
	// Check for saved theme preference or default to light mode
	const currentTheme = localStorage.getItem('theme') || 'light';
	document.documentElement.setAttribute('data-theme', currentTheme);

	// Function to toggle theme
	function toggleTheme() {
		const currentTheme = document.documentElement.getAttribute('data-theme');
		const newTheme = currentTheme === 'dark' ? 'light' : 'dark';
		document.documentElement.setAttribute('data-theme', newTheme);
		localStorage.setItem('theme', newTheme);
		updateThemeIcon(newTheme);
	}

	// Function to update theme icon
	function updateThemeIcon(theme) {
		const themeToggles = document.querySelectorAll('.theme-toggle');
		themeToggles.forEach((toggle) => {
			const icon = toggle.querySelector('.theme-icon');
			if (icon) {
				icon.textContent = theme === 'dark' ? '☀️' : '🌙';
			}
		});
	}

	// Initialize theme icon on page load
	document.addEventListener('DOMContentLoaded', function () {
		const currentTheme = document.documentElement.getAttribute('data-theme');
		updateThemeIcon(currentTheme);

		// Add event listeners to all theme toggle buttons
		const themeToggles = document.querySelectorAll('.theme-toggle');
		themeToggles.forEach((toggle) => {
			toggle.addEventListener('click', toggleTheme);
		});
	});
})();
