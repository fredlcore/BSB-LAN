/*
 * Emulation of presence buttons for room units as well as DHW/TWW push functionality on selected pins.
 * Buttons need to be connected to the pins defined in variable "button_on_pin" in BSB_LAN_custom_global.h
 * Parameters 10102, 10103 and 10104 need to be copied from version 2.2.1's BSB_LAN_custom_defs.h and added to current BSB_LAN_custom_defs.h
 * If these parameter numbers are already in use, changes need to be made to the parameter numbers in BSB_LAN_custom.h
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
  PressedButtons |= TWW_PUSH_BUTTON_PRESSED;
}
void interruptHandlerPresenceROOM1() {
  PressedButtons |= ROOM1_PRESENCE_BUTTON_PRESSED;
}
void interruptHandlerPresenceROOM2() {
  PressedButtons |= ROOM2_PRESENCE_BUTTON_PRESSED;
}
void interruptHandlerPresenceROOM3() {
  PressedButtons |= ROOM3_PRESENCE_BUTTON_PRESSED;
}

void switchPresenceState(uint16_t set_mode, uint16_t current_state) {
  //RGT1 701, 10102
  //RGT2 1001, 10103
  //RGT3 1301, 10104
  int state = 0;
  char buf[9];
  unsigned int i0, i1;
  query(current_state);
  strcpy(buf, "%02x%02x");
  if (2 != sscanf(decodedTelegram.value, buf, &i0, &i1)) return;
  if (i0 != 0x01) return; // 1 = Automatic
  switch (i1) {
    case 0x01: state = 0x02; break; //Automatic in Reduced mode -> Automatic Reduced pushed into Comfort
    case 0x02: state = 0x01; break; //Automatic in Comfort mode -> Automatic Comfort pushed into Reduced
    case 0x03: state = 0x02; break; //Automatic Comfort mode, but pushed into Reduced -> Automatic Comfort
    case 0x04: state = 0x01; break; //Automatic Reduced mode, but pushed into Comfort -> Automatic Reduced
    default: return;
  }
  sprintf_P(buf, "%d", state);
  set(set_mode, buf, true);
}
