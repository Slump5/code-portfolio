// Author: Thomas Hoerger
// Thomas Hoerger - Copyright © 2025 SkyView Weather App Final Build
// Solo Group 9
// 4-23-2025
// Description: Allows users to register by sending username, email, and password to the server. Validates duplicate users.

import React, { useState } from 'react';
import { View, Text, TextInput, Button, StyleSheet, Alert } from 'react-native';

export default function RegisterScreen({ navigation }) {
  const [username, setUsername] = useState('');
  const [email, setEmail] = useState('');
  const [password, setPassword] = useState('');

  // Called when Register button is pressed
  const handleRegister = async () => {
    // Check for missing fields
    if (!username || !email || !password) {
      Alert.alert('Missing Fields', 'Please fill in all fields.');
      return;
    }

    try {
      const response = await fetch('http://34.123.143.201/register_user.php', {
        method: 'POST',
        headers: { 'Content-Type': 'application/json' },
        body: JSON.stringify({ username, email, password }),
      });

      const data = await response.json();

      // If registration succeeded
      if (data.status === 'success') {
        Alert.alert('✅ Registration Successful', data.message);
        navigation.navigate('Login');
      } else {
        Alert.alert('❌ Registration Failed', data.message || 'Unknown error');
      }
    } catch (error) {
      Alert.alert('⚠️ Error', 'Could not connect to server.');
      console.error('Registration error:', error);
    }
  };

  return (
    <View style={styles.container}>
      <Text style={styles.title}>SkyView Register</Text>

      {/* Username input */}
      <TextInput
        placeholder="Username"
        value={username}
        onChangeText={setUsername}
        style={styles.input}
        autoCapitalize="none"
      />

      {/* Email input */}
      <TextInput
        placeholder="Email"
        value={email}
        onChangeText={setEmail}
        style={styles.input}
        keyboardType="email-address"
        autoCapitalize="none"
      />

      {/* Password input */}
      <TextInput
        placeholder="Password"
        value={password}
        onChangeText={setPassword}
        secureTextEntry
        style={styles.input}
      />

      {/* Register button */}
      <Button title="Register" onPress={handleRegister} />

      {/* Navigation link to login screen */}
      <Text style={styles.link} onPress={() => navigation.navigate('Login')}>
        Already have an account? Login
      </Text>
    </View>
  );
}

// Layout styles
const styles = StyleSheet.create({
  container: {
    flex: 1,
    justifyContent: 'center',
    padding: 20,
  },
  title: {
    fontSize: 28,
    fontWeight: 'bold',
    color: '#007AFF',
    marginBottom: 20,
    textAlign: 'center',
  },
  input: {
    borderWidth: 1,
    borderColor: '#aaa',
    padding: 10,
    marginBottom: 12,
    borderRadius: 6,
  },
  link: {
    marginTop: 12,
    color: '#007AFF',
    textAlign: 'center',
  },
});

