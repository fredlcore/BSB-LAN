/*
 * Emulation of temperature sensor of room unit.
 * You can enter up to five parameter numbers which provide temperature data (for example sensors attached to BSB-LAN) and 
 * enter these into the three segments of "rgte_sensorid" in BSB_LAN_custom_global.h
 * The segments 1 to 3 correspond to the room units configured for heating circuits 1 to 3.
 * If you enter more than one parameter number for one segment, then an average will be calulated and sent to the heater.
 * A segment of all zeros means that no data will be sent to the corresponding heating circuit.
*/

parameter rgte_sensorid[3][5] = {{0, 0, 0, 0, 0}, {0, 0, 0, 0, 0}, {0, 0, 0, 0, 0}}; //Temperature sensor program IDs for RGT1/PPS - RGT3. If zero then RGT will not be emulated. If more than one program set per RGT then average will be calculated and used.
byte newMinuteValue = 99;
