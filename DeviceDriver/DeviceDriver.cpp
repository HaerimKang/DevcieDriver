#include "DeviceDriver.h"

#include <exception>

DeviceDriver::DeviceDriver(FlashMemoryDevice* hardware) : m_hardware(hardware)
{}

class ReadFailException : public std::exception {};
class WriteFailException : public std::exception {};

int DeviceDriver::read(long address)
{
    int result = (int)(m_hardware->read(address));

    const int RETRY_COUNT = 4;
    for (int i = 0; i < RETRY_COUNT; i++) {
        if (result == (int)m_hardware->read(address)) continue;
        throw ReadFailException();
    }
    return result;
}

void DeviceDriver::write(long address, int data)
{
    if ((int)m_hardware->read(address) != 0xFF) {
        throw WriteFailException();
    }
    m_hardware->write(address, (unsigned char)data);

}