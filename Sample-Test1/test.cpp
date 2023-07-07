#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "../DeviceDriver/DeviceDriver.cpp"
#include "../DeviceDriver/FlashMemoryDevice.h"

using namespace testing;

class MockFlash : public FlashMemoryDevice
{
public:
	MOCK_METHOD(unsigned char, read, (long address), (override));
	MOCK_METHOD(void, write, (long address, unsigned char data), (override));
};

TEST(TestCaseName, WriteSuccess) {
	MockFlash mockFlash;
	DeviceDriver driver(&mockFlash);

	EXPECT_CALL(mockFlash, read(100))
		.WillOnce(Return(0xFF))
		.WillRepeatedly(Return(100));

	driver.write(100, 100);

	EXPECT_THAT(driver.read(100), 100);
}

TEST(TestCaseName, WriteFail) {
	MockFlash mockFlash;
	DeviceDriver driver(&mockFlash);

	EXPECT_CALL(mockFlash, read(100))
		.WillOnce(Return(100));

	EXPECT_THROW(driver.write(100, 100), std::exception);

TEST(TestCaseName, ReadSuccess) {
	MockFlash mock_device;
	DeviceDriver driver{ &mock_device };

	EXPECT_CALL(mock_device, read(100))
		.Times(5)
		.WillRepeatedly(Return(100));

	EXPECT_THAT(driver.read(100), Eq(100));
}

TEST(TestCaseName, ReadFail) {
	MockFlash mock_device;
	DeviceDriver driver{ &mock_device };

	EXPECT_CALL(mock_device, read(100))
		.WillOnce(Return(100))
		.WillRepeatedly(Return(50));

	EXPECT_THROW(driver.read(100), std::exception);
}