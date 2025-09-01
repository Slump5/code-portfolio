// Author: Thomas Hoerger
// Thomas Hoerger - Copyright © 2025 SkyView Weather App Final Build
// Solo Group 9
// 4-23-2025
// Description: Displays user feedback as a pie chart using react-native-chart-kit.

import React, { useEffect, useState } from 'react';
import { View, Text, Dimensions, StyleSheet, Alert, Button } from 'react-native';
import { PieChart } from 'react-native-chart-kit';
import LottieView from 'lottie-react-native';

// Functional component to render the chart screen
export default function ChartScreen() {
  const [chartData, setChartData] = useState(null); // State to hold pie chart data

  // Function to fetch feedback stats from the backend
  const loadChartData = () => {
    fetch('http://34.123.143.201/get_feedback_stats.php') // Fetch data from PHP endpoint
      .then((res) => res.json()) // Parse JSON response
      .then((data) => {
        const liked = parseInt(data.liked);       // Parse liked count as integer
        const disliked = parseInt(data.disliked); // Parse disliked count as integer

        // Validate data
        if (isNaN(liked) || isNaN(disliked)) {
          Alert.alert('Error', 'Invalid feedback data');
          return;
        }

        // Set pie chart data
        setChartData([
          {
            name: 'Liked',
            population: liked,
            color: 'green',
            legendFontColor: '#000',
            legendFontSize: 14,
          },
          {
            name: 'Disliked',
            population: disliked,
            color: 'red',
            legendFontColor: '#000',
            legendFontSize: 14,
          },
        ]);
      })
      .catch((err) => {
        console.error('Chart fetch error:', err);
        Alert.alert('Error', 'Could not load feedback data');
      });
  };

  // Load chart data once when the component mounts
  useEffect(() => {
    loadChartData();
  }, []);

  return (
    <View style={styles.container}>
      {/* Lottie animation displayed above the chart */}
      <View style={styles.lottieWrapper}>
        <LottieView
          source={require('../assets/animations/sun.json')}
          autoPlay
          loop
          style={styles.lottie}
        />
      </View>

      {/* App title and screen title */}
      <Text style={styles.appTitle}>SkyView</Text>
      <Text style={styles.title}>User Feedback</Text>

      {/* Refresh button to reload chart data */}
      <View style={{ marginBottom: 20 }}>
        <Button title="Refresh Chart" onPress={loadChartData} />
      </View>

      {/* Display pie chart if data is available, else show loading message */}
      {chartData ? (
        <PieChart
          data={chartData}
          width={Dimensions.get('window').width - 20}
          height={220}
          chartConfig={{
            backgroundColor: '#fff',
            backgroundGradientFrom: '#fff',
            backgroundGradientTo: '#fff',
            color: (opacity = 1) => `rgba(0, 0, 0, ${opacity})`,
            labelColor: () => '#000',
          }}
          accessor="population"
          backgroundColor="transparent"
          paddingLeft="15"
          absolute
        />
      ) : (
        <Text style={styles.loading}>Loading chart...</Text>
      )}
    </View>
  );
}

// Styles for the chart screen layout and elements
const styles = StyleSheet.create({
  container: {
    marginTop: 40,
    alignItems: 'center',
    paddingHorizontal: 10,
  },
  lottieWrapper: {
    position: 'absolute',
    top: -160,
    zIndex: 1,
    width: '100%',
    alignItems: 'center',
  },
  lottie: {
    width: 100,
    height: 100,
  },
  appTitle: {
    fontSize: 28,
    fontWeight: 'bold',
    color: '#007AFF',
    marginBottom: 10,
    textAlign: 'center',
  },
  title: {
    fontSize: 20,
    fontWeight: 'bold',
    marginBottom: 10,
  },
  loading: {
    fontStyle: 'italic',
    color: '#555',
  },
});


