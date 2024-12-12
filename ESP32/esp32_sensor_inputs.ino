#include <WiFi.h>
#include <Firebase_ESP_Client.h>  // Firebase Arduino Library
#include <ArduinoJson.h>
#include "time.h"

// /Libraries/
#include "addons/TokenHelper.h" //Provide the token generation process info.
#include "addons/RTDBHelper.h" //Provide the RTDB payload printing info and other helper functions.

// /Authentication with Firebase Realtime Database/
#define API_KEY "<YOUR_API_KEY>"
#define DATABASE_URL "<YOUR_DATABASE_URL>"

// /Connection of ESP32 Wifi Module/
const char* ssid = "<YOUR_SSID>";
const char* password = "<YOUR_PASSWORD>";

WiFiServer server(80);
// /Creation of Firebase Database Object/
FirebaseData fbdo;
FirebaseAuth auth;
FirebaseConfig config;
int timestamp;
const char* ntpServer = "pool.ntp.org";

// /Variable Initialization & Defining the Pin Numbers for ESP32 board/
int tdsPin = 34;  // Analog pin for TDS sensor
int pHPin = 32;   // Analog pin for pH sensor
bool signupOK = false;

unsigned long getTime() {
  time_t now;
  struct tm timeinfo;
  if (!getLocalTime(&timeinfo)) {
    return(0);
  }
  time(&now);
  return now;
}

void setup() {
  pinMode(tdsPin, INPUT);
  pinMode(pHPin, INPUT);
  Serial.begin(115200);

  // Connecting to ESP32 Wifi Module
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(2000);
    Serial.println("Connecting to WiFi...");
  }

  Serial.println();
  Serial.println("Connected to WiFi");

  // Printing the local WiFi IP Address 
  Serial.println(WiFi.localIP());
  Serial.println();
  configTime(0, 0, ntpServer);
  // Configuring API Key and Database URL for Firebase Communication
  config.api_key = API_KEY;
  config.database_url = DATABASE_URL;

  // Sign up process for an anonymous user in Firebase Communication
  if (Firebase.signUp(&config, &auth, "", "")) {
    Serial.println("ok");
    signupOK = true;
  } else {
    Serial.printf("%s\n", config.signer.signupError.message.c_str());
  }

  /* Assign the callback function for the long-running token generation task */
  config.token_status_callback = tokenStatusCallback;  // see addons/TokenHelper.h

  Firebase.begin(&config, &auth);
  Firebase.reconnectWiFi(true);
}


void loop() {
  int tdsVal = analogRead(tdsPin);
  float tds = map(tdsVal, 0, 4095, 0, 1000);  // Adjust the mapping based on your TDS sensor specifications
  int pHVal = analogRead(pHPin);
  float pH = map(pHVal, 0, 4095, 0, 14);

Serial.print ("time: ");
Serial.println (timestamp);

  // Set the data in the Firebase Realtime Database with a timestamp
  if (signupOK) {
    if (Firebase.RTDB.setFloat(&fbdo, ("/sensorData/" + String(timestamp) + "/timestamp").c_str(), timestamp)) {
      Serial.println("Timestamp Data sent to Firebase with timestamp: " + String(timestamp));
    } else {
      Serial.println("pH Data send to Firebase failed. Error: " + fbdo.errorReason());
    }

    if (Firebase.RTDB.setFloat(&fbdo, ("/sensorData/" + String(timestamp) + "/TDS").c_str(), tds)) {
      Serial.println("TDS Data sent to Firebase with timestamp: " + String(timestamp));
    } else {
      Serial.println("TDS Data send to Firebase failed. Error: " + fbdo.errorReason());
    }

    if (Firebase.RTDB.setFloat(&fbdo, ("/sensorData/" + String(timestamp) + "/pH").c_str(), pH)) {
      Serial.println("pH Data sent to Firebase with timestamp: " + String(timestamp));
    } else {
      Serial.println("pH Data send to Firebase failed. Error: " + fbdo.errorReason());
    }
    
  }

  Serial.print("TDS Value: ");
  Serial.println(tds);
  
  Serial.print("pH Value: ");
  Serial.println(pH);

  Serial.print("Current Time: ");
  Serial.println(timestamp);

  delay(60000);
}
