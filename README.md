# ESP32 Sensor Data Monitoring with Firebase

This project was created as part of a minor project work in college. It involves using an ESP32 microcontroller, and sensors to monitor live data and display it in a secure web application.

## Overview

The project demonstrates:
- Collecting sensor data (e.g., pH, Temperature, and TDS) using ESP32.
- Storing real-time sensor data in Firebase Realtime Database.
- Displaying live data on a web app with user authentication and security.
- Visualizing data through live charts and tables using Chart.js.

## Features

1. **Sensor Inputs:**
   - pH sensor (connected to analog pin 32).
   - TDS sensor (connected to analog pin 34).
   - Temperature

2. **Data Storage:**
   - Real-time data is stored in Firebase Realtime Database for future analysis and retrieval.

3. **Web Application:**
   - Displays live sensor data with authentication to ensure data security.
   - Features live data visualization using Chart.js for intuitive understanding.

4. **Security:**
   - Firebase authentication is implemented for secure user access.

## Setup Instructions

### Hardware Requirements
- ESP32 development board
- TDS sensor
- pH sensor
- Temperature sensor
- USB cable
- Wi-Fi access

### Software Requirements
- Arduino IDE
- Firebase ESP Client library
- ArduinoJson library
- Chart.js for web app

### Steps

1. **Hardware Setup:**
   - Connect the TDS sensor to analog pin 34 of the ESP32.
   - Connect the pH sensor to analog pin 32 of the ESP32.

2. **Firmware Configuration:**
   - Open the Arduino IDE.
   - Install the required libraries (`Firebase ESP Client` and `ArduinoJson`).
   - Replace placeholders (`<YOUR_API_KEY>`, `<YOUR_DATABASE_URL>`, `<YOUR_SSID>`, `<YOUR_PASSWORD>`) in the firmware with your Firebase API key, database URL, Wi-Fi credentials, etc.
   - Upload the firmware to the ESP32.

3. **Web App:**
   - Set up a basic web application.
   - Fetch data from the Firebase database.
   - Use Chart.js to display live charts and tables for TDS and pH values.

4. **Run the Project:**
   - Power up the ESP32.
   - Access the web app to view live data updates.

## Code Highlights

- Firebase integration:
  ```cpp
  config.api_key = API_KEY;
  config.database_url = DATABASE_URL;
  ```

- Real-time data updates:
  ```cpp
  Firebase.RTDB.setFloat(&fbdo, ("/sensorData/" + String(timestamp) + "/TDS").c_str(), tds);
  Firebase.RTDB.setFloat(&fbdo, ("/sensorData/" + String(timestamp) + "/pH").c_str(), pH);
  ```

- Live data mapping:
  ```cpp
  float tds = map(tdsVal, 0, 4095, 0, 1000);
  float pH = map(pHVal, 0, 4095, 0, 14);
  ```

## Future Enhancements
- Adding more sensors for comprehensive environmental monitoring.
- Creating advanced analytics and notifications in the web app.
- Implementing a mobile application for on-the-go monitoring.

## Acknowledgments
- Faculty guidance and support.
- Firebase documentation and Arduino community.
