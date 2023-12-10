# Callbacks

## [Register read/write callback](onSet/onSet.ino)

## [Use one callback function for multiple registers](onGetShared/onGetShared.ino)

## [Incoming request callback (applicable to server/slave)](Request/Request.ino)

## [Modbus TCP/TLS Incoming connection callback](onSet/onSet.ino)

## [Modbus TCP/TLS Transaction result](Transactional/Transactional.ino)

### Callback API

```c
bool onSetCoil(uint16_t address, cbModbus cb = nullptr, uint16_t numregs = 1);
bool onSetHreg(uint16_t address, cbModbus cb = nullptr, uint16_t numregs = 1);
bool onSetIsts(uint16_t address, cbModbus cb = nullptr, uint16_t numregs = 1);
bool onSetIreg(uint16_t address, cbModbus cb = nullptr, uint16_t numregs = 1);
```

- `address`   Address of register assign callback on
- `cb`    Callback function
- `numregs`   Count of sequental segisters assign this callback to

Assign callback function on register modify event. Multiple sequental registers can be affected by specifing `numregs` parameter.


```c
bool onGetCoil(uint16_t address, cbModbus cb = nullptr, uint16_t numregs = 1);
bool onGetHreg(uint16_t address, cbModbus cb = nullptr, uint16_t numregs = 1);
bool onGetIsts(uint16_t address, cbModbus cb = nullptr, uint16_t numregs = 1);
bool onGetIreg(uint16_t address, cbModbus cb = nullptr, uint16_t numregs = 1);
```

- `address`   Address of register assign callback on
- `cb`    Callback function
- `numregs`   Count of sequental segisters assign this callback to

Assign callback function on register query event. Multiple sequental registers can be affected by specifing `numregs` parameter.

```c
bool removeOnGetCoil(uint16_t offset, cbModbus cb = nullptr, uint16_t numregs = 1);
bool removeOnSetCoil(uint16_t offset, cbModbus cb = nullptr, uint16_t numregs = 1);
bool removeOnGetHreg(uint16_t offset, cbModbus cb = nullptr, uint16_t numregs = 1);
bool removeOnSetHreg(uint16_t offset, cbModbus cb = nullptr, uint16_t numregs = 1);
bool removeOnGetIsts(uint16_t offset, cbModbus cb = nullptr, uint16_t numregs = 1);
bool removeOnSetIsts(uint16_t offset, cbModbus cb = nullptr, uint16_t numregs = 1);
bool removeOnGetIreg(uint16_t offset, cbModbus cb = nullptr, uint16_t numregs = 1);
bool removeOnSetIreg(uint16_t offset, cbModbus cb = nullptr, uint16_t numregs = 1);
```

- `address`   Address of register assign callback on
- `cb`    Callback function or NULL to remove all the callbacks.
- `numregs`   Count of sequental segisters remove this callback to.

Disconnect specific callback function or all callbacks of the type if cb=NULL.

```c
typedef Modbus::ResultCode (*cbRequest)(Modbus::FunctionCode fc, const Modbus::RequestData data);
bool onRequest(cbRequest cb = _onRequestDefault);
bool onRequestSuccess(cbRequest cb = _onRequestDefault);

union Modbus::RequestData {
    struct {
        TAddress reg;
        uint16_t regCount;
    };
    struct {
        TAddress regRead;
        uint16_t regReadCount;
        TAddress regWrite;
        uint16_t regWriteCount;
    };
    struct {
        TAddress regMask;
        uint16_t andMask;
        uint16_t orMask;
    };
};
```

Callback function receives Modbus function code, structure `Modbus::RequestData` containing register type and offset (`TAddress` structure) and count of registers requested. The function should return [result code](#Result codes *Modbus::ResultCode*) `Modbus::EX_SUCCESS` to allow request processing or Modbus error code to block processing. This code will be returned to client/master.

```c
void onConnect(cbModbusConnect cb);
void onDisonnect(cbModbusConnect cb);
```

Assign callback function on incoming connection event.

```c
typedef bool (*cbModbusConnect)(IPAddress ip);
```

- `ip` Client's address of incomig connection source. `INADDR_NONE` for on disconnect callback.

## Result codes *Modbus::ResultCode*

|Value|Hex|Definition|Decription|
|---|---|---|---|
|Modbus::EX_SUCCESS|0x00|Custom|No error|
|Modbus::EX_ILLEGAL_FUNCTION|0x01|Modbus|Function Code not Supported|
|Modbus::EX_ILLEGAL_ADDRESS|0x02|Modbus|Output Address not exists|
|Modbus::EX_ILLEGAL_VALUE|0x03|Modbus|Output Value not in Range|
|Modbus::EX_SLAVE_FAILURE|0x04|Modbus|Slave or Master Device Fails to process request
|Modbus::EX_ACKNOWLEDGE|0x05|Modbus|Not used|
|Modbus::EX_SLAVE_DEVICE_BUSY|0x06|Modbus|Not used|
|Modbus::EX_MEMORY_PARITY_ERROR|0x08|Modbus|Not used|
|Modbus::EX_PATH_UNAVAILABLE|0x0A|Modbus|Not used|
|Modbus::EX_DEVICE_FAILED_TO_RESPOND|0x0B|Modbus|Not used|
|Modbus::EX_GENERAL_FAILURE|0xE1|Custom|Unexpected master error|
|Modbus::EX_DATA_MISMACH|0xE2|Custom|Inpud data size mismach|
|Modbus::EX_UNEXPECTED_RESPONSE|0xE3|Custom|Returned result doesn't mach transaction|
|Modbus::EX_TIMEOUT|0xE4|Custom|Operation not finished within reasonable time|
|Modbus::EX_CONNECTION_LOST|0xE5|Custom|Connection with device lost|
|Modbus::EX_CANCEL|0xE6|Custom|Transaction/request canceled|

# Modbus Library for Arduino
### ModbusRTU, ModbusTCP and ModbusTCP Security

(c)2020 [Alexander Emelianov](mailto:a.m.emelianov@gmail.com)

The code in this repo is licensed under the BSD New License. See LICENSE.txt for more info.