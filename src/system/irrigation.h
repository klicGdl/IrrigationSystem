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
#if !defined(__IRRIGATION_SYSTEM_H__)
#define __IRRIGATION_SYSTEM_H__

#include "system/time/itime_provider.h"
#include "system_data.h"
#include "system/relays/io_expander.h"
#include "system/relays/io_relay.h"
#include "time/services/ntp.h"
#include "time/services/rtc.h"
#include "utils/list.h"

#define KERNEL_VERSION "0.2.1"
#define KERNEL_SERIAL_SPEED 115200

class SystemTimeProvider : public ITimeProvider {
    LinkedList<ITimeProvider*> providers;
public:
    SystemTimeProvider()
    : providers () { }

    template <typename Tprovider>
    bool TryToRegisterTimeProvider () {
        Tprovider *p = new Tprovider();
        providers.add(p);
        return true;
    }

    int countTimeProviders () {
        return providers.size();
    }

    virtual const char* getTypeName () const { return "None"; }

    const LinkedList<const char*> getNames() {
        LinkedList<const char*> names;
        _for_each(providers, _tp, ITimeProvider *)
        {
            names.add(_tp->getTypeName());
        }
        return names;
    }

    bool init() {
        bool success = true;
        _for_each(providers, _tp, ITimeProvider *)
        {
            if (!_tp->init())
            {
                delete _tp;
                success = false;
            }
        }
        return success;
    }

    bool update() {
        bool anySucess = false;
        _for_each(providers, _tp, ITimeProvider *)
        {
            if (_tp->update()) {
                datetime = _tp->get();
                anySucess = true;
            } else if (anySucess) {
                _tp->set(datetime);
            }
        }
        return anySucess;
    }
};

class IrrigationSystem {
    //
    // Components
    //
    SystemTimeProvider timeProviders;
    IOExpander ioExpander;
    LinkedList<IORelay*> *relays;

    //
    // Private methods
    //
    void DumpSysInfo();
    void InitLogger();
    void InitWifi();
    void InitDevices();
    void InitSensors();
    void InitRelays();
    void ConfigureTimeProviders();

    void ScanI2CDevicesAndDumpTable();

    bool IsSystemInitializedAtMinimal ();

    //
    // Data members
    //
    SystemData_t Status;
public:
    IrrigationSystem();
    bool init();
    void run();
};

#endif // __IRRIGATION_SYSTEM_H__
