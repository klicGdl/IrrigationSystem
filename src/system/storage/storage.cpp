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

#include "storage.h"


storage::storage(int _num_releys)
{
  this->num_releys = _num_releys;
  // offset for credentials, plus space requred to save the configuration for each reley
  EEPROM.begin(CONF_MEM_START + (sizeof(conf_time_t) * _num_releys));
}

storage::~storage()
{
}

bool storage::saveCredentials(String templateID, String templateName, String authToken)
{
  EEPROM.put(BLYNK_TEMPLATE_ID_BASE,templateID);
  EEPROM.put(BLYNK_TEMPLATE_NAME_BASE, templateName);
  EEPROM.put(BLYNK_AUTH_TOKEN_BASE, authToken);
  EEPROM.commit();
  return true;
}

bool storage::saveConfiguration(int releyID, uint8_t hour, uint8_t minute, uint8_t second, uint8_t duration, uint8_t days)
{
  reley.hour = hour;
  reley.min = minute;
  reley.sec = second;
  reley.duration = duration;
  reley.days = days;

  EEPROM.put(CONF_MEM_START * releyID, reley);
  EEPROM.commit();

  return true;
}

bool storage::getCredentials(String templateID, String templateName, String authToken)
{
  EEPROM.get(BLYNK_TEMPLATE_ID_BASE,templateID);
  EEPROM.get(BLYNK_TEMPLATE_NAME_BASE,templateName);
  EEPROM.get(BLYNK_AUTH_TOKEN_BASE,authToken);

  logger << LOG_INFO << "templateID " << templateID << EndLine;
  logger << LOG_INFO << "templateName " << templateName << EndLine;
  logger << LOG_INFO << "authToken " << authToken << EndLine;

  return true;
}

bool storage::getConfiguration(int releyID, uint8_t hour, uint8_t minute, uint8_t second, uint8_t duration, uint8_t days)
{
  EEPROM.get(CONF_MEM_START * releyID, reley);
  hour    = reley.hour;
  minute  = reley.min;
  second  = reley.sec;
  duration  = reley.duration;
  days    = reley.days;

  return true;
}
