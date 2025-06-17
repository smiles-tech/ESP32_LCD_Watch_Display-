// This code demonstrates how to display the current date and time on an LCD using an ESP32.
// It synchronizes time using NTP (Network Time Protocol).

// Required Libraries:
// 1. `WiFi.h` (Built-in for ESP32)
// 2. `NTPClient.h` (Install from Arduino Library Manager: "NTPClient by Fabrice Weinberg")
// 3. `U8g2lib.h` (Install from Arduino Library Manager: "U8g2 by oliver")
// 4. `Wire.h` (Built-in for I2C communication)

#include <U8g2lib.h>
#include <NTPClient.h>
#include <WiFi.h>
#include <WiFiUdp.h>
#include <Wire.h> // Required for I2C communication

// --- WiFi Credentials ---
// Replace with your WiFi network's SSID and password
const char* ssid = "Mr-Smile";
const char* password = "smile123@Y";

// --- NTP Client Setup ---
// You can change the NTP server if needed (e.g., "pool.ntp.org")
const long utcOffsetInSeconds = 3 * 3600; // EAT (East Africa Time) is UTC+3. Adjust this for your timezone.
WiFiUDP ntpUdp;
NTPClient timeClient(ntpUdp, "pool.ntp.org", utcOffsetInSeconds);


// Common I2C pins for ESP32:
// SDA: GPIO21
// SCL: GPIO22
//
// Ensure your display's SDA and SCL pins are connected to these ESP32 pins.
U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0); // Rotation 0, using hardware I2C

void setup() {
  Serial.begin(115200);
  Serial.println("\nConnecting to WiFi...");

  // Initialize I2C communication
  Wire.begin();

  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWiFi connected.");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());

  // Initialize NTP client
  timeClient.begin();
  timeClient.update(); // Initial time update
  Serial.println("NTP time updated.");

  // Initialize U8g2 display
  u8g2.begin();
  u8g2.setFont(u8g2_font_ncenB10_tr); // Set a suitable font for initialization message
  u8g2.clearBuffer();
  u8g2.drawStr(0, 15, "Initializing...");
  u8g2.sendBuffer();
  delay(1000); // Give some time for display to show initialization message
}

void loop() {
  // Update the time client regularly
  // update() returns true if the time was updated, false otherwise.
  // It only updates once per 'updateInterval' (default 60 seconds).
  timeClient.update();

  // Get formatted time string
  String formattedTime = timeClient.getFormattedTime();

  // Get date components
  unsigned long epochTime = timeClient.getEpochTime();
  struct tm *ptm = gmtime ((time_t *)&epochTime);
  int monthDay = ptm->tm_mday;
  int currentMonth = ptm->tm_mon; // Month is 0-11, so add 1
  int currentYear = ptm->tm_year; // Year is years since 1900, so add 1900

  // Create date string
  char dateBuffer[16]; // Buffer for "DD/MM/YYYY" + null terminator
  sprintf(dateBuffer, "%02d/%02d/%04d", monthDay, currentMonth, currentYear);
  String dateString = dateBuffer;

  // Clear the display buffer
  u8g2.clearBuffer();

  // Display time
  u8g2.setFont(u8g2_font_logisoso24_tn); // Larger font for time
  u8g2.drawStr(0, 25, formattedTime.c_str());

  // Display date
  u8g2.setFont(u8g2_font_ncenB10_tr); // Smaller font for date
  u8g2.drawStr(0, 50, dateString.c_str());

  // Send the buffer to the display
  u8g2.sendBuffer();

  // Print to Serial for debugging
  Serial.print("Date: ");
  Serial.print(dateString);
  Serial.print(", Time: ");
  Serial.println(formattedTime);

  delay(1000); // Update every second
}
