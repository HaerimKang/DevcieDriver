#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "../DeviceDriver/DeviceDriver.cpp"
#include "../DeviceDriver/FlashMemoryDevice.h"

using namespace testing;

class MockDevice : public FlashMemoryDevice
{
public:
	MOCK_METHOD(unsigned char, read, (long address), (override));
	MOCK_METHOD(void, write, (long address, unsigned char data), (override));
};

TEST(TestCaseName, Read) {
	MockDevice mock_device;
	DeviceDriver driver{ &mock_device };

	EXPECT_CALL(mock_device, read(100))
		.Times(5)
		.WillRepeatedly(Return(100));

	std::cout << driver.read(100);
}