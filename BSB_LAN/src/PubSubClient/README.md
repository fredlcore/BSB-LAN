## ThingsBoard note

This is a fork of the main repository, which was last updated in 2020.
Since we have an SDK based on this client, we decided to continue with this repository.
We also believe that this library provides a lot of opportunities for people who want to build their own IoT devices.
As with our other open source repositories, we appreciate every contribution to this library.


# Arduino Client for MQTT

This library provides a client for doing simple publish/subscribe messaging with
a server that supports MQTT.

## Examples

The library comes with a number of example sketches. See File > Examples > PubSubClient
within the Arduino application.

Full API documentation is available here: https://pubsubclient.knolleary.net

## Limitations

 - It can only publish QoS 0 messages. It can subscribe at QoS 0 or QoS 1.
 - Individual buffers are used to send and receive messages. The default maximum message size in each buffer, including header, is **256 bytes**. This
   is configurable via `MQTT_MAX_PACKET_SIZE` in `PubSubClient.h` or each buffer's size can be changed at runtime
   by calling `PubSubClient::setBufferSize(uint16_t receive_size, uint16_t send_size)`.
 - The keepalive interval is set to 15 seconds by default. This is configurable
   via `MQTT_KEEPALIVE` in `PubSubClient.h` or can be changed by calling
   `PubSubClient::setKeepAlive(keepAlive)`.
 - The client uses MQTT 3.1.1 by default. It can be changed to use MQTT 3.1 by
   changing value of `MQTT_VERSION` in `PubSubClient.h`.


## Compatible Hardware

The library uses the Arduino Ethernet Client api for interacting with the
underlying network hardware. This means it Just Works with a growing number of
boards and shields, including:

 - Arduino Ethernet
 - Arduino Ethernet Shield
 - Arduino YUN – use the included `YunClient` in place of `EthernetClient`, and
   be sure to do a `Bridge.begin()` first
 - Arduino WiFi Shield - if you want to send packets > 90 bytes with this shield,
   enable the `MQTT_MAX_TRANSFER_SIZE` define in `PubSubClient.h`.
 - Sparkfun WiFly Shield – [library](https://github.com/dpslwk/WiFly)
 - TI CC3000 WiFi - [library](https://github.com/sparkfun/SFE_CC3000_Library)
 - Intel Galileo/Edison
 - ESP8266
 - ESP32

The library cannot currently be used with hardware based on the ENC28J60 chip –
such as the Nanode or the Nuelectronics Ethernet Shield. For those, there is an
[alternative library](https://github.com/njh/NanodeMQTT) available.

## License

This code is released under the MIT License.
