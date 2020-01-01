// =====================================================================================
// Copyright(c) 2019, Ruvendix. All Rights Reserved.
// 
// 이 저작물은 크리에이티브 커먼즈 저작자표시 4.0 국제 라이선스에 따라 이용할 수 있습니다.
// http://creativecommons.org/licenses/by/4.0/
// =====================================================================================

#include <crtdbg.h>
#include <cstdio>
#include <type_traits>

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

// SAFE_DELETE를 템플릿 함수로 구현하려면 포인터의 참조자가 필요해요.
template <typename T>
void SafeDelete(T*& ptr) // 별로 좋은 방법은 아님...
{
	static_assert(std::is_pointer_v<T> != true, "It's not single pointer");
	
	if (ptr != nullptr)
	{
		delete ptr;
		ptr = nullptr;
	}
}

//////////////////////////////////////////////////////////////////////////
// 프로그램이 시작되는 곳이에요.
Int32 main()
{
	// 메모리 누수를 확인하는 방법이에요.
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

#if 0
	Int32* pNum = new Int32(100);
	printf("pNum : 0x%p\t*pNum : %d\n", pNum, *pNum);

	delete pNum;

	// pNum은 nullptr이 아니지만 댕글링(Dangling) 포인터가 되므로 프로그램이 뻗어요...
	if (pNum != nullptr)
	{
		printf("pNum은 댕글링 포인터! (pNum : 0x%p)\n", pNum);
	}
#endif

#if 0
	Int32* pNum = new Int32(100);
	printf("pNum : 0x%p\t*pNum : %d\n", pNum, *pNum);

	// 댕글링 포인터를 방지하기 위해 SAFE_DELETE를 사용하죠.
	SafeDelete(pNum);

	if (pNum == nullptr)
	{
		printf("pNum은 완벽하게 해제된 포인터! (pNum : 0x%p)\n", pNum);
	}	
#endif

#if 0
	// 할당된 메모리 자동 해제 및 널포인터 체크를 생략하려고 등장한 스마트 포인터!
	// 스마트 포인터는 포인터처럼 보이는 것뿐이지 실제로는 객체라는 팩트를 잊지 마세요!
	std::unique_ptr<Int32> spNum = std::make_unique<Int32>(100);
	printf("spNum : 0x%p\t*spNum : %d\n", spNum.get(), *spNum);

	// 하지만 raw 포인터로 생성할 때는 댕글링 포인터를 방지할 수 없어요...
	Int32* pNum = new Int32(200);
	printf("pNum : 0x%p\t*pNum : %d\n", pNum, *pNum);

	{
		std::unique_ptr<Int32> spNum(pNum);
		printf("spNum : 0x%p\t*spNum : %d\n", spNum.get(), *spNum);

		// std::unique_ptr은 소유권이 유일하므로 소유권을 공유할 수 없어요...
		//std::unique_ptr<Int32> spNewNum = spNumInScope;

		// 하지만 소유권을 포기하고 넘기는 건 가능하죠!
		std::unique_ptr<Int32> spNewNum = std::move(spNum);

		// 소유권이 사라지면 자동으로 널포인터!
		printf("spNum : 0x%p\n", spNum.get());

		// 소유권을 새로 받은 스마트 포인터로만 사용 가능해요!
		printf("spNewNum : 0x%p\t*spNewNum : %d\n", spNewNum.get(), *spNewNum);
	}

	// 이 경우에는 댕글링 포인터에요...
	printf("pNum : 0x%p\t*pNum : %d\n", pNum, *pNum);
#endif
	
#if 0
	// 소유권을 공유할 수 있는 스마트 포인터가 있어요!
	// 참조 카운트를 이용해서 소유권을 공유하죠.
	std::shared_ptr<Int32> spNum = std::make_shared<Int32>(100);
	printf("spNum : 0x%p\t*spNum : %d\n", spNum.get(), *spNum);

	// std::unique_ptr -> std::shared_ptr은 가능하지만 반대는 불가능해요!
	std::unique_ptr<Int32> spUniqueNum = std::make_unique<Int32>(200);
	std::shared_ptr<Int32> spSharedNum = std::move(spUniqueNum); // 이제부터는 소유권을 공유할 수 있어요!
	printf("spSharedNum : 0x%p\t*spSharedNum : %d\n", spSharedNum.get(), *spSharedNum);
	
	// 참조 카운트를 확인해볼까요?
	printf("spSharedNum의 참조 카운트 : %d\n", spSharedNum.use_count());
	
	// 참조 카운트를 증가시켜볼게요.
	{
		std::shared_ptr<Int32> spNewSharedNum = spSharedNum;
		printf("spSharedNum의 참조 카운트 : %d\n", spSharedNum.use_count());
		printf("spNewSharedNum의 참조 카운트 : %d\n", spNewSharedNum.use_count());
	}

	// 다시 참조 카운트가 줄어들어요.
	printf("spSharedNum의 참조 카운트 : %d\n", spSharedNum.use_count());	
#endif

	if (_CrtDumpMemoryLeaks() != 0)
	{
		printf("메모리 누수 발생!\n");
	}

	return 0;
}