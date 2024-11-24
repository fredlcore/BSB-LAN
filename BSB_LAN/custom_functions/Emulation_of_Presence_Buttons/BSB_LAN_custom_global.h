/*
 * Emulation of presence buttons for room units as well as DHW/TWW push functionality on selected pins.
 * Buttons need to be connected to the pins defined in variable "button_on_pin" in BSB_LAN_custom_global.h
 * Note regarding to pins: On Arduino Due any Digital pins can be selected excluding 12, 16-21, 31, 33, 53.
 * On ESP32, this depends on the model used.
 * Make sure you aren't using pins which are already in use for sensors or change them accordingly.
*/

uint8_t button_on_pin[4] = {0, 0, 0, 0}; // Order: TWW push, presence ROOM1, presence ROOM2, presence ROOM3

volatile byte PressedButtons = 0;
#define TWW_PUSH_BUTTON_PRESSED 1
#define ROOM1_PRESENCE_BUTTON_PRESSED 2
#define ROOM2_PRESENCE_BUTTON_PRESSED 4
#define ROOM3_PRESENCE_BUTTON_PRESSED 8

void interruptHandlerTWWPush() {
  PressedButtons = PressedButtons | TWW_PUSH_BUTTON_PRESSED;
}
void interruptHandlerPresenceROOM1() {
  PressedButtons = PressedButtons | ROOM1_PRESENCE_BUTTON_PRESSED;
}
void interruptHandlerPresenceROOM2() {
  PressedButtons = PressedButtons | ROOM2_PRESENCE_BUTTON_PRESSED;
}
void interruptHandlerPresenceROOM3() {
  PressedButtons = PressedButtons | ROOM3_PRESENCE_BUTTON_PRESSED;
}

void switchPresenceState(uint16_t set_mode, uint16_t current_state_index) {
  byte msg[33] = { 0 };     // response buffer
  byte tx_msg[33] = { 0 };  // xmit buffer
  if (bus->Send(TYPE_QUR, 0x2D3D0211 + (current_state_index << 24) , msg, tx_msg, 0, 0, true) != BUS_OK) return;
  if (msg[bus->getPl_start()] != 0x01) return; // 1 = Automatic
  switch (msg[bus->getPl_start() + 1]) {
    case 0x01: set(set_mode, "2", true); break; //Automatic in Reduced mode -> Automatic Reduced pushed into Comfort
    case 0x02: set(set_mode, "1", true); break; //Automatic in Comfort mode -> Automatic Comfort pushed into Reduced
    case 0x03: set(set_mode, "2", true); break; //Automatic Comfort mode, but pushed into Reduced -> Automatic Comfort
    case 0x04: set(set_mode, "1", true); break; //Automatic Reduced mode, but pushed into Comfort -> Automatic Reduced
    default: return;
  }
  // msg[bus->getPl_start() + 2] until msg[bus->getPl_start() + 7] contain the three time programs for the current day (multiply the value by 10 minutes, FF means disabled)
}
