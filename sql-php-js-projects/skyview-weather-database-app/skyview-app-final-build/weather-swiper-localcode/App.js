// Author: Thomas Hoerger
// Thomas Hoerger - Copyright © 2025 SkyView Weather App Final Build
// Solo Group 9
// 4-23-2025
// Description: App entry point using navigation. Shows login/register until user is authenticated.

import React, { useState } from 'react';
import { NavigationContainer } from '@react-navigation/native';
import { createNativeStackNavigator } from '@react-navigation/native-stack';

import LoginScreen from './screens/auth/LoginScreen';
import RegisterScreen from './screens/auth/RegisterScreen';
import MainSwiper from './MainSwiper';

// Create navigation stack
const Stack = createNativeStackNavigator();

export default function App() {
  // Manage login state (null if not logged in)
  const [user, setUser] = useState(null);

  // Handler to update user state on login
  const handleLogin = (username) => {
    setUser(username);
  };

  // Handler to reset user state on logout
  const handleLogout = () => {
    setUser(null);
  };

  return (
    <NavigationContainer>
      <Stack.Navigator screenOptions={{ headerShown: false }}>
        {!user ? (
          // Show login and registration if user is not logged in
          <>
            <Stack.Screen name="Login">
              {props => <LoginScreen {...props} onLogin={handleLogin} />}
            </Stack.Screen>
            <Stack.Screen name="Register" component={RegisterScreen} />
          </>
        ) : (
          // Show main swiper navigation once logged in
          <Stack.Screen name="Main">
            {props => (
              <MainSwiper {...props} username={user} onLogout={handleLogout} />
            )}
          </Stack.Screen>
        )}
      </Stack.Navigator>
    </NavigationContainer>
  );
}
