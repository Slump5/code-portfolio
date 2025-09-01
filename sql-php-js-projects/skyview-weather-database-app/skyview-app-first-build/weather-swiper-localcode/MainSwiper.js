// Author: Thomas Hoerger
// Thomas Hoerger - Copyright © 2025 SkyView Weather App First Build
// 4-17-2025
// Description: Main component that controls swipe-based navigation between app screens.
// Each screen is displayed as a slide in the swiper with pagination and navigation arrows.

// Import React to use JSX and create functional components
import React from 'react';

// Import Swiper for swipe-based navigation between screens
import Swiper from 'react-native-swiper';

// Import core React Native components
import { View, StyleSheet, Text } from 'react-native';

// Import each screen component of your app
import AddScreen from './screens/AddScreen';
import SearchScreen from './screens/SearchScreen';
import MapScreen from './screens/MapScreen';
import FeedbackScreen from './screens/FeedbackScreen';
import ChartScreen from './screens/ChartScreen';

// Main functional component to control the swipe navigation
const MainSwiper = () => {
  return (
    <Swiper
      // Disable infinite loop – swipe stops at the first and last screens
      loop={false}

      // Show pagination dots (● ● ●) at the bottom of the swiper
      showsPagination={true}

      // Show navigation arrows (< >) on the left and right
      showsButtons={true}

      // Allow users to swipe between screens manually
      scrollEnabled={true}

      // Duration (ms) for screen transition animation
      scrollAnimationDuration={600}

      // Style for inactive pagination dots
      dotStyle={{ backgroundColor: '#bbb', width: 8, height: 8, borderRadius: 4 }}

      // Style for active (selected) pagination dot
      activeDotStyle={{ backgroundColor: '#007AFF', width: 10, height: 10, borderRadius: 5 }}

      // Customize the "Next" button with a right arrow ›
      nextButton={<Text style={styles.arrow}>›</Text>}

      // Customize the "Previous" button with a left arrow ‹
      prevButton={<Text style={styles.arrow}>‹</Text>}
    >
      {/* Each screen is wrapped in a View styled as a swiper "slide" */}
      <View style={styles.slide}><AddScreen /></View>
      <View style={styles.slide}><SearchScreen /></View>
      <View style={styles.slide}><MapScreen /></View>
      <View style={styles.slide}><FeedbackScreen /></View>
      <View style={styles.slide}><ChartScreen /></View>
    </Swiper>
  );
};

// Styles used for each swiper slide and arrow buttons
const styles = StyleSheet.create({
  // Style for each screen container (slide)
  slide: {
    flex: 1,                      // Fill the screen
    paddingHorizontal: 15,        // Add horizontal padding on left and right
    backgroundColor: '#fff',      // White background for a clean look
    justifyContent: 'center',     // Center content vertically
    alignItems: 'center',         // Center content horizontally
  },
  // Style for left/right arrow buttons
  arrow: {
    color: '#007AFF',             // iOS-style blue color
    fontSize: 36,                 // Large arrow icon
    fontWeight: 'bold',          // Bold for visibility
    paddingHorizontal: 20,        // Padding around the arrows
  },
});

// Export this swiper component so it can be used in App.js
export default MainSwiper;
