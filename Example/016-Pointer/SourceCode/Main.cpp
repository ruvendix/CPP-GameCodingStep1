// =====================================================================================
// Copyright(c) 2019, Ruvendix. All Rights Reserved.
// 
// �� ���۹��� ũ������Ƽ�� Ŀ���� ������ǥ�� 4.0 ���� ���̼����� ���� �̿��� �� �ֽ��ϴ�.
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

// ���ø� ���ڴ� ���� ������ �ǰ�, �Լ� ���ڴ� ���ø� ���ڸ� �̿��ϰ� �ſ�.
template <typename T>
void CheckNullptr(const T* ptr)
{
	static_assert(std::is_pointer_v<T> == false, "It's not single pointer"); // ��� ��� ����...
	if (ptr == nullptr)
	{
		// ��ũ�� �Լ��ʹ� �ٸ��� �� ���� �̸����� �˷��� �� �����.
		printf("ptr is nullptr\n");
	}
}

//////////////////////////////////////////////////////////////////////////
// ���α׷��� ���۵Ǵ� ���̿���.
Int32 main()
{
#if 0
	// nullptr�� ��������, ��, �ƹ��͵� ����Ű�� �ʴ� �����͸� ���ؿ�.
	Int32* pNull = nullptr;

	// �������ʹϱ� �翬�� �������� �ϸ� ���α׷��� ������... (���ǵ��� ���� �ൿ, undefined behavior)
	//*pNull;

	// �������� üũ�� �ʹ��ϴ� ���� ������ �ص� ���ƿ�!
	if (pNull == nullptr)
	{
		printf("pNull�� ����Ű�� �ּҴ� 0x%p����.\n", pNull);
	}

	// �������� üũ�� �̷��� ��ũ�� �Լ��� �̿��ص� �ǰ�...
	CHECK_NULLPTR(pNull);

	// ���ø� �Լ��� �̿��ص� �ſ�
	CheckNullptr(pNull);	
#endif

#if 0
	// C����� ���� �Ҵ� ����̿���.
	// ������ low level���� �Ҵ��� ���� �������.
	Int32* pNum = (Int32*)malloc(sizeof(Int32));
	
	*pNum = 100;
	printf("pNum�� ���� %d\n", *pNum);
	
	free(pNum);
#endif

#if 0
	// C++����� ���� �Ҵ� ����̿���.
	// ���ݵ� ���� ��������� ������ ����Ʈ �����͵� �������. (����Ʈ �����ʹ� ���� �ð���...)
	Int32* pNum = new Int32;

	*pNum = 200;
	printf("pNum�� ���� %d\n", *pNum);

	delete pNum;	
#endif
	
	return 0;
}