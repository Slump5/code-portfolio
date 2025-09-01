// Author: Thomas Hoerger
// Thomas Hoerger - Copyright © 2025 SkyView Weather App Final Build
// Solo Group 9
// 4-24-2025
// Description: Swiper navigation for SkyView app. Includes welcome/logout header on all screens except MapScreen. DisplayScreen added before Map.

import React from 'react';
import { View, Text, StyleSheet, TouchableOpacity, SafeAreaView } from 'react-native';
import Swiper from 'react-native-swiper';

// Screens
import AddScreen from './screens/AddScreen';
import SearchScreen from './screens/SearchScreen';
import DisplayScreen from './screens/DisplayScreen';  // NEW screen!
import MapScreen from './screens/MapScreen';
import FeedbackScreen from './screens/FeedbackScreen';
import ChartScreen from './screens/ChartScreen';

export default function MainSwiper({ username, onLogout }) {
  // Wrapper component to display header unless suppressed
  const ScreenWrapper = ({ children, showHeader = true }) => (
    <SafeAreaView style={styles.safe}>
      {showHeader && (
        <View style={styles.header}>
          <Text style={styles.welcome}>Welcome, {username}</Text>
          <TouchableOpacity onPress={onLogout}>
            <Text style={styles.logout}>Logout</Text>
          </TouchableOpacity>
        </View>
      )}
      <View style={styles.content}>
        {children}
      </View>
    </SafeAreaView>
  );

  return (
    <Swiper
      loop={false}
      showsPagination={true}
      showsButtons={true}
      scrollEnabled={true}
      scrollAnimationDuration={600}
      dotStyle={{ backgroundColor: '#bbb', width: 8, height: 8, borderRadius: 4 }}
      activeDotStyle={{ backgroundColor: '#007AFF', width: 10, height: 10, borderRadius: 5 }}
      nextButton={<Text style={styles.arrow}>›</Text>}
      prevButton={<Text style={styles.arrow}>‹</Text>}
    >
      {/* Each screen wrapped to include consistent header layout */}
      <View style={styles.slide}>
        <ScreenWrapper><AddScreen /></ScreenWrapper>
      </View>

      <View style={styles.slide}>
        <ScreenWrapper><SearchScreen /></ScreenWrapper>
      </View>

      <View style={styles.slide}>
        <ScreenWrapper><DisplayScreen /></ScreenWrapper>
      </View>

      <View style={{ flex: 1 }}>
        <MapScreen />
      </View>

      <View style={styles.slide}>
        <ScreenWrapper><FeedbackScreen /></ScreenWrapper>
      </View>

      <View style={styles.slide}>
        <ScreenWrapper><ChartScreen /></ScreenWrapper>
      </View>
    </Swiper>
  );
}

const styles = StyleSheet.create({
  safe: {
    flex: 1,
    backgroundColor: '#fff',
  },
  content: {
    flex: 1,
    justifyContent: 'center',
    alignItems: 'center',
    paddingHorizontal: 15,
  },
  slide: {
    flex: 1,
    backgroundColor: '#fff',
  },
  header: {
    paddingTop: 10,
    paddingBottom: 10,
    paddingHorizontal: 20,
    backgroundColor: '#f2f2f2',
    flexDirection: 'row',
    justifyContent: 'space-between',
    alignItems: 'center',
  },
  welcome: {
    fontSize: 16,
    color: '#333',
    fontWeight: '500',
  },
  logout: {
    color: '#007AFF',
    fontWeight: 'bold',
    fontSize: 16,
  },
  arrow: {
    color: '#007AFF',
    fontSize: 36,
    fontWeight: 'bold',
    paddingHorizontal: 20,
  },
});


