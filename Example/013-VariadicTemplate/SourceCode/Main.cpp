// =====================================================================================
// Copyright(c) 2019, Ruvendix. All Rights Reserved.
// 
// 이 저작물은 크리에이티브 커먼즈 저작자표시 4.0 국제 라이선스에 따라 이용할 수 있습니다.
// http://creativecommons.org/licenses/by/4.0/
// =====================================================================================

#include <typeinfo>
#include <cstdio>
#include <string>

using int32  = signed __int32;
using real32 = float;

class MyClass
{

};

template <typename TData>
void ShowDataTypeImpl(const TData& data)
{
	std::string strType = typeid(TData).name();
	if (strType == "int")
	{
		printf("TData는 int 타입!\n");
	}
	else if (strType == "char")
	{
		printf("TData는 char 타입!\n");
	}
	else if (strType == "float")
	{
		printf("TData는 float 타입!\n");
	}
	else if (strType == "class MyClass")
	{
		printf("TData는 class MyClass 타입!\n");
	}
	printf("\n");
}

// 가변 템플릿에는 Base Case가 필요해요.
template <typename TData>
void ShowDataType(const TData& data)
{
	printf("Base Case 진입!\n");
	ShowDataTypeImpl(data);
}

template <typename TData, typename ... TOthers>
void ShowDataType(const TData& data, const TOthers& ... others)
{
	printf("파라미터 팩 개수 : %d\n", sizeof...(TOthers));

	ShowDataTypeImpl(data);
	ShowDataType(others...); // 팩 익스펜션
}

// C++17의 폴드 식을 이용한 방법이에요.
template <typename TData, typename ... TOthers>
TData SumNum(const TData& begin, const TOthers& ... others)
{
	return (begin + ... + others);
}

int32 main()
{
	ShowDataType(10, 23.25f, 'W', MyClass());
	
	//printf("1부터 5까지 정수 합 : %d\n", SumNum(1, 2, 3, 4, 5));
	//printf("1부터 5까지 실수 합 : %f\n", SumNum(1.0f, 2.0f, 3.0f, 4.0f, 5.0f));
	
	return EXIT_SUCCESS;
}