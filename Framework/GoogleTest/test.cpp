// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// 이 저작물은 크리에이티브 커먼즈 저작자표시 4.0 국제 라이선스에 따라 이용할 수 있습니다.
// http://creativecommons.org/licenses/by/4.0/
//
// 구글 테스트 예제입니다.
// =====================================================================================
#include "pch.h"

class Player final
{
public:
	Player() = default;
	~Player() = default;

	int getHP() const
	{
		return m_HP;
	}

	void setHP(int HP)
	{
		m_HP = HP;
	}

	int getMP() const
	{
		return m_MP;
	}

	void setMP(int MP)
	{
		m_MP = MP;
	}

private:
	int m_HP = 0;
	int m_MP = 0;
};

class PlayerTest : public testing::Test
{
protected:
	virtual void SetUp() override
	{
		m_pPlayer = new Player();
		printf("플레이어 메모리 할당!\n");
	}

	virtual void TearDown() override
	{
		delete m_pPlayer;
		printf("플레이어 메모리 해제!\n");
	}

	Player* m_pPlayer = nullptr;
};
TEST_F(PlayerTest, InitHP)
{
	ASSERT_EQ(m_pPlayer->getHP(), 0);
}

TEST_F(PlayerTest, InitMP)
{
	ASSERT_EQ(m_pPlayer->getMP(), 0);
}

struct PlayerTestInfo
{
	int HP = 0;
	int MP = 0;

	friend std::ostream& operator<<(std::ostream& os, const PlayerTestInfo& info)
	{
		return os
			<< "HP: " << info.HP
			<< ",MP: " << info.MP;
	}
};

class PlayerStatTest : public PlayerTest, public testing::WithParamInterface<PlayerTestInfo>
{

};

TEST_P(PlayerStatTest, InputStat)
{
	const PlayerTestInfo& info = GetParam();
	m_pPlayer->setHP(info.HP);
	m_pPlayer->setMP(info.MP);

	ASSERT_EQ(m_pPlayer->getHP(), info.HP);
	ASSERT_EQ(m_pPlayer->getMP(), info.MP);
}

INSTANTIATE_TEST_CASE_P(
	Player, // 어떤 값들인지를 나타내는 접두사
	PlayerStatTest, // TEST_P의 이름
	testing::Values(
		PlayerTestInfo{ 100, 50 },
		PlayerTestInfo{ 200, 100 },
		PlayerTestInfo{ 300, 150 })
);