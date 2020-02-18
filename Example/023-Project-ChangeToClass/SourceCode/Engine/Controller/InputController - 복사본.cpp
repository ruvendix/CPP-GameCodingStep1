// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// 이 저작물은 크리에이티브 커먼즈 저작자표시 4.0 국제 라이선스에 따라 이용할 수 있습니다.
// http://creativecommons.org/licenses/by/4.0/
//
// 키보드와 마우스 입력을 제어합니다.
// 델타타임마다 폴링하므로 문자열 비교 대신 열거형으로 고정합니다.
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

		Uint32 inputCnt = 0; // 매핑된 정보에서 원하는 입력 조합을 눌렀는지 확인해야 해요!
		InputMappingInfo* pInputMappingInfo = iter.second;
		CHECK_NULLPTR(pInputMappingInfo);

		// 입력 조합표가 없으면 무시!
		if (pInputMappingInfo->vecInput.empty() == true)
		{
			continue;
		}

		TSize size = pInputMappingInfo->vecInput.size();
		for (TSize i = 0; i < size; ++i)
		{
			// 입력 조합 순서대로 되었는지 확인!
			if (i != size - 1)
			{
				if (::GetAsyncKeyState(pInputMappingInfo->vecInput[i]) & INPUT_DOWN_FLAG)
				{
					if (IS_BITSET(m_bitsetInputDown, pInputMappingInfo->vecInput[i + 1]) == false)
					{
						DEBUG_LOG_CATEGORY(InputController, "값 순서대로 추가!(%d, %d)", pInputMappingInfo->vecInput[i], i);
						++inputCnt;

						ON_BITSET(m_bitsetInputDown, pInputMappingInfo->vecInput[i]);
					}
					else
					{
						//DEBUG_LOG_CATEGORY(InputController, "뒤에값 이미 누름!(%d, %d)", pInputMappingInfo->vecInput[i + 1], i);

						// 이미 입력 조합을 누른 상태에서는 의미가 없음!
						if ( (IS_BITSET_ENUM(pInputMappingInfo->bitsetInputState, EInputMappingState::DOWN)) ||
							 (IS_BITSET_ENUM(pInputMappingInfo->bitsetInputState, EInputMappingState::PRESSING)) )
						{
							++inputCnt;
							DEBUG_LOG_CATEGORY(InputController,
								"이미 조합을 만족한 상태이므로 입력값 추가!(%d, %d)", pInputMappingInfo->vecInput[i], i);
						}
						// 이 경우에는 입력 조합이 미완성된 것으로 볼게요!
						else
						{
							ON_BITSET_ENUM(pInputMappingInfo->bitsetInputState, EInputMappingState::INCOMPLETION);
						}
					}
				}
			}
			// 마지막인 경우
			else
			{
				if ( (::GetAsyncKeyState(pInputMappingInfo->vecInput[i]) & INPUT_DOWN_FLAG) &&
					 (IS_BITSET(m_bitsetInputDown, pInputMappingInfo->vecInput[i - 1])) )
				{
					DEBUG_LOG_CATEGORY(InputController, "마지막값 순서대로 추가!(%d, %d)", pInputMappingInfo->vecInput[i], i);
					++inputCnt;

					ON_BITSET(m_bitsetInputDown, pInputMappingInfo->vecInput[i]);
				}
				else
				{
					ON_BITSET_ENUM(pInputMappingInfo->bitsetInputState, EInputMappingState::INCOMPLETION);
				}
			}
		}

		// 매핑된 정보에서 원하는 입력 조합을 누른 상태! (DOWN 아니면 PRESSING)
		if (inputCnt == pInputMappingInfo->vecInput.size())
		{
			// 해당 입력값이 눌리거나 누르는 상태가 아닐 때
			if ( (IS_BITSET_ENUM(pInputMappingInfo->bitsetInputState, EInputMappingState::DOWN) == false) &&
				 (IS_BITSET_ENUM(pInputMappingInfo->bitsetInputState, EInputMappingState::PRESSING) == false) )
			{
				ON_BITSET_ENUM(pInputMappingInfo->bitsetInputState, EInputMappingState::DOWN);
				DEBUG_LOG_CATEGORY(InputController, "키 눌렀다!");
			}
			// 해당 입력값이 눌러진 상태에서 또 눌렀을 때 (누르는 중이라는 의미)
			else if (IS_BITSET_ENUM(pInputMappingInfo->bitsetInputState, EInputMappingState::DOWN))
			{
				OFF_BITSET_ENUM(pInputMappingInfo->bitsetInputState, EInputMappingState::DOWN);
				ON_BITSET_ENUM(pInputMappingInfo->bitsetInputState, EInputMappingState::PRESSING);
				DEBUG_LOG_CATEGORY(InputController, "키 누르는중!");
			}
		}
		// 매핑된 정보에서 원하는 입력 조합을 누르지 못한 상태! (NONE 아니면 UP)
		else
		{
			// 해당 입력값이 눌렸거나 눌리는 중이었을 때
			if ( (IS_BITSET_ENUM(pInputMappingInfo->bitsetInputState, EInputMappingState::DOWN)) ||
				 (IS_BITSET_ENUM(pInputMappingInfo->bitsetInputState, EInputMappingState::PRESSING)) )
			{
				OFF_BITSET_ENUM(pInputMappingInfo->bitsetInputState, EInputMappingState::DOWN);
				OFF_BITSET_ENUM(pInputMappingInfo->bitsetInputState, EInputMappingState::PRESSING);
				ON_BITSET_ENUM(pInputMappingInfo->bitsetInputState, EInputMappingState::UP);
				DEBUG_LOG_CATEGORY(InputController, "키를 뗐으니 해당되는 입력 조합 전부 무효!");

				// 키를 뗐다는 건 잘못된 조합이어도 무효!
				for (auto& iter : pInputMappingInfo->vecInput)
				{
					OFF_BITSET(m_bitsetInputDown, iter);
				}
			}
			// 해당 입력값이 눌리지 않은 상태에서 또 누르지 않았을 때 (누르지 않고 있다는 의미)
			else if (IS_BITSET_ENUM(pInputMappingInfo->bitsetInputState, EInputMappingState::UP))
			{
				OFF_BITSET_ENUM(pInputMappingInfo->bitsetInputState, EInputMappingState::UP);
				ON_BITSET_ENUM(pInputMappingInfo->bitsetInputState, EInputMappingState::NONE);
				DEBUG_LOG_CATEGORY(InputController, "키 떼고 있다!");
			}
			// 일부만 조합되었거나 아예 조합되지 않았을 때
			else if (IS_BITSET_ENUM(pInputMappingInfo->bitsetInputState, EInputMappingState::INCOMPLETION))
			{
				Uint32 inputUpCnt = 0;

				for (auto& iter : pInputMappingInfo->vecInput)
				{
					if (IS_INPUT_UP(iter))
					{
						++inputUpCnt;
						OFF_BITSET(m_bitsetInputDown, iter);
						DEBUG_LOG_CATEGORY(InputController, "비트 false다! (%d)", iter);
					}
				}

				if (inputUpCnt == pInputMappingInfo->vecInput.size())
				{
					OFF_BITSET_ENUM(pInputMappingInfo->bitsetInputState, EInputMappingState::INCOMPLETION);
					DEBUG_LOG_CATEGORY(InputController, "잘못된 입력 전부 초기화!");
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
		DEBUG_LOG_CATEGORY(InputController, "%s 액션이 없어요!", szInputAction.data());
		return nullptr;
	}

	return iter->second;
}