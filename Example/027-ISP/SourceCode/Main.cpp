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
#define NO_ISP

struct Food
{
    std::string strName;
};

#ifdef NO_ISP
class IRequireFood abstract
{
public:
    IRequireFood() = default;
    virtual ~IRequireFood() = default;

    virtual void Eat(const Food& food) const abstract;
    virtual void LightCandelabra() const abstract;
    virtual void LayoutCutlery() const abstract;
};

class SavagePerson : public IRequireFood
{
public:
    using IRequireFood::IRequireFood;
    virtual ~SavagePerson() = default;

    virtual void Eat(const Food& food) const override
    {
        printf("\"%s\" 먹는다!\n", food.strName.c_str());
    }

    virtual void LightCandelabra() const override
    {
        printf("난 양초 필요 없다!\n");
    }

    virtual void LayoutCutlery() const override
    {
        printf("난 손으로만 먹는다!\n");
    }
};

class CulturedPerson : public IRequireFood
{
public:
    using IRequireFood::IRequireFood;
    virtual ~CulturedPerson() = default;

    virtual void Eat(const Food & food) const override
    {
        printf("\"%s\" 먹을게요!\n", food.strName.c_str());
    }

    virtual void LightCandelabra() const override
    {
        printf("양초는 분위기 있게 해주죠!\n");
    }

    virtual void LayoutCutlery() const override
    {
        printf("수저가 필요해요!\n");
    }
};
#else
class IRequireFood abstract
{
public:
    IRequireFood() = default;
    virtual ~IRequireFood() = default;

    virtual void Eat(const Food& food) const abstract;
};

class SavagePerson : public IRequireFood
{
public:
    using IRequireFood::IRequireFood;
    virtual ~SavagePerson() = default;

    virtual void Eat(const Food& food) const override
    {
        printf("\"%s\" 먹는다!\n", food.strName.c_str());
    }
};

class IRequireFoodForCulturedPerson : public IRequireFood
{
public:
    using IRequireFood::IRequireFood;
    virtual ~IRequireFoodForCulturedPerson() = default;

    virtual void LightCandelabra() const abstract;
    virtual void LayoutCutlery() const abstract;
};

class CulturedPerson : public IRequireFoodForCulturedPerson
{
public:
    using IRequireFoodForCulturedPerson::IRequireFoodForCulturedPerson;
    virtual ~CulturedPerson() = default;

    virtual void Eat(const Food& food) const override
    {
        printf("\"%s\" 먹을게요!\n", food.strName.c_str());
    }

    virtual void LightCandelabra() const override
    {
        printf("양초는 분위기 있게 해주죠!\n");
    }

    virtual void LayoutCutlery() const override
    {
        printf("수저가 필요해요!\n");
    }
};
#endif

//////////////////////////////////////////////////////////////////////////
// 프로그램이 시작되는 곳이에요.
int main()
{
    Food food;
    food.strName = "소고기";

#ifdef NO_ISP
    SavagePerson savagePerson;
    printf("<야만인의 식사>\n");
    savagePerson.Eat(food);
    savagePerson.LightCandelabra();
    savagePerson.LayoutCutlery();

    printf("\n");

    CulturedPerson culturedPerson;
    printf("<문화인의 식사>\n");
    culturedPerson.Eat(food);
    culturedPerson.LightCandelabra();
    culturedPerson.LayoutCutlery();
#else
    SavagePerson savagePerson;
    printf("<야만인의 식사>\n");
    savagePerson.Eat(food);

    printf("\n");

    CulturedPerson culturedPerson;
    printf("<문화인의 식사>\n");
    culturedPerson.Eat(food);
    culturedPerson.LightCandelabra();
    culturedPerson.LayoutCutlery();
#endif

    printf("\n");
    return 0;
}