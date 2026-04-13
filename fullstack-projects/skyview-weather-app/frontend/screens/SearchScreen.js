// Author: Thomas Hoerger
// Thomas Hoerger - Copyright © 2025 SkyView Weather App Final Build
// Solo Group 9
// 4-24-2025
// Description: Search screen. Lets user search a city and retrieve data for it.

import React, { useState } from 'react';
import {
  View,
  Text,
  TextInput,
  Button,
  FlatList,
  StyleSheet,
  TouchableWithoutFeedback,
  Keyboard,
} from 'react-native';
import LottieView from 'lottie-react-native';

const SearchScreen = () => {
  const [searchTerm, setSearchTerm] = useState('');
  const [results, setResults] = useState([]);

  // Fetch weather data from the server for a given city
  const handleSearch = async () => {
    if (!searchTerm.trim()) {
      alert('Please enter a city name.');
      return;
    }

    try {
      const response = await fetch(`http://34.123.143.201/search_weather.php?city=${searchTerm}`);
      const data = await response.json();
      setResults(data); // store result in state
    } catch (error) {
      console.error('Error fetching weather data:', error);
      setResults([]); // clear results if error
    }
  };

  return (
    <TouchableWithoutFeedback onPress={Keyboard.dismiss}>
      <View style={styles.container}>
        {/* Floating sun animation */}
        <View style={styles.lottieWrapper}>
          <LottieView
            source={require('../assets/animations/sun.json')}
            autoPlay
            loop
            style={styles.lottie}
          />
        </View>

        {/* Title and input */}
        <View style={styles.centeredContent}>
          <Text style={styles.appTitle}>SkyView</Text>
          <Text style={styles.title}>Search Weather</Text>

          <TextInput
            style={styles.input}
            placeholder="Enter city name"
            value={searchTerm}
            onChangeText={setSearchTerm}
          />
          <Button title="Search" onPress={handleSearch} />
        </View>

        {/* Results output */}
        <View style={styles.resultsSection}>
          {results.length > 0 ? (
            <FlatList
              data={results}
              keyExtractor={(item, index) => index.toString()}
              keyboardShouldPersistTaps="handled"
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
            searchTerm !== '' && (
              <Text style={styles.noMatch}>No match found for “{searchTerm}”</Text>
            )
          )}
        </View>
      </View>
    </TouchableWithoutFeedback>
  );
};

const styles = StyleSheet.create({
  container: {
    flex: 1,
    padding: 16,
    justifyContent: 'center',
    alignItems: 'center',
    backgroundColor: '#fff',
  },
  lottieWrapper: {
    position: 'absolute',
    top: 40,
    zIndex: 1,
    alignItems: 'center',
    width: '100%',
  },
  lottie: {
    width: 100,
    height: 100,
  },
  centeredContent: {
    alignItems: 'center',
    justifyContent: 'center',
    marginBottom: 20,
    width: '100%',
    maxWidth: 400,
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
    width: 180, // fixed input width
  },
  resultsSection: {
    width: '100%',
    maxWidth: 400,
    flexShrink: 1,
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

export default SearchScreen;




