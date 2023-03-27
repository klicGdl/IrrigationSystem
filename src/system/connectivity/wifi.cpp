#include "wifi.h"
#include "utils/logger.h"
#include "utils/storage.h"

#define WIFI_MANAGER_PARAMETER_SIZE 20

static WiFiManager wm;
using namespace WiFiConnection;

static String templateID;
static String deviceName;
static String token;

static void setPreSaveConfigCallback()
{
    if((wm.server->hasArg("template_id")) || (wm.server->hasArg("device_name")) || (wm.server->hasArg("auth_token")))
    {
        templateID = wm.server->arg("template_id");
        deviceName = wm.server->arg("device_name");
        token = wm.server->arg("auth_token");
        logger << LOG_INFO << "TemplateID = " << templateID << EndLine;
        logger << LOG_INFO << "Device Name = " << deviceName << EndLine;
        logger << LOG_INFO << "Token = " << token << EndLine;
    }
    else 
    {
        logger << LOG_ERROR << "At least one of the configuration is missing" << EndLine;
    }

    storage.saveCredentials(templateID,deviceName,token);
    storage.setPrevSavedInfo();
}

/**
 * @brief Initialize WIFI interface using the specified configuration.
 * 
 * @param wifi_ssid      [Optional] WiFi SSID as a const char string.
 * @param wifi_password  [Optional] WiFi Password as a const char string.
 * @return wl_status_t   WiFi status code.
 */
wl_status_t WiFiConnection::WifiInitialize (
    const char* wifi_ssid,
    const char* wifi_password
    )
{
    String templ_id = "template_id";
    String dev_name = "Device_name";
    String auth_token = "auth_token";

    logger << LOG_INFO << "Initializing WiFi provider!" << EndLine;
    if(storage.getPrevSavedInfo()) {
        storage.getCredentials(templ_id,dev_name,auth_token);
    }
    // parameters  = ID, label, default_value, size
    WiFiManagerParameter templateID("template_id", "TEMPLATE_ID", templ_id.c_str(), WIFI_MANAGER_PARAMETER_SIZE);
    WiFiManagerParameter deviceName("device_name", "DEVICE_NAME", dev_name.c_str(), WIFI_MANAGER_PARAMETER_SIZE);
    WiFiManagerParameter authToken("auth_token", "AUTH_TOKEN", auth_token.c_str(), WIFI_MANAGER_PARAMETER_SIZE);

    wm.addParameter(&templateID);
    wm.addParameter(&deviceName);
    wm.addParameter(&authToken);

    wm.setPreSaveConfigCallback(setPreSaveConfigCallback);

    wm.setTitle("Irrigation System");
    const char *menu[] = {"wifi","info","param","sep","restart","exit"};
    wm.setMenu(menu,6);
    wm.setClass("invert");

    // wm.resetSettings();
    // Set the ESP as AccesPoint
    WiFi.mode(WIFI_STA);

    // will try to connect when it has saved credentials
    // if it fails will start the access point
    if (wm.autoConnect(wifi_ssid,wifi_password)){
        logger << LOG_INFO << "WiFi AutoConnect done! IP: " << WiFi.localIP() << EndLine;
    }

    return WL_CONNECTED;
}



