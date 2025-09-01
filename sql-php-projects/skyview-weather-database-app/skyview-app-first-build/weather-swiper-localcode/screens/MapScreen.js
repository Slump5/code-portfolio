// Author: Thomas Hoerger
// Thomas Hoerger - Copyright © 2025 SkyView Weather App First Build
// 4-17-2025
// Description: This screen displays a map and allows users to search for a city. 
// The map zooms to the selected city using coordinates from the backend or the OpenWeatherMap API.


// Import React and hooks to manage component state
import React, { useState } from 'react';

// Import necessary UI and dimension tools from React Native
import { View, StyleSheet, TextInput, Button, Dimensions } from 'react-native';

// Import MapView and Marker components from the react-native-maps library
import MapView, { Marker } from 'react-native-maps';

// Main functional component for the Map screen
export default function MapScreen() {
  // State variable for the city name input (default is "Minneapolis")
  const [city, setCity] = useState('Minneapolis');

  // State for the map region, including coordinates and zoom level (delta)
  const [region, setRegion] = useState({
    latitude: 44.9778,          // Default latitude for Minneapolis
    longitude: -93.2650,        // Default longitude for Minneapolis
    latitudeDelta: 0.2,         // Zoom level vertically
    longitudeDelta: 0.2,        // Zoom level horizontally
  });

  // Function to fetch coordinates from the server and update the map region
  const handleZoom = async () => {
    try {
      // Call your PHP backend with the city name to get latitude and longitude
      const response = await fetch(`http://34.123.143.201/get_coords.php?city=${city}`);
      const data = await response.json();

      // If valid coordinates are returned, update the region to center the map
      if (data.latitude && data.longitude) {
        setRegion({
          latitude: parseFloat(data.latitude),
          longitude: parseFloat(data.longitude),
          latitudeDelta: 0.2,
          longitudeDelta: 0.2,
        });
      } else {
        // Show an alert if the city is not found in the backend
        alert('City not found.');
      }
    } catch (err) {
      // Handle any fetch or network errors
      alert('Failed to fetch coordinates.');
    }
  };

  // Render the full map view along with the search input and button
  return (
    <View style={styles.container}>
      {/* Map component showing the region centered on the selected city */}
      <MapView
        style={styles.map}
        initialRegion={region}  // Initial region to show when the screen loads
        region={region}         // Updated region after zooming
      >
        {/* Marker showing the location of the selected city */}
        <Marker coordinate={{ latitude: region.latitude, longitude: region.longitude }} title={city} />
      </MapView>

      {/* Search input and zoom button positioned over the map */}
      <View style={styles.searchBar}>
        <TextInput
          style={styles.input}
          placeholder="Enter city name"
          value={city}
          onChangeText={setCity}
        />
        <Button title="Zoom" onPress={handleZoom} />
      </View>
    </View>
  );
}

// Styles used in the Map screen
const styles = StyleSheet.create({
  // Container fills the entire screen
  container: {
    flex: 1,
  },

  // Fullscreen map using window dimensions
  map: {
    width: Dimensions.get('window').width,
    height: Dimensions.get('window').height,
  },

  // Search bar positioned at the top of the map
  searchBar: {
    position: 'absolute',
    top: 40,
    left: 20,
    right: 20,
    flexDirection: 'row',
    backgroundColor: '#fff',
    borderRadius: 8,
    padding: 8,

    // Shadow for iOS
    shadowColor: '#000',
    shadowOffset: { width: 0, height: 2 },
    shadowOpacity: 0.3,
    shadowRadius: 3,

    // Elevation for Android
    elevation: 4,
  },

  // Style for the text input field
  input: {
    flex: 1,                   // Take up available space
    paddingHorizontal: 10,     // Horizontal padding inside the input
  },
});

