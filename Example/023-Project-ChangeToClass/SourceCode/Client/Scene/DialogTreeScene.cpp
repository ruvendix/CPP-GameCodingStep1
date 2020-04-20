// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// �� ���۹��� ũ������Ƽ�� Ŀ���� ������ǥ�� 4.0 ���� ���̼����� ���� �̿��� �� �ֽ��ϴ�.
// http://creativecommons.org/licenses/by/4.0/
//
// ��ȭ Ʈ�� ���Դϴ�.
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
	static InputForDialogNodeCallback m_inputForDialogNodeCallback; // ���� ����
};

InputForDialogNodeCallback DialogTreeSceneHelper::m_inputForDialogNodeCallback = OnCallback_InputForDialogNode;

void DialogTreeSceneHelper::InitDialogTree(_Out_ std::unique_ptr<DialogTree>& spDialogTree)
{
	std::shared_ptr<TriggerDialogNode> spRootNode = spDialogTree->CreateNode<TriggerDialogNode>("���� ���", "�ȳ��ϼ���, �츮 ������ ���� �� ȯ���մϴ�!");
	spDialogTree->setRootNode(spRootNode);

#pragma region N0
	std::shared_ptr<DialogNode> spLinkNode_N0 = spDialogTree->CreateNode<DialogNode>("�÷��̾�", "������ ������!");
	spRootNode->AddTrigger("�����Ⱑ ���δ�.", spLinkNode_N0);

	spLinkNode_N0 = spDialogTree->LinkNewNextNode<DialogNode>(spLinkNode_N0, "���� ���", "������ ������� �� �� ���� �����.");
#pragma endregion

#pragma region N1
	std::shared_ptr<DialogNode> spLinkNode_N1 = spDialogTree->CreateNode<DialogNode>("�÷��̾�", "�ȳ��ϼ���, ���� �Ұ� �� ���ּ���.");
	spRootNode->AddTrigger("���� �Ұ��� ��Ź�Ѵ�.", spLinkNode_N1);

	spLinkNode_N1 = spDialogTree->LinkNewNextNode<DialogNode>(spLinkNode_N1, "���� ���", "���� �Ұ� ���̱���, �˰ڽ��ϴ�!");
	spLinkNode_N1 = spDialogTree->LinkNewNextNode<DialogNode>(spLinkNode_N1, "���� ���", "�츮 ������ ������ ��� ���� ���̿���.");
	spLinkNode_N1 = spDialogTree->LinkNewNextNode<DialogNode>(spLinkNode_N1, "���� ���", "���� ����� �νɵ� ����, ��ǵ� ���� �Ͼ�� ����!");

	std::shared_ptr<TriggerDialogNode> spLinkTriggerNode_N1 =
		spDialogTree->LinkNewNextNode<TriggerDialogNode>(spLinkNode_N1, "���� ���", "�׷���... ��... (���� �ӹ��Ÿ���)");
#pragma endregion

#pragma region N2
	std::shared_ptr<DialogNode> spLinkNode_N2 = spDialogTree->CreateNode<DialogNode>("�÷��̾�", "�Ƿ�����, ���̴� ��� �ǽó���?");
	spRootNode->AddTrigger("���̸� ���´�.", spLinkNode_N2);

	spLinkNode_N2 = spDialogTree->LinkNewNextNode<DialogNode>(spLinkNode_N2, "���� ���", "�� ���̿�...?");
	spLinkNode_N2 = spDialogTree->LinkNewNextNode<DialogNode>(spLinkNode_N2, "���� ���", "��... ��...");
	spLinkNode_N2 = spDialogTree->LinkNewNextNode<DialogNode>(spLinkNode_N2, "���� ���", "�˼�������, �˷��帱 �� �����ϴ�.");
#pragma endregion

#pragma region N1->N0
	std::shared_ptr<DialogNode> spLinkNode_N1_N0 = spDialogTree->CreateNode<DialogNode>("�÷��̾�", "�׷�����, �׷� �� �̸�...");
	spLinkTriggerNode_N1->AddTrigger("�����ϰ� ������.", spLinkNode_N1_N0);
#pragma endregion

#pragma region N1->N1
	std::shared_ptr<DialogNode> spLinkNode_N1_N1 = spDialogTree->CreateNode<DialogNode>("�÷��̾�", "���� ���̶� �ֳ���?");
	spLinkTriggerNode_N1->AddTrigger("���� ������ �����.", spLinkNode_N1_N1);

	spLinkNode_N1_N1 = spDialogTree->LinkNewNextNode<DialogNode>(spLinkNode_N1_N1, "���� ���", "���� �㸸 �Ǹ� ���� �Ű� ������...");
	spLinkNode_N1_N1 = spDialogTree->LinkNewNextNode<DialogNode>(spLinkNode_N1_N1, "���� ���", "�ν÷���� �Ҹ��� �鸰�ٰ� �ϰ�...");
	spLinkNode_N1_N1 = spDialogTree->LinkNewNextNode<DialogNode>(spLinkNode_N1_N1, "���� ���", "���� ���� �ôٴ� ����� �־��...");

	std::shared_ptr<TriggerDialogNode> spLinkTriggerNode_N1_N1 =
		spDialogTree->LinkNewNextNode<TriggerDialogNode>(spLinkNode_N1_N1, "���� ���", "������ ���ذ� ������, �ٵ� �Ű��� ���̳� ����...");
#pragma endregion

#pragma region N1->N1->N0
	spLinkTriggerNode_N1_N1->AddTrigger("�����ϰ� ������.", spLinkNode_N1_N0);
#pragma endregion

#pragma region N1->N1->N1
	std::shared_ptr<DialogNode> spLinkNode_N1_N1_N1 = spDialogTree->CreateNode<DialogNode>("�÷��̾�", "���� ������ ���� �˾ƺ��Կ�.");
	spLinkTriggerNode_N1_N1->AddTrigger("�����غ��ٰ� �Ѵ�.", spLinkNode_N1_N1_N1);

	spLinkNode_N1_N1_N1 = spDialogTree->LinkNewNextNode<DialogNode>(spLinkNode_N1_N1_N1, "���� ���", "��...! �����մϴ�, ��ħ ������ �ʿ��߾��!");
	spLinkNode_N1_N1_N1 = spDialogTree->LinkNewNextNode<DialogNode>(spLinkNode_N1_N1_N1, "���� ���", "���� ����Բ� �ȳ��ص帮�ڽ��ϴ�!");
#pragma endregion
}

void DialogTreeSceneHelper::DrawDialogBox()
{
	EConsoleOutputColorType currentConsoleOutputColor = ConsoleController::I()->QueryCurrentConsoleOutputColor(EConsoleOutputType::TEXT);
	ConsoleController::I()->ChangeConsoleOutputColor(EConsoleOutputType::TEXT, EConsoleOutputColorType::GRAY);

	for (Int32 i = 0; i < DIALOG_BOX_WIDTH; i += 2)
	{
		PUT_STRING(i, 0, "��");
		PUT_STRING(i, DIALOG_BOX_HEIGHT, "��");
	}

	for (Int32 i = 1; i < DIALOG_BOX_HEIGHT; ++i)
	{
		PUT_STRING(0, i, "��");
		PUT_STRING(DIALOG_BOX_WIDTH - 2, i, "��");
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
		DEBUG_LOG("SelectUp ������!");
	}

	if (InputController::I()->CheckInputState("SelectDown", EInputMappingState::DOWN) == true)
	{
		ConsoleController::I()->AddSelectorPosY(+1);
		targetHelper.m_localTime = 0.0f;
		DEBUG_LOG("SelectDown ������!");
	}

	BEGIN_INPUT_FPS_LIMITED_HELPER(targetHelper);
	if (InputController::I()->CheckInputState("SelectUp", EInputMappingState::PRESSING) == true)
	{
		ConsoleController::I()->AddSelectorPosY(-1);
		DEBUG_LOG("SelectUp ������ ��!");
	}

	if (InputController::I()->CheckInputState("SelectDown", EInputMappingState::PRESSING) == true)
	{
		ConsoleController::I()->AddSelectorPosY(+1);
		DEBUG_LOG("SelectDown ������ ��!");
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

		DEBUG_LOG("Enter ����!");
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