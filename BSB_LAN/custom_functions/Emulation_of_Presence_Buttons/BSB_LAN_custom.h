/*
 * Emulation of presence buttons for room units as well as DHW/TWW push functionality on selected pins.
 * Buttons need to be connected to the pins defined in variable "button_on_pin" in BSB_LAN_custom_global.h
 * Parameters 10102, 10103 and 10104 need to be copied from version 2.2.1's BSB_LAN_custom_defs.h and added to current BSB_LAN_custom_defs.h
 * If these parameter numbers are already in use, changes need to be made to the parameter numbers in BSB_LAN_custom.h
 * Note regarding to pins: On Arduino Due any Digital pins can be selected excluding 12, 16-21, 31, 33, 53.
 * On ESP32, this depends on the model used.
 * Make sure you aren't using pins which are already in use for sensors or change them accordingly.
*/

  if (PressedButtons) {
    for (uint8_t i = 0; i < 8; i++) {
      switch (PressedButtons & (0x01 << i)) {
        case TWW_PUSH_BUTTON_PRESSED:
          strcpy_P(decodedTelegram.value, PSTR("1"));
          set(1603, decodedTelegram.value, true);
          PressedButtons &= ~TWW_PUSH_BUTTON_PRESSED;
          break;
        case ROOM1_PRESENCE_BUTTON_PRESSED:
          switchPresenceState(701, 10102);
          PressedButtons &= ~ROOM1_PRESENCE_BUTTON_PRESSED;
          break;
        case ROOM2_PRESENCE_BUTTON_PRESSED:
          switchPresenceState(1001, 10103);
          PressedButtons &= ~ROOM2_PRESENCE_BUTTON_PRESSED;
          break;
        case ROOM3_PRESENCE_BUTTON_PRESSED:
          switchPresenceState(1301, 10104);
          PressedButtons &= ~ROOM3_PRESENCE_BUTTON_PRESSED;
          break;
        default: PressedButtons &= ~(0x01 << i); break; //clear unknown state
      }
    }
  }
