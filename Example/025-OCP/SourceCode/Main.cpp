// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// �� ���۹��� ũ������Ƽ�� Ŀ���� ������ǥ�� 4.0 ���� ���̼����� ���� �̿��� �� �ֽ��ϴ�.
// http://creativecommons.org/licenses/by/4.0/
// =====================================================================================

// �׽�Ʈ�� �Ϸ��� ���ӽ����̽��� �������ּ���.
// ��) no_OCP::UnitTest();

#include <cstdio>

namespace no_OCP
{

    class Player
    {
    public:
        Player() = default;
        ~Player() = default;

        // �� ������ ���� �Լ�
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
            printf("[���� ����]�� �� �Գ�~\n");
        }

        void SellWeapon(const Player& player) const
        {
            printf("[���� ����]���� �÷��̾� ������ ��ȸ�մϴ�.\n");
            printf("�÷��̾��� ������: %d��\n", player.getMoney());
        }
    };

    class MagicShop
    {
    public:
        MagicShop() = default;
        ~MagicShop() = default;

        void WelcomePlayer() const
        {
            printf("[���� ����]�� �� �Ծ��~\n");
        }

        void SellMagic(const Player& player) const
        {
            printf("[���� ����]���� �÷��̾� ������ ��ȸ�մϴ�.\n");
            printf("�÷��̾��� ������: %d��\n", player.getMoney());
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

    void UnitTest()
    {
        Player player;
        player.EnterWeaponShop();
        player.EnterMagicShop();
    }

} // namespce no_OCP end

namespace OCP
{

    class IShop;

    class Player
    {
    public:
        Player() = default;
        ~Player() = default;

        // ���� ������ ���� �Լ��� �ϳ�!
        void EnterShop(const IShop& shop) const;

        int getMoney() const
        {
            return m_money;
        }

    private:
        int m_money = 1000;
    };

    // ��� ������ �� �������̽��� ����ؾ� �ؿ�!
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
            printf("[���� ����]�� �� �Գ�~\n");
        }

        virtual void SellItem(const Player& player) const override
        {
            printf("[���� ����]���� �÷��̾� ������ ��ȸ�մϴ�.\n");
            printf("�÷��̾��� ������: %d��\n", player.getMoney());
        }
    };

    class MagicShop : public IShop
    {
    public:
        using IShop::IShop;
        virtual ~MagicShop() = default;

        virtual void WelcomePlayer() const override
        {
            printf("[���� ����]�� �� �Ծ��~\n");
        }

        virtual void SellItem(const Player& player) const override
        {
            printf("[���� ����]���� �÷��̾� ������ ��ȸ�մϴ�.\n");
            printf("�÷��̾��� ������: %d��\n", player.getMoney());
        }
    };

    class FoodShop : public IShop
    {
    public:
        using IShop::IShop;
        virtual ~FoodShop() = default;

        virtual void WelcomePlayer() const override
        {
            printf("[���� ����]�� �� �Ծ��~\n");
        }

        virtual void SellItem(const Player& player) const override
        {
            printf("[���� ����]���� �÷��̾� ������ ��ȸ�մϴ�.\n");
            printf("�÷��̾��� ������: %d��\n", player.getMoney());
        }
    };

    void Player::EnterShop(const IShop& shop) const
    {
        printf("===========================================\n");
        shop.WelcomePlayer();
        shop.SellItem(*this);
        printf("===========================================\n");
    }

    void UniTest()
    {
        Player player;
        player.EnterShop(WeaponShop());
        player.EnterShop(MagicShop());
        player.EnterShop(FoodShop());
    }

} // namespace OCP

//////////////////////////////////////////////////////////////////////////
// ���α׷��� ���۵Ǵ� ���̿���.
int main()
{
    no_OCP::UnitTest();
    //OCP::UniTest();

    return 0;
}