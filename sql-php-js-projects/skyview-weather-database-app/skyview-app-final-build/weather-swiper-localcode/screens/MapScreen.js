// Author: Thomas Hoerger
// Thomas Hoerger - Copyright © 2025 SkyView Weather App Final Build
// Solo Group 9
// 4-23-2025
// Description: Map screen with city-based zoom functionality using react-native-maps

import React, { useState } from 'react';
import { View, StyleSheet, TextInput, Button, Dimensions } from 'react-native';
import MapView, { Marker } from 'react-native-maps';

export default function MapScreen() {
  // Default city input
  const [city, setCity] = useState('Minneapolis');

  // Map region state (initial region centered on Minneapolis)
  const [region, setRegion] = useState({
    latitude: 44.9778,
    longitude: -93.2650,
    latitudeDelta: 0.2,
    longitudeDelta: 0.2,
  });

  // Fetch coordinates for city and update map view
  const handleZoom = async () => {
    try {
      const response = await fetch(`http://34.123.143.201/get_coords.php?city=${city}`);
      const data = await response.json();

      // If valid coordinates received, update the region
      if (data.latitude && data.longitude) {
        setRegion({
          latitude: parseFloat(data.latitude),
          longitude: parseFloat(data.longitude),
          latitudeDelta: 0.2,
          longitudeDelta: 0.2,
        });
      } else {
        alert('City not found.');
      }
    } catch (err) {
      alert('Failed to fetch coordinates.');
    }
  };

  return (
    <View style={styles.container}>
      {/* Fullscreen map */}
      <MapView
        style={styles.map}
        initialRegion={region}
        region={region}
      >
        {/* City marker */}
        <Marker
          coordinate={{ latitude: region.latitude, longitude: region.longitude }}
          title={city}
        />
      </MapView>

      {/* Input and zoom button overlay */}
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

// Styling for layout and map
const styles = StyleSheet.create({
  container: {
    flex: 1,
  },
  map: {
    width: Dimensions.get('window').width,
    height: Dimensions.get('window').height,
  },
  searchBar: {
    position: 'absolute',
    top: 40,
    left: 20,
    right: 20,
    flexDirection: 'row',
    backgroundColor: '#fff',
    borderRadius: 8,
    padding: 8,

    // iOS shadow
    shadowColor: '#000',
    shadowOffset: { width: 0, height: 2 },
    shadowOpacity: 0.3,
    shadowRadius: 3,

    // Android shadow
    elevation: 4,
  },
  input: {
    flex: 1,
    paddingHorizontal: 10,
  },
});


