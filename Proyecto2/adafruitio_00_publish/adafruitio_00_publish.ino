// Adafruit IO Publish Example
//
// Adafruit invests time and resources providing this open source code.
// Please support Adafruit and open source hardware by purchasing
// products from Adafruit!
//
// Written by Todd Treece for Adafruit Industries
// Copyright (c) 2016 Adafruit Industries
// Licensed under the MIT license.
//
// All text above must be included in any redistribution.

/************************** Configuration ***********************************/

// edit the config.h tab and enter your Adafruit IO credentials
// and any additional configuration needed for WiFi, cellular,
// or ethernet clients.
#include "config.h"

/************************ Example Starts Here *******************************/

// this int will hold the current count for our sketch
//int count = 0;
int temp = 0;
// set up the 'counter' feed
//AdafruitIO_Feed *counter = io.feed("counter");
// set up the 'counter' feed

/*
 * There are three serial ports on the ESP known as U0UXD, U1UXD and U2UXD.
 * 
 * U0UXD is used to communicate with the ESP32 for programming and during reset/boot.
 * U1UXD is unused and can be used for your projects. Some boards use this port for SPI Flash access though
 * U2UXD is unused and can be used for your projects.
 * 
*/

#define RXD2 16
#define TXD2 17
AdafruitIO_Feed *Temperatura = io.feed("Temperatura");
void setup() {

  // start the serial connection
  Serial.begin(115200);

  // wait for serial monitor to open
  while (! Serial);

  Serial.print("Connecting to Adafruit IO");

  // connect to io.adafruit.com
  io.connect();

  // wait for a connection
  while (io.status() < AIO_CONNECTED) {
    Serial.print(".");
    delay(500);

    // Note the format for setting a serial port is as follows: Serial2.begin(baud-rate, protocol, RX pin, TX pin);
    Serial.begin(115200);
   //Serial1.begin(9600, SERIAL_8N1, RXD2, TXD2);
    Serial2.begin(9600, SERIAL_8N1, RXD2, TXD2);
    delay(200);
  }

  // we are connected
  Serial.println();
  Serial.println(io.statusText());

}



void loop() {
  Serial.print("Temperatura:");
  Serial.println(Serial2.readString());
  

  // io.run(); is required for all sketches.
  // it should always be present at the top of your loop
  // function. it keeps the client connected to
  // io.adafruit.com, and processes any incoming data.
  io.run();
  temp = Serial2.read();

  // save count to the 'counter' feed on Adafruit IO
  //Serial.print("sending -> ");
  //Serial.println(temp);
  Temperatura->save(temp);

  // increment the count by 1

  // Adafruit IO is rate limited for publishing, so a delay is required in
  // between feed->save events. In this example, we will wait three seconds
  // (1000 milliseconds == 1 second) during each loop.
  delay(3000);
  

}
