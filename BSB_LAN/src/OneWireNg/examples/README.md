# OneWireNg examples

### [`DallasTemperature`](DallasTemperature/DallasTemperature.ino)

Dallas temperature sensors example. Scan the bus for all supported types of
slaves. Convert temperature for all sensors simultaneously and read them
one-by-one. Possible permanent configuration change. The example uses generic
Dallas thermometers driver [`DSTherm`](../src/drivers/DSTherm.h).

### [`MAX31850`](MAX31850/MAX31850.ino)

MAX31850/MAX31851 thermocouple example. Scan the bus for supported
slaves. Convert temperature for all sensors simultaneously and read them
one-by-one. The example uses [`MAX31850`](../src/drivers/MAX31850.h) driver.

### [`OverdriveMode`](OverdriveMode/OverdriveMode.ino)

Basic overdrive example. Scan the bus for overdrive enabled devices.

### [`DS2431`](DS2431/DS2431.ino)

Simple DS2431 device (EEPROM memory) example. Read + write. Overdrive mode
support.
