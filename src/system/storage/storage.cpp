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


Storage::Storage(int _num_releys)
{
  this->num_releys = _num_releys;
  // offset for credentials, plus space requred to save the configuration for each reley
  EEPROM.begin(CONF_MEM_START + (sizeof(eeprom_map_conf_time_t ) * _num_releys));
}

Storage::~Storage()
{
}

bool Storage::saveCredentials(String templateID, String templateName, String authToken)
{
  EEPROM.put(offsetof(EEPROM_CredentialStorage_t, templateid),templateID);
  EEPROM.put(offsetof(EEPROM_CredentialStorage_t, templateName), templateName);
  EEPROM.put(offsetof(EEPROM_CredentialStorage_t, authToken), authToken);
  EEPROM.commit();
  return true;
}

bool Storage::saveConfiguration(int releyID, uint8_t hour, uint8_t minute, uint8_t second, uint8_t duration, uint8_t days)
{
  ReleyConfigTime.hour = hour;
  ReleyConfigTime.min = minute;
  ReleyConfigTime.sec = second;
  ReleyConfigTime.duration = duration;
  ReleyConfigTime.days = days;

  EEPROM.put(CONF_MEM_START * releyID, ReleyConfigTime);
  EEPROM.commit();

  return true;
}

bool Storage::getCredentials(String templateID, String templateName, String authToken)
{
  EEPROM.get(offsetof(EEPROM_CredentialStorage_t, templateid),templateID);
  EEPROM.get(offsetof(EEPROM_CredentialStorage_t, templateName),templateName);
  EEPROM.get(offsetof(EEPROM_CredentialStorage_t, authToken),authToken);

  logger << LOG_INFO << "templateID " << templateID << EndLine;
  logger << LOG_INFO << "templateName " << templateName << EndLine;
  logger << LOG_INFO << "authToken " << authToken << EndLine;

  return true;
}

bool Storage::getConfiguration(int releyID, uint8_t hour, uint8_t minute, uint8_t second, uint8_t duration, uint8_t days)
{
  EEPROM.get(CONF_MEM_START * releyID, ReleyConfigTime);
  hour    = ReleyConfigTime.hour;
  minute  = ReleyConfigTime.min;
  second  = ReleyConfigTime.sec;
  duration  = ReleyConfigTime.duration;
  days    = ReleyConfigTime.days;

  return true;
}
