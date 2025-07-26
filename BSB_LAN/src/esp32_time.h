//time library wrapper for ESP32 with TimeLib compatibility
#if defined(ESP32) || defined(ARDUINO_ARCH_ESP32)
#include <time.h>
#include <sys/time.h>
void setTime(int hr,int min,int sec,int day, int month, int yr){
  struct tm t = {0};        // Initalize to all 0's
  t.tm_year = yr - 1900;    // This is year-1900, so 121 = 2021
  t.tm_mon = month - 1;     // Month 0 - 11 
  t.tm_mday = day;          //Day of month
  t.tm_hour = hr;
  t.tm_min = min;
  t.tm_sec = sec;
  time_t epoch_ts = mktime(&t);
  struct timeval tv_ts = {.tv_sec = epoch_ts};
  settimeofday(&tv_ts, NULL);
}

int year(){
  struct tm now;
  getLocalTime(&now,0);
  return now.tm_year + 1900;
}

int month(){
  struct tm now;
  getLocalTime(&now,0);
  return now.tm_mon + 1;
}

int day(){
  struct tm now;
  getLocalTime(&now,0);
  return now.tm_mday;
}

int hour(){
  struct tm now;
  getLocalTime(&now,0);
  return now.tm_hour;
}

int minute(){
  struct tm now;
  getLocalTime(&now,0);
  return now.tm_min;
}

int second(){
  struct tm now;
  getLocalTime(&now,0);
  return now.tm_sec;
}
int weekday() {   // Sunday is day 1
  struct tm now;
  getLocalTime(&now,0);
  return now.tm_wday + 1;
}

#endif
