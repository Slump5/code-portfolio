// Author: Thomas Hoerger
// Thomas Hoerger - Copyright © 2025 SkyView Weather App First Build
// 4-17-2025
// Description: This screen displays a pie chart of feedback statistics using data retrieved from the backend.
// Users can refresh the chart to see updated feedback (likes/dislikes).

// Import React and hooks for component state and lifecycle
import React, { useState, useEffect } from 'react';

// Import core components from React Native
import { View, Text, Dimensions, StyleSheet, Alert, Button } from 'react-native';

// Import the PieChart component from the chart-kit library
import { PieChart } from 'react-native-chart-kit';

// Define the ChartScreen component
export default function ChartScreen() {
  // State to store formatted chart data
  const [chartData, setChartData] = useState([]);

  // Function to fetch and prepare feedback data from the server
  const loadChartData = () => {
    fetch('http://34.123.143.201/get_feedback_stats.php')
      .then((res) => res.json()) // Parse JSON response
      .then((data) => {
        // Convert the liked/disliked values to integers
        const liked = parseInt(data.liked);
        const disliked = parseInt(data.disliked);

        // If the response contains invalid values, show an error alert
        if (isNaN(liked) && isNaN(disliked)) {
          Alert.alert('Error', 'Invalid feedback data.');
          return;
        }

        // Format the data into an array for PieChart component
        const formatted = [
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
        ];

        // Update the state with the formatted chart data
        setChartData(formatted);
      })
      .catch((err) => {
        // Handle any network or parsing errors
        console.error('Chart fetch error:', err);
        Alert.alert('Error', 'Could not load chart data.');
      });
  };

  // useEffect runs once on mount to fetch the initial chart data
  useEffect(() => {
    loadChartData();
  }, []);

  // Render the layout
  return (
    <View style={styles.container}>
      {/* App title displayed at the top */}
      <Text style={styles.appTitle}>SkyView</Text>

      {/* Subtitle for the chart section */}
      <Text style={styles.title}>User Feedback</Text>

      {/* Button to manually refresh the chart */}
      <Button title="Refresh Chart" onPress={loadChartData} />

      {/* If chartData is available, show the PieChart. Otherwise, show loading message. */}
      {chartData.length > 0 ? (
        <PieChart
          data={chartData} // Data to display in the chart
          width={Dimensions.get('window').width - 20} // Chart width based on screen size
          height={220} // Chart height
          chartConfig={{
            backgroundColor: '#fff',
            backgroundGradientFrom: '#fff',
            backgroundGradientTo: '#fff',
            color: (opacity = 1) => `rgba(0, 0, 0, ${opacity})`, // Chart segment color
            labelColor: () => '#000', // Label color
          }}
          accessor="population" // Tells PieChart which key holds the numeric values
          backgroundColor="transparent"
          paddingLeft="15"
          absolute // Shows numeric values inside the chart
        />
      ) : (
        <Text style={styles.loading}>Loading chart data...</Text>
      )}
    </View>
  );
}

// Styles for the ChartScreen layout and elements
const styles = StyleSheet.create({
  // Main container for the screen
  container: {
    marginTop: 40,
    alignItems: 'center',
    paddingHorizontal: 10,
  },
  // App title style
  appTitle: {
    fontSize: 28,
    fontWeight: 'bold',
    color: '#007AFF', // iOS blue
    marginBottom: 10,
    textAlign: 'center',
  },
  // Subtitle/header for the chart
  title: {
    fontSize: 20,
    fontWeight: 'bold',
    marginBottom: 20,
  },
  // Style for the loading message
  loading: {
    fontStyle: 'italic',
    marginTop: 20,
    color: '#666',
  },
});




