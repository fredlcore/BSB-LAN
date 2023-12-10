/*
    Modbus Library for Arduino
    ModbusTCP for W5x00 Ethernet
    Copyright (C) 2022 Alexander Emelianov (a.m.emelianov@gmail.com)
*/

#pragma once
#if defined(MODBUSIP_USE_DNS)
#include <Dns.h>
#endif
#include "ModbusAPI.h"
#include "ModbusTCPTemplate.h"

// Ethernet class wrapper to be able to compile for ESP32
class EthernetServerWrapper : public EthernetServer {
    public:
    EthernetServerWrapper(uint16_t port) : EthernetServer(port) {

    }
    void begin(uint16_t port=0) {

    }
};

class ModbusEthernet : public ModbusAPI<ModbusTCPTemplate<EthernetServerWrapper, EthernetClient>> {
#if defined(MODBUSIP_USE_DNS)
    private:
    static IPAddress resolver (const char* host) {
        DNSClient dns;
        IPAddress ip;
        
        dns.begin(Ethernet.dnsServerIP());
        if (dns.getHostByName(host, ip) == 1)
            return ip;
        else
            return IPADDR_NONE;
    }
    public:
    ModbusEthernet() : ModbusAPI() {
        resolve = resolver;
    }
#endif
};
