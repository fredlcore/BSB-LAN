# Modbus\TCP Security Example

### *Target Platforms:*
- *ESP8266 (CLient/Server)*
- *ESP32 (Client only)*

## [Sample certificates](certs)

[cert.cmd](certs/cert.cmd) Script to recreate all the certificates in the catalog. Requires OpenSSL installed.

[Good issue explanation to read](https://github.com/esp8266/Arduino/issues/6128)

## [Client](client/client.ino)

```c
bool connect(const char* host, uint16_t port, const char* client_cert = nullptr, const char* client_private_key = nullptr, const char* ca_cert = nullptr);
bool connectWithKnownKey(IPAddress ip, uint16_t port, const char* client_cert = nullptr, const char* client_private_key = nullptr, const char* key = nullptr);
```

- `const char* host`    Host name to connect to
- `uint16_t port` Host port
- `const char* client_cert` Client's certificate
- `const char* client_private_key`  Client's private key
- `const char* ca_cert` Certificate of CA. Can be omitted (or set NULL) to escape certificate chain verifying.
- `IPAddress ip`    Host IP address to connect to
- `const char* key` Server's public key

All certificates must be in PEM format and can be stored in PROGMEM.

## [Server](server/server.ino)

```c
void server(uint16_t port, const char* server_cert = nullptr, const char* server_private_key = nullptr, const char* ca_cert = nullptr);
```
- `uint16_t port`   Port to bind to
- `const char* server_cert` Server certificate in PEM format.
- `const char* server_private_key`  Server private key in PEM format.
- `const char* ca_cert` Certificate of CA.

All certificates must be in PEM format and can be stored in PROGMEM.

# Modbus Library for Arduino
### ModbusRTU, ModbusTCP and ModbusTCP Security

(c)2020 [Alexander Emelianov](mailto:a.m.emelianov@gmail.com)

The code in this repo is licensed under the BSD New License. See LICENSE.txt for more info.
