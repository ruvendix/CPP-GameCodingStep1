#include "pch.h"

TEST(NumberTest, CheckEqualInt)
{
	EXPECT_EQ(1, 1);
}

TEST(NumberTest, CheckEqualFloat)
{
	EXPECT_FLOAT_EQ(1.0f, 1.0f) << "���� �ٸ� �ε��Ҽ������Դϴ�!";
}

TEST(StringTest, CheckEqualString)
{
	EXPECT_STREQ("�׽�Ʈ", "�׽�Ʈ");
}