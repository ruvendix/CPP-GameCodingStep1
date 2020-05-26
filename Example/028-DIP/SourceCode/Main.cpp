// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// �� ���۹��� ũ������Ƽ�� Ŀ���� ������ǥ�� 4.0 ���� ���̼����� ���� �̿��� �� �ֽ��ϴ�.
// http://creativecommons.org/licenses/by/4.0/
// =====================================================================================

// �׽�Ʈ�� �Ϸ��� ���ӽ����̽��� �������ּ���.
// ��) no_DIP::UnitTest();

#include <cstdio>
#include <string>

namespace no_DIP
{

    class Lamp
    {
    public:
        Lamp() = default;
        ~Lamp() = default;

        void TurnOn() const
        {
            printf("[Lamp]: ������ �״�!\n");
        }

        void TurnOff() const
        {
            printf("[Lamp]: ������ ����!\n");
        }
    };

    class House
    {
    public:
        // ������ ���� �̿�!
        House(Lamp* pLamp) :
            m_pLamp(pLamp)
        {

        }

        ~House()
        {
            delete m_pLamp;
        }

        void UseLamp(bool bUse)
        {
            if (bUse == true)
            {
                m_pLamp->TurnOn();
            }
            else
            {
                m_pLamp->TurnOff();
            }
        }

    private:
        Lamp* m_pLamp = nullptr;
    };

    void UnitTest()
    {
        printf("<������ ������ ����غ���!>\n");

        House house(new Lamp());
        house.UseLamp(true);
        house.UseLamp(false);
    }

} // namespace no_DIP end

namespace DIP
{

    class ILamp abstract
    {
    public:
        ILamp() = default;
        virtual ~ILamp() = default;

        virtual void TurnOn() const abstract;
        virtual void TurnOff() const abstract;
    };

    class Lamp : public ILamp
    {
    public:
        using ILamp::ILamp;
        virtual ~Lamp() = default;

        virtual void TurnOn() const override
        {
            printf("[Lamp]: ������ �״�!\n");
        }

        virtual void TurnOff() const override
        {
            printf("[Lamp]: ������ ����!\n");
        }
    };

    class CharacterLamp : public ILamp
    {
    public:
        using ILamp::ILamp;
        virtual ~CharacterLamp() = default;

        virtual void TurnOn() const override
        {
            printf("[CharacterLamp]: ������ �״�!\n");
        }

        virtual void TurnOff() const override
        {
            printf("[CharacterLamp]: ������ ����!\n");
        }
    };

    class House
    {
    public:
        // ������ ���� �̿�!
        House(ILamp* pLamp) :
            m_pLamp(pLamp)
        {

        }

        ~House()
        {
            delete m_pLamp;
        }

        void UseLamp(bool bUse)
        {
            if (bUse == true)
            {
                m_pLamp->TurnOn();
            }
            else
            {
                m_pLamp->TurnOff();
            }
        }

        // Setter�� ������ ������ ����!
        void setLamp(ILamp* pLamp)
        {
            delete m_pLamp;
            m_pLamp = pLamp;
        }

    private:
        ILamp* m_pLamp = nullptr;
    };

    void UnitTest()
    {
        printf("<������ ������ ����غ���!>\n");

        House house(new Lamp());
        house.UseLamp(true);
        house.UseLamp(false);

        printf("\n");
        printf("ĳ���� ������ �ٲܷ�!\n");
        printf("\n");

        house.setLamp(new CharacterLamp());
        house.UseLamp(true);
        house.UseLamp(false);
    }

} // namespace DIP end

//////////////////////////////////////////////////////////////////////////
// ���α׷��� ���۵Ǵ� ���̿���.
int main()
{
    no_DIP::UnitTest();
    //DIP::UnitTest();

    printf("\n");
    return 0;
}