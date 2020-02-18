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

void InputController::PollInput()
{
	for (auto& iter : m_mapInputMappingInfo)
	{
		if (iter.second == nullptr)
		{
			continue;
		}

		Uint32 inputCnt = 0; // ���ε� �������� ���ϴ� �Է� ������ �������� Ȯ���ؾ� �ؿ�!
		InputMappingInfo* pInputMappingInfo = iter.second;
		CHECK_NULLPTR(pInputMappingInfo);

		// �Է� ����ǥ�� ������ ����!
		if (pInputMappingInfo->vecInput.empty() == true)
		{
			continue;
		}

		TSize size = pInputMappingInfo->vecInput.size();
		for (TSize i = 0; i < size; ++i)
		{
			// �Է� ���� ������� �Ǿ����� Ȯ��!
			if (i != size - 1)
			{
				if (::GetAsyncKeyState(pInputMappingInfo->vecInput[i]) & INPUT_DOWN_FLAG)
				{
					if (IS_BITSET(m_bitsetInputDown, pInputMappingInfo->vecInput[i + 1]) == false)
					{
						DEBUG_LOG_CATEGORY(InputController, "�� ������� �߰�!(%d, %d)", pInputMappingInfo->vecInput[i], i);
						++inputCnt;

						ON_BITSET(m_bitsetInputDown, pInputMappingInfo->vecInput[i]);
					}
					else
					{
						//DEBUG_LOG_CATEGORY(InputController, "�ڿ��� �̹� ����!(%d, %d)", pInputMappingInfo->vecInput[i + 1], i);

						// �̹� �Է� ������ ���� ���¿����� �ǹ̰� ����!
						if ( (IS_BITSET_ENUM(pInputMappingInfo->bitsetInputState, EInputMappingState::DOWN)) ||
							 (IS_BITSET_ENUM(pInputMappingInfo->bitsetInputState, EInputMappingState::PRESSING)) )
						{
							++inputCnt;
							DEBUG_LOG_CATEGORY(InputController,
								"�̹� ������ ������ �����̹Ƿ� �Է°� �߰�!(%d, %d)", pInputMappingInfo->vecInput[i], i);
						}
						// �� ��쿡�� �Է� ������ �̿ϼ��� ������ ���Կ�!
						else
						{
							ON_BITSET_ENUM(pInputMappingInfo->bitsetInputState, EInputMappingState::INCOMPLETION);
						}
					}
				}
			}
			// �������� ���
			else
			{
				if ( (::GetAsyncKeyState(pInputMappingInfo->vecInput[i]) & INPUT_DOWN_FLAG) &&
					 (IS_BITSET(m_bitsetInputDown, pInputMappingInfo->vecInput[i - 1])) )
				{
					DEBUG_LOG_CATEGORY(InputController, "�������� ������� �߰�!(%d, %d)", pInputMappingInfo->vecInput[i], i);
					++inputCnt;

					ON_BITSET(m_bitsetInputDown, pInputMappingInfo->vecInput[i]);
				}
				else
				{
					ON_BITSET_ENUM(pInputMappingInfo->bitsetInputState, EInputMappingState::INCOMPLETION);
				}
			}
		}

		// ���ε� �������� ���ϴ� �Է� ������ ���� ����! (DOWN �ƴϸ� PRESSING)
		if (inputCnt == pInputMappingInfo->vecInput.size())
		{
			// �ش� �Է°��� �����ų� ������ ���°� �ƴ� ��
			if ( (IS_BITSET_ENUM(pInputMappingInfo->bitsetInputState, EInputMappingState::DOWN) == false) &&
				 (IS_BITSET_ENUM(pInputMappingInfo->bitsetInputState, EInputMappingState::PRESSING) == false) )
			{
				ON_BITSET_ENUM(pInputMappingInfo->bitsetInputState, EInputMappingState::DOWN);
				DEBUG_LOG_CATEGORY(InputController, "Ű ������!");
			}
			// �ش� �Է°��� ������ ���¿��� �� ������ �� (������ ���̶�� �ǹ�)
			else if (IS_BITSET_ENUM(pInputMappingInfo->bitsetInputState, EInputMappingState::DOWN))
			{
				OFF_BITSET_ENUM(pInputMappingInfo->bitsetInputState, EInputMappingState::DOWN);
				ON_BITSET_ENUM(pInputMappingInfo->bitsetInputState, EInputMappingState::PRESSING);
				DEBUG_LOG_CATEGORY(InputController, "Ű ��������!");
			}
		}
		// ���ε� �������� ���ϴ� �Է� ������ ������ ���� ����! (NONE �ƴϸ� UP)
		else
		{
			// �ش� �Է°��� ���Ȱų� ������ ���̾��� ��
			if ( (IS_BITSET_ENUM(pInputMappingInfo->bitsetInputState, EInputMappingState::DOWN)) ||
				 (IS_BITSET_ENUM(pInputMappingInfo->bitsetInputState, EInputMappingState::PRESSING)) )
			{
				OFF_BITSET_ENUM(pInputMappingInfo->bitsetInputState, EInputMappingState::DOWN);
				OFF_BITSET_ENUM(pInputMappingInfo->bitsetInputState, EInputMappingState::PRESSING);
				ON_BITSET_ENUM(pInputMappingInfo->bitsetInputState, EInputMappingState::UP);
				DEBUG_LOG_CATEGORY(InputController, "Ű�� ������ �ش�Ǵ� �Է� ���� ���� ��ȿ!");

				// Ű�� �ôٴ� �� �߸��� �����̾ ��ȿ!
				for (auto& iter : pInputMappingInfo->vecInput)
				{
					OFF_BITSET(m_bitsetInputDown, iter);
				}
			}
			// �ش� �Է°��� ������ ���� ���¿��� �� ������ �ʾ��� �� (������ �ʰ� �ִٴ� �ǹ�)
			else if (IS_BITSET_ENUM(pInputMappingInfo->bitsetInputState, EInputMappingState::UP))
			{
				OFF_BITSET_ENUM(pInputMappingInfo->bitsetInputState, EInputMappingState::UP);
				ON_BITSET_ENUM(pInputMappingInfo->bitsetInputState, EInputMappingState::NONE);
				DEBUG_LOG_CATEGORY(InputController, "Ű ���� �ִ�!");
			}
			// �Ϻθ� ���յǾ��ų� �ƿ� ���յ��� �ʾ��� ��
			else if (IS_BITSET_ENUM(pInputMappingInfo->bitsetInputState, EInputMappingState::INCOMPLETION))
			{
				Uint32 inputUpCnt = 0;

				for (auto& iter : pInputMappingInfo->vecInput)
				{
					if (IS_INPUT_UP(iter))
					{
						++inputUpCnt;
						OFF_BITSET(m_bitsetInputDown, iter);
						DEBUG_LOG_CATEGORY(InputController, "��Ʈ false��! (%d)", iter);
					}
				}

				if (inputUpCnt == pInputMappingInfo->vecInput.size())
				{
					OFF_BITSET_ENUM(pInputMappingInfo->bitsetInputState, EInputMappingState::INCOMPLETION);
					DEBUG_LOG_CATEGORY(InputController, "�߸��� �Է� ���� �ʱ�ȭ!");
				}
			}
		}
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
	return (IS_BITSET_ENUM(pInputMappingInfo->bitsetInputState, inputState));
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