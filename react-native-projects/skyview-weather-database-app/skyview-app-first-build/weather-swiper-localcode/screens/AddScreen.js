// Author: Thomas Hoerger
// Thomas Hoerger - Copyright © 2025 SkyView Weather App First Build
// 4-17-2025
// Description: This screen allows users to submit new weather reports by entering a city, temperature, and humidity. 
// It sends the data to the backend and updates the database.

// Import React and useState for handling form state
import React, { useState } from 'react';

// Import necessary UI components from React Native
import { View, Text, TextInput, Button, StyleSheet } from 'react-native';

// Define the AddScreen functional component
export default function AddScreen() {
  // State variables to store user input for city, temperature, and humidity
  const [city, setCity] = useState('');
  const [temperature, setTemp] = useState('');
  const [humidity, setHumidity] = useState('');

  // Function that gets called when the Submit button is pressed
  const handleSubmit = async () => {
    try {
      // Send the input data to the PHP backend using a POST request
      await fetch('http://34.123.143.201/add_weather.php', {
        method: 'POST',
        headers: { 'Content-Type': 'application/json' }, // Set request headers
        body: JSON.stringify({ city, temperature, humidity }), // Convert form data to JSON
      });

      // Alert the user of success
      alert('✅ Weather report added!');

      // Clear input fields after submission
      setCity('');
      setTemp('');
      setHumidity('');
    } catch (err) {
      // Show an error message if the request fails
      alert("⚠️ Failed to add weather. Check connection.");
    }
  };

  // Return the UI layout for the screen
  return (
    <View style={styles.container}>
      {/* App name displayed at the top */}
      <Text style={styles.appTitle}>SkyView</Text>

      {/* Screen title below app name */}
      <Text style={styles.header}>Add Weather Report</Text>

      {/* Input for City Name */}
      <TextInput
        placeholder="City"
        value={city}
        onChangeText={setCity}
        style={styles.input}
      />

      {/* Input for Temperature */}
      <TextInput
        placeholder="Temperature (°F)"
        value={temperature}
        onChangeText={setTemp}
        keyboardType="numeric" // Brings up numeric keypad
        style={styles.input}
      />

      {/* Input for Humidity */}
      <TextInput
        placeholder="Humidity (%)"
        value={humidity}
        onChangeText={setHumidity}
        keyboardType="numeric"
        style={styles.input}
      />

      {/* Submit button that triggers handleSubmit */}
      <Button title="Submit" onPress={handleSubmit} />
    </View>
  );
}

// Styles for layout and UI design
const styles = StyleSheet.create({
  container: {
    flex: 1,                  // Fills the screen vertically
    width: '100%',            // Full width
    alignItems: 'center',     // Center horizontally
    justifyContent: 'center', // Center vertically
    padding: 16,              // Add padding around the form
  },

  // Style for the app title (SkyView)
  appTitle: {
    fontSize: 28,
    fontWeight: 'bold',
    color: '#007AFF',         // Blue color for branding
    textAlign: 'center',
    marginBottom: 10,
  },

  // Style for the form section title
  header: {
    fontSize: 22,
    fontWeight: 'bold',
    marginBottom: 20,
    textAlign: 'center',
  },

  // Style for each input field
  input: {
    borderWidth: 1,
    borderColor: '#ccc',
    marginBottom: 12,
    padding: 10,
    borderRadius: 5,
    width: '100%',
    maxWidth: 400, // Keeps form a nice width on wider screens
  },
});


