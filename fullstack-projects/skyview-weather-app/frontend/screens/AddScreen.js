// Author: Thomas Hoerger
// Thomas Hoerger - Copyright © 2025 SkyView Weather App Final Build
// Solo Group 9
// 4-23-2025
// Description: Add Screen. Lets user add data to the database.

import React, { useState } from 'react';
import { View, Text, TextInput, Button, StyleSheet } from 'react-native';
import LottieView from 'lottie-react-native';

export default function AddScreen() {
  // State to store form input values
  const [city, setCity] = useState('');
  const [temperature, setTemp] = useState('');
  const [humidity, setHumidity] = useState('');

  // Submits weather data to backend
  const handleSubmit = async () => {
    try {
      await fetch('http://34.123.143.201/add_weather.php', {
        method: 'POST',
        headers: { 'Content-Type': 'application/json' },
        body: JSON.stringify({ city, temperature, humidity }),
      });

      alert('✅ Weather report added!');
      setCity('');
      setTemp('');
      setHumidity('');
    } catch (err) {
      alert("⚠️ Failed to add weather. Check connection.");
    }
  };

  return (
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

      {/* Input fields and submit button */}
      <View style={styles.content}>
        <Text style={styles.appTitle}>SkyView</Text>
        <Text style={styles.header}>Add Weather Report</Text>

        <TextInput placeholder="City" value={city} onChangeText={setCity} style={styles.input} />
        <TextInput placeholder="Temperature (°F)" value={temperature} onChangeText={setTemp} keyboardType="numeric" style={styles.input} />
        <TextInput placeholder="Humidity (%)" value={humidity} onChangeText={setHumidity} keyboardType="numeric" style={styles.input} />

        <Button title="Submit" onPress={handleSubmit} />
      </View>
    </View>
  );
}

// Styles
const styles = StyleSheet.create({
  container: {
    flex: 1,
    alignItems: 'center',
    justifyContent: 'center',
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
  content: {
    alignItems: 'center',
    width: '100%',
    paddingHorizontal: 16,
    maxWidth: 400,
  },
  appTitle: {
    fontSize: 28,
    fontWeight: 'bold',
    color: '#007AFF',
    textAlign: 'center',
    marginBottom: 10,
  },
  header: {
    fontSize: 22,
    fontWeight: 'bold',
    marginBottom: 20,
    textAlign: 'center',
  },
  input: {
    borderWidth: 1,
    borderColor: '#ccc',
    marginBottom: 12,
    padding: 10,
    borderRadius: 5,
    width: 300,
  },
});




