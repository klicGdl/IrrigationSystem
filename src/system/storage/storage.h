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
 * Let's have Fun!!                                                     *
 *                                                                      *
 * ---------------------------------------------------------------------*/

#if !defined(__IRRIGATION_SYSTEM_STORAGE_STORAGE_H__)
#define __IRRIGATION_SYSTEM_STORAGE_STORAGE_H__
#include <Arduino.h>
#include <EEPROM.h>
#include <stddef.h>
#include  <stdint.h>
#include "../../utils/logger.h"

#define TEMPLATE_ID_MAX     20  // Max number of characters
#define TEMPLATE_NAME_MAX   20
#define AUTH_TOKEN_MAX      40
#define TEMPLATE_ID_BASE    0   // base address in bytes
#define TEMPLATE_NAME_BASE  20
#define AUTH_TOKEN_BASE     40


typedef struct {
  uint8_t hour;
  uint8_t min;
  uint8_t sec;
  uint8_t duration;
  uint8_t days;
} eeprom_map_conf_time_t;


class Storage
{
private:
  int num_relays;
  eeprom_map_conf_time_t relayConfigTime;
  
public:
  Storage(int _num_relays);
  ~Storage();
  bool saveCredentials(String templateID, String templateName, String authToken);
  bool saveConfiguration(int relayID, uint8_t hour, uint8_t minute, uint8_t second, uint8_t duration, uint8_t days);
  bool getCredentials(String templateID, String templateName, String authToken);
  bool getConfiguration(int relayID, uint8_t hour, uint8_t minute, uint8_t second, uint8_t duration, uint8_t days);
  
};

#endif //__IRRIGATION_SYSTEM_STORAGE_STORAGE_H__
