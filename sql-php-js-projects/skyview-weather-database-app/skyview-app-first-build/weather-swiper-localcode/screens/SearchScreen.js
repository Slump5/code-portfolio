// Author: Thomas Hoerger
// Thomas Hoerger - Copyright © 2025 SkyView Weather App First Build
// 4-17-2025
// Description: This screen lets users search for weather reports by city name.
// It retrieves and displays weather information like temperature, humidity, condition, and wind speed.

// Import necessary React and React Native components
import React, { useState } from 'react';
import {
  View,
  Text,
  TextInput,
  Button,
  FlatList,
  StyleSheet,
  SafeAreaView,
  TouchableWithoutFeedback,
  Keyboard,
} from 'react-native';

// Main functional component for the search screen
const SearchScreen = () => {
  // State to hold the user's search input
  const [searchTerm, setSearchTerm] = useState('');
  // State to store the search results from the API
  const [results, setResults] = useState([]);

  // Function to fetch weather data based on the user's input
  const handleSearch = async () => {
    try {
      // Make a GET request to the PHP API on the VPS
      const response = await fetch(`http://34.123.143.201/search_weather.php?city=${searchTerm}`);
      const data = await response.json(); // Parse JSON response
      setResults(data); // Update state with returned weather records
    } catch (error) {
      console.error('Error fetching weather data:', error);
      setResults([]); // Reset results on error
    }
  };

  return (
    // SafeAreaView ensures UI stays inside safe boundaries (e.g., notch or status bar)
    <SafeAreaView style={styles.safeArea}>
      {/* Dismiss the keyboard when the user taps outside the input */}
      <TouchableWithoutFeedback onPress={Keyboard.dismiss}>
        <View style={styles.container}>
          
          {/* Centered content: title, input, and search button */}
          <View style={styles.centeredContent}>
            <Text style={styles.appTitle}>SkyView</Text>
            <Text style={styles.title}>Search Weather</Text>

            {/* Input box for entering a city name */}
            <TextInput
              style={styles.input}
              placeholder="Enter city name"
              value={searchTerm}
              onChangeText={setSearchTerm}
            />

            {/* Button to trigger the search */}
            <Button title="Search" onPress={handleSearch} />
          </View>

          {/* Section to display search results below the input */}
          <View style={styles.resultsSection}>
            {results.length > 0 ? (
              // If results are returned, show them using a FlatList
              <FlatList
                data={results}
                keyExtractor={(item, index) => index.toString()}
                renderItem={({ item }) => (
                  <View style={styles.resultBox}>
                    <Text style={styles.city}>{item.City}</Text>
                    <Text>{item.temperature}°F | {item.humidity}% Humidity</Text>
                    <Text>{item.weather_condition} | Wind: {item.wind_speed} mph</Text>
                    <Text>{item.report_time}</Text>
                  </View>
                )}
              />
            ) : (
              // If no results and a search term exists, show a message
              searchTerm !== '' && (
                <Text style={styles.noMatch}>No match found for “{searchTerm}”</Text>
              )
            )}
          </View>
        </View>
      </TouchableWithoutFeedback>
    </SafeAreaView>
  );
};

// StyleSheet for the layout and visual styling
const styles = StyleSheet.create({
  safeArea: {
    flex: 1,
    backgroundColor: '#fff', // white background
  },
  container: {
    flex: 1,
    padding: 16,
    justifyContent: 'center', // centers vertically
    alignItems: 'center',     // centers horizontally
  },
  centeredContent: {
    alignItems: 'center',
    justifyContent: 'center',
    marginBottom: 20,
    width: '100%',
    maxWidth: 400, // prevent stretching too far on large screens
  },
  appTitle: {
    fontSize: 28,
    fontWeight: 'bold',
    color: '#007AFF',
    marginBottom: 10,
    textAlign: 'center',
  },
  title: {
    fontSize: 22,
    fontWeight: 'bold',
    marginBottom: 12,
    textAlign: 'center',
  },
  input: {
    borderWidth: 1,
    borderColor: '#aaa',
    padding: 10,
    marginBottom: 10,
    borderRadius: 6,
    width: '100%',
  },
  resultsSection: {
    width: '100%',
    maxWidth: 400,
    flexShrink: 1, // allows shrinking if there's not enough space
  },
  resultBox: {
    backgroundColor: '#f0f0f0',
    padding: 10,
    borderRadius: 6,
    marginBottom: 12,
  },
  city: {
    fontSize: 18,
    fontWeight: 'bold',
  },
  noMatch: {
    marginTop: 20,
    fontStyle: 'italic',
    color: 'gray',
    textAlign: 'center',
  },
});

// Export the component so it can be used in the app
export default SearchScreen;



