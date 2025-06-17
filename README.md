ESP32 Date & Time Display with NTP and OLED

This project demonstrates how to display the current date and time on an OLED screen using an ESP32 microcontroller. The time is synchronized via NTP (Network Time Protocol), and the display is handled using a 128x64 I2C OLED screen with the U8g2 graphics library.
Features
-	Connects to WiFi
-	Retrieves accurate time from an NTP server
-	Displays current time (HH:MM:SS) and date (DD/MM/YYYY)
-	Updates every second
-	Debug output via Serial Monitor
Hardware Requirements
-	ESP32 development board
-	0.96" or 1.3" I2C OLED display (SSD1306 128x64)
-	Jumper wires
-	Breadboard (optional)
Wiring (ESP32 I2C default)
 - SDA - GPIO 21
 - SCL - GPIO 22
 - VCC - 3.3V or 5V (depending on your display)
 - GND - GND

 ![image](https://github.com/user-attachments/assets/fdf77551-8b9a-4e86-8c68-c3d3b2726aef)

 Required Libraries
-	WiFi (Built-in for ESP32)
-	NTPClient (by Fabrice Weinberg)
-	U8g2 (by Oliver)
-	Wire (Built-in)

Setup Instructions
1.	Clone or copy this code into your Arduino IDE.
2.	Replace WiFi credentials in the code:    const char* ssid = "YOUR_SSID";    const char* password = "YOUR_PASSWORD";
3.	Adjust timezone offset if needed.
4.	Set up your board and display connected as stated in wiring section
5.	Select the correct Board (ESP32 Dev Module) and Port in Arduino IDE.
6.	Upload the sketch to your ESP32.
7.	Open Serial Monitor at 115200 baud.

Time & Date Format

- Time: HH:MM:SS (24-hour) 
- Date: DD/MM/YYYY

Sample Serial Output
- Connecting to WiFi...............
- WiFi connected.
- IP address: 92.168.1.10
- NTP time updated.
- Date: 17/06/2025, Time: 14:35:08

Prototype display 

 ![image](https://github.com/user-attachments/assets/876dba11-675f-445e-bfec-e9d3f963f4ae)


License

This project is provided as-is for educational and prototyping purposes. Feel free to modify and extend it for your own applications.
 
