/*
 * Emulation of presence buttons for room units as well as DHW/TWW push functionality on selected pins.
 * Buttons need to be connected to the pins defined in variable "button_on_pin" in BSB_LAN_custom_global.h
 * Note regarding to pins: On Arduino Due any Digital pins can be selected excluding 12, 16-21, 31, 33, 53.
 * On ESP32, this depends on the model used.
 * Make sure you aren't using pins which are already in use for sensors or change them accordingly.
*/

if (button_on_pin[0]) {
  pinMode(button_on_pin[0], INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(button_on_pin[0]), interruptHandlerTWWPush, FALLING); //TWW push-button
}
if (button_on_pin[1]) {
  pinMode(button_on_pin[1], INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(button_on_pin[1]), interruptHandlerPresenceROOM1, FALLING); //Presence ROOM 1 button
}
if (button_on_pin[2]) {
  pinMode(button_on_pin[2], INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(button_on_pin[2]), interruptHandlerPresenceROOM2, FALLING); //Presence ROOM 2 button
}
if (button_on_pin[3]) {
  pinMode(button_on_pin[3], INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(button_on_pin[3]), interruptHandlerPresenceROOM3, FALLING); //Presence ROOM 3 button
}
