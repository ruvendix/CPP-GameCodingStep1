// =====================================================================================
// Copyright(c) 2019, Ruvendix. All Rights Reserved.
// 
// 이 저작물은 크리에이티브 커먼즈 저작자표시 4.0 국제 라이선스에 따라 이용할 수 있습니다.
// http://creativecommons.org/licenses/by/4.0/
// =====================================================================================

#include <cstdio>
#include <type_traits>

using Int32 = signed __int32;
using Real32 = float;

#define CHECK_NULLPTR(ptr)\
	if (ptr == nullptr)\
	{\
		printf("%s is nullptr\n", #ptr);\
	}

// 템플릿 인자는 바탕 형식이 되고, 함수 인자는 템플릿 인자를 이용하게 돼요.
template <typename T>
void CheckNullptr(const T* ptr)
{
	static_assert(std::is_pointer_v<T> == false, "It's not single pointer"); // 영어만 사용 가능...
	if (ptr == nullptr)
	{
		// 매크로 함수와는 다르게 이 때는 이름으로 알려줄 수 없어요.
		printf("ptr is nullptr\n");
	}
}

//////////////////////////////////////////////////////////////////////////
// 프로그램이 시작되는 곳이에요.
Int32 main()
{
#if 0
	// nullptr은 널포인터, 즉, 아무것도 가리키지 않는 포인터를 말해요.
	Int32* pNull = nullptr;

	// 널포인터니까 당연히 역참조를 하면 프로그램이 터지죠... (정의되지 않은 행동, undefined behavior)
	//*pNull;

	// 널포인터 체크는 너무하다 싶을 정도로 해도 좋아요!
	if (pNull == nullptr)
	{
		printf("pNull이 가리키는 주소는 0x%p에요.\n", pNull);
	}

	// 널포인터 체크는 이렇게 매크로 함수를 이용해도 되고...
	CHECK_NULLPTR(pNull);

	// 템플릿 함수를 이용해도 돼요
	CheckNullptr(pNull);	
#endif

#if 0
	// C언어의 동적 할당 방법이에요.
	// 이제는 low level에서 할당할 때만 사용하죠.
	Int32* pNum = (Int32*)malloc(sizeof(Int32));
	
	*pNum = 100;
	printf("pNum의 값은 %d\n", *pNum);
	
	free(pNum);
#endif

#if 0
	// C++언어의 동적 할당 방법이에요.
	// 지금도 많이 사용하지만 요즘은 스마트 포인터도 사용하죠. (스마트 포인터는 다음 시간에...)
	Int32* pNum = new Int32;

	*pNum = 200;
	printf("pNum의 값은 %d\n", *pNum);

	delete pNum;	
#endif
	
	return 0;
}