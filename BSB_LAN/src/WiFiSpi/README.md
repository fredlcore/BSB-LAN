WiFiSpi
=======

This library connects Arduino to ESP8266 module and uses it as a dedicated WiFi device. The SPI interface is used because of its strictly master/slave nature.

The library allows Arduino to be client or server on the WiFi network.

## News

#### 2021-01-25

Added UDP Multicast support

#### 2021-01-02

Fixed a bug with closing server connection when closing asynchronously opened another client.
Changed deprecated boolean type to bool. 

#### 2019-02-18

Added SSL connection to WiFiClient class. Added verifySSL function.

#### 2019-01-27

Enhanced communications protocol (added CRC-8 and confirmation of message reception). Shortened the status message from 4 bytes to 2 bytes and added XOR check. The protocol version is now 0.2.0 and is incompatible with the former one.

Added support for hardware circuit removing the problems with ESP8266 reset by pulling GPIO15 (SS) pin to GND on reset.

## Requirements

### ESP8266 device

The ESP8266 has two SPI interfaces. The first is connected to the flash memory, the second (named HSPI) can be used by user. The HSPI signals are multiplexed with GPIO12-15. Suitable device for the slave is ESP-12. On the ESP device must be run a custom firmware - see WifiESPSPI project.

### Wiring

The library uses hardware SPI on Arduino so most of the signals are fixed to certain pins.

The wiring is as follows:

     Name  |   Uno   | STM32F103C8 |     ESP8266
           |         |  SPI1 SPI2  |  GPIO    NodeMCU
    -------+---------+---------------------------------
      SS   |   D10   |  PA4  PB12  |   15       D8
     MOSI  |   D11   |  PA7  PB15  |   13       D7
     MISO  |   D12   |  PA6  PB14  |   12       D6
     SCK   |   D13   |  PA5  PB13  |   14       D5

The SS pin is the only pin the user can change. Changing SS to another pin enables more devices on one SPI interface.

Please be careful, the ESP8266 chip ports are **NOT** 5V tolerant, if you're connecting to a 5V device you have to use a level converter.

## Library Reference

The library implements almost the same functions as the [Arduino WiFi library](https://www.arduino.cc/en/Reference/WiFi).

### Setup

All the important defines are in file **config.h**. The user can comment and/or uncomment them and modify the behaviour of the library.

### WiFiSpiClass

After including *WiFiSpi.h* header the *WiFiSpi* variable is automatically instantiated. Use the variable to perform the following calls.

- **void init(int8_t pin, uint32_t max_speed = 0, SPIClass *in_spi = &SPI, int8_t hwResetPin = -1)**
Initializes the library and the Arduino SPI interface. Must be called on beginning of the communication. The parameter *max_speed* limits the SPI speed. Tests on STM32F1 show that speeds as high as 9 Mhz are usable. The parameter *in_spi* allows to use another SPI port (if there are more present in the MCU). Refer to a particular implementation of SPIClass. The optional parameter *hwResetPin* defines the pin which is connected to reset pin on ESP8266 for hardware reset. Then this parameter is present,  master resets the ESP8266 on start.

- **char* firmwareVersion()**
Returns version of custom firmware loaded into ESP8266.

- **char* protocolVersion()**
Returns version of protocol the ESP8266 firmware operates with.

- **char* masterProtocolVersion()**
Returns version of protocol the master runs.

- **uint8_t checkProtocolVersion()**
Checks master and ESP protocol version. If they match, returns 1, otherwise 0.

- **uint8_t begin(const char* ssid)**
Connects to an open (unencrypted) wifi. Returns a value from *wl_status_t* enum(when connected returns WL_CONNECTED). Establishing of the connection may last several seconds.

- **uint8_t begin(const char* ssid, const char *passphrase)**
Connects to a WPA/WPA2 encrypted wifi. Returns status from *wl_status_t* type (when connected returns WL_CONNECTED). Establishing of the connection may last several seconds.

- **int disconnect(void)**
Disconnects from the WiFi network. Returns a value from *wl_status_t* enum(when disconnected returns WL_DISCONNECTED).

- **uint8_t status()**
Returns the connection status of the WiFi interface. The returned value is one of the enum *wl_status_t*.

- **int8_t hostByName(const char* aHostname, IPAddress& aResult)**
Resolves the given hostname to an IP address. Returns 1 for Ok else error code.

 - **void softReset(void)**
 Sends reset command to ESP8266. The ESP8266 then resets itself. The command is performed only if the connection between the host and ESP8266 is not broken. 

 - **void hardReset(void)**
 Resets the ESP8266. One pin on master unit must be wired to reset pin on ESP8266. The pin is defined in **init** function.

----------


- **bool config(IPAddress local_ip)**
Changes IP configuration, sets local IP address and disables DHCP client.

- **bool config(IPAddress local_ip, IPAddress dns_server)**
Changes IP configuration, sets local IP address, primary DNS server and disables DHCP client.

- **bool config(IPAddress local_ip, IPAddress dns_server, IPAddress gateway)**
Changes IP configuration, sets local IP address, primary DNS server, static gateway address and disables DHCP client.

- **bool config(IPAddress local_ip, IPAddress dns_server, IPAddress gateway, IPAddress subnet)**
Changes IP configuration, sets local IP address, primary DNS server, static gateway address, subnet mask and disables DHCP client.

- **bool setDNS(IPAddress dns_server1)**
Changes IP configuration, sets primary DNS server IP address.

- **bool setDNS(IPAddress dns_server1, IPAddress dns_server2)**
Changes IP configuration, sets primary and secondary DNS server IP addresses.

- **uint8_t* macAddress(uint8_t* mac)**
Returns MAC address value of the WiFi interface. The MAC address is copiend to the array *mac* and also returned as a pointer to this array. The array size must be at least 6 bytes.

- **IPAddress localIP()**
Returns local IP address value.

- **IPAddress subnetMask()**
Returns interface subnet mask value.

- **IPAddress gatewayIP()**
Returns interface gateway address value.

- **char* SSID()**
Returns the current SSID associated with the network.

- **uint8_t* BSSID()**
Returns the current BSSID associated with the network. It is in fact the MAC address of the Access Point. Returns a pointer to byte array of 6 byte length.

- **int32_t RSSI()**
Returns the currect RSSI (signal strength in dBm) as a signed value.


----------


- **int8_t scanNetworks()**
Scans the WiFi network. Returns the number of networks found or error value (WL_FAILURE). The call may last several seconds.

- **char* SSID(uint8_t networkItem)**
Returns the current SSID associated with the discovered network during the network scan. Parameter *networkItem* is the index into a discovered networks array.

- **uint8_t	encryptionType(uint8_t networkItem)**
Returns the encryption type of the discovered network during the network scan. The returned value is one of the enum *wl_enc_type*. Parameter *networkItem* is the index into a discovered networks array.

- **int32_t RSSI(uint8_t networkItem)**
Returns the signal strength in dBm of the discovered network during the network scan. The returned value is signed 32 bit integer. Parameter *networkItem* is the index into a discovered networks array.

### WiFiSpiClient

The WiFiSpiClient class performs data communication between your program and the remote site. It is used not only with client connections (where Arduino acts as a client) but also in server connections (sending responses to a web request) and udp connections.
The library has a pool of 4 sockets and after exhausting all the sockets no more connection is available. Therefore it is important to close the socket (i. e. stop the client) when it is no longer used.

- **WiFiSpiClient()**
Default constructor, creates a closed connection. Use it for client side of communication.

- **WiFiSpiClient(uint8_t sock)**
Creates client for open server connection. Called by the library in when server connection has data.

- **int connect(IPAddress ip, uint16_t port)**
Connects to the specified IP address and port. Returns a value from enum *wl_tcp_state* (for open connection returns ESTABLISHED).

- **int connect(const char *host, uint16_t port)**
Connects to the specified host and port. Returns a value from enum *wl_tcp_state* (for open connection returns ESTABLISHED).

- **int connectSSL(IPAddress ip, uint16_t port)**
Connects using SSL to the specified IP address and port. Returns a value from enum *wl_tcp_state* (for open connection returns ESTABLISHED). No authentification checks are performed, recommended to use *verifySSL* function to check the server certificate.

- **int connectSSL(const char *host, uint16_t port)**
Connects using SSL to the specified host and port. Returns a value from enum *wl_tcp_state* (for open connection returns ESTABLISHED). No authentification checks are performed, recommended to use *verifySSL* function to check the server certificate.

- **uint8_t connected()**
Returns connection state as a logic value: 1 = connected, 0 = error. Note that the connection could be closed by a server when ESP8266 reads all data in its internal buffer although the master haven't read it yet.

- **uint8_t status()**
Returns connection state as a value from enum *wl_tcp_state* (for open connection returns ESTABLISHED).

- **void stop()**
Stops the client (disconnects from the remote server if still connected) and frees the socket used for the client.

- **operator bool()**
Returns true when the client is associated with a socket.

- **int verifySSL(uint8_t* fingerprint, const char *host)**
Verifies server SSL certificate for a fingerprint and domain name. The fingerprint is a 20 byte SHA-1 value certificate fingerprint. It can be read e.g. from web browser examinig the certificate. The parameter *fingerprint* is a 20 byte uint8_t array, it is *not* a character string. The parameter *host* is the domain name of the server we are connecting to.


----------

- **int available()**
Returns available bytes in the input queue (data received from the network) for reading.

- **int read()**
Reads one byte from the input queue. Returns -1 for an error.

- **int read(uint8_t *buf, size_t size)**
Reads *size* bytes into an input buffer *buf*. Returns 0 on success, -1 on error or insufficient data in the input queue.

- **int peek()**
Peeks into the input queue and returns the first byte in the queue. On error returns -1.

- **size_t write(uint8_t)**
Sends one byte to the network. Returns 1 on success, 0 on error.

- **size_t write(const void *buf, size_t size)**
Sends the buffer to the network. Returns number of bytes transmitted.

- **size_t write(const char *str)**
Sends the character string to the network. Returns number of bytes transmitted.

- **IPAddress remoteIP()**
Returns the IP address of the host who sent the current incoming packet. When there is no incoming connection returns 0.0.0.0.
 
- **uint16_t remotePort()**
Returns the port of the host who sent the current incoming packet. When there is no incoming connection returns 0.

### WiFiSpiServer

The library has a pool of 4 sockets and after exhausting all the sockets no more connection is available. Therefore it is important to close the socket (i. e. stop the server) when it is no longer used. This version of the library is further constrained to one client connection per server.

- **WiFiSpiServer(uint16_t port)**
Constructor. Does not open a connection.

- **void begin()**
Creates and starts the server listener on specified *port*.

- **uint8_t status()**
Returns the server's status. Return 1 for opened connection, 0 for closed or error.

- **void stop()**
Stops the listener, stops the associated client (if any) and frees the socket.

- **WiFiSpiClient available(uint8_t* status = NULL)**
Returns WiFiSpiClient instance for communication with remote client. Returns opened WiFiSpiClient instance when there is a remote client connected. When there is no connection the function returns closed client. Use the WiFiSpiClient's bool operator on the return value to test it.
When pointer *status* is not null, loads it with the remote client's status.
  
- **size_t write(uint8_t)**
Writes a byte to the output queue. Returns 1 on success, 0 on error.

- **size_t write(const uint8_t *buf, size_t size)**
Writes a buffer to the output queue. Returns number of bytes written.
Note: transmitting data can be also achieved using a WiFiSpiClient object returned by the *WiFiSpiServer::available()* function.

### WiFiSpiUDP

- **WiFiSpiUdp()**
Default constuctor.

- **uint8_t begin(uint16_t port)**
Initializes the instance, starts listening on specified *port*. Returns 1 if successful, 0 on error.

- **uint8_t begin(uint16_t multicastIP, uint16_t port)**
Initializes the instance, starts listening on specified *port* for multicast messages from *multicastIP* address. Returns 1 if successful, 0 on error.

- **void stop()**
Stops listening on the UDP port, frees the UDP socket used.

- **int beginPacket(IPAddress ip, uint16_t port)**
Starts building up a packet to send to the remote host specific in *ip* and *port*. Returns 1 if successful, 0 if there was a problem with the connection. This function works for both unicast and multicast communication.
    
- **int endPacket()**
Finishes the packet and sends it. Returns 1 if the packet was sent successfully, 0 if there was an error.
  
- **size_t write(uint8_t)**
Writes a single byte into the packet. Returns 1 on sucesss, 0 on error.
  
- **size_t write(const uint8_t *buffer, size_t size)**
Writes *size* bytes from buffer into the packet. Returns number of bytes written, on error returns 0.
 
- **int parsePacket();**
Starts processing the next available incoming packet. Returns the size of the packet in bytes, or 0 if no packets are available.
    
- **int available()**
Returns the number of bytes remaining in the current packet.
  
 - **int read()**
Reads a single byte from the current packet.

- **int read(unsigned char* buffer, size_t len) **
- **int read(char* buffer, size_t len)**
Reads up to *len* bytes from the current packet and places them into *buffer*. Returns the number of bytes read, or 0 if none are available or an error occurred.
    
- **int peek()**
Returns the next byte from the current packet without moving on to the next byte.

- **IPAddress remoteIP()**
Returns the IP address of the host who sent the current incoming packet. When there is no incoming connection returns 0.0.0.0.
 
- **uint16_t remotePort()**
Returns the port of the host who sent the current incoming packet. When there is no incoming connection returns 0.

## Examples

- **ConnectWithWPA**
Connects to the network and prints out some information.

- **WiFiWebClient**
Connects to the google.com site and transmits the http response.

- **MQTT_Publish**
Simple mqtt messaging.

- **UdpNTPClient**
Reads current time and date from a NTP server.

- **UDP_Multicast_Transmitter**
Peridically transmits a short messaage via UDP multicast.

- **UDP_Multicast_Receiver**
Listens for multicast messages, reads them and prints them out.

More examples to come soon. But you can easily use the ones from WiFi library. Don't forget to add a line *WiFiSpi.init();* before using other library functions.

## Debugging

For some debugging information on Serial output uncomment line 23 (#define _DEBUG) in file espspi_srv.cpp.

## ToDo and Wish Lists

- more SPI protocol optimization

## Credits

The protocol running on SPI interface was inspired by protocol used in Arduino WiFi library. The code structure and some code is taken from this library, too.

The SPI master code was inspired and parts were taken from the [ESPSlave example](https://github.com/esp8266/Arduino/tree/master/libraries/SPISlave) of the ESP8266 Arduino project.


