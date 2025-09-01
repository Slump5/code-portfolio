// Author: Thomas Hoerger
// Thomas Hoerger - Copyright © 2025 SkyView Weather App First Build
// 4-17-2025
// Description: This screen lets users submit their feedback about the app by choosing like or dislike.
// It sends the result to the backend and displays a thank-you message after submission.

// Import necessary hooks and UI components from React and React Native
import React, { useState } from 'react';
import { View, Text, Button, StyleSheet } from 'react-native';

// Functional component for the Feedback screen
export default function FeedbackScreen() {
  // Declare a state variable to track whether feedback was submitted
  const [submitted, setSubmitted] = useState(false);

  // Function to handle feedback submission
  const handleFeedback = async (liked) => {
    try {
      // Send POST request to backend PHP endpoint with feedback
      await fetch('http://34.123.143.201/submit_feedback.php', {
        method: 'POST',
        headers: { 'Content-Type': 'application/json' },
        body: JSON.stringify({
          username: 'guest_user',        // Simulated username
          liked: liked ? 1 : 0,          // Send 1 if liked, 0 if disliked
        }),
      });

      // Once submission is successful, update the state
      setSubmitted(true);
    } catch (error) {
      // Alert the user if submission fails
      alert('Failed to submit feedback.');
    }
  };

  // Return the visual layout of the screen
  return (
    <View style={styles.container}>
      {/* Title at the top of the screen */}
      <Text style={styles.appTitle}>SkyView</Text>

      {/* Show feedback buttons only if not yet submitted */}
      {!submitted ? (
        <>
          {/* Feedback prompt */}
          <Text style={styles.question}>Do you like this app?</Text>

          {/* Like/Dislike buttons */}
          <View style={styles.buttons}>
            <Button title="👍 I Like It" onPress={() => handleFeedback(true)} />
            <View style={{ height: 10 }} />
            <Button title="👎 I Don't Like It" onPress={() => handleFeedback(false)} />
          </View>
        </>
      ) : (
        // After feedback is submitted, show thank you message
        <Text style={styles.thanks}>Thanks for your feedback! ✅</Text>
      )}
    </View>
  );
}

// Styles for the Feedback screen
const styles = StyleSheet.create({
  // Overall container for layout
  container: {
    flex: 1,                          // Fill entire screen
    paddingTop: 40,                   // Top padding for spacing
    alignItems: 'center',             // Center all items horizontally
    justifyContent: 'center',         // Center items vertically
    paddingHorizontal: 16,            // Add side padding
  },

  // SkyView app title style
  appTitle: {
    fontSize: 28,                     // Large title text
    fontWeight: 'bold',              // Bold font
    color: '#007AFF',                // iOS blue color
    marginBottom: 20,
    textAlign: 'center',
  },

  // "Do you like this app?" question style
  question: {
    fontSize: 22,
    fontWeight: 'bold',
    marginBottom: 20,
    textAlign: 'center',
  },

  // Container for feedback buttons
  buttons: {
    width: '80%',                     // Constrain button width
  },

  // Style for the thank you message
  thanks: {
    fontSize: 18,
    color: 'green',
    textAlign: 'center',
  },
});

