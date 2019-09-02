// =====================================================================================
// Copyright(c) 2019, Ruvendix. All Rights Reserved.
// 
// 이 저작물은 크리에이티브 커먼즈 저작자표시 4.0 국제 라이선스에 따라 이용할 수 있습니다.
// http://creativecommons.org/licenses/by/4.0/
// =====================================================================================

#include <string>

using int32 = signed   __int32; // "typedef signed   __int32 int32"와 같아요.

int main()
{
#if 0

	//////////////////////////////////////////////////////////////////////////
	// 1차원 배열을 이용해봐요~
	//////////////////////////////////////////////////////////////////////////

	// std::string만큼의 공간을 4개 가진 배열이에요.
	std::string techTreeTable[4];

	// 배열의 인덱스는 0부터 시작해요!
	techTreeTable[0] = "연합체";
	techTreeTable[1] = "관문";
	techTreeTable[2] = "우주관문";
	techTreeTable[3] = "로봇공학시설";

	printf("<1차원 배열로 문자열 출력하기~>\n\n");
	for (int32 i = 0; i < 4; ++i)
	{
		printf("\"%s\"\n", techTreeTable[i].c_str());
	}
	printf("\n");

#endif

#if 0

	//////////////////////////////////////////////////////////////////////////
	// 2차원 배열을 이용해봐요~
	//////////////////////////////////////////////////////////////////////////

	// std::string만큼의 공간을 7개씩 갖고 있는 배열 4개에요.
	// 즉, "4 * 7 = 28"개의 공간을 갖게 되죠~
	std::string techTreeTable[4][7];

	// 연합체를 설정할게요.
	techTreeTable[0][0] = "연결체";
	techTreeTable[0][1] = "탐사정";
	techTreeTable[0][2] = "모선";

	// 관문을 설정할게요.
	techTreeTable[1][0] = "관문";
	techTreeTable[1][1] = "광전사";
	techTreeTable[1][2] = "파수기";
	techTreeTable[1][3] = "추적자";
	techTreeTable[1][4] = "사도";
	techTreeTable[1][5] = "고위 기사";
	techTreeTable[1][6] = "암흑 기사";

	// 우주관문을 설정할게요.
	techTreeTable[2][0] = "우주관문";
	techTreeTable[2][1] = "불사조";
	techTreeTable[2][2] = "예언자";
	techTreeTable[2][3] = "공허 포격기";
	techTreeTable[2][4] = "폭풍함";
	techTreeTable[2][5] = "우주모함";

	// 로봇공학 시설을 설정할게요.
	techTreeTable[3][0] = "로봇공학 시설";
	techTreeTable[3][1] = "관측선";
	techTreeTable[3][2] = "차원 분광기";
	techTreeTable[3][3] = "불멸자";
	techTreeTable[3][4] = "거신";
	techTreeTable[3][5] = "분열기";

	printf("<2차원 배열로 문자열 출력하기~>\n\n");
	for (int32 i = 0; i < 4; ++i)
	{
		printf("\"%s\" 테크 트리\n", techTreeTable[i][0].c_str());

		for (int32 j = 1; j < 7; ++j)
		{
			std::string szTechTreeUnitName = techTreeTable[i][j];
			if (szTechTreeUnitName.empty() == true)
			{
				break;
			}

			printf("   \"%s\"\n", techTreeTable[i][j].c_str());
		}

		printf("\n");
	}

#endif

	return EXIT_SUCCESS;
}