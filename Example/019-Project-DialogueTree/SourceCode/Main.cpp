// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// �� ���۹��� ũ������Ƽ�� Ŀ���� ������ǥ�� 4.0 ���� ���̼����� ���� �̿��� �� �ֽ��ϴ�.
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

struct DialogueNode; // ���� ����
using DialogueNodePtr = std::shared_ptr<DialogueNode>;

#ifdef _DEBUG
#define new new(_NORMAL_BLOCK, __FILE__, __LINE__ )                                            
#endif

/**
 * ��� �����Դϴ�.
 */
struct DialogueInfo
{
	std::string strName; // ȭ��(���ϴ� ���)�� �̸�
	std::string strContents; // ��� ����
};

/**
 * ��ȭ Ʈ���� ����Դϴ�.
 */
struct DialogueNode
{
	DialogueInfo                 selfDialogueInfo; // ȭ���� ����
	std::vector<DialogueInfo>    vecSequenceDialogueInfo; // �������� ����Ǵ� ��� ����
	std::vector<std::string>     vecStrTriggerContents; // �б�Ǵ� ���� ����
	std::vector<DialogueNodePtr> vecNextDialogueNode; // ���� ��� ���� (�ϳ� �̻��� ���� ����!)
};

/**
 * ���� ���Ǵ� �ܼ� �ؽ�Ʈ ���� ����Դϴ�.
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

#pragma region ��ƿ��Ƽ �Լ� ���� ����
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

#pragma region ��ȭ Ʈ�� �Լ� ���� ����
void InitDialogueTree();
void RunDialogue(const DialogueNodePtr& spDialogueNode);
void EndDialogue();
void ShowDialogueInfo(const DialogueInfo& dialogueInfo);
void DrawDialogueEdge();
void ReplaceDialogueContents(_Out_ std::string& destStrContents, const std::string_view& srcStrContents);
DialogueNodePtr CreateDialogueNode(const std::string_view& strName, const std::string_view& strContents);
#pragma endregion

DialogueNodePtr g_spRootDialogueNode; // ��ȭ�� ��Ʈ ���� �ʼ�!

/**
 * ���α׷��� ���۵Ǵ� ���Դϴ�.
 */
Int32 main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	InitDialogueTree();
	RunDialogue(g_spRootDialogueNode);
	EndDialogue();
	
	return 0;
}

#pragma region ��ƿ �Լ� ���� ����
/**
 * ���� ���α׷��� ��� ����ϴ�.
 */
void PauseApp()
{
	system("pause");
}

/**
 * �ܼ�â�� �����ϰ� ����ϴ�.
 */
void ClearConsoleScreen()
{
	system("cls");
}

/**
 * ǥ�� �Է� ���۸� ���ϴ�.
 */
void ClearStdInputBuffer()
{
	char ch = '0'; // EOF�� '\n'�� �ƴϸ� �����ƿ�.

	// ǥ�� �Է� ���۸� ���� ����̿���.
	// std::fflush(stdin)�� ������, ǥ�ؿ��� �������� �ʾƼ� �����ҰԿ�.
	while ( (ch != EOF) &&
		    (ch != '\n') )
	{
		ch = static_cast<char>(getchar());
	}
}

/**
 * �ܼ� �ؽ�Ʈ ������ �����մϴ�.
 */
void ChangeConsoleTextColor(EConsoleTextColorType consoleTextColorType)
{
	::SetConsoleTextAttribute(::GetStdHandle(STD_OUTPUT_HANDLE), ToUnderlyingType(consoleTextColorType));
}

/**
 * �ܼ� ��ǥ�� �̵���ŵ�ϴ�.
 */
void MoveConsolePos(Int32 x, Int32 y)
{
	const COORD pos = { static_cast<short>(x), static_cast<short>(y) };
	::SetConsoleCursorPosition(::GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

/**
 * ���ڸ� �Է� ������ ���ÿ� �Է� ������ ����� �ڵ� �����մϴ�.
 */
bool InputNumAutoRange(_Out_ Int32& destNum, Int32 minNum, Int32 maxNum)
{
	// �ּڰ��� �ִ񰪺��� ũ�ٸ� ���� �ٲ�� �ؿ�! (swap)
	if (minNum > maxNum)
	{
		std::swap(minNum, maxNum);
	}

	printf("�Է� ������ ����� �ڵ� �����˴ϴ�. (%d ~ %d)\n", minNum, maxNum);
	printf("> ");

	Int32 inputResult = scanf_s("%d", &destNum);
	printf("\n");
	ClearStdInputBuffer();

	if (inputResult == 0)
	{
		printf("������ �Է� �����ؿ�!\n\n");
		return false;
	}

	destNum = ClampNum(destNum, minNum, maxNum);
	return true;
}

/**
 * ���ڸ� ���ѵ� ������ ������ŵ�ϴ�.
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
 * ���� �ܼ� �ؽ�Ʈ ������ �˷��ݴϴ�.
 */
EConsoleTextColorType QueryCurrentConsoleTextColor()
{
	CONSOLE_SCREEN_BUFFER_INFO consoleScreenBufferInfo;
	::ZeroMemory(&consoleScreenBufferInfo, sizeof(consoleScreenBufferInfo));

	::GetConsoleScreenBufferInfo(::GetStdHandle(STD_OUTPUT_HANDLE), &consoleScreenBufferInfo);

	if ( (consoleScreenBufferInfo.wAttributes < 0) ||
		 (consoleScreenBufferInfo.wAttributes > 15) )
	{
		printf("�����Ǵ� ���� ������ �ʰ��߾��!\n");
	}
	
	return static_cast<EConsoleTextColorType>(consoleScreenBufferInfo.wAttributes);
}
#pragma endregion

#pragma region ��ȭ Ʈ�� �Լ� ���� ����
/**
 * ��ȭ Ʈ���� �����մϴ�.
 * ��ȭ Ʈ���� ���̸� D(Depth)�� �ϰ�, ���� N(Node)�� �ҰԿ�.
 * ������ �׸����� ������� �ϴµ� ������ D0N1->D1N0 �̷��� ǥ���ҰԿ�.
 * �ܼ��ϰ� ����Ǵ� ��ȭ�� Depth�� �ϳ��� �������.
 */
void InitDialogueTree()
{
	g_spRootDialogueNode = CreateDialogueNode("���� ���", "�ȳ��ϼ���, �츮 ������ ���� �� ȯ���մϴ�!");

	// D0�� �б� ����
	g_spRootDialogueNode->vecStrTriggerContents.emplace_back("�����Ⱑ ���δ�.");
	g_spRootDialogueNode->vecStrTriggerContents.emplace_back("���� �Ұ��� ��Ź�Ѵ�.");
	g_spRootDialogueNode->vecStrTriggerContents.emplace_back("���̸� ���´�.");
	
#pragma region D0�� ���� ����
	// D0N0�� ���� ���
	DialogueNodePtr spDepth1DialogueNode = CreateDialogueNode("�÷��̾�", "������ ������!");

	DialogueInfo dialogueInfo = {"���� ���", "������ ������� �� �� ���� �����."};
	spDepth1DialogueNode->vecSequenceDialogueInfo.push_back(dialogueInfo);
	g_spRootDialogueNode->vecNextDialogueNode.push_back(spDepth1DialogueNode);

#pragma region D0N1�� ���� ��� ����
	// D0N1�� ���� ���
	spDepth1DialogueNode = CreateDialogueNode("�÷��̾�", "�ȳ��ϼ���, ���� �Ұ� �� ���ּ���.");

	ReplaceDialogueContents(dialogueInfo.strContents, "���� �Ұ� ���̱���, �˰ڽ��ϴ�!");
	spDepth1DialogueNode->vecSequenceDialogueInfo.push_back(dialogueInfo);

	ReplaceDialogueContents(dialogueInfo.strContents, "�츮 ������ ������ ��� ���� ���̿���.");
	spDepth1DialogueNode->vecSequenceDialogueInfo.push_back(dialogueInfo);

	ReplaceDialogueContents(dialogueInfo.strContents, "���� ����� �νɵ� ����, ��ǵ� ���� �Ͼ�� ����!");
	spDepth1DialogueNode->vecSequenceDialogueInfo.push_back(dialogueInfo);

	ReplaceDialogueContents(dialogueInfo.strContents, "�׷���... ��... (���� �ӹ��Ÿ���)");
	spDepth1DialogueNode->vecSequenceDialogueInfo.push_back(dialogueInfo);

	spDepth1DialogueNode->vecStrTriggerContents.emplace_back("�����ϰ� ������.");
	spDepth1DialogueNode->vecStrTriggerContents.emplace_back("���� ������ �����.");

#pragma region D0N1->D1�� ���� ����
	// D0N1->D1N0�� ���� ���
	DialogueNodePtr spDepth2DialogueNode = CreateDialogueNode("�÷��̾�", "�׷�����, �׷� �� �̸�...");
	spDepth1DialogueNode->vecNextDialogueNode.push_back(spDepth2DialogueNode);

#pragma region D0N1->D1N1�� ���� ��� ����
	// D0N1->D1N1�� ���� ���
	spDepth2DialogueNode = CreateDialogueNode("�÷��̾�", "���� ���̶� �ֳ���?");

	ReplaceDialogueContents(dialogueInfo.strContents, "���� �㸸 �Ǹ� ���� �Ű� ������...");
	spDepth2DialogueNode->vecSequenceDialogueInfo.push_back(dialogueInfo);

	ReplaceDialogueContents(dialogueInfo.strContents, "�ν÷���� �Ҹ��� �鸰�ٰ� �ϰ�...");
	spDepth2DialogueNode->vecSequenceDialogueInfo.push_back(dialogueInfo);

	ReplaceDialogueContents(dialogueInfo.strContents, "���� ���� �ôٴ� ����� �־��...");
	spDepth2DialogueNode->vecSequenceDialogueInfo.push_back(dialogueInfo);

	ReplaceDialogueContents(dialogueInfo.strContents, "������ ���ذ� ������, �ٵ� �Ű��� ���̳� ����...");
	spDepth2DialogueNode->vecSequenceDialogueInfo.push_back(dialogueInfo);

	spDepth2DialogueNode->vecStrTriggerContents.emplace_back("�����ϰ� ������.");
	spDepth2DialogueNode->vecStrTriggerContents.emplace_back("�����غ��ٰ� �Ѵ�.");

#pragma region D0N1->D1N1->D2�� ���� ����
	// D0N1->D1N1->D2N0�� ���� ���
	DialogueNodePtr spDepth3DialogueNode = CreateDialogueNode("�÷��̾�", "�׷�����, �׷� �� �̸�..."); // �ߺ� ����
	spDepth2DialogueNode->vecNextDialogueNode.push_back(spDepth3DialogueNode);

#pragma region D0N1->D1N1->D2N1�� ���� ��� ����
	// D0N1->D1N1->D2N1�� ���� ���
	spDepth3DialogueNode = CreateDialogueNode("�÷��̾�", "���� ������ ���� �˾ƺ��Կ�.");

	ReplaceDialogueContents(dialogueInfo.strContents, "��...! �����մϴ�, ��ħ ������ �ʿ��߾��!");
	spDepth3DialogueNode->vecSequenceDialogueInfo.push_back(dialogueInfo);

	ReplaceDialogueContents(dialogueInfo.strContents, "���� ����Բ� �ȳ��ص帮�ڽ��ϴ�!");
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

#pragma region D0N2�� ���� ��� ����
	// D0N2�� ���� ���
	spDepth1DialogueNode = CreateDialogueNode("�÷��̾�", "�Ƿ�����, ���̴� ��� �ǽó���?");

	ReplaceDialogueContents(dialogueInfo.strContents, "�� ���̿�...?");
	spDepth1DialogueNode->vecSequenceDialogueInfo.push_back(dialogueInfo);

	ReplaceDialogueContents(dialogueInfo.strContents, "��... ��...");
	spDepth1DialogueNode->vecSequenceDialogueInfo.push_back(dialogueInfo);

	ReplaceDialogueContents(dialogueInfo.strContents, "�˼�������, �˷��帱 �� �����ϴ�.");
	spDepth1DialogueNode->vecSequenceDialogueInfo.push_back(dialogueInfo);

	g_spRootDialogueNode->vecNextDialogueNode.push_back(spDepth1DialogueNode);
#pragma endregion	
#pragma endregion	
}

/**
 * ��ȭ ��带 �����մϴ�.
 */
DialogueNodePtr CreateDialogueNode(const std::string_view& strName, const std::string_view& strContents)
{
	DialogueNodePtr spDialogueNode = std::make_shared<DialogueNode>();
	spDialogueNode->selfDialogueInfo.strName = strName;
	spDialogueNode->selfDialogueInfo.strContents = strContents;
	return spDialogueNode;
}

/**
 * ��ȭ�� �����մϴ�.
 * ù ��° ȣ�⿡���� �ݵ�� ��Ʈ ��带 �־��ּ���!
 */
void RunDialogue(const DialogueNodePtr& spDialogueNode)
{
	ShowDialogueInfo(spDialogueNode->selfDialogueInfo);

	// ���� ��� ���� �κ��̿���.
	if (spDialogueNode->vecSequenceDialogueInfo.empty() != true)
	{
		PauseApp();
		
		for (const auto& iter : spDialogueNode->vecSequenceDialogueInfo)
		{
			ShowDialogueInfo(iter);
			PauseApp();
		}

		// ���� ����� ��� ���� ��� ����� �ε����� 0 �����̿���!
		// ���� ��� ��忡 �������� ���� ���� ���� ���� �̵��ؾ� �ؿ�.
		if ( (spDialogueNode->vecNextDialogueNode.empty() != true) &&
			 (spDialogueNode->vecStrTriggerContents.empty() == true) )
		{
			RunDialogue(spDialogueNode->vecNextDialogueNode.at(0));
		}

		// �� �ǹ� ���� ȭ�� ���ſ��̿���.
		ShowDialogueInfo(*(--spDialogueNode->vecSequenceDialogueInfo.end()));
	}
	
	// �б� ��� ���� �κ��̿���.
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

		// ���õ� �ε����� �´� ���� ��� ���� ��� �Լ��� ȣ���ؾ� �ؿ�!
		if (spDialogueNode->vecNextDialogueNode.empty() != true)
		{
			RunDialogue(spDialogueNode->vecNextDialogueNode.at(selectedIdx));
			return;
		}
		else
		{
			printf("�б� ��翡���� ���� ��ȭ ��尡 ������ �־�� �ؿ�!\n");
		}
	}
}

/**
 * ��ȭ�� ���Ḧ �˷��ݴϴ�.
 */
void EndDialogue()
{
	printf("��ȭ�� ����Ǿ����!\n\n");
}

/**
 * ��縦 ����մϴ�.
 */
void ShowDialogueInfo(const DialogueInfo& dialogueInfo)
{
	ClearConsoleScreen();

	EConsoleTextColorType backupConsoleTextColor = QueryCurrentConsoleTextColor();

	// ȭ���� �̸��� ����ؿ�.
	MoveConsolePos(4, 2);
	ChangeConsoleTextColor(EConsoleTextColorType::YELLOW);
	printf("%s", dialogueInfo.strName.c_str());
	
	// ȭ���� ��縦 ����ؿ�.
	MoveConsolePos(6, 4);
	ChangeConsoleTextColor(EConsoleTextColorType::AQUA);
	printf("%s", dialogueInfo.strContents.c_str());

	DrawDialogueEdge();

	// ���� ����ϴ� �������� ���������.
	ChangeConsoleTextColor(backupConsoleTextColor);
}

/**
 * ��� ������ �׸��ϴ�.
 */
void DrawDialogueEdge()
{
	ChangeConsoleTextColor(EConsoleTextColorType::GRAY);
	
	for (Int32 i = 0; i < DIALOG_RANGE_WIDTH; i += 2)
	{
		MoveConsolePos(i, 0);
		printf("��");
	}
	
	for (Int32 i = 1; i < DIALOG_RANGE_HEIGHT; ++i)
	{
		MoveConsolePos(0, i);
		printf("��");

		MoveConsolePos(DIALOG_RANGE_WIDTH - 2, i);
		printf("��");
	}
	
	for (Int32 i = 0; i < DIALOG_RANGE_WIDTH; i += 2)
	{
		MoveConsolePos(i, DIALOG_RANGE_HEIGHT);
		printf("��");
	}

	MoveConsolePos(0, DIALOG_RANGE_HEIGHT + 2);
}

/**
 * ��� ������ �����մϴ�.
 * std::string�� replace()�� ���� ����� �ٿ����.
 */
void ReplaceDialogueContents(_Out_ std::string& destStrContents, const std::string_view& srcStrContents)
{
	destStrContents.replace(destStrContents.cbegin(), destStrContents.cend(), srcStrContents);
}
#pragma endregion
