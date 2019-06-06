#include "ltme01_sdk/Device.h"

#include "ltme01_sdk/Transport.h"
#include "ltme01_sdk/ControlPacket.h"

#include <ctime>
#include <cstring>

ltme01_sdk::Device::Device(const ltme01_sdk::DeviceInfo& deviceInfo)
  : Device(deviceInfo.location())
{
}

ltme01_sdk::Device::Device(const Location& location)
  : transport_(Transport::createInstance(location))
{
  srand((unsigned int)time(NULL));
  reference_ = (uint16_t)rand();
}

ltme01_sdk::Device::~Device()
{
  close();
}

const ltme01_sdk::Location& ltme01_sdk::Device::location() const
{
  return transport_->location();
}

int ltme01_sdk::Device::open()
{
  return transport_->open();
}

void ltme01_sdk::Device::close()
{
  transport_->close();
}

int ltme01_sdk::Device::readDataPacket(DataPacket& dataPacket)
{
  return readDataPacket(dataPacket, 0);
}

int ltme01_sdk::Device::readDataPacket(DataPacket& dataPacket, unsigned int timeout)
{
  return transport_->doDataTransaction(dataPacket, timeout);
}

bool ltme01_sdk::Device::enterLowPowerMode()
{
  ltme01_sdk::GenericRequestPacket requestPacket(RequestPacket::REQUEST_ENTER_LOW_POWER);
  requestPacket.setReference(reference_++);
  requestPacket.updateChecksum();

  ltme01_sdk::GenericResponsePacket responsePacket;
  int result = transport_->doCtrlTransaction(requestPacket, responsePacket, 0);
  if (result == ltme01_sdk::RESULT_SUCCESS) {
    if ((!responsePacket.isValid()) || (responsePacket.reference() != requestPacket.reference()))
      return false;
    else
      return true;
  }
  else
    return false;
}

bool ltme01_sdk::Device::exitLowPowerMode()
{
  ltme01_sdk::GenericRequestPacket requestPacket(RequestPacket::REQUEST_EXIT_LOW_POWER);
  requestPacket.setReference(reference_++);
  requestPacket.updateChecksum();

  ltme01_sdk::GenericResponsePacket responsePacket;
  int result = transport_->doCtrlTransaction(requestPacket, responsePacket, 0);
  if (result == ltme01_sdk::RESULT_SUCCESS) {
    if ((!responsePacket.isValid()) || (responsePacket.reference() != requestPacket.reference()))
      return false;
    else
      return true;
  }
  else
    return false;
}
