//
//    usage.ino
//    Purpose: Library example code
//
//    Author: Richard Nash
//    Version: 1.0.2 01/03/17 

// Example usage for RemoteConsole library by rvnash.
// Follow the code from top to bottom reading the comments to learn pretty much all there is to
// know about this simple libary.

#include "RemoteConsole.h"

// Construct the rcons object, will listen on port 23
RemoteConsole rcons(23);

// Some vars to keep track of state
bool lastConnected = false;
unsigned long lastSend = 0;

// A little formatting help for IPAddress
String myIPString(IPAddress ip)
{
  return String::format("%d.%d.%d.%d", ip[0], ip[1], ip[2], ip[3]);
}


void setup() {
    // In setup you need to initialize the Serial function.
    Serial.begin();

    // Turn on echo on Serial (USB), even though this line isn't needed because true is the default.
    rcons.setEchoOnSerial(true);

    // Here is how to log information. In this case just some messages telling this devices IP address
    rcons.printf("My local IP is: %s\r\n", myIPString(WiFi.localIP()).c_str());
    rcons.printf("Wating for connection\r\n");
}

void loop()
{
    // New connections are checked for in the function "isTerminalConnected", so this needs to be
    // called in your "loop()" function.
    // Note: You can also call any of these functions, as they call "isTerminalConnected" internally.
    //      remoteIP()
    //      printf()
    //      available()
    //      read()
    if (rcons.isTerminalConnected()) {
        if (!lastConnected) {
            // When a client connects, log their IP as well as yours.
            // This should be the first message that appears on the remote client.
            rcons.printf("Connection from %s.\r\n",myIPString(rcons.remoteIP()).c_str());
            rcons.printf("Connected to %s.\r\n",myIPString(WiFi.localIP()).c_str());
            lastConnected = true;
        }
    } else {
        if (lastConnected) {
            rcons.printf("Lost the connection.\r\n");
            lastConnected = false;
        }
    }
    // Poll to see if a character is input from the USB port OR the connected client
    if (rcons.available()) {
        char c = rcons.read();
        // Just echo it back to USB AND any connected client
        rcons.printf("Typed: %c\r\n", c);
    }
    // The following code just prints "Hello world" every 3 seconds to the USB and any connected client.
    if (millis() - lastSend >= 3000) {
        rcons.printf("Hello world %lu\r\n", millis());
        lastSend += 3000;
    }
}
