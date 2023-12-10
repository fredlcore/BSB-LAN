// Start Modbus server
mb.server(502);                     // Start Modbus server on port 502

// Callback functions
mb.onConnect(cbConn);            // Add callback on connection event - remove this when using Modbus RTU (over serial / RS485)
mb.onGetHreg(0, cbGet, 20720);   // add callback for get holding register request
mb.onSetHreg(0, cbSet, 20720);   // add callback for set holding register request

// Add registers that should be accessible over Modbus here. 
// ATTENTION: These registers comsume RAM and definig too many can lead to crashes of the ESP32!
mb.addHreg(700, 0, 100);         // add one holding register for each parameter from 700 to 799
mb.addHreg(10000, 0, 1);         // holding register for parameter 10000
mb.addHreg(20700, 0, 20);        // holding register for custom floats (20700-20719)
