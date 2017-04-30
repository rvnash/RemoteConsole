//
//    RemoteConsole.cpp
//    Purpose: Gives a console logging and input structure
//
//    Author: Richard Nash
//    Version: 1.0.1 01/03/17 

#include "RemoteConsole.h"

RemoteConsole::RemoteConsole(int port):server(port)
{
    echoOnSerial1 = true;
}

void RemoteConsole::init()
{
    server.begin();
}

bool RemoteConsole::isTerminalConnected()
{
    if (client.connected()) return true; // If already connected, return it
    client = server.available(); // See if new a connection is available
    return client.connected();
}

IPAddress RemoteConsole::remoteIP()
{
    if (isTerminalConnected()) {
      return client.remoteIP();
    } else {
      return 0UL;
    }
}

void RemoteConsole::printf(const char *fmt, ...)
{
    if (!isTerminalConnected() && !echoOnSerial1) return; // Short circuit if nothing to output
    // Test how many bytes we need to malloc
    va_list marker;
    va_start(marker, fmt);
    const int bufsize = 5;
    char test[bufsize];
    size_t n = vsnprintf(test, bufsize, fmt, marker);
    va_end(marker);
    // Malloc and do printf
    char *result = (char *)malloc(n + 1); // adds +1 for null terminator
    va_start(marker, fmt);
    vsnprintf(result, n+1, fmt, marker);
    va_end(marker);
    if (echoOnSerial1) Serial.print(result);
    if (isTerminalConnected()) server.print(result);
    free(result);
}

bool RemoteConsole::available()
{
    if (echoOnSerial1) {
        if (Serial.available()) return true; // Return true if there is a character available on Serial1
    }
    if (!isTerminalConnected()) return false;
    return client.available();
}

int RemoteConsole::read()
{
    if (echoOnSerial1) {
        if (Serial.available()) return Serial.read(); // Return a char if available on the serial port
    }
    if (!isTerminalConnected()) return -2;
    if (!client.available()) return -1;
    return client.read();
}

void RemoteConsole::setEchoOnSerial(bool flag)
{
    echoOnSerial1 = flag;
}