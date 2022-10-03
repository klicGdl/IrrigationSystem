/*----------------------------------------------------------------------*
 *  _   __ _     _____ _____                                            *
 * | | / /| |   |_   _/  __ \   This software is been developed by      *
 * | |/ / | |     | | | /  \/   a group of enthusiast hobbiest          *
 * |    \ | |     | | | |       with the purpose of learn and           *
 * | |\  \| |_____| |_| \__/\   have fun, so nobody is responsible or   *
 * \_| \_/\_____/\___/ \____/   will provide warranty.                  *
 *                                                                      *
 * This software will run in a ESP8266 microcontrolller, the objective  *
 * is to have a irrigation system controler that can read some sensors  *
 * and decide if a valve should be open.                                *
 * There is not restriction to use, modify and improve the code, so     *
 * please do it and share the improvements.                             *
 *                                                                      *
 * Letś have Fun!!                                                      *
 *                                                                      *
 * ---------------------------------------------------------------------*/
#if !defined(__IRRIGATION_SYSTEM_TIME_H__)
#define __IRRIGATION_SYSTEM_TIME_H__

#include <stdint.h>
#include <Arduino.h>
#include <RTClib.h>

typedef enum {
  SUNDAY = 0,
  MONDAY = 1,
  TUESDAY = 2,
  WENSDAY = 3,
  THURSDAY = 4,
  FRIDAY = 5,
  SATURNDAY = 6,
  DAYS_PER_WEEK = 7
} WeekDays_e;

struct Time_s {
  uint16_t year;
  uint8_t month;
  uint8_t day;
  uint8_t hour;
  uint8_t minute;
  uint8_t second;
  
  Time_s() { }
  Time_s(uint16_t year, uint8_t month, uint8_t day, uint8_t hour, uint8_t minute, uint8_t second);
  Time_s(DateTime time);

  String toString() const;
  void toCharArray(char *buff) const;
  DateTime toDateTime() const;
  bool operator==(Time_s&);
};
typedef struct Time_s Time_s;

#endif // __IRRIGATION_SYSTEM_TIME_H__
