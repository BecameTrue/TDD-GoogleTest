#include <gmock/gmock.h>
#include <romanNumeralConverterTest.h>

using namespace testing;

TEST_F(RomanNumeralConverterFixture, CanHandleInvalidInput) {
    ASSERT_EQ(converter.get(-123), "");
    ASSERT_EQ(converter.get(0), "");
}

TEST_F(RomanNumeralConverterFixture, CanConvertValidInput) {
    ASSERT_EQ(converter.get(1), "I");
    ASSERT_EQ(converter.get(3), "III");
    ASSERT_EQ(converter.get(5), "V");
    ASSERT_EQ(converter.get(8), "VIII");
    ASSERT_EQ(converter.get(10), "X");
    ASSERT_EQ(converter.get(12), "XII");
    ASSERT_EQ(converter.get(15), "XV");
    ASSERT_EQ(converter.get(18), "XVIII");
    ASSERT_EQ(converter.get(20), "XX");
    ASSERT_EQ(converter.get(2019), "MMXVIIII");
    ASSERT_EQ(converter.get(12019), "MMMMMMMMMMMMXVIIII");
}