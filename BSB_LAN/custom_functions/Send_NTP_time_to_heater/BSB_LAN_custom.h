/*
 * This script sends the current time and date to the heater every 10 minutes.
 * For this to make sense, you must have the USE_NTP definement enabled in BSB_LAN_config.h.
 * Works only on ESP32-based microcontrollers, not (yet) Arduino Due!
*/
#if defined(ESP32) || defined(ARDUINO_ARCH_ESP32)
if (custom_timer > custom_timer_compare+600000) {    // every 10 minutes
  custom_timer_compare = millis();
  char date_string[20];
  struct tm now;
  getLocalTime(&now,100);
  sprintf_P(date_string,"%02d.%02d.%d_%02d:%02d:%02d", now.tm_mday, now.tm_mon + 1, now.tm_year + 1900, now.tm_hour,now.tm_min,now.tm_sec);
  if (now.tm_year > 100 && now.tm_hour > 4) {       // only send time after 04:00 in case that day the heater changes time because of daylight saving
    set(0,date_string,1);
  }
}
#endif
