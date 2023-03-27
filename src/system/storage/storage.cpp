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


static String templateId;
static String templateName;
static String authToken;

Storage::Storage(int _num_relays)
{
  this->num_relays = _num_relays;
  // offset for credentials, plus space requred to save the configuration for each relay
  EEPROM.begin(CONF_MEM_START + (sizeof(eeprom_map_conf_time_t ) * _num_relays));
}

Storage::Storage()
{

}

Storage::~Storage()
{

}

void Storage::init(int _num_relays)
{
  this->num_relays = _num_relays;
  // offset for credentials, plus space requred to save the configuration for each relay
  EEPROM.begin(CONF_MEM_START + (sizeof(eeprom_map_conf_time_t ) * _num_relays));

}

bool Storage::saveCredentials(String templateID, String templateName, String authToken)
{
  EEPROM.put(TEMPLATE_ID_BASE,templateID);
  EEPROM.put(TEMPLATE_NAME_BASE, templateName);
  EEPROM.put(AUTH_TOKEN_BASE, authToken);
  EEPROM.commit();
  return true;
}

bool Storage::saveConfiguration(int relayID, uint8_t hour, uint8_t minute, uint8_t second, uint8_t duration, uint8_t days)
{
  relayConfigTime.hour      = hour;
  relayConfigTime.min       = minute;
  relayConfigTime.sec       = second;
  relayConfigTime.duration  = duration;
  relayConfigTime.days      = days;

  EEPROM.put(CONF_MEM_START * relayID, relayConfigTime);
  EEPROM.commit();

  return true;
}

bool Storage::getCredentials(String templateID, String templateName, String authToken)
{
  EEPROM.get(TEMPLATE_ID_BASE,templateID);
  EEPROM.get(TEMPLATE_NAME_BASE,templateName);
  EEPROM.get(AUTH_TOKEN_BASE,authToken);

  logger << LOG_INFO << "templateID " << templateID << EndLine;
  logger << LOG_INFO << "templateName " << templateName << EndLine;
  logger << LOG_INFO << "authToken " << authToken << EndLine;

  return true;
}

bool Storage::getConfiguration(int relayID, uint8_t hour, uint8_t minute, uint8_t second, uint8_t duration, uint8_t days)
{
  EEPROM.get(CONF_MEM_START + (sizeof(eeprom_map_conf_time_t) * relayID), relayConfigTime);
  hour      = relayConfigTime.hour;
  minute    = relayConfigTime.min;
  second    = relayConfigTime.sec;
  duration  = relayConfigTime.duration;
  days      = relayConfigTime.days;

  return true;
}

bool Storage::getPrevSavedInfo() 
{
  uint8_t isSaved = 0;
  EEPROM.get(SAVED_FLAG_START, isSaved);
  if (SAVED_DATA_FLAG == isSaved) {
    return true;
  }
  return false;
}

void Storage::setPrevSavedInfo() 
{
  EEPROM.put(SAVED_FLAG_START,SAVED_DATA_FLAG);
}
