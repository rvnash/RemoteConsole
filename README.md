# RemoteConsole

A Particle library for RemoteConsole

## Welcome to your library!

This library is intended to give way to log information to the console similar to what the Serial.print family of functions gives. The additional functionality this library brings, is that it starts ad TCPServer which listens for connections on a given port. You can then connect remotely to your Particle devices and see the same console logging statements that would be going to the USB connected computer. It also provides the ability to interact with your program by accepting characters over either the USB (Serial) connection or the TCP/IP client and providing a single stream of characters to your program.

Refer to RemoteConsoleExample.ino and RemoteConsole.h for a full description of how to use this library.


## Usage

Connect Particle hardware, add the RemoteConsole library to your project and follow this simple example: RemoteConsoleExample.ino

## LICENSE

See LICENSE
