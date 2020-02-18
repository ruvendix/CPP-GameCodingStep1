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

DEFINE_LOG_CATEGORY(InputController);
DEFINE_SINGLETON(InputController);

namespace
{
	template <typename TContainer>
	bool IsOverlapVal(const TContainer& container, const typename TContainer::value_type& val)
	{
		for (const auto& iter : container)
		{
			if (iter == val)
			{
				return true;
			}
		}

		return false;
	}
}

void InputController::PollInput()
{
	for (auto& iter : m_mapInputMappingInfo)
	{
		if (iter.second == nullptr)
		{
			continue;
		}

		//Uint32 inputCnt = 0; // ���ε� �������� ���ϴ� �Է� ������ �������� Ȯ���ؾ� �ؿ�!
		InputMappingInfo* pInputMappingInfo = iter.second;
		CHECK_NULLPTR(pInputMappingInfo);

		// �Է� ����ǥ�� ������ ����!
		if (pInputMappingInfo->vecInput.empty() == true)
		{
			continue;
		}

		TSize size = pInputMappingInfo->vecInput.size();
		const std::vector<TInput>& vecInput = pInputMappingInfo->vecInput;
		std::list<TInput>& listInputChecker = pInputMappingInfo->listInputChecker;

		for (TSize i = 0; i < size; ++i)
		{
			TInput inputVal = vecInput[i];

			// ����Ʈ�� ���� ���� �־�� ��!
			if (IsOverlapVal(listInputChecker, inputVal) == false)
			{
				// ����Ʈ�� ���� �������� �Է°� �߰�!
				if (::GetAsyncKeyState(inputVal) & INPUT_DOWN_FLAG)
				{
					listInputChecker.push_back(inputVal);
					DEBUG_LOG_CATEGORY(InputController, "�� �߰�! (%d)", inputVal);
				}
			}
			// �̹� ����Ʈ�� �ִ� ���̸�? ������ ���� �����ִ��� Ȯ��!
			else
			{
				if (IS_INPUT_DOWN(inputVal))
				{
					DEBUG_LOG_CATEGORY(InputController, "�̹� ������ �ִ� ��! (%d)", inputVal);
				}
				else
				{
					listInputChecker.pop_back();
					DEBUG_LOG_CATEGORY(InputController, "������ �ִ� ���� ��! (%d)", inputVal);
				}
			}
		}

		EInputMappingState inputMappingState = pInputMappingInfo->state;

		// ���ε� �������� ���ϴ� �Է� ������ ���� ����! (DOWN �ƴϸ� PRESSING)
		//if (inputCnt == pInputMappingInfo->vecInput.size())
		if (std::equal(vecInput.cbegin(), vecInput.cend(), listInputChecker.cbegin(), listInputChecker.cend()) == true)
		{
			DEBUG_LOG_CATEGORY(InputController, "�Է� ������ �����ߴ�!");

			// �ش� �Է°��� �����ų� ������ ���°� �ƴ� ��
			if ( (inputMappingState != EInputMappingState::DOWN) &&
				 (inputMappingState != EInputMappingState::PRESSING) )
			{
				inputMappingState = EInputMappingState::DOWN;
				DEBUG_LOG_CATEGORY(InputController, "�Է� ������ ���ʷ� ������!");
			}
			// �ش� �Է°��� ������ ���¿��� �� ������ �� (������ ���̶�� �ǹ�)
			else if (inputMappingState == EInputMappingState::DOWN)
			{
				inputMappingState = EInputMappingState::PRESSING;
				DEBUG_LOG_CATEGORY(InputController, "�Է� ������ ��� ��������!");
			}
		}
		// ���ε� �������� ���ϴ� �Է� ������ ������ ���� ����! (NONE �ƴϸ� UP)
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
				inputMappingState = EInputMappingState::NONE;
				DEBUG_LOG_CATEGORY(InputController, "�Է� ������ ��� ������ �ʰ� ����!");
			}
		}

		// �Է� ���� ���� ����
		pInputMappingInfo->state = inputMappingState;
	}
}

void InputController::DeleteAllInputMappingInfo()
{
	for (auto& iter : m_mapInputMappingInfo)
	{
		SAFE_DELETE(iter.second);
	}
}

bool InputController::CheckInputState(const std::string_view& szInputAction, EInputMappingState inputState) const
{
	InputMappingInfo* pInputMappingInfo = FindInputMappingInfo(szInputAction);
	CHECK_NULLPTR(pInputMappingInfo);
	return (pInputMappingInfo->state == inputState);
}

InputMappingInfo* InputController::FindInputMappingInfo(const std::string_view& szInputAction) const
{
	const auto& iter = m_mapInputMappingInfo.find(szInputAction.data());
	if ( (iter == m_mapInputMappingInfo.cend()) ||
		 (iter->second == nullptr) )
	{
		DEBUG_LOG_CATEGORY(InputController, "%s �׼��� �����!", szInputAction.data());
		return nullptr;
	}

	return iter->second;
}