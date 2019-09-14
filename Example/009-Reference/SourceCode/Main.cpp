// =====================================================================================
// Copyright(c) 2019, Ruvendix. All Rights Reserved.
// 
// 이 저작물은 크리에이티브 커먼즈 저작자표시 4.0 국제 라이선스에 따라 이용할 수 있습니다.
// http://creativecommons.org/licenses/by/4.0/
// =====================================================================================

#include <string>

using int32 = signed __int32; // "typedef signed __int32 int32"와 같아요.

int main()
{
#if 0
	//////////////////////////////////////////////////////////////////////////
	// 참조자를 알아볼게요~
	//////////////////////////////////////////////////////////////////////////
	int32  forceLevel = 4;
	int32& refForceLevel = forceLevel; // 참조자는 초기화 필수!

	++refForceLevel;
	printf("포스 레벨 : %d (원본)\n", forceLevel);
	printf("포스 레벨 : %d (참조자)\n", refForceLevel);

	const int32& refConstForceLevel = refForceLevel; // 참조자끼리는 할당 가능!
	//++refConstForceLevel; // const가 붙은 참조자는 수정 불가능!
#endif

#if 0
	//////////////////////////////////////////////////////////////////////////
	// 참조자를 반복자로 이용해볼게요~
	//////////////////////////////////////////////////////////////////////////
	std::string szAnimalsName[4] = { "곰", "늑대", "사자", "코끼리" };

	// 참조자 iter는 데이터 복사가 발생되지 않아요.
	printf("<참조자를 사용한 결과에요>\n");
	for (std::string& iter : szAnimalsName)
	{
		iter.insert(0, "흉폭한 ");
		printf("동물 목록 : %s\n", iter.c_str());

		// 데이터를 원래대로 복구할게요.
		iter = iter.substr(7, iter.length());
	}
	printf("\n");

	printf("<const 참조자를 사용한 결과에요>\n");
	for (const std::string& iter : szAnimalsName)
	{
		//iter.insert(0, "흉폭한 "); // const 참조자는 데이터를 수정할 수 없어요!
		printf("동물 목록 : %s\n", iter.c_str());
	}
	printf("\n");
#endif

	return EXIT_SUCCESS;
}