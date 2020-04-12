// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// �� ���۹��� ũ������Ƽ�� Ŀ���� ������ǥ�� 4.0 ���� ���̼����� ���� �̿��� �� �ֽ��ϴ�.
// http://creativecommons.org/licenses/by/4.0/
//
// Ű����� ���콺 �Է��� �����մϴ�.
// ��ŸŸ�Ӹ��� �����ϹǷ� ���ڿ� �� ��� ���������� �����մϴ�.
// =====================================================================================

#include "PCH.h"
#include "InputController.h"

#include "FrameController.h"

DEFINE_LOG_CATEGORY(InputController);
DEFINE_PHOENIX_SINGLETON(InputController);

/*
�Է� ���� ������ ������� �Է� ���¸� ��� Ȯ���ϸ� �����մϴ�.
*/
void InputController::PollInput()
{
	for (auto& iter : m_mapInputMappingInfo)
	{
		InputMappingInfo* pInputMappingInfo = iter.second;
		CHECK_NULLPTR_CONTINUE(pInputMappingInfo);

		// �Է� ����ǥ�� ������ ����!
		if (pInputMappingInfo->vecInputTable.empty() == true)
		{
			continue;
		}
		
		const std::vector<TInput>& vecInputTable = pInputMappingInfo->vecInputTable;
		std::list<TInput>& listInputChecker = pInputMappingInfo->listInputChecker;
		
		TSize size = pInputMappingInfo->vecInputTable.size();
		for (TSize i = 0; i < size; ++i)
		{
			TInput inputValue = vecInputTable[i];

			// ����Ʈ�� ���� ���� �־�� ��!
			if (common_func::IsOverlapValue(listInputChecker, inputValue) == false)
			{
				// ����Ʈ�� ���� �������� �Է°� �߰�!
				if (::GetAsyncKeyState(inputValue) & INPUT_DOWN_FLAG)
				{
					listInputChecker.push_back(inputValue);
					DEBUG_LOG_CATEGORY(InputController, "�� �߰�! (%d) (%s)", inputValue, iter.first.c_str());
				}
			}
			// �̹� ����Ʈ�� �ִ� ���̸�? ������ ���� �����ִ��� Ȯ��!
			else
			{
				if (IS_INPUT_DOWN(inputValue))
				{
					DEBUG_LOG_CATEGORY(InputController, "�̹� ������ �ִ� ��! (%d) (%s)", inputValue, iter.first.c_str());
				}
				else
				{
					listInputChecker.pop_back();
					DEBUG_LOG_CATEGORY(InputController, "������ �ִ� ���� ��! (%d) (%s)", inputValue, iter.first.c_str());
				}
			}
		}

		EInputMappingState inputMappingState = pInputMappingInfo->state;

		// ���ε� ������ �����ϴ� ����! (DOWN �ƴϸ� PRESSING)
		if (std::equal(vecInputTable.cbegin(), vecInputTable.cend(), listInputChecker.cbegin(), listInputChecker.cend()) == true)
		{
			//DEBUG_LOG_CATEGORY(InputController, "�Է� ������ �����ߴ�!");

			// �ش� �Է°��� �����ų� ������ ���°� �ƴ� ��
			if ( (inputMappingState != EInputMappingState::DOWN) &&
				 (inputMappingState != EInputMappingState::PRESSING) )
			{
				inputMappingState = EInputMappingState::DOWN;
				DEBUG_LOG_CATEGORY(InputController, "�Է� ������ ���ʷ� �����ߴ�!");
			}
			// �ش� �Է°��� ������ ���¿��� �� ������ �� (������ ���̶�� �ǹ�)
			else if (inputMappingState == EInputMappingState::DOWN)
			{
				inputMappingState = EInputMappingState::PRESSING;
				DEBUG_LOG_CATEGORY(InputController, "�Է� ������ ������!");
			}
		}
		// ���ε� ������ �������� ���� ����! (IDLE �ƴϸ� UP)
		else
		{
			//DEBUG_LOG_CATEGORY(InputController, "�Է� ������ �������� ����!");

			// �ش� �Է°��� ���Ȱų� ������ ���̾��� ��
			if ( (inputMappingState == EInputMappingState::DOWN) || 
				 (inputMappingState == EInputMappingState::PRESSING) )
			{
				inputMappingState = EInputMappingState::UP;
				DEBUG_LOG_CATEGORY(InputController, "������ �Է� ������ �������� ����!");				
			}
			// �ش� �Է°��� ������ ���� ���¿��� �� ������ �ʾ��� �� (������ �ʰ� �ִٴ� �ǹ�)
			else if (inputMappingState == EInputMappingState::UP)
			{
				inputMappingState = EInputMappingState::IDLE;
				DEBUG_LOG_CATEGORY(InputController, "�Է� ������ ��� �������� ����!");
			}
		}

		// �Է� ���� ���� ����
		pInputMappingInfo->state = inputMappingState;
	}
}

/*
��� �Է� ���� ������ �����մϴ�.
*/
void InputController::Finalize()
{
	for (auto& iter : m_mapInputMappingInfo)
	{
		SAFE_DELETE(iter.second);
	}
}

/*
���ε� �Է� ������ �����մϴ�.
*/
void InputController::DeleteInputMappingInfo(const std::string& strInputMappingName)
{
	m_mapInputMappingInfo.erase(strInputMappingName);
}

void InputController::ResetInputState()
{
	for (auto& iter : m_mapInputMappingInfo)
	{
		CHECK_NULLPTR_CONTINUE(iter.second);
		iter.second->state = EInputMappingState::IDLE;
	}
}

/*
���ϴ� �Է� ���� �̸��� �ش�Ǵ� ���¸� �˷��ݴϴ�.
*/
bool InputController::CheckInputState(const std::string_view& szInputMappingName, EInputMappingState inputState) const
{
	InputMappingInfo* pInputMappingInfo = FindInputMappingInfo(szInputMappingName);
	CHECK_NULLPTR(pInputMappingInfo);
	return (pInputMappingInfo->state == inputState);
}

/*
���ϴ� �Է� ���� �̸��� �ش�Ǵ� ������ �˷��ݴϴ�.
*/
InputMappingInfo* InputController::FindInputMappingInfo(const std::string_view& szInputMappingName) const
{
	const auto& iter = m_mapInputMappingInfo.find(szInputMappingName.data());
	if ( (iter == m_mapInputMappingInfo.cend()) ||
		 (iter->second == nullptr) )
	{
		//DEFAULT_ERROR_HANDLER(EErrorType::NO_INPUT_MAPPING_INFO, szInputMappingName);
		return nullptr;
	}

	return iter->second;
}