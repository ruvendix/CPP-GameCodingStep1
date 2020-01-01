// =====================================================================================
// Copyright(c) 2019, Ruvendix. All Rights Reserved.
// 
// �� ���۹��� ũ������Ƽ�� Ŀ���� ������ǥ�� 4.0 ���� ���̼����� ���� �̿��� �� �ֽ��ϴ�.
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

// SAFE_DELETE�� ���ø� �Լ��� �����Ϸ��� �������� �����ڰ� �ʿ��ؿ�.
template <typename T>
void SafeDelete(T*& ptr) // ���� ���� ����� �ƴ�...
{
	static_assert(std::is_pointer_v<T> != true, "It's not single pointer");
	
	if (ptr != nullptr)
	{
		delete ptr;
		ptr = nullptr;
	}
}

//////////////////////////////////////////////////////////////////////////
// ���α׷��� ���۵Ǵ� ���̿���.
Int32 main()
{
	// �޸� ������ Ȯ���ϴ� ����̿���.
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

#if 0
	Int32* pNum = new Int32(100);
	printf("pNum : 0x%p\t*pNum : %d\n", pNum, *pNum);

	delete pNum;

	// pNum�� nullptr�� �ƴ����� ��۸�(Dangling) �����Ͱ� �ǹǷ� ���α׷��� �����...
	if (pNum != nullptr)
	{
		printf("pNum�� ��۸� ������! (pNum : 0x%p)\n", pNum);
	}
#endif

#if 0
	Int32* pNum = new Int32(100);
	printf("pNum : 0x%p\t*pNum : %d\n", pNum, *pNum);

	// ��۸� �����͸� �����ϱ� ���� SAFE_DELETE�� �������.
	SafeDelete(pNum);

	if (pNum == nullptr)
	{
		printf("pNum�� �Ϻ��ϰ� ������ ������! (pNum : 0x%p)\n", pNum);
	}	
#endif

#if 0
	// �Ҵ�� �޸� �ڵ� ���� �� �������� üũ�� �����Ϸ��� ������ ����Ʈ ������!
	// ����Ʈ �����ʹ� ������ó�� ���̴� �ͻ����� �����δ� ��ü��� ��Ʈ�� ���� ������!
	std::unique_ptr<Int32> spNum = std::make_unique<Int32>(100);
	printf("spNum : 0x%p\t*spNum : %d\n", spNum.get(), *spNum);

	// ������ raw �����ͷ� ������ ���� ��۸� �����͸� ������ �� �����...
	Int32* pNum = new Int32(200);
	printf("pNum : 0x%p\t*pNum : %d\n", pNum, *pNum);

	{
		std::unique_ptr<Int32> spNum(pNum);
		printf("spNum : 0x%p\t*spNum : %d\n", spNum.get(), *spNum);

		// std::unique_ptr�� �������� �����ϹǷ� �������� ������ �� �����...
		//std::unique_ptr<Int32> spNewNum = spNumInScope;

		// ������ �������� �����ϰ� �ѱ�� �� ��������!
		std::unique_ptr<Int32> spNewNum = std::move(spNum);

		// �������� ������� �ڵ����� ��������!
		printf("spNum : 0x%p\n", spNum.get());

		// �������� ���� ���� ����Ʈ �����ͷθ� ��� �����ؿ�!
		printf("spNewNum : 0x%p\t*spNewNum : %d\n", spNewNum.get(), *spNewNum);
	}

	// �� ��쿡�� ��۸� �����Ϳ���...
	printf("pNum : 0x%p\t*pNum : %d\n", pNum, *pNum);
#endif
	
#if 0
	// �������� ������ �� �ִ� ����Ʈ �����Ͱ� �־��!
	// ���� ī��Ʈ�� �̿��ؼ� �������� ��������.
	std::shared_ptr<Int32> spNum = std::make_shared<Int32>(100);
	printf("spNum : 0x%p\t*spNum : %d\n", spNum.get(), *spNum);

	// std::unique_ptr -> std::shared_ptr�� ���������� �ݴ�� �Ұ����ؿ�!
	std::unique_ptr<Int32> spUniqueNum = std::make_unique<Int32>(200);
	std::shared_ptr<Int32> spSharedNum = std::move(spUniqueNum); // �������ʹ� �������� ������ �� �־��!
	printf("spSharedNum : 0x%p\t*spSharedNum : %d\n", spSharedNum.get(), *spSharedNum);
	
	// ���� ī��Ʈ�� Ȯ���غ����?
	printf("spSharedNum�� ���� ī��Ʈ : %d\n", spSharedNum.use_count());
	
	// ���� ī��Ʈ�� �������Ѻ��Կ�.
	{
		std::shared_ptr<Int32> spNewSharedNum = spSharedNum;
		printf("spSharedNum�� ���� ī��Ʈ : %d\n", spSharedNum.use_count());
		printf("spNewSharedNum�� ���� ī��Ʈ : %d\n", spNewSharedNum.use_count());
	}

	// �ٽ� ���� ī��Ʈ�� �پ����.
	printf("spSharedNum�� ���� ī��Ʈ : %d\n", spSharedNum.use_count());	
#endif

	if (_CrtDumpMemoryLeaks() != 0)
	{
		printf("�޸� ���� �߻�!\n");
	}

	return 0;
}