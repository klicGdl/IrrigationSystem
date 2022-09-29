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
#if !defined(__IRRIGATION_SYSTEM_RELAY_BUILDER_H__)
#define __IRRIGATION_SYSTEM_RELAY_BUILDER_H__

#include "io_expander.h"
#include "io_relay.h"
#include "system/system_data.h"
#include "system/time/itime_provider.h"
#include <utils/list.h>

class RelayBuilder;

class RelayCollectionBuilder
{
    LinkedList<IORelay*> relays;
    IOExpander *expander;
    ITimeProvider *timeProvider;
    SystemData_t *sysData;

    friend class RelayBuilder;

public:
    static RelayCollectionBuilder create()
    {
        return RelayCollectionBuilder();
    }

    RelayCollectionBuilder();

    RelayCollectionBuilder &setExpander(IOExpander *expander);
    RelayCollectionBuilder &setTimeProvider(ITimeProvider *expander);
    RelayCollectionBuilder &setSystemData(SystemData_t *sysData);
    RelayBuilder forPin(IOActionPin_e position);

    LinkedList<IORelay*> build();
};

class RelayBuilder
{
    RelayCollectionBuilder *parent;
    IOActionPin_e position;
    IORelayConfig_t config;

public:
    RelayBuilder(IOActionPin_e position, RelayCollectionBuilder *parent = nullptr);

    RelayBuilder forPin(IOActionPin_e position);
    IORelay *build();

    RelayCollectionBuilder* done();

    RelayBuilder &onTime (uint8_t hour, uint8_t minute, uint8_t second);
    RelayBuilder &onDay (WeekDays_e day);
    RelayBuilder &duration (uint16_t seconds);
};

#endif // __IRRIGATION_SYSTEM_RELAY_BUILDER_H__
