// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// �� ���۹��� ũ������Ƽ�� Ŀ���� ������ǥ�� 4.0 ���� ���̼����� ���� �̿��� �� �ֽ��ϴ�.
// http://creativecommons.org/licenses/by/4.0/
// =====================================================================================

#include <cstdio>
#include <string>

struct FoodInfo
{
    std::string strName;
    bool bFinishedCooking = false;
};

// �׽�Ʈ�� ���� �����ΰ��� Ȱ�����ּ���.
//#define NO_SRP

#ifdef NO_SRP
class Chef
{
public:
    Chef() = default;
    ~Chef() = default;

    void TakeAnOrder(const std::string& strOrderedMenuName)
    {
        m_ordereMenuInfo.strName = strOrderedMenuName;
        printf("�丮��: \"%s\" �ֹ��޾ҽ��ϴ�!\n", m_ordereMenuInfo.strName.c_str());
    }

    void Cook()
    {
        printf("=========================================\n");
        printf("�丮��: \"%s\" �丮 ��...\n", m_ordereMenuInfo.strName.c_str());

        m_ordereMenuInfo.bFinishedCooking = true;

        printf("�丮��: \"%s\" �丮 ��...\n", m_ordereMenuInfo.strName.c_str());
        printf("=========================================\n");
    }

    const FoodInfo& BringOrderedMenuInfo() const
    {
        printf("�丮��: ����... ���� �ֹ��Ͻ� \"%s\"�Դϴ�.\n",
            m_ordereMenuInfo.strName.c_str()); // ���� ������ ��ģ �丮��

        return m_ordereMenuInfo;
    }

private:
    FoodInfo m_ordereMenuInfo;
};
#else
class WaitingStaff; // ���漱�� �ʿ�!

class Chef
{
public:
    Chef() = default;
    ~Chef() = default;

    void PreCook(const FoodInfo& orderedMenuInfo)
    {
        m_ordereMenuInfo = orderedMenuInfo;
        printf("�丮��: \"%s\" �丮 �����ҰԿ�!\n", m_ordereMenuInfo.strName.c_str());
    }

    void Cook()
    {
        printf("=========================================\n");
        printf("�丮��: \"%s\" �丮 ��...\n", m_ordereMenuInfo.strName.c_str());

        m_ordereMenuInfo.bFinishedCooking = true;

        printf("�丮��: \"%s\" �丮 ��...\n", m_ordereMenuInfo.strName.c_str());
        printf("=========================================\n");
    }

    void FinishedCooking(_Out_ WaitingStaff& waitingStaff);

private:
    FoodInfo m_ordereMenuInfo;
};

class WaitingStaff
{
public:
    WaitingStaff() = default;
    ~WaitingStaff() = default;

    void TakeAnOrder(const std::string& strOrderedMenuName)
    {
        m_ordereMenuInfo.strName = strOrderedMenuName;
        printf("������: \"%s\" �ֹ��޾ҽ��ϴ�!\n", m_ordereMenuInfo.strName.c_str());
    }

    void TalkForOrderedMenu(_Out_ Chef& chef)
    {
        printf("������: \"%s\" �ֹ� ���Խ��ϴ�.\n", m_ordereMenuInfo.strName.c_str());
        chef.PreCook(m_ordereMenuInfo); // �������� �丮�翡�� �ֹ����� �޴� ����
    }

    const FoodInfo& BringOrderedMenu()
    {
        printf("������: ���� �ֹ��Ͻ� \"%s\"�Դϴ�.\n",
            m_ordereMenuInfo.strName.c_str()); // ������ �������� �����Ѵ�!

        return m_ordereMenuInfo;
    }

    void setOrderedMenuInfo(const FoodInfo& orderedMenuInfo)
    {
        m_ordereMenuInfo = orderedMenuInfo;
    }

private:
    FoodInfo m_ordereMenuInfo;
};

void Chef::FinishedCooking(_Out_ WaitingStaff& waitingStaff)
{
    // �丮�� ������ ���� ���������� �˷��� �ؿ�!
    if (m_ordereMenuInfo.bFinishedCooking == false)
    {
        return;
    }

    printf("�丮��: \"%s\" �ϼ������� ����������.\n", m_ordereMenuInfo.strName.c_str());
    waitingStaff.setOrderedMenuInfo(m_ordereMenuInfo);
}
#endif

//////////////////////////////////////////////////////////////////////////
// ���α׷��� ���۵Ǵ� ���̿���.
int main()
{
#ifdef NO_SRP
    Chef chef;
    chef.TakeAnOrder("������ũ");
    chef.Cook();
    chef.BringOrderedMenuInfo();
#else
    WaitingStaff waitingStaff;
    waitingStaff.TakeAnOrder("������ũ");

    Chef chef;
    waitingStaff.TalkForOrderedMenu(chef);

    chef.Cook();
    chef.FinishedCooking(waitingStaff);

    waitingStaff.BringOrderedMenu();
#endif

    printf("\n");
    return 0;
}