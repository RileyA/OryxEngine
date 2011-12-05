//#define BOOST_TEST_DYN_LINK
//#define BOOST_TEST_MODULE StringUtilsTest

#include <boost/test/unit_test.hpp>
#include "OryxStringUtils.h"

using namespace Oryx;

/** Tests the StringUtils class */

//-----------------------------------------------------------------------
BOOST_AUTO_TEST_CASE(StringUtilsLongLongToStringSmall)
{
	long long test = 5;
	BOOST_CHECK_EQUAL("5", StringUtils::toString(test));
}

//-----------------------------------------------------------------------
BOOST_AUTO_TEST_CASE(StringUtilsLongLongToStringLarge)
{
	long long test = 281474976710655;
	BOOST_CHECK_EQUAL("281474976710655", StringUtils::toString(test));
}
//-----------------------------------------------------------------------

BOOST_AUTO_TEST_CASE(StringUtilsLongLongToStringNegative)
{
	long long test = -5;
	BOOST_CHECK_EQUAL("-5", StringUtils::toString(test));
}
//-----------------------------------------------------------------------

BOOST_AUTO_TEST_CASE(StringUtilsLongLongToStringZero)
{
	long long test = 0;
	BOOST_CHECK_EQUAL("0", StringUtils::toString(test));
}
//-----------------------------------------------------------------------

BOOST_AUTO_TEST_CASE(StringUtilsIntToStringSmall)
{
	long long test = 5;
	BOOST_CHECK_EQUAL("5", StringUtils::toString(test));
}
//-----------------------------------------------------------------------

BOOST_AUTO_TEST_CASE(StringUtilsIntToStringLarge)
{
	long long test = 2000000000;
	BOOST_CHECK_EQUAL("2000000000", StringUtils::toString(test));
}
//-----------------------------------------------------------------------

BOOST_AUTO_TEST_CASE(StringUtilsIntToStringNegative)
{
	long long test = -5;
	BOOST_CHECK_EQUAL("-5", StringUtils::toString(test));
}
//-----------------------------------------------------------------------

BOOST_AUTO_TEST_CASE(StringUtilsIntToStringZero)
{
	long long test = 0;
	BOOST_CHECK_EQUAL("0", StringUtils::toString(test));
}
//-----------------------------------------------------------------------
