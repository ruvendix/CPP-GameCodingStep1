// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// 이 저작물은 크리에이티브 커먼즈 저작자표시 4.0 국제 라이선스에 따라 이용할 수 있습니다.
// http://creativecommons.org/licenses/by/4.0/
// =====================================================================================

#include <cstdio>

// 문제가 해결된 상황을 보고 싶으면
// 아래에 있는 디파인값을 주석 처리해주세요.
#define NO_OCP

#ifdef NO_OCP
class Player
{
public:
    Player() = default;
    ~Player() = default;

    // 각 상점에 들어가는 함수
    void EnterWeaponShop() const;
    void EnterMagicShop() const;

    int getMoney() const
    {
        return m_money;
    }

private:
    int m_money = 1000;
};

class WeaponShop
{
public:
    WeaponShop() = default;
    ~WeaponShop() = default;

    void WelcomePlayer() const
    {
        printf("[무기 상점]에 잘 왔네~\n");
    }

    void SellWeapon(const Player& player) const
    {
        printf("[무기 상점]에서 플레이어 정보를 조회합니다.\n");
        printf("플레이어의 소지금: %d원\n", player.getMoney());
    }
};

class MagicShop
{
public:
    MagicShop() = default;
    ~MagicShop() = default;

    void WelcomePlayer() const
    {
        printf("[마법 상점]에 잘 왔어요~\n");
    }

    void SellMagic(const Player& player) const
    {
        printf("[마법 상점]에서 플레이어 정보를 조회합니다.\n");
        printf("플레이어의 소지금: %d원\n", player.getMoney());
    }
};

void Player::EnterWeaponShop() const
{
    printf("===========================================\n");
    WeaponShop weaponShop;
    weaponShop.WelcomePlayer();
    weaponShop.SellWeapon(*this);
    printf("===========================================\n");
}

void Player::EnterMagicShop() const
{
    printf("===========================================\n");
    MagicShop magicShop;
    magicShop.WelcomePlayer();
    magicShop.SellMagic(*this);
    printf("===========================================\n");
}
#else

class IShop;

class Player
{
public:
    Player() = default;
    ~Player() = default;

    // 이제 상점에 들어가는 함수는 하나!
    void EnterShop(const IShop& shop) const;

    int getMoney() const
    {
        return m_money;
    }

private:
    int m_money = 1000;
};

// 모든 상점은 요 인터페이스를 사용해야 해요!
class IShop abstract
{
public:
    IShop() = default;
    virtual ~IShop() = default;

    virtual void WelcomePlayer() const abstract;
    virtual void SellItem(const Player& player) const abstract;
};

class WeaponShop : public IShop
{
public:
    using IShop::IShop;
    virtual ~WeaponShop() = default;

    virtual void WelcomePlayer() const override
    {
        printf("[무기 상점]에 잘 왔네~\n");
    }

    virtual void SellItem(const Player& player) const override
    {
        printf("[무기 상점]에서 플레이어 정보를 조회합니다.\n");
        printf("플레이어의 소지금: %d원\n", player.getMoney());
    }
};

class MagicShop : public IShop
{
public:
    using IShop::IShop;
    virtual ~MagicShop() = default;

    virtual void WelcomePlayer() const override
    {
        printf("[마법 상점]에 잘 왔어요~\n");
    }

    virtual void SellItem(const Player& player) const override
    {
        printf("[마법 상점]에서 플레이어 정보를 조회합니다.\n");
        printf("플레이어의 소지금: %d원\n", player.getMoney());
    }
};

class FoodShop : public IShop
{
public:
    using IShop::IShop;
    virtual ~FoodShop() = default;

    virtual void WelcomePlayer() const override
    {
        printf("[음식 상점]에 잘 왔어요~\n");
    }

    virtual void SellItem(const Player& player) const override
    {
        printf("[음식 상점]에서 플레이어 정보를 조회합니다.\n");
        printf("플레이어의 소지금: %d원\n", player.getMoney());
    }
};

void Player::EnterShop(const IShop& shop) const
{
   printf("===========================================\n");
   shop.WelcomePlayer();
   shop.SellItem(*this);
   printf("===========================================\n");
}
#endif

//////////////////////////////////////////////////////////////////////////
// 프로그램이 시작되는 곳이에요.
int main()
{
#ifdef NO_OCP
    Player player;
    player.EnterWeaponShop();
    player.EnterMagicShop();
#else
    Player player;
    player.EnterShop(WeaponShop());
    player.EnterShop(MagicShop());
    player.EnterShop(FoodShop());
#endif

    return 0;
}