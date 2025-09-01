// Author: Thomas Hoerger
// Thomas Hoerger - Copyright © 2025 SkyView Weather App Final Build
// Solo Group 9
// Date: 4-24-2025
// Description: Reusable animated header with SkyView title and Lottie.

import React from 'react';
import { View, Text, StyleSheet } from 'react-native';
import LottieView from 'lottie-react-native';

export default function AnimatedHeader({ username, onLogout }) {
  return (
    <View style={styles.header}>
      {/* Sun animation at the top */}
      <LottieView
        source={require('../assets/animations/sun.json')}
        autoPlay
        loop
        style={styles.animation}
      />

      {/* Main app title */}
      <Text style={styles.title}>SkyView</Text>

      {/* Optional welcome message if user is logged in */}
      {username && (
        <Text style={styles.welcome}>Welcome, {username}</Text>
      )}
    </View>
  );
}

// Styles for header layout
const styles = StyleSheet.create({
  header: {
    alignItems: 'center',
    paddingTop: 20,
  },
  animation: {
    width: 100,
    height: 100,
  },
  title: {
    fontSize: 28,
    fontWeight: 'bold',
    color: '#007AFF',
    marginTop: -10,     // Moves title closer to the animation
    marginBottom: 8,
  },
  welcome: {
    fontSize: 16,
    color: '#444',
  },
});
