//
//    RemoteConsole.h
//    Purpose: Gives a console logging and input structure
//
//    Author: Richard Nash
//    Version: 1.0.2 01/03/17

// This library is intended to give way to log information to the console similar to what
// the Serial.print family of functions gives. The additional functionality this library
// brings, is that it starts ad TCPServer which listens for connections on a given port.
// You can then connect remotely to your Particle devices and see the same console logging
// statements that would be going to the USB connected computer. It also provides the ability
// to interact with your program by accepting characters over either the USB (Serial) connection
// or the TCP/IP client and providing a single stream of characters to your program.
//
// See the usage.ino for an example of how to use this library.
//
// I have written a very simple raw TCP and local monitor program for Mac OSX
// which you can find here: https://github.com/rvnash/nmon
//
// Alternatively, I'd suggest using PuTTY (http://www.putty.org/) with this program to connect in RAW mode
// https://the.earth.li/~sgtatham/putty/0.69/htmldoc/Chapter3.html#using-rawprot
//

#pragma once

#include "Particle.h"

class RemoteConsole
{
private:
  TCPServer server;
  TCPClient client;
  bool echoOnSerial1;

public:
// Delete the default constructor
  RemoteConsole() = delete;

// Constructor
// Param: port: The TCP/IP port to listen for connections on, 23 (telnet) is the default.
// Note: This isn't really a telnet server, as it doesn't implement the telnet protocol.
//       It is just raw socket connection to send/recieve characters. Perhaps port 23 as
//       the default is a bad choice because of this.
  RemoteConsole(int port = 23);

// init()
// Call from your setup() function to initiate the TCP/IP listener
  void init();

// isTerminalConnected()
// Returns: true if a remote terminal is connected, false otherwise
  bool isTerminalConnected();

// remoteIP()
// Returns: the IPAddress of the remote client if "isTerminalConnected()" is true.
//          otherwise it returns "0.0.0.0"
  IPAddress remoteIP();

// printf()
// The way to log information is all with printf style logs.
// Paramters: szFormat - the format of the information to send to the console(s)
//            Variable Arguments - to satisfy the printf style substitution string
// Example: rcons.printf("The temperature is %.2f\n", temp);
  void printf(const char *szFormat, ...);

// available()
// Returns: true if a character from the remote terminal is waiting to be read, false otherwise
  bool available();

// read()
// Returns: the character from the remote terminal, or -1 if none available
// Note: If you want to know if a character is available, call "available()"
  int read();

// setEchoOnSerial()
// Param: flag - Turn of "Serial" echoing.
// This means that the Serial connection (USB) will participate in the
// logging AND input the same as the TCP/IP clinet that is. Default is true.
  void setEchoOnSerial(bool flag);

};
