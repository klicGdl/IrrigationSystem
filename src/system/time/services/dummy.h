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
#if !defined(__IRRIGATION_SYSTEM_TIME_SERVICES_DUMMY_H__)
#define __IRRIGATION_SYSTEM_TIME_SERVICES_DUMMY_H__

#include "../itime_provider.h"
#include "../datetime.h"

class DummyTimeProvider : public ITimeProvider
{
public:
    /**
     * @brief Initialize the time provider.
     * 
     * @return true  On success
     * @return false On failure
     */
    bool init() override {
        return true;
    }

    /**
     * @brief Update the internal datetime.
     * 
     * @return true  On success
     * @return false On failure
     */
    bool update() override {
        return true;
    }
};


#endif // __IRRIGATION_SYSTEM_TIME_SERVICES_DUMMY_H__
