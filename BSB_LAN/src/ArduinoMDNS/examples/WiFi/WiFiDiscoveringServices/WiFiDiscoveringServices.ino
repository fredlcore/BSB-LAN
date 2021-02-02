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

//  Illustrates how to discover Bonjour services on your network.

#include <SPI.h>
#include <WiFi101.h>
#include <WiFiUdp.h>
#include <ArduinoMDNS.h>

char ssid[] = "yourNetwork";     //  your network SSID (name)
char pass[] = "secretPassword";  // your network password
int status = WL_IDLE_STATUS;     // the Wifi radio's status

WiFiUDP udp;
MDNS mdns(udp);

void serviceFound(const char* type, MDNSServiceProtocol proto,
                  const char* name, IPAddress ip, unsigned short port,
                  const char* txtContent);

void setup()
{
  //Initialize serial and wait for port to open:
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }
  
  // check for the presence of the shield:
  if (WiFi.status() == WL_NO_SHIELD) {
    Serial.println("WiFi shield not present");
    // don't continue:
    while (true);
  }

  // attempt to connect to Wifi network:
  while ( status != WL_CONNECTED) {
    Serial.print("Attempting to connect to WPA SSID: ");
    Serial.println(ssid);
    // Connect to WPA/WPA2 network:
    status = WiFi.begin(ssid, pass);

    // wait 10 seconds for connection:
    delay(10000);
  }

  Serial.print("You're connected to the network");
  
  // Initialize the mDNS library. You can now reach or ping this
  // Arduino via the host name "arduino.local", provided that your operating
  // system is mDNS/Bonjour-enabled (such as MacOS X).
  // Always call this before any other method!
  mdns.begin(WiFi.localIP(), "arduino");

  // We specify the function that the mDNS library will call when it
  // discovers a service instance. In this case, we will call the function
  // named "serviceFound".
  mdns.setServiceFoundCallback(serviceFound);

  Serial.println("Enter a mDNS service name via the Arduino Serial Monitor "
                 "to discover instances");
  Serial.println("on the network.");
  Serial.println("Examples are \"_http\", \"_afpovertcp\" or \"_ssh\" (Note "
                 "the underscores).");
}

void loop()
{ 
  char serviceName[256];
  int length = 0;
  
  // read in a service name from the Arduino IDE's serial monitor.
  while (Serial.available()) {
    serviceName[length] = Serial.read();
    length = (length+1) % 256;
    delay(5);
  }
  serviceName[length] = '\0';
  
  // You can use the "isDiscoveringService()" function to find out whether the
  // mDNS library is currently discovering service instances.
  // If so, we skip this input, since we want our previous request to continue.
  if (!mdns.isDiscoveringService()) {
    if (length > 0) {    
      Serial.print("Discovering services of type '");
      Serial.print(serviceName);
      Serial.println("' via Multi-Cast DNS (Bonjour)...");

      // Now we tell the mDNS library to discover the service. Below, I have
      // hardcoded the TCP protocol, but you can also specify to discover UDP
      // services.
      // The last argument is a duration (in milliseconds) for which we will
      // search (specify 0 to run the discovery indefinitely).
      // Note that the library will resend the discovery message every 10
      // seconds, so if you search for longer than that, you will receive
      // duplicate instances.

      mdns.startDiscoveringService(serviceName,
                                   MDNSServiceTCP,
                                   5000);
    }  
  }

  // This actually runs the mDNS module. YOU HAVE TO CALL THIS PERIODICALLY,
  // OR NOTHING WILL WORK!
  // Preferably, call it once per loop().
  mdns.run();
}

// This function is called when a name is resolved via mMDNS/Bonjour. We set
// this up in the setup() function above. The name you give to this callback
// function does not matter at all, but it must take exactly these arguments
// as below.
// If a service is discovered, name, ipAddr, port and (if available) txtContent
// will be set.
// If your specified discovery timeout is reached, the function will be called
// with name (and all successive arguments) being set to NULL.
void serviceFound(const char* type, MDNSServiceProtocol /*proto*/,
                  const char* name, IPAddress ip,
                  unsigned short port,
                  const char* txtContent)
{
  if (NULL == name) {
	Serial.print("Finished discovering services of type ");
	Serial.println(type);
  } else {
    Serial.print("Found: '");
    Serial.print(name);
    Serial.print("' at ");
    Serial.print(ip);
    Serial.print(", port ");
    Serial.print(port);
    Serial.println(" (TCP)");

    // Check out http://www.zeroconf.org/Rendezvous/txtrecords.html for a
    // primer on the structure of TXT records. Note that the Bonjour
    // library will always return the txt content as a zero-terminated
    // string, even if the specification does not require this.
    if (txtContent) {
      Serial.print("\ttxt record: ");
      
      char buf[256];
      char len = *txtContent++;
      int i=0;
      while (len) {
        i = 0;
        while (len--)
          buf[i++] = *txtContent++;
        buf[i] = '\0';
        Serial.print(buf);
        len = *txtContent++;
        
        if (len)
          Serial.print(", ");
        else
          Serial.println();
      }
    }
  }
}

