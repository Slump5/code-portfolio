// Author: Thomas Hoerger
// Thomas Hoerger - Copyright © 2025 SkyView Weather App Final Build
// Solo Group 9
// 4-24-2025
// Description: Feedback screen. Lets user submit feedback to the database.

import React, { useState } from 'react';
import { View, Text, Button, StyleSheet } from 'react-native';
import LottieView from 'lottie-react-native'; // 🌞 Lottie animation

export default function FeedbackScreen() {
  const [submitted, setSubmitted] = useState(false); // tracks if feedback is sent

  // Sends feedback to the backend
  const handleFeedback = async (liked) => {
    try {
      await fetch('http://34.123.143.201/submit_feedback.php', {
        method: 'POST',
        headers: { 'Content-Type': 'application/json' },
        body: JSON.stringify({
          username: 'guest_user',
          liked: liked ? 1 : 0, // send 1 for like, 0 for dislike
        }),
      });

      setSubmitted(true); // flag as submitted
    } catch (error) {
      alert('Failed to submit feedback.');
    }
  };

  return (
    <View style={styles.container}>
      {/* Floating sun animation at top */}
      <View style={styles.lottieWrapper}>
        <LottieView
          source={require('../assets/animations/sun.json')}
          autoPlay
          loop
          style={styles.lottie}
        />
      </View>

      {/* Content block */}
      <View style={styles.content}>
        <Text style={styles.appTitle}>SkyView</Text>

        {/* Conditional feedback buttons or thank-you message */}
        <View style={styles.feedbackBlock}>
          {!submitted ? (
            <>
              <Text style={styles.question}>Do you like this app?</Text>
              <Button title="👍 I Like It" onPress={() => handleFeedback(true)} />
              <View style={{ height: 10 }} />
              <Button title="👎 I Don't Like It" onPress={() => handleFeedback(false)} />
            </>
          ) : (
            <Text style={styles.thanks}>Thanks for your feedback! ✅</Text>
          )}
        </View>
      </View>
    </View>
  );
}

// Layout styling
const styles = StyleSheet.create({
  container: {
    flex: 1,
    alignItems: 'center',
    justifyContent: 'center',
    paddingHorizontal: 16,
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
    justifyContent: 'center',
    width: '100%',
    maxWidth: 400,
    paddingHorizontal: 16,
  },
  appTitle: {
    fontSize: 28,
    fontWeight: 'bold',
    color: '#007AFF',
    marginBottom: 20,
    textAlign: 'center',
  },
  question: {
    fontSize: 22,
    fontWeight: 'bold',
    marginBottom: 20,
    textAlign: 'center',
  },
  feedbackBlock: {
    height: 140, // fixed block height for consistent layout
    justifyContent: 'center',
    alignItems: 'center',
  },
  thanks: {
    fontSize: 18,
    color: 'green',
    textAlign: 'center',
  },
});

