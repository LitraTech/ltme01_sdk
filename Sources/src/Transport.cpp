#include "ltme01_sdk/Transport.h"

#include <typeinfo>

#include "ltme01_sdk/lan/LanLocation.h"
#include "ltme01_sdk/lan/LanTransport.h"

#include "ltme01_sdk/usb/UsbLocation.h"
#include "ltme01_sdk/usb/UsbTransport.h"

ltme01_sdk::Transport* ltme01_sdk::Transport::createInstance(const Location& location)
{
#ifdef ENABLE_USB
  if (typeid(location) == typeid(UsbLocation))
    return new UsbTransport(dynamic_cast<const UsbLocation&>(location));
#endif
  if (typeid(location) == typeid(LanLocation))
    return new LanTransport(dynamic_cast<const LanLocation&>(location));
  return NULL;
}
