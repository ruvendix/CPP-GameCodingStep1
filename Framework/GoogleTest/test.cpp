#include "pch.h"

TEST(NumberTest, CheckEqualInt)
{
	EXPECT_EQ(1, 1);
}

TEST(NumberTest, CheckEqualFloat)
{
	EXPECT_FLOAT_EQ(1.0f, 1.0f) << "서로 다른 부동소수점수입니다!";
}

TEST(StringTest, CheckEqualString)
{
	EXPECT_STREQ("테스트", "테스트");
}