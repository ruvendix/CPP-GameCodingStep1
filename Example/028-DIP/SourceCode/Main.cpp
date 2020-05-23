// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// 이 저작물은 크리에이티브 커먼즈 저작자표시 4.0 국제 라이선스에 따라 이용할 수 있습니다.
// http://creativecommons.org/licenses/by/4.0/
// =====================================================================================

#include <cstdio>
#include <string>

// 문제가 해결된 상황을 보고 싶으면
// 아래에 있는 디파인값을 주석 처리해주세요.
#define NO_DIP

#ifdef NO_DIP
class Lamp
{
public:
    Lamp() = default;
    ~Lamp() = default;

    void TurnOn() const
    {
        printf("[Lamp]: 램프를 켰다!\n");
    }

    void TurnOff() const
    {
        printf("[Lamp]: 램프를 껐다!\n");
    }
};

class House
{
public:
    // 의존성 주입 이용!
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
#else
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
        printf("[Lamp]: 램프를 켰다!\n");
    }

    virtual void TurnOff() const override
    {
        printf("[Lamp]: 램프를 껐다!\n");
    }
};

class CharacterLamp : public ILamp
{
public:
    using ILamp::ILamp;
    virtual ~CharacterLamp() = default;

    virtual void TurnOn() const override
    {
        printf("[CharacterLamp]: 램프를 켰다!\n");
    }

    virtual void TurnOff() const override
    {
        printf("[CharacterLamp]: 램프를 껐다!\n");
    }
};

class House
{
public:
    // 의존성 주입 이용!
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

    // Setter도 의존성 주입이 가능!
    void setLamp(ILamp* pLamp)
    {
        delete m_pLamp;
        m_pLamp = pLamp;
    }

private:
    ILamp* m_pLamp = nullptr;
};
#endif

//////////////////////////////////////////////////////////////////////////
// 프로그램이 시작되는 곳이에요.
int main()
{
    printf("<집에서 램프를 사용해보자!>\n");

#ifdef NO_DIP
    House house(new Lamp());
    house.UseLamp(true);
    house.UseLamp(false);
#else
    House house(new Lamp());
    house.UseLamp(true);
    house.UseLamp(false);

    printf("\n");
    printf("캐릭터 램프로 바꿀래!\n");
    printf("\n");

    house.setLamp(new CharacterLamp());
    house.UseLamp(true);
    house.UseLamp(false);
#endif

    printf("\n");
    return 0;
}