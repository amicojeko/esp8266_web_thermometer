/*
 * Copyright (c) 2015, Majenko Technologies
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * * Redistributions of source code must retain the above copyright notice, this
 *   list of conditions and the following disclaimer.
 *
 * * Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 *
 * * Neither the name of Majenko Technologies nor the names of its
 *   contributors may be used to endorse or promote products derived from
 *   this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

void handleRoot() {
  digitalWrite ( LEDPIN, 1 );
  char tmp[800];
  int sec = millis() / 1000;
  int min = sec / 60;
  int hr = min / 60;
  char temp_buff[10];
  char hum_buff[10];

  snprintf ( tmp, 800,

"<html>\
  <head>\
    <meta http-equiv='refresh' content='5'/>\
    <title>Termometro</title>\
    <style>\
      body { background-color: #000000; font-family: Arial, Helvetica, Sans-Serif; Color: #FFFFFF; }\
    </style>\
  </head>\
  <body>\
    <h1>\
      Temp: %2s &#8451;\
      <br>\
      Hum: %2s %\
    </h1>\
  </body>\
</html>",

    dtostrf(dht.readTemperature(), 4, 1, temp_buff),
    dtostrf(dht.readHumidity(), 4, 1, hum_buff)
  );
  server.send ( 200, "text/html", tmp );
  digitalWrite ( LEDPIN, 0 );
}

void handleNotFound() {
  digitalWrite ( LEDPIN, 1 );
  String message = "File Not Found\n\n";
  message += "URI: ";
  message += server.uri();
  message += "\nMethod: ";
  message += ( server.method() == HTTP_GET ) ? "GET" : "POST";
  message += "\nArguments: ";
  message += server.args();
  message += "\n";

  for ( uint8_t i = 0; i < server.args(); i++ ) {
    message += " " + server.argName ( i ) + ": " + server.arg ( i ) + "\n";
  }

  Serial.print("Not Found: ");
  Serial.print(server.uri());

  server.send ( 404, "text/plain", message );
  digitalWrite ( LEDPIN, 0 );
}

void handleGetCurrentRelativeHumidity() {
  digitalWrite ( LEDPIN, 1 );
  char tmp[50];
  char hum_buff[10];
  snprintf ( tmp, 50,
    "{\"value\":%2s}",
    dtostrf(dht.readHumidity(), 4, 1, hum_buff)
  );
  server.send ( 200, "application/json", tmp );
  digitalWrite ( LEDPIN, 0 );
}

void handleGetCurrentTemperature() {
  digitalWrite ( LEDPIN, 1 );
  char tmp[50];
  char hum_buff[10];
  snprintf ( tmp, 50,
    "{\"value\":%2s}",
    dtostrf(dht.readTemperature(), 4, 1, hum_buff)
  );
  server.send ( 200, "application/json", tmp );
  digitalWrite ( LEDPIN, 0 );
}
