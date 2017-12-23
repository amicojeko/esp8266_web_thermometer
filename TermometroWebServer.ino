/*
* MIT License
*
* Copyright (c) 2017 Stefano Guglielmetti
*
* Permission is hereby granted, free of charge, to any person obtaining a copy
* of this software and associated documentation files (the "Software"), to deal
* in the Software without restriction, including without limitation the rights
* to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
* copies of the Software, and to permit persons to whom the Software is
* furnished to do so, subject to the following conditions:
*
* The above copyright notice and this permission notice shall be included in all
* copies or substantial portions of the Software.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
* AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
* LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
* OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
* SOFTWARE.
*/

#include "LedControl.h"
#include <DHT.h>;
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>

#define DHTPIN   D1
#define DHTTYPE  DHT22
#define LCD_TEMP 0
#define LCD_HUM  1
#define DATAPIN  D2
#define CLKPIN   D4
#define LOADPIN  D3
#define LEDPIN   D5

const char *ssid = "<WIFI SSID>";
const char *password = "<WIFI PASSWORD>";

DHT dht(DHTPIN, DHTTYPE); // Initialize DHT sensor for normal 16mhz Arduino
LedControl lc=LedControl(DATAPIN, CLKPIN, LOADPIN, 1); // Initialize LCD
ESP8266WebServer server ( 80 ); // Initialize web server

unsigned long Timer=0; // will be used by the non-blocking timer

float hum;  // Stores humidity value
float temp; // Stores temperature value

void setup() {
  pinMode ( LEDPIN, OUTPUT ); // Initialize LED Pin
  digitalWrite ( LEDPIN, 0 ); // Ensure the LED is off

  Serial.begin ( 115200 ); // Start serial
  WiFi.begin ( ssid, password ); // Connect to WiFi
  dht.begin(); // Start DHT

  lc.shutdown(0,false);
  lc.setIntensity(0,8); // Set LCD Intensitiy to a medium value
  lc.clearDisplay(0); // Wipe LCD Screen

  Serial.println ("Termometro Started");

  // Wait for connection
  while ( WiFi.status() != WL_CONNECTED ) {
    delay ( 500 );
    Serial.print ( "." );
  }

  // Some debug, useful to retrieve the IP Address
  Serial.println ( "" );
  Serial.print   ( "Connected to " );
  Serial.println ( ssid );
  Serial.print   ( "IP address: " );
  Serial.println ( WiFi.localIP() );

  if ( MDNS.begin ( "esp8266" ) ) {
    Serial.println ( "MDNS responder started" );
  }

  // Termometro web interface will be available at
  // http://<termometro IP address>/

  server.on ( "/", handleRoot ); // Assign "/" route to the handleRoot(); function
  server.onNotFound ( handleNotFound ); // Assign not found route (404) to the handleNotFound (); function

  server.begin(); // Start HTTP Server
  Serial.println ( "HTTP server started" );
}

void loop() {
  server.handleClient(); // The HTTP server is listening constantly

  // This is a non blocking timer: Every 5000ms (5sec) it reads the
  // humidity and temperature from the DHT22, and sends them to the LCD
  if ( (millis() - Timer) >= 5000) {
    Timer = millis();

    hum  = dht.readHumidity();
    temp = dht.readTemperature();

    Serial.print("Humidity: ");
    Serial.print(hum);
    Serial.print(" %, Temp: ");
    Serial.print(temp);
    Serial.println(" Celsius");

    sendToLCD(temp * 10, LCD_TEMP);
    sendToLCD(hum * 10, LCD_HUM);
  }

}
