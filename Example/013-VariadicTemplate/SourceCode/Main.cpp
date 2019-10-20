// =====================================================================================
// Copyright(c) 2019, Ruvendix. All Rights Reserved.
// 
// �� ���۹��� ũ������Ƽ�� Ŀ���� ������ǥ�� 4.0 ���� ���̼����� ���� �̿��� �� �ֽ��ϴ�.
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
		printf("TData�� int Ÿ��!\n");
	}
	else if (strType == "char")
	{
		printf("TData�� char Ÿ��!\n");
	}
	else if (strType == "float")
	{
		printf("TData�� float Ÿ��!\n");
	}
	else if (strType == "class MyClass")
	{
		printf("TData�� class MyClass Ÿ��!\n");
	}
	printf("\n");
}

// ���� ���ø����� Base Case�� �ʿ��ؿ�.
template <typename TData>
void ShowDataType(const TData& data)
{
	printf("Base Case ����!\n");
	ShowDataTypeImpl(data);
}

template <typename TData, typename ... TOthers>
void ShowDataType(const TData& data, const TOthers& ... others)
{
	printf("�Ķ���� �� ���� : %d\n", sizeof...(TOthers));

	ShowDataTypeImpl(data);
	ShowDataType(others...); // �� �ͽ����
}

// C++17�� ���� ���� �̿��� ����̿���.
template <typename TData, typename ... TOthers>
TData SumNum(const TData& begin, const TOthers& ... others)
{
	return (begin + ... + others);
}

int32 main()
{
	ShowDataType(10, 23.25f, 'W', MyClass());
	
	//printf("1���� 5���� ���� �� : %d\n", SumNum(1, 2, 3, 4, 5));
	//printf("1���� 5���� �Ǽ� �� : %f\n", SumNum(1.0f, 2.0f, 3.0f, 4.0f, 5.0f));
	
	return EXIT_SUCCESS;
}