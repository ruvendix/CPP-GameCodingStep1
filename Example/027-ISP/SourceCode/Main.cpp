// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// �� ���۹��� ũ������Ƽ�� Ŀ���� ������ǥ�� 4.0 ���� ���̼����� ���� �̿��� �� �ֽ��ϴ�.
// http://creativecommons.org/licenses/by/4.0/
// =====================================================================================

// �׽�Ʈ�� �Ϸ��� ���ӽ����̽��� �������ּ���.
// ��) no_ISP::UnitTest();

#include <cstdio>
#include <string>

struct Food
{
    std::string strName;
};

namespace no_ISP
{

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
            printf("\"%s\" �Դ´�!\n", food.strName.c_str());
        }

        virtual void LightCandelabra() const override
        {
            printf("�� ���� �ʿ� ����!\n");
        }

        virtual void LayoutCutlery() const override
        {
            printf("�� �����θ� �Դ´�!\n");
        }
    };

    class CulturedPerson : public IRequireFood
    {
    public:
        using IRequireFood::IRequireFood;
        virtual ~CulturedPerson() = default;

        virtual void Eat(const Food& food) const override
        {
            printf("\"%s\" �����Կ�!\n", food.strName.c_str());
        }

        virtual void LightCandelabra() const override
        {
            printf("���ʴ� ������ �ְ� ������!\n");
        }

        virtual void LayoutCutlery() const override
        {
            printf("������ �ʿ��ؿ�!\n");
        }
    };

    void UnitTest()
    {
        Food food;
        food.strName = "�Ұ��";

        SavagePerson savagePerson;
        printf("<�߸����� �Ļ�>\n");
        savagePerson.Eat(food);
        savagePerson.LightCandelabra();
        savagePerson.LayoutCutlery();

        printf("\n");

        CulturedPerson culturedPerson;
        printf("<��ȭ���� �Ļ�>\n");
        culturedPerson.Eat(food);
        culturedPerson.LightCandelabra();
        culturedPerson.LayoutCutlery();
    }

} // namespace no_ISP end

namespace ISP
{

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
            printf("\"%s\" �Դ´�!\n", food.strName.c_str());
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
            printf("\"%s\" �����Կ�!\n", food.strName.c_str());
        }

        virtual void LightCandelabra() const override
        {
            printf("���ʴ� ������ �ְ� ������!\n");
        }

        virtual void LayoutCutlery() const override
        {
            printf("������ �ʿ��ؿ�!\n");
        }
    };

    void UnitTest()
    {
        Food food;
        food.strName = "�Ұ��";

        SavagePerson savagePerson;
        printf("<�߸����� �Ļ�>\n");
        savagePerson.Eat(food);

        printf("\n");

        CulturedPerson culturedPerson;
        printf("<��ȭ���� �Ļ�>\n");
        culturedPerson.Eat(food);
        culturedPerson.LightCandelabra();
        culturedPerson.LayoutCutlery();
    }

} // namespace ISP end

//////////////////////////////////////////////////////////////////////////
// ���α׷��� ���۵Ǵ� ���̿���.
int main()
{
    no_ISP::UnitTest();
    //ISP::UnitTest();

    printf("\n");
    return 0;
}