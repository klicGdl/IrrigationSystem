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
/*
 * Save them in the simulated EEPROM
 * |------------| 0x0
 * | templateID |
 * |------------|
 * | templ name |
 * |------------|
 * | auth_token |
 * |------------|
*/
bool Storage::saveCredentials(String templateID, String templateName, String authToken)
{
  EEPROM_CredentialStorage_t d;
  strcpy(d._templateid,templateID.c_str());
  strcpy(d._templateName,templateName.c_str());
  strcpy(d._authToken,authToken.c_str());
  EEPROM.put(offsetof(EEPROM_CredentialStorage_t, _templateid),d);

  EEPROM.commit();
  logger << LOG_INFO << "Credentials saved" << EndLine;

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
  EEPROM_CredentialStorage_t d;
  // Check if info was saved previously, if not return empty strings
  if(getPrevSavedInfo()) {
    // Credentials are on the bottom of the reserved memory, use address 0
    EEPROM.get(0,d);
    templateID = d._templateid;
    templateName = d._templateName;
    authToken = d._authToken;

    logger << LOG_INFO << "templateID " << templateID << EndLine;
    logger << LOG_INFO << "templateName " << templateName << EndLine;
    logger << LOG_INFO << "authToken " << authToken << EndLine;
  } else {
    templateID = templateName = authToken = "";
  }
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
  logger << LOG_INFO << "Checking saved flag = " << INT_HEX << isSaved << EndLine;
  if (SAVED_DATA_FLAG == isSaved) {
    return true;
  }
  return false;
}

void Storage::setPrevSavedInfo() 
{
  EEPROM.put(SAVED_FLAG_START,SAVED_DATA_FLAG);
  logger << LOG_INFO << "Setting saved flag - " << INT_HEX << SAVED_DATA_FLAG << EndLine; 
}
