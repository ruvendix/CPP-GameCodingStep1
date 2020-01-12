// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// 이 저작물은 크리에이티브 커먼즈 저작자표시 4.0 국제 라이선스에 따라 이용할 수 있습니다.
// http://creativecommons.org/licenses/by/4.0/
// =====================================================================================

#include <cstdio>
#include <memory>

using Int32 = signed __int32;
using Real32 = float;

// 부모 클래스에요.
class Parent
{
public:
#pragma region 생성자 및 소멸자
	Parent() // 기본 생성자에요.
	{
		printf("부모 생성자 호출!\n");
	}

	explicit Parent(Int32 data) :
		m_data(data) // 생성 후 초기화를 하는 방법!
	{
		printf("Int32 하나를 인자로 받는 부모 생성자 호출!\n");
	}

	explicit Parent(Real32 data) :
		Parent(static_cast<Int32>(data)) // 생성자 위임
	{
		printf("Real32 하나를 인자로 받는 부모 생성자 호출!\n");
	}

	// 복사 생성자를 만들게 되면
	// 자동 이동 생성자는 만들어지지 않아요!
	Parent(const Parent& lVal)
	{
		printf("부모 복사 생성자 호출!\n");
	}

	// 이동 생성자를 만들게 되면
	// 자동 복사 생성자는 만들어지지 않아요!
	Parent(const Parent&& rVal)
	{
		printf("부모 이동 생성자 호출!\n");
	}

	virtual ~Parent()
	{
		printf("부모 소멸자 호출!\n");
	}
#pragma endregion

#pragma region 접근자
	// getter라고 해요.
	// const를 항상 붙여주세요!
	Int32 getData() const
	{
		return m_data;
	}

	// setter라고 해요.
	void setData(Int32 data)
	{
		m_data = data;
	}
#pragma endregion

private:
	Int32 m_data = 0; // static이 아니라면 즉시 초기화 가능!
};

// 자식 클래스에요.
// 이렇게 부모한테서 받은 걸 그대로 사용할 경우 "구현(된 것을) 상속(받았다)"이라고도 해요.
class Child : public Parent
{
public:
	using Parent::Parent; // 생성자 상속

#pragma region 생성자 및 소멸자
	// 상속 관계에서는 "부모 생성자 호출 -> 자식 생성자 호출" 이런 순서가 돼요!
	Child() :
		Parent() // 상속 관계에서는 생성자 호출 관계가 숨어있어요!
	{
		printf("자식 생성자 호출!\n");
	}

	// 상속 관계에서는 "자식 소멸자 호출 -> 부모 소멸자 호출" 이런 순서가 돼요!
	virtual ~Child()
	{
		printf("자식 소멸자 호출!\n");
	}
#pragma endregion

	void CallChildFunc()
	{
		printf("자식 함수 호출!\n");
	}
};

// 부모 클래스를 생성하는 함수에요.
Parent CreateParent()
{
	Parent parent;
	printf("\n");
	return parent;
}

// 자식 클래스를 생성하는 함수에요.
Child CreateChild()
{
	Child child;
	printf("\n");
	return child;
}

//////////////////////////////////////////////////////////////////////////
// 프로그램이 시작되는 곳이에요.
Int32 main()
{
#if 0
	Parent parent;
	printf("parent의 m_data : %d\n", parent.getData());
#endif

#if 0
	Parent parent(10.02f);
	printf("parent의 m_data : %d\n", parent.getData());
#endif

#if 0
	Parent parent = CreateParent();
	printf("parent의 m_data : %d\n", parent.getData());
#endif

#if 0
	Child child = CreateChild();
	child.setData(13);
	printf("child의 m_data : %d\n", child.getData());
#endif

#if 0
	Parent* pSomething = new Child; // 업캐스팅
	dynamic_cast<Child*>(pSomething)->CallChildFunc(); // 다운캐스팅
	delete pSomething;
#endif

#if 0
	std::unique_ptr<Parent> pSomething = std::make_unique<Child>(); // 업캐스팅
	dynamic_cast<Child*>(pSomething.get())->CallChildFunc(); // 다운캐스팅
#endif

	printf("\n");
	return 0;
}