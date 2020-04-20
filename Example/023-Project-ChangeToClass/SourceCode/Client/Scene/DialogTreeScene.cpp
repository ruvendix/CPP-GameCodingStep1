// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// 이 저작물은 크리에이티브 커먼즈 저작자표시 4.0 국제 라이선스에 따라 이용할 수 있습니다.
// http://creativecommons.org/licenses/by/4.0/
//
// 대화 트리 씬입니다.
// =====================================================================================

#include "PCH.h"
#include "DialogTreeScene.h"

#include "Controller\ConsoleController.h"
#include "Controller\InputController.h"
#include "Controller\FrameController.h"
#include "Manager\SceneManager.h"
#include "IntroMenuScene.h"
#include "MiniGame\DialogTree\DialogConstant.h"
#include "MiniGame\DialogTree\TriggerDialogNode.h"

using InputForDialogNodeCallback = std::function<void(_Inout_ DialogTreeScene&)>;

class DialogTreeSceneHelper final
{
	NON_COPYABLE_ONLY_PRIVATE_CLASS(DialogTreeSceneHelper);

public:
	static void InitDialogTree(_Out_ std::unique_ptr<DialogTree>& spDialogTree);
	static void DrawDialogBox();
	static void AdjustSelectorPosForTriggerDialogNode(std::shared_ptr<DialogNode> spDialogNode);

	static bool IsTriggerDialogNode(std::shared_ptr<DialogNode> spDialogNode);
	
	static void ChangeCallback(const InputForDialogNodeCallback& inputForDialogNodeCallback);
	static void RunCallback(_Inout_ DialogTreeScene& targetHelper);
	static void OnCallback_InputForDialogNode(_Inout_ DialogTreeScene& targetHelper);
	static void OnCallback_InputForTriggerDialogNode(_Inout_ DialogTreeScene& targetHelper);

private:
	static InputForDialogNodeCallback m_inputForDialogNodeCallback; // 전략 패턴
};

InputForDialogNodeCallback DialogTreeSceneHelper::m_inputForDialogNodeCallback = OnCallback_InputForDialogNode;

void DialogTreeSceneHelper::InitDialogTree(_Out_ std::unique_ptr<DialogTree>& spDialogTree)
{
	std::shared_ptr<TriggerDialogNode> spRootNode = spDialogTree->CreateNode<TriggerDialogNode>("마을 사람", "안녕하세요, 우리 마을에 오신 걸 환영합니다!");
	spDialogTree->setRootNode(spRootNode);

#pragma region N0
	std::shared_ptr<DialogNode> spLinkNode_N0 = spDialogTree->CreateNode<DialogNode>("플레이어", "마을이 후졌네!");
	spRootNode->AddTrigger("분위기가 별로다.", spLinkNode_N0);

	spLinkNode_N0 = spDialogTree->LinkNewNextNode<DialogNode>(spLinkNode_N0, "마을 사람", "무례한 사람에게 더 할 말은 없어요.");
#pragma endregion

#pragma region N1
	std::shared_ptr<DialogNode> spLinkNode_N1 = spDialogTree->CreateNode<DialogNode>("플레이어", "안녕하세요, 마을 소개 좀 해주세요.");
	spRootNode->AddTrigger("마을 소개를 부탁한다.", spLinkNode_N1);

	spLinkNode_N1 = spDialogTree->LinkNewNextNode<DialogNode>(spLinkNode_N1, "마을 사람", "마을 소개 말이군요, 알겠습니다!");
	spLinkNode_N1 = spDialogTree->LinkNewNextNode<DialogNode>(spLinkNode_N1, "마을 사람", "우리 마을은 작지만 살기 좋은 곳이에요.");
	spLinkNode_N1 = spDialogTree->LinkNewNextNode<DialogNode>(spLinkNode_N1, "마을 사람", "마을 사람들 인심도 좋고, 사건도 거의 일어나지 않죠!");

	std::shared_ptr<TriggerDialogNode> spLinkTriggerNode_N1 =
		spDialogTree->LinkNewNextNode<TriggerDialogNode>(spLinkNode_N1, "마을 사람", "그런데... 음... (말을 머뭇거린다)");
#pragma endregion

#pragma region N2
	std::shared_ptr<DialogNode> spLinkNode_N2 = spDialogTree->CreateNode<DialogNode>("플레이어", "실례지만, 나이는 어떻게 되시나요?");
	spRootNode->AddTrigger("나이를 묻는다.", spLinkNode_N2);

	spLinkNode_N2 = spDialogTree->LinkNewNextNode<DialogNode>(spLinkNode_N2, "마을 사람", "제 나이요...?");
	spLinkNode_N2 = spDialogTree->LinkNewNextNode<DialogNode>(spLinkNode_N2, "마을 사람", "어... 음...");
	spLinkNode_N2 = spDialogTree->LinkNewNextNode<DialogNode>(spLinkNode_N2, "마을 사람", "죄송하지만, 알려드릴 수 없습니다.");
#pragma endregion

#pragma region N1->N0
	std::shared_ptr<DialogNode> spLinkNode_N1_N0 = spDialogTree->CreateNode<DialogNode>("플레이어", "그렇군요, 그럼 전 이만...");
	spLinkTriggerNode_N1->AddTrigger("무시하고 떠난다.", spLinkNode_N1_N0);
#pragma endregion

#pragma region N1->N1
	std::shared_ptr<DialogNode> spLinkNode_N1_N1 = spDialogTree->CreateNode<DialogNode>("플레이어", "무슨 일이라도 있나요?");
	spLinkTriggerNode_N1->AddTrigger("무슨 일인지 물어본다.", spLinkNode_N1_N1);

	spLinkNode_N1_N1 = spDialogTree->LinkNewNextNode<DialogNode>(spLinkNode_N1_N1, "마을 사람", "요즘 밤만 되면 밭이 신경 쓰여요...");
	spLinkNode_N1_N1 = spDialogTree->LinkNewNextNode<DialogNode>(spLinkNode_N1_N1, "마을 사람", "부시럭대는 소리가 들린다고도 하고...");
	spLinkNode_N1_N1 = spDialogTree->LinkNewNextNode<DialogNode>(spLinkNode_N1_N1, "마을 사람", "빨간 눈을 봤다는 사람도 있어요...");

	std::shared_ptr<TriggerDialogNode> spLinkTriggerNode_N1_N1 =
		spDialogTree->LinkNewNextNode<TriggerDialogNode>(spLinkNode_N1_N1, "마을 사람", "아직은 피해가 없지만, 다들 신경이 쓰이나 봐요...");
#pragma endregion

#pragma region N1->N1->N0
	spLinkTriggerNode_N1_N1->AddTrigger("무시하고 떠난다.", spLinkNode_N1_N0);
#pragma endregion

#pragma region N1->N1->N1
	std::shared_ptr<DialogNode> spLinkNode_N1_N1_N1 = spDialogTree->CreateNode<DialogNode>("플레이어", "무슨 일인지 제가 알아볼게요.");
	spLinkTriggerNode_N1_N1->AddTrigger("조사해본다고 한다.", spLinkNode_N1_N1_N1);

	spLinkNode_N1_N1_N1 = spDialogTree->LinkNewNextNode<DialogNode>(spLinkNode_N1_N1_N1, "마을 사람", "앗...! 감사합니다, 마침 도움이 필요했어요!");
	spLinkNode_N1_N1_N1 = spDialogTree->LinkNewNextNode<DialogNode>(spLinkNode_N1_N1_N1, "마을 사람", "제가 촌장님께 안내해드리겠습니다!");
#pragma endregion
}

void DialogTreeSceneHelper::DrawDialogBox()
{
	EConsoleOutputColorType currentConsoleOutputColor = ConsoleController::I()->QueryCurrentConsoleOutputColor(EConsoleOutputType::TEXT);
	ConsoleController::I()->ChangeConsoleOutputColor(EConsoleOutputType::TEXT, EConsoleOutputColorType::GRAY);

	for (Int32 i = 0; i < DIALOG_BOX_WIDTH; i += 2)
	{
		PUT_STRING(i, 0, "■");
		PUT_STRING(i, DIALOG_BOX_HEIGHT, "■");
	}

	for (Int32 i = 1; i < DIALOG_BOX_HEIGHT; ++i)
	{
		PUT_STRING(0, i, "■");
		PUT_STRING(DIALOG_BOX_WIDTH - 2, i, "■");
	}

	ConsoleController::I()->ChangeConsoleOutputColor(EConsoleOutputType::TEXT, currentConsoleOutputColor);
}

void DialogTreeSceneHelper::AdjustSelectorPosForTriggerDialogNode(std::shared_ptr<DialogNode> spDialogNode)
{
	ConsoleSelector& consoleSelector = ConsoleController::I()->getCurrentConsoleSelector();
	Int32 startPosY = DIALOG_BOX_HEIGHT + 2;
	consoleSelector.setSelectorPos(0, startPosY);
	consoleSelector.setMinSelectorPosY(startPosY);

	std::shared_ptr<TriggerDialogNode> spTriggerDialogNode = std::dynamic_pointer_cast<TriggerDialogNode>(spDialogNode);
	consoleSelector.setMaxSelectorPosY(startPosY + spTriggerDialogNode->getTriggerCnt() - 1);
}

bool DialogTreeSceneHelper::IsTriggerDialogNode(std::shared_ptr<DialogNode> spDialogNode)
{
	if (dynamic_cast<TriggerDialogNode*>(&(*spDialogNode)) != nullptr)
	{
		return true;
	}

	return false;
}

void DialogTreeSceneHelper::ChangeCallback(const InputForDialogNodeCallback& inputForDialogNodeCallback)
{
	m_inputForDialogNodeCallback = inputForDialogNodeCallback;
}

void DialogTreeSceneHelper::RunCallback(_Inout_ DialogTreeScene& targetHelper)
{
	m_inputForDialogNodeCallback(targetHelper);
}

void DialogTreeSceneHelper::OnCallback_InputForDialogNode(_Inout_ DialogTreeScene& targetHelper)
{

}

void DialogTreeSceneHelper::OnCallback_InputForTriggerDialogNode(_Inout_ DialogTreeScene& targetHelper)
{
	if (InputController::I()->CheckInputState("SelectUp", EInputMappingState::DOWN) == true)
	{
		ConsoleController::I()->AddSelectorPosY(-1);
		targetHelper.m_localTime = 0.0f;
		DEBUG_LOG("SelectUp 눌렀다!");
	}

	if (InputController::I()->CheckInputState("SelectDown", EInputMappingState::DOWN) == true)
	{
		ConsoleController::I()->AddSelectorPosY(+1);
		targetHelper.m_localTime = 0.0f;
		DEBUG_LOG("SelectDown 눌렀다!");
	}

	BEGIN_INPUT_FPS_LIMITED_HELPER(targetHelper);
	if (InputController::I()->CheckInputState("SelectUp", EInputMappingState::PRESSING) == true)
	{
		ConsoleController::I()->AddSelectorPosY(-1);
		DEBUG_LOG("SelectUp 누르는 중!");
	}

	if (InputController::I()->CheckInputState("SelectDown", EInputMappingState::PRESSING) == true)
	{
		ConsoleController::I()->AddSelectorPosY(+1);
		DEBUG_LOG("SelectDown 누르는 중!");
	}
	END_INPUT_FPS_LIMITED();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////

DEFINE_LOG_CATEGORY(DialogTreeScene);

EErrorType DialogTreeScene::OnInitialize()
{
	InputController::I()->InsertInputMappingInfo("GotoIntro", VK_ESCAPE);
	InputController::I()->InsertInputMappingInfo("SelectUp", VK_UP);
	InputController::I()->InsertInputMappingInfo("SelectDown", VK_DOWN);
	InputController::I()->InsertInputMappingInfo("Enter", VK_RETURN);

	m_spDialogTree = std::make_unique<DialogTree>();
	DialogTreeSceneHelper::InitDialogTree(m_spDialogTree);

	m_spCurrentDialogNode = m_spDialogTree->getRootNode();
	if (DialogTreeSceneHelper::IsTriggerDialogNode(m_spCurrentDialogNode))
	{
		DialogTreeSceneHelper::ChangeCallback(&DialogTreeSceneHelper::OnCallback_InputForTriggerDialogNode);
	}

	return EErrorType::NOTHING;
}

EErrorType DialogTreeScene::OnPostInitialize()
{
	if (DialogTreeSceneHelper::IsTriggerDialogNode(m_spCurrentDialogNode) == false)
	{
		return EErrorType::NOTHING;
	}

	DialogTreeSceneHelper::AdjustSelectorPosForTriggerDialogNode(m_spCurrentDialogNode);
	return EErrorType::NOTHING;
}

EErrorType DialogTreeScene::OnInput()
{
	if (m_spCurrentDialogNode == nullptr)
	{
		return EErrorType::NOTHING;
	}

	if (Scene::OnInput() == EErrorType::FIRST_INPUT)
	{
		return EErrorType::FIRST_INPUT;
	}

	if (InputController::I()->CheckInputState("GotoIntro", EInputMappingState::DOWN) == true)
	{
		SceneMgr::I()->CreateScene<IntroMenuScene>(ECreateType::NEXT);
	}

	if (InputController::I()->CheckInputState("Enter", EInputMappingState::DOWN) == true)
	{
		std::shared_ptr<DialogNode> spNextNode = m_spCurrentDialogNode->FindNextNode();
		if (spNextNode != nullptr)
		{
			m_spCurrentDialogNode = spNextNode;
		}
		else
		{
			SceneMgr::I()->CreateScene<IntroMenuScene>(ECreateType::NEXT);
		}

		if (DialogTreeSceneHelper::IsTriggerDialogNode(m_spCurrentDialogNode))
		{
			DialogTreeSceneHelper::AdjustSelectorPosForTriggerDialogNode(m_spCurrentDialogNode);
			DialogTreeSceneHelper::ChangeCallback(&DialogTreeSceneHelper::OnCallback_InputForTriggerDialogNode);
		}

		DEBUG_LOG("Enter 누름!");
	}

	DialogTreeSceneHelper::RunCallback(*this);

	return EErrorType::NOTHING;
}

EErrorType DialogTreeScene::OnRender()
{
	m_spCurrentDialogNode->Draw(0, 0);
	DialogTreeSceneHelper::DrawDialogBox();

	return EErrorType::NOTHING;
}