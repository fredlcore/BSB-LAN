//  Copyright (C) 2010 Georg Kaindl
//  http://gkaindl.com
//
//  This file is part of Arduino EthernetBonjour.
//
//  EthernetBonjour is free software: you can redistribute it and/or
//  modify it under the terms of the GNU Lesser General Public License
//  as published by the Free Software Foundation, either version 3 of
//  the License, or (at your option) any later version.
//
//  EthernetBonjour is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU Lesser General Public License for more details.
//
//  You should have received a copy of the GNU Lesser General Public
//  License along with EthernetBonjour. If not, see
//  <http://www.gnu.org/licenses/>.
//

//  Illustrates how to register a service with a TXT record.

#include <SPI.h>
#include <Ethernet.h>
#include <EthernetUdp.h>
#include <ArduinoMDNS.h>

EthernetUDP udp;
MDNS mdns(udp);

// you can find this written on the board of some Arduino Ethernets or shields
byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED }; 

// NOTE: Alternatively, you can assign a fixed IP to configure your
//       Ethernet shield.
//       byte ip[] = { 192, 168, 0, 154 };

EthernetServer server(80);

void setup()
{
// NOTE: Alternatively, you can assign a fixed IP to configure your
//       Ethernet shield.
//       Ethernet.begin(mac, ip);   
  Ethernet.begin(mac); 

  // Initialize the mDNS library. You can now reach or ping this
  // Arduino via the host name "arduino.local", provided that your operating
  // system is mDNS/Bonjour-enabled (such as MacOS X).
  // Always call this before any other method!
  mdns.begin(Ethernet.localIP(), "arduino");

  // Now let's register the service we're offering (a web service) via mDNS!
  // To do so, we call the addServiceRecord() method. The first argument is the
  // name of our service instance and its type, separated by a dot. In this
  // case, the service type is _http. There are many other service types, use
  // google to look up some common ones, but you can also invent your own
  // service type, like _mycoolservice - As long as your clients know what to
  // look for, you're good to go.
  // The second argument is the port on which the service is running. This is
  // port 80 here, the standard HTTP port.
  // The last argument is the protocol type of the service, either TCP or UDP.
  // Of course, our service is a TCP service.
  // With the service registered, it will show up in a Bonjour-enabled web
  // browser. As an example, if you are using Apple's Safari, you will now see
  // the service under Bookmarks -> Bonjour (Provided that you have enabled
  // Bonjour in the "Bookmarks" preferences in Safari).
  mdns.addServiceRecord("Arduino Bonjour Webserver Example._http",
                        0,
                        MDNSServiceTCP);

  // Now we'll register a second service record: This time, we specify a TXT
  // content as well, in order to point to a specific page on our server.
  // This is just an example to show that the mDNS library supports TXT
  // records as well, but I won't go into detail about how they work. Check
  // out http://www.zeroconf.org/Rendezvous/txtrecords.html for an excellent
  // primer.
  // What this does is that your browser will now show a second mDNS entry,
  // which will take you to another page on the Arduino web server.
  mdns.addServiceRecord("Arduino mDNS Webserver Example, Page 2"
                         "._http",
                         80,
                         MDNSServiceTCP,
                         "\x7path=/2");
}

void loop()
{ 
  // This actually runs the mDNS module. YOU HAVE TO CALL THIS PERIODICALLY,
  // OR NOTHING WILL WORK! Preferably, call it once per loop().
  mdns.run();

  // The code below is just taken from the "WebServer" example in the Ethernet
  // library. The only difference here is that this web server gets announced
  // over Bonjour, but this happens in setup(). This just displays something
  // in the browser when you connect.
  EthernetClient client = server.available();
  char lastLetter = '\0';
  char isPage2 = 0;
  if (client) {
    // an http request ends with a blank line
    bool current_line_is_blank = true;
    while (client.connected()) {
      if (client.available()) {
        char c = client.read();
        
        if ('/' == lastLetter && '2' == c)
          isPage2 = 1;        
        lastLetter = c;

        // if we've gotten to the end of the line (received a newline
        // character) and the line is blank, the http request has ended,
        // so we can send a reply
        if (c == '\n' && current_line_is_blank) {
          // send a standard http response header
          client.println("HTTP/1.1 200 OK");
          client.println("Content-Type: text/html");
          client.println();
          
          if (isPage2) {
            client.println("This is the second page advertised via Bonjour!");
          } else {
            client.println("Hello from a mDNS-enabled web-server running ");
            client.println("on your Arduino board!");
          }

          break;
        }
        if (c == '\n') {
          // we're starting a new line
          current_line_is_blank = true;
        } else if (c != '\r') {
          // we've gotten a character on the current line
          current_line_is_blank = false;
        }
      }
    }
    // give the web browser time to receive the data
    delay(1);
    client.stop();
  }
}
