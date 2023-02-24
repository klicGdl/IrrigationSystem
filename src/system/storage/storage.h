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
#include "../../utils/logger.h"

#define BLYNK_TEMPLATE_ID_MAX     20  // Max number of characters
#define BLYNK_TEMPLATE_NAME_MAX   20
#define BLYNK_AUTH_TOKEN_MAX      40
#define BLYNK_TEMPLATE_ID_BASE    0   // base address in bytes
#define BLYNK_TEMPLATE_NAME_BASE  20
#define BLYNK_AUTH_TOKEN_BASE     40

#define CONF_MEM_START  80            // leave the first space for credentials
                                      // save the conf above this address

typedef struct {
  uint8_t hour;
  uint8_t min;
  uint8_t sec;
  uint8_t duration;
  uint8_t days;
} conf_time_t;


String templateId;
String templateName;
String authToken;

class storage
{
private:
  int num_releys;
  conf_time_t reley;
  
public:
  storage(int _num_releys);
  ~storage();
  bool saveCredentials(String templateID, String templateName, String authToken);
  bool saveConfiguration(int releyID, uint8_t hour, uint8_t minute, uint8_t second, uint8_t duration, uint8_t days);
  bool getCredentials(String templateID, String templateName, String authToken);
  bool getConfiguration(int releyID, uint8_t hour, uint8_t minute, uint8_t second, uint8_t duration, uint8_t days);
  
};

#endif //__IRRIGATION_SYSTEM_STORAGE_STORAGE_H__
