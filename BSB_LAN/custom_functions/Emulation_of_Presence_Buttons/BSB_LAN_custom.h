/*
 * Emulation of presence buttons for room units as well as DHW/TWW push functionality on selected pins.
 * Buttons need to be connected to the pins defined in variable "button_on_pin" in BSB_LAN_custom_global.h
 * Note regarding to pins: On Arduino Due any Digital pins can be selected excluding 12, 16-21, 31, 33, 53.
 * On ESP32, this depends on the model used.
 * Make sure you aren't using pins which are already in use for sensors or change them accordingly.
*/

if (PressedButtons) {
  for (uint8_t i = 0; i < 8; i++) {
    switch (PressedButtons & (0x01 << i)) {
      case TWW_PUSH_BUTTON_PRESSED:
        set(10019, "1", true);
        PressedButtons = PressedButtons & ~TWW_PUSH_BUTTON_PRESSED;
        break;
      case ROOM1_PRESENCE_BUTTON_PRESSED:
        switchPresenceState(10110, 0);
        PressedButtons = PressedButtons & ~ROOM1_PRESENCE_BUTTON_PRESSED;
        break;
      case ROOM2_PRESENCE_BUTTON_PRESSED:
        switchPresenceState(10111, 1);
        PressedButtons = PressedButtons & ~ROOM2_PRESENCE_BUTTON_PRESSED;
        break;
      case ROOM3_PRESENCE_BUTTON_PRESSED:
        switchPresenceState(10112, 2);
        PressedButtons = PressedButtons & ~ROOM3_PRESENCE_BUTTON_PRESSED;
        break;
      default: PressedButtons = PressedButtons & ~(0x01 << i); break; //clear unknown state
    }
  }
}
