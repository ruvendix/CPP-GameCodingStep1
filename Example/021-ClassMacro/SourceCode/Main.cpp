// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// 이 저작물은 크리에이티브 커먼즈 저작자표시 4.0 국제 라이선스에 따라 이용할 수 있습니다.
// http://creativecommons.org/licenses/by/4.0/
// =====================================================================================

#include <crtdbg.h>
#include <cstdio>
#include <memory>

using Int32 = signed __int32;
using Real32 = float;

#ifdef _DEBUG
#define new new(_NORMAL_BLOCK, __FILE__, __LINE__ )                                            
#endif

#define SAFE_DELETE(ptr)\
	if (ptr != nullptr)\
	{\
		delete ptr;\
		ptr = nullptr;\
	}

// 복사 및 이동을 금지하는 매크로에요. (Copy Semantics, Move Semantics)
#define NON_COPYABLE_CLASS(TClass)\
public:\
	TClass(const TClass&) = delete;\
	TClass(const TClass&&) = delete;\
	TClass& operator=(const TClass&) = delete;\
	TClass&& operator=(const TClass&&) = delete;

// 외부에서만 생성 및 소멸을 막는 매크로에요. (기본 생성자만 막힘)
// 하지만 상속 관계에서는 접근 가능하게 해줘야 해요.
#define NON_EXTERNAL_CLASS(TClass)\
protected:\
	TClass() = default;\
	virtual ~TClass() = default;

class NonCopyableParent
{
	NON_COPYABLE_CLASS(NonCopyableParent);

public:
	NonCopyableParent() = default;
	virtual ~NonCopyableParent() = default;
};

class NonCopyableChild : NonCopyableParent
{
public:
	NonCopyableChild() = default;
	virtual ~NonCopyableChild() = default;
};

class NonExternalParent
{
	NON_EXTERNAL_CLASS(NonExternalParent);

public:
	// 부모를 생성해서 반환하는 함수에요.
	static NonExternalParent* Create()
	{
		printf("부모를 생성했어요!\n");
		return new NonExternalParent;
	}

	// 생성된 부모를 삭제하는 함수에요.
	static void Delete(NonExternalParent* pParent)
	{
		printf("부모를 삭제했어요!\n");
		delete pParent;
	}
};

class NonExternalChild : NonExternalParent
{
public:
	NonExternalChild() = default;
	virtual ~NonExternalChild() = default;

	static NonExternalParent* CreateParent()
	{
		printf("자식에서 부모를 생성할게요!\n");

		// 상속 관계에서도 생성자에 접근할 수 없어요!
		//NonExternalParent parent;
		//NonExternalParent* pParent = new NonExternalParent;
		//std::unique_ptr<NonExternalParent> spParent = std::make_unique<NonExternalParent>();

		// 부모의 함수를 이용하면 이렇게 생성할 수 있어요!
		return NonExternalParent::Create();
	}
};

// NON_COPYABLE_CLASS와 NON_EXTERNAL_CLASS를 합한 싱글톤 클래스에요.
// 인스턴스를 생성하는 부분은 없어도 문제 없지만...
// 싱글톤의 정의가 인스턴스 개수를 제한하는 것이므로 최소한 1개는 만들어야 해요.
class Singleton
{
	NON_COPYABLE_CLASS(Singleton);
	NON_EXTERNAL_CLASS(Singleton);

public:
	static Singleton* I() // 자주 호출되므로 무조건 짧은 이름으로! (I는 Instance의 약자)
	{
		if (m_pInst == nullptr)
		{
			m_pInst = new Singleton;
		}

		return m_pInst;
	}

	static void Destroy() // 외부에서 소멸자에 접근할 수 없으므로 직접 삭제해줘야 해요!
	{
		SAFE_DELETE(m_pInst);
	}

	void Log()
	{
		printf("싱글톤 테스트 로그!\n");
	}

private:
	static Singleton* m_pInst;
};

Singleton* Singleton::m_pInst = nullptr;

//////////////////////////////////////////////////////////////////////////
// 프로그램이 시작되는 곳이에요.
Int32 main()
{
	// 메모리 누수를 확인하는 방법이에요.
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

#if 0 // NON_COPYABLE_CLASS를 테스트해볼게요.	
	NonCopyableParent firstParent;
	NonCopyableParent secondParent;
	//firstParent = secondParent; // 대입 연산이 막혔어요!

	NonCopyableChild firstChild;
	NonCopyableChild secondChild;
	//firstChild = secondChild; // 상속 관계도 막혀요!
#endif

#if 0 // NON_EXTERNAL_CLASS를 테스트해볼게요.
	//NonExternalParent parent; // 외부에서의 생성이 막혔어요!
	NonExternalChild child; // 상속 관계라면 가능해요!

	//NonExternalParent* pParent = new NonExternalParent; // 동적할당도 막혀요!
	NonExternalChild* pChild = new NonExternalChild; // 상속 관계라면 가능해요!
	SAFE_DELETE(pChild);

	//std::unique_ptr<NonExternalParent> spParent = std::make_unique<NonExternalParent>(); // 스마트 포인터도 막혀요!
	std::unique_ptr<NonExternalChild> spChild = std::make_unique<NonExternalChild>(); // 상속 관계라면 가능해요!

	// 외부에서는 부모의 함수를 이용해서 생성할 수 있어요!
	// 하지만 소멸도 직접해줘야 하죠...
	NonExternalParent* pParent = NonExternalParent::Create();
	NonExternalParent::Delete(pParent);

	// 정의하기 나름이지만 외부에서는 자식의 함수를 이용해서 생성할 수도 있어요!
	// 이렇게 내부 구현을 그대로 이용하는 방법을 래핑 또는 어댑터라고 하죠.
	// 다른 말로 표현하면 인터페이스가 어댑터 역할을 한다고도 해요.
	NonExternalParent* pParentFromChild = NonExternalChild::CreateParent();
	NonExternalParent::Delete(pParentFromChild);
#endif

#if 0 // NON_COPYABLE_CLASS와 NON_EXTERNAL_CLASS가 적용된 싱글톤을 보여드릴게요.
	//Singleton singleton; // 외부에서 생성할 수 없어요!
	Singleton* pSingleton = Singleton::I(); // 포인터로 복사할 수는 있어요!
	//delete pSingleton; // 하지만 외부에서는 삭제할 수 없어요!

	Singleton::I()->Log(); // 싱글톤의 함수 호출 방법이에요!
	Singleton::Destroy(); // 싱글톤은 외부에서 삭제할 수 없으므로 이렇게 삭제해줘야 해요!
#endif

	return 0;
}