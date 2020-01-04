// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// 이 저작물은 크리에이티브 커먼즈 저작자표시 4.0 국제 라이선스에 따라 이용할 수 있습니다.
// http://creativecommons.org/licenses/by/4.0/
// =====================================================================================

#include <crtdbg.h>
#include <windows.h>

#include <cstdio>
#include <queue>
#include <string>
#include <memory>

using Int32 = signed __int32;
using Real32 = float;

struct DialogueNode; // 전방 선언
using DialogueNodePtr = std::shared_ptr<DialogueNode>;

#ifdef _DEBUG
#define new new(_NORMAL_BLOCK, __FILE__, __LINE__ )                                            
#endif

/**
 * 대사 정보입니다.
 */
struct DialogueInfo
{
	std::string strName; // 화자(말하는 사람)의 이름
	std::string strContents; // 대사 내용
};

/**
 * 대화 트리의 노드입니다.
 */
struct DialogueNode
{
	DialogueInfo                 selfDialogueInfo; // 화자의 정보
	std::vector<DialogueInfo>    vecSequenceDialogueInfo; // 연속으로 진행되는 대사 모음
	std::vector<std::string>     vecStrTriggerContents; // 분기되는 내용 모음
	std::vector<DialogueNodePtr> vecNextDialogueNode; // 다음 대사 모음 (하나 이상일 수도 있음!)
};

/**
 * 자주 사용되는 콘솔 텍스트 색상 목록입니다.
 */
enum class EConsoleTextColorType : Int32
{
	BLACK = 0,
	BLUE,
	GREEN,
	AQUA,
	RED,
	PURPLE,
	YELLOW,
	WHITE,
	GRAY,
	LIGHT_BLUE,
	LIGHT_GREEN,
	LIGHT_AQUA,
	LIGHT_RED,
	LIGHT_PURPLE,
	LIGHT_YELLOW,
	BRIGHT_WHITE,
};

const Int32 DIALOG_RANGE_WIDTH = 60;
const Int32 DIALOG_RANGE_HEIGHT = 6;

#pragma region 유틸리티 함수 선언 모음
template <typename EType>
constexpr auto ToUnderlyingType(EType val) noexcept
{
	static_assert(std::is_enum_v<EType>, "Only use enum type!");
	return static_cast<std::underlying_type_t<EType>>(val);
}

void PauseApp();
void ClearConsoleScreen();
void ClearStdInputBuffer();
void ChangeConsoleTextColor(EConsoleTextColorType consoleTextColorType);
void MoveConsolePos(Int32 x, Int32 y);
bool InputNumAutoRange(_Out_ Int32& destNum, Int32 minNum, Int32 maxNum);
Int32 ClampNum(Int32 targetNum, Int32 minNum, Int32 maxNum);
EConsoleTextColorType QueryCurrentConsoleTextColor();
#pragma endregion

#pragma region 대화 트리 함수 선언 모음
void InitDialogueTree();
void RunDialogue(const DialogueNodePtr& spDialogueNode);
void EndDialogue();
void ShowDialogueInfo(const DialogueInfo& dialogueInfo);
void DrawDialogueEdge();
void ReplaceDialogueContents(_Out_ std::string& destStrContents, const std::string_view& srcStrContents);
DialogueNodePtr CreateDialogueNode(const std::string_view& strName, const std::string_view& strContents);
#pragma endregion

DialogueNodePtr g_spRootDialogueNode; // 대화당 루트 노드는 필수!

/**
 * 프로그램이 시작되는 곳입니다.
 */
Int32 main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	InitDialogueTree();
	RunDialogue(g_spRootDialogueNode);
	EndDialogue();
	
	return 0;
}

#pragma region 유틸 함수 정의 모음
/**
 * 응용 프로그램을 잠시 멈춥니다.
 */
void PauseApp()
{
	system("pause");
}

/**
 * 콘솔창을 깨끗하게 지웁니다.
 */
void ClearConsoleScreen()
{
	system("cls");
}

/**
 * 표준 입력 버퍼를 비웁니다.
 */
void ClearStdInputBuffer()
{
	char ch = '0'; // EOF나 '\n'만 아니면 괜찮아요.

	// 표준 입력 버퍼를 비우는 방법이에요.
	// std::fflush(stdin)도 있지만, 표준에는 적합하지 않아서 생략할게요.
	while ( (ch != EOF) &&
		    (ch != '\n') )
	{
		ch = static_cast<char>(getchar());
	}
}

/**
 * 콘솔 텍스트 색상을 변경합니다.
 */
void ChangeConsoleTextColor(EConsoleTextColorType consoleTextColorType)
{
	::SetConsoleTextAttribute(::GetStdHandle(STD_OUTPUT_HANDLE), ToUnderlyingType(consoleTextColorType));
}

/**
 * 콘솔 좌표를 이동시킵니다.
 */
void MoveConsolePos(Int32 x, Int32 y)
{
	const COORD pos = { static_cast<short>(x), static_cast<short>(y) };
	::SetConsoleCursorPosition(::GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

/**
 * 숫자를 입력 받음과 동시에 입력 범위를 벗어나면 자동 조절합니다.
 */
bool InputNumAutoRange(_Out_ Int32& destNum, Int32 minNum, Int32 maxNum)
{
	// 최솟값이 최댓값보다 크다면 둘을 바꿔야 해요! (swap)
	if (minNum > maxNum)
	{
		std::swap(minNum, maxNum);
	}

	printf("입력 범위를 벗어나면 자동 조절됩니다. (%d ~ %d)\n", minNum, maxNum);
	printf("> ");

	Int32 inputResult = scanf_s("%d", &destNum);
	printf("\n");
	ClearStdInputBuffer();

	if (inputResult == 0)
	{
		printf("정수만 입력 가능해요!\n\n");
		return false;
	}

	destNum = ClampNum(destNum, minNum, maxNum);
	return true;
}

/**
 * 숫자를 제한된 범위로 고정시킵니다.
 */
Int32 ClampNum(Int32 targetNum, Int32 minNum, Int32 maxNum)
{
	Int32 resultNum = targetNum;

	if (resultNum < minNum)
	{
		resultNum = minNum;
	}
	else if (resultNum > maxNum)
	{
		resultNum = maxNum;
	}

	return resultNum;
}

/**
 * 현재 콘솔 텍스트 색상을 알려줍니다.
 */
EConsoleTextColorType QueryCurrentConsoleTextColor()
{
	CONSOLE_SCREEN_BUFFER_INFO consoleScreenBufferInfo;
	::ZeroMemory(&consoleScreenBufferInfo, sizeof(consoleScreenBufferInfo));

	::GetConsoleScreenBufferInfo(::GetStdHandle(STD_OUTPUT_HANDLE), &consoleScreenBufferInfo);

	if ( (consoleScreenBufferInfo.wAttributes < 0) ||
		 (consoleScreenBufferInfo.wAttributes > 15) )
	{
		printf("제공되는 색상 범위를 초과했어요!\n");
	}
	
	return static_cast<EConsoleTextColorType>(consoleScreenBufferInfo.wAttributes);
}
#pragma endregion

#pragma region 대화 트리 함수 정의 모음
/**
 * 대화 트리를 구성합니다.
 * 대화 트리의 깊이를 D(Depth)라 하고, 노드는 N(Node)라 할게요.
 * 원래는 그림으로 보여줘야 하는데 지금은 D0N1->D1N0 이렇게 표현할게요.
 * 단순하게 진행되는 대화는 Depth를 하나로 묶었어요.
 */
void InitDialogueTree()
{
	g_spRootDialogueNode = CreateDialogueNode("마을 사람", "안녕하세요, 우리 마을에 오신 걸 환영합니다!");

	// D0의 분기 대사들
	g_spRootDialogueNode->vecStrTriggerContents.emplace_back("분위기가 별로다.");
	g_spRootDialogueNode->vecStrTriggerContents.emplace_back("마을 소개를 부탁한다.");
	g_spRootDialogueNode->vecStrTriggerContents.emplace_back("나이를 묻는다.");
	
#pragma region D0의 반응 대사들
	// D0N0의 반응 대사
	DialogueNodePtr spDepth1DialogueNode = CreateDialogueNode("플레이어", "마을이 후졌네!");

	DialogueInfo dialogueInfo = {"마을 사람", "무례한 사람에게 더 할 말은 없어요."};
	spDepth1DialogueNode->vecSequenceDialogueInfo.push_back(dialogueInfo);
	g_spRootDialogueNode->vecNextDialogueNode.push_back(spDepth1DialogueNode);

#pragma region D0N1의 반응 대사 묶음
	// D0N1의 반응 대사
	spDepth1DialogueNode = CreateDialogueNode("플레이어", "안녕하세요, 마을 소개 좀 해주세요.");

	ReplaceDialogueContents(dialogueInfo.strContents, "마을 소개 말이군요, 알겠습니다!");
	spDepth1DialogueNode->vecSequenceDialogueInfo.push_back(dialogueInfo);

	ReplaceDialogueContents(dialogueInfo.strContents, "우리 마을은 작지만 살기 좋은 곳이에요.");
	spDepth1DialogueNode->vecSequenceDialogueInfo.push_back(dialogueInfo);

	ReplaceDialogueContents(dialogueInfo.strContents, "마을 사람들 인심도 좋고, 사건도 거의 일어나지 않죠!");
	spDepth1DialogueNode->vecSequenceDialogueInfo.push_back(dialogueInfo);

	ReplaceDialogueContents(dialogueInfo.strContents, "그런데... 음... (말을 머뭇거린다)");
	spDepth1DialogueNode->vecSequenceDialogueInfo.push_back(dialogueInfo);

	spDepth1DialogueNode->vecStrTriggerContents.emplace_back("무시하고 떠난다.");
	spDepth1DialogueNode->vecStrTriggerContents.emplace_back("무슨 일인지 물어본다.");

#pragma region D0N1->D1의 반응 대사들
	// D0N1->D1N0의 반응 대사
	DialogueNodePtr spDepth2DialogueNode = CreateDialogueNode("플레이어", "그렇군요, 그럼 전 이만...");
	spDepth1DialogueNode->vecNextDialogueNode.push_back(spDepth2DialogueNode);

#pragma region D0N1->D1N1의 반응 대사 묶음
	// D0N1->D1N1의 반응 대사
	spDepth2DialogueNode = CreateDialogueNode("플레이어", "무슨 일이라도 있나요?");

	ReplaceDialogueContents(dialogueInfo.strContents, "요즘 밤만 되면 밭이 신경 쓰여요...");
	spDepth2DialogueNode->vecSequenceDialogueInfo.push_back(dialogueInfo);

	ReplaceDialogueContents(dialogueInfo.strContents, "부시럭대는 소리가 들린다고도 하고...");
	spDepth2DialogueNode->vecSequenceDialogueInfo.push_back(dialogueInfo);

	ReplaceDialogueContents(dialogueInfo.strContents, "빨간 눈을 봤다는 사람도 있어요...");
	spDepth2DialogueNode->vecSequenceDialogueInfo.push_back(dialogueInfo);

	ReplaceDialogueContents(dialogueInfo.strContents, "아직은 피해가 없지만, 다들 신경이 쓰이나 봐요...");
	spDepth2DialogueNode->vecSequenceDialogueInfo.push_back(dialogueInfo);

	spDepth2DialogueNode->vecStrTriggerContents.emplace_back("무시하고 떠난다.");
	spDepth2DialogueNode->vecStrTriggerContents.emplace_back("조사해본다고 한다.");

#pragma region D0N1->D1N1->D2의 반응 대사들
	// D0N1->D1N1->D2N0의 반응 대사
	DialogueNodePtr spDepth3DialogueNode = CreateDialogueNode("플레이어", "그렇군요, 그럼 전 이만..."); // 중복 내용
	spDepth2DialogueNode->vecNextDialogueNode.push_back(spDepth3DialogueNode);

#pragma region D0N1->D1N1->D2N1의 반응 대사 묶음
	// D0N1->D1N1->D2N1의 반응 대사
	spDepth3DialogueNode = CreateDialogueNode("플레이어", "무슨 일인지 제가 알아볼게요.");

	ReplaceDialogueContents(dialogueInfo.strContents, "앗...! 감사합니다, 마침 도움이 필요했어요!");
	spDepth3DialogueNode->vecSequenceDialogueInfo.push_back(dialogueInfo);

	ReplaceDialogueContents(dialogueInfo.strContents, "제가 촌장님께 안내해드리겠습니다!");
	spDepth3DialogueNode->vecSequenceDialogueInfo.push_back(dialogueInfo);

	spDepth2DialogueNode->vecNextDialogueNode.push_back(spDepth3DialogueNode);
#pragma endregion

	spDepth2DialogueNode->vecNextDialogueNode.push_back(spDepth3DialogueNode);
#pragma endregion

	spDepth1DialogueNode->vecNextDialogueNode.push_back(spDepth2DialogueNode);
#pragma endregion
#pragma endregion

	g_spRootDialogueNode->vecNextDialogueNode.push_back(spDepth1DialogueNode);
#pragma endregion

#pragma region D0N2의 반응 대사 묶음
	// D0N2의 반응 대사
	spDepth1DialogueNode = CreateDialogueNode("플레이어", "실례지만, 나이는 어떻게 되시나요?");

	ReplaceDialogueContents(dialogueInfo.strContents, "제 나이요...?");
	spDepth1DialogueNode->vecSequenceDialogueInfo.push_back(dialogueInfo);

	ReplaceDialogueContents(dialogueInfo.strContents, "어... 음...");
	spDepth1DialogueNode->vecSequenceDialogueInfo.push_back(dialogueInfo);

	ReplaceDialogueContents(dialogueInfo.strContents, "죄송하지만, 알려드릴 수 없습니다.");
	spDepth1DialogueNode->vecSequenceDialogueInfo.push_back(dialogueInfo);

	g_spRootDialogueNode->vecNextDialogueNode.push_back(spDepth1DialogueNode);
#pragma endregion	
#pragma endregion	
}

/**
 * 대화 노드를 생성합니다.
 */
DialogueNodePtr CreateDialogueNode(const std::string_view& strName, const std::string_view& strContents)
{
	DialogueNodePtr spDialogueNode = std::make_shared<DialogueNode>();
	spDialogueNode->selfDialogueInfo.strName = strName;
	spDialogueNode->selfDialogueInfo.strContents = strContents;
	return spDialogueNode;
}

/**
 * 대화를 진행합니다.
 * 첫 번째 호출에서는 반드시 루트 노드를 넣어주세요!
 */
void RunDialogue(const DialogueNodePtr& spDialogueNode)
{
	ShowDialogueInfo(spDialogueNode->selfDialogueInfo);

	// 연속 대사 진행 부분이에요.
	if (spDialogueNode->vecSequenceDialogueInfo.empty() != true)
	{
		PauseApp();
		
		for (const auto& iter : spDialogueNode->vecSequenceDialogueInfo)
		{
			ShowDialogueInfo(iter);
			PauseApp();
		}

		// 연속 대사일 경우 다음 대사 노드의 인덱스는 0 고정이에요!
		// 묶음 대사 노드에 선택지가 없을 때만 다음 대사로 이동해야 해요.
		if ( (spDialogueNode->vecNextDialogueNode.empty() != true) &&
			 (spDialogueNode->vecStrTriggerContents.empty() == true) )
		{
			RunDialogue(spDialogueNode->vecNextDialogueNode.at(0));
		}

		// 별 의미 없는 화면 갱신용이에요.
		ShowDialogueInfo(*(--spDialogueNode->vecSequenceDialogueInfo.end()));
	}
	
	// 분기 대사 진행 부분이에요.
	if (spDialogueNode->vecStrTriggerContents.empty() != true)
	{
		MoveConsolePos(0, DIALOG_RANGE_HEIGHT + 2);
		
		size_t size = spDialogueNode->vecStrTriggerContents.size();
		for (size_t i = 0; i < size; ++i)
		{
			printf("%d. %s\n", i + 1, spDialogueNode->vecStrTriggerContents[i].c_str());
		}
		printf("\n");

		Int32 selectedIdx = 0;
		if (InputNumAutoRange(selectedIdx, 1, size) == false)
		{
			return;
		}
		
		--selectedIdx;

		// 선택된 인덱스에 맞는 다음 대사 노드로 재귀 함수를 호출해야 해요!
		if (spDialogueNode->vecNextDialogueNode.empty() != true)
		{
			RunDialogue(spDialogueNode->vecNextDialogueNode.at(selectedIdx));
			return;
		}
		else
		{
			printf("분기 대사에서는 다음 대화 노드가 무조건 있어야 해요!\n");
		}
	}
}

/**
 * 대화의 종료를 알려줍니다.
 */
void EndDialogue()
{
	printf("대화가 종료되었어요!\n\n");
}

/**
 * 대사를 출력합니다.
 */
void ShowDialogueInfo(const DialogueInfo& dialogueInfo)
{
	ClearConsoleScreen();

	EConsoleTextColorType backupConsoleTextColor = QueryCurrentConsoleTextColor();

	// 화자의 이름을 출력해요.
	MoveConsolePos(4, 2);
	ChangeConsoleTextColor(EConsoleTextColorType::YELLOW);
	printf("%s", dialogueInfo.strName.c_str());
	
	// 화자의 대사를 출력해요.
	MoveConsolePos(6, 4);
	ChangeConsoleTextColor(EConsoleTextColorType::AQUA);
	printf("%s", dialogueInfo.strContents.c_str());

	DrawDialogueEdge();

	// 전에 사용하던 색상으로 복구해줘요.
	ChangeConsoleTextColor(backupConsoleTextColor);
}

/**
 * 대사 영역을 그립니다.
 */
void DrawDialogueEdge()
{
	ChangeConsoleTextColor(EConsoleTextColorType::GRAY);
	
	for (Int32 i = 0; i < DIALOG_RANGE_WIDTH; i += 2)
	{
		MoveConsolePos(i, 0);
		printf("■");
	}
	
	for (Int32 i = 1; i < DIALOG_RANGE_HEIGHT; ++i)
	{
		MoveConsolePos(0, i);
		printf("■");

		MoveConsolePos(DIALOG_RANGE_WIDTH - 2, i);
		printf("■");
	}
	
	for (Int32 i = 0; i < DIALOG_RANGE_WIDTH; i += 2)
	{
		MoveConsolePos(i, DIALOG_RANGE_HEIGHT);
		printf("■");
	}

	MoveConsolePos(0, DIALOG_RANGE_HEIGHT + 2);
}

/**
 * 대사 내용을 변경합니다.
 * std::string의 replace()로 복사 비용을 줄였어요.
 */
void ReplaceDialogueContents(_Out_ std::string& destStrContents, const std::string_view& srcStrContents)
{
	destStrContents.replace(destStrContents.cbegin(), destStrContents.cend(), srcStrContents);
}
#pragma endregion
