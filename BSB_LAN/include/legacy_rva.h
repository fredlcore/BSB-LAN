#ifndef BSB_LAN_LEGACY_RVA_H
#define BSB_LAN_LEGACY_RVA_H

#include <stdint.h>
#include <stddef.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

// Legacy LPB helpers used by the tested family 22 and 23, variant 254 profiles.
// See docs/development/eurocontrol-k-lpb.md and eurocontrol-m-lpb.md for limits.
inline bool decodeScalarEnableState(const uint8_t *payload, size_t length, uint8_t &value) {
  if (length != 2 || payload[0] > 1) return false;
  value = payload[0] == 0 ? 1 : 0;
  return true;
}

inline bool decodeRawRelayOnOff(const uint8_t *payload, size_t length, uint32_t flags, uint8_t &value) {
  const uint8_t offset = (flags >> 16) & 0x0F;
  const uint8_t width = (flags >> 20) & 0x0F;
  if (length != 8 || width != 1 || offset >= length) return false;
  if (payload[offset] != 0 && payload[offset] != 0xFF) return false;
  value = payload[offset] == 0 ? 0 : 1;
  return true;
}

inline bool legacyRvaSettingValid(uint8_t busType, uint8_t family, uint8_t variant,
                                  uint32_t command, const char *value, bool isSet) {
  if (busType != 1 || family != 22 || variant != 254) return true;
  if (command != 0x0500060F && command != 0x0500060B) return true;
  if (!isSet || value == nullptr) return false; // Only SET has been verified.
  if (command == 0x0500060B) return strcmp(value, "0") == 0 || strcmp(value, "1") == 0;
  if (strcmp(value, "---") == 0 || value[0] == '\0') return true;
  char *end = nullptr;
  const double number = strtod(value, &end);
  if (end == value || !isfinite(number)) return false;
  while (*end == ' ' || *end == '\t') ++end;
  return *end == '\0' && number >= 0.5 && number <= 4.0;
}

// These strings are available before a custom command table is included.
const char RVA_ROOM_STATE[] = RVA_ROOM_STATE_TEXT;
const char RVA_ROOM_GAIN[] = RVA_ROOM_GAIN_TEXT;
const char RVA_ROOM_DIFF[] = RVA_ROOM_DIFF_TEXT;
const char RVA_ADAPTATION[] = RVA_ADAPTATION_TEXT;
const char RVA_PUMP_Q1[] = RVA_PUMP_Q1_TEXT;
const char RVA_MODE[] = STR700_TEXT;
const char RVA_MODE_ENUM[] = {
  "\x00 Standby\0"
  "\x01 " RVA_MODE_AUTO_TEXT "\0"
  "\x04 " RVA_MODE_MANUAL_TEXT
};
// M panel test: upper continuous-operation button, emergency manual OFF.
// Keep K's historical mapping separate until its own controlled panel test.
const char RVA_M_MODE_ENUM[] = {
  "\x00 Standby\0"
  "\x01 " RVA_MODE_AUTO_TEXT "\0"
  "\x04 " RVA_MODE_CONTINUOUS_TEXT
};
// VT_CUSTOM_BYTE reads the retained numeric component even when influence is off.
const char RVA_GAIN_BYTE[] = {1, 1, ' '};

// Model-neutral labels: the M panel numbering is not established by the K manual.
const char RVA_ROOM_STATE_GENERIC[] = RVA_ROOM_STATE_GENERIC_TEXT;
const char RVA_ROOM_DIFF_GENERIC[] = RVA_ROOM_DIFF_GENERIC_TEXT;
const char RVA_LEGACY_CURVE[] = RVA_LEGACY_CURVE_TEXT;
const char RVA_PUMP_OVERRUN[] = RVA_PUMP_OVERRUN_TEXT;
const char RVA_OUTSIDE[] = RVA_OUTSIDE_TEXT;
const char RVA_M_PUMP[] = RVA_M_PUMP_TEXT;
const char RVA_M_MIXER_OPEN[] = RVA_M_MIXER_OPEN_TEXT;
const char RVA_M_MIXER_CLOSE[] = RVA_M_MIXER_CLOSE_TEXT;

#endif
