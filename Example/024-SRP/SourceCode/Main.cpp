// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// 이 저작물은 크리에이티브 커먼즈 저작자표시 4.0 국제 라이선스에 따라 이용할 수 있습니다.
// http://creativecommons.org/licenses/by/4.0/
// =====================================================================================

#include <cstdio>
#include <string>

struct FoodInfo
{
    std::string strName;
    bool bFinishedCooking = false;
};

// 테스트할 때는 디파인값을 활성해주세요.
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
        printf("요리사: \"%s\" 주문받았습니다!\n", m_ordereMenuInfo.strName.c_str());
    }

    void Cook()
    {
        printf("=========================================\n");
        printf("요리사: \"%s\" 요리 중...\n", m_ordereMenuInfo.strName.c_str());

        m_ordereMenuInfo.bFinishedCooking = true;

        printf("요리사: \"%s\" 요리 끝...\n", m_ordereMenuInfo.strName.c_str());
        printf("=========================================\n");
    }

    const FoodInfo& BringOrderedMenuInfo() const
    {
        printf("요리사: 헥헥... 여기 주문하신 \"%s\"입니다.\n",
            m_ordereMenuInfo.strName.c_str()); // 갖은 업무로 지친 요리사

        return m_ordereMenuInfo;
    }

private:
    FoodInfo m_ordereMenuInfo;
};
#else
class WaitingStaff; // 전방선언 필요!

class Chef
{
public:
    Chef() = default;
    ~Chef() = default;

    void PreCook(const FoodInfo& orderedMenuInfo)
    {
        m_ordereMenuInfo = orderedMenuInfo;
        printf("요리사: \"%s\" 요리 시작할게요!\n", m_ordereMenuInfo.strName.c_str());
    }

    void Cook()
    {
        printf("=========================================\n");
        printf("요리사: \"%s\" 요리 중...\n", m_ordereMenuInfo.strName.c_str());

        m_ordereMenuInfo.bFinishedCooking = true;

        printf("요리사: \"%s\" 요리 끝...\n", m_ordereMenuInfo.strName.c_str());
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
        printf("종업원: \"%s\" 주문받았습니다!\n", m_ordereMenuInfo.strName.c_str());
    }

    void TalkForOrderedMenu(_Out_ Chef& chef)
    {
        printf("종업원: \"%s\" 주문 들어왔습니다.\n", m_ordereMenuInfo.strName.c_str());
        chef.PreCook(m_ordereMenuInfo); // 종업원이 요리사에게 주문받은 메뉴 전달
    }

    const FoodInfo& BringOrderedMenu()
    {
        printf("종업원: 여기 주문하신 \"%s\"입니다.\n",
            m_ordereMenuInfo.strName.c_str()); // 이제는 종업원이 서빙한다!

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
    // 요리가 끝났을 때만 종업원에게 알려야 해요!
    if (m_ordereMenuInfo.bFinishedCooking == false)
    {
        return;
    }

    printf("요리사: \"%s\" 완성했으니 가져가세요.\n", m_ordereMenuInfo.strName.c_str());
    waitingStaff.setOrderedMenuInfo(m_ordereMenuInfo);
}
#endif

//////////////////////////////////////////////////////////////////////////
// 프로그램이 시작되는 곳이에요.
int main()
{
#ifdef NO_SRP
    Chef chef;
    chef.TakeAnOrder("스테이크");
    chef.Cook();
    chef.BringOrderedMenuInfo();
#else
    WaitingStaff waitingStaff;
    waitingStaff.TakeAnOrder("스테이크");

    Chef chef;
    waitingStaff.TalkForOrderedMenu(chef);

    chef.Cook();
    chef.FinishedCooking(waitingStaff);

    waitingStaff.BringOrderedMenu();
#endif

    printf("\n");
    return 0;
}