// Author: Thomas Hoerger
// Thomas Hoerger - Copyright © 2025 SkyView Weather App First Build
// 4-17-2025
// Description: Entry point of the React Native app. It renders the main swiper navigation
// component that handles screen transitions between different views of the weather app.

// Import libraries that enable gesture handling across all screens
import 'react-native-gesture-handler'; // Needed for swipe and tap gestures in navigators

// Import Reanimated to support animations like swiping transitions and UI effects
import 'react-native-reanimated'; // Required for some React Native UI libraries (e.g., Swiper)

// Import core React library to create and render components
import React from 'react';

// Redundant import of gesture-handler (optional to remove if desired)
import 'react-native-gesture-handler';

// Import the main swipe-based navigation component you created
import MainSwiper from './MainSwiper';

// Root component of your application
export default function App() {
  // Render the MainSwiper, which handles screen navigation and layout
  return <MainSwiper />;
}
