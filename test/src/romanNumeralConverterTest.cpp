#include <gmock/gmock.h>
#include <romanNumeralConverterTest.h>

using namespace testing;

TEST_F(RomanNumeralConverterFixture, CanHandleInvalidInput) {
    ASSERT_EQ(converter.get(-123), "INVALID");
    ASSERT_EQ(converter.get(0), "INVALID");
}