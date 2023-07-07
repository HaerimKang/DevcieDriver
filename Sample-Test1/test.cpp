#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "../Project139/DeviceDriver.cpp";
using namespace testing;

class FlashMock : public FlashMemoryDevice {
public:
	MOCK_METHOD(unsigned char, read, (long address), (override));
	MOCK_METHOD(void, write, (long address, unsigned char data));
};

TEST(ReadWithMock, ReadFive) {
	FlashMock mockDevice;
	EXPECT_CALL(mockDevice, read)
		.Times(5);

	DeviceDriver dd(&mockDevice);
	dd.read(0xA);
}

TEST(ReadWithMock, ReadException) {
	FlashMock mockDevice;
	EXPECT_CALL(mockDevice, read)
		.WillOnce(Return((unsigned char)0xA))
		.WillOnce(Return((unsigned char)0xA))
		.WillOnce(Return((unsigned char)0xA))
		.WillOnce(Return((unsigned char)0xB));

	DeviceDriver dd(&mockDevice);
	EXPECT_THROW(dd.read(11), std::exception);
}

TEST(WriteWithMock, Write) {
	FlashMock mockDevice;
	EXPECT_CALL(mockDevice, read)
		.Times(1)
		.WillRepeatedly(Return(0xFF));

	DeviceDriver dd(&mockDevice);
	dd.write(0xAL, 0xB);
}

TEST(WriteWithMock, WriteException) {
	FlashMock mockDevice;
	EXPECT_CALL(mockDevice, read)
		.WillRepeatedly(Return(0xA));

	DeviceDriver dd(&mockDevice);
	EXPECT_THROW(dd.write(0xA, 0xB), std::exception);
}