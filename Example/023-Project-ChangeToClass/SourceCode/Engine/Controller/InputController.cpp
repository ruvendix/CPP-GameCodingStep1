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

		//Uint32 inputCnt = 0; // 매핑된 정보에서 원하는 입력 조합을 눌렀는지 확인해야 해요!
		InputMappingInfo* pInputMappingInfo = iter.second;
		CHECK_NULLPTR(pInputMappingInfo);

		// 입력 조합표가 없으면 무시!
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

			// 리스트에 없는 값만 넣어야 함!
			if (IsOverlapVal(listInputChecker, inputVal) == false)
			{
				// 리스트에 없는 값에서만 입력값 추가!
				if (::GetAsyncKeyState(inputVal) & INPUT_DOWN_FLAG)
				{
					listInputChecker.push_back(inputVal);
					DEBUG_LOG_CATEGORY(InputController, "값 추가! (%d)", inputVal);
				}
			}
			// 이미 리스트에 있는 값이면? 여전히 값이 눌려있는지 확인!
			else
			{
				if (IS_INPUT_DOWN(inputVal))
				{
					DEBUG_LOG_CATEGORY(InputController, "이미 누르고 있는 값! (%d)", inputVal);
				}
				else
				{
					listInputChecker.pop_back();
					DEBUG_LOG_CATEGORY(InputController, "누르고 있던 값을 뗌! (%d)", inputVal);
				}
			}
		}

		EInputMappingState inputMappingState = pInputMappingInfo->state;

		// 매핑된 정보에서 원하는 입력 조합을 누른 상태! (DOWN 아니면 PRESSING)
		//if (inputCnt == pInputMappingInfo->vecInput.size())
		if (std::equal(vecInput.cbegin(), vecInput.cend(), listInputChecker.cbegin(), listInputChecker.cend()) == true)
		{
			DEBUG_LOG_CATEGORY(InputController, "입력 조합을 만족했다!");

			// 해당 입력값이 눌리거나 누르는 상태가 아닐 때
			if ( (inputMappingState != EInputMappingState::DOWN) &&
				 (inputMappingState != EInputMappingState::PRESSING) )
			{
				inputMappingState = EInputMappingState::DOWN;
				DEBUG_LOG_CATEGORY(InputController, "입력 조합을 최초로 눌렀다!");
			}
			// 해당 입력값이 눌러진 상태에서 또 눌렀을 때 (누르는 중이라는 의미)
			else if (inputMappingState == EInputMappingState::DOWN)
			{
				inputMappingState = EInputMappingState::PRESSING;
				DEBUG_LOG_CATEGORY(InputController, "입력 조합을 계속 누르는중!");
			}
		}
		// 매핑된 정보에서 원하는 입력 조합을 누르지 못한 상태! (NONE 아니면 UP)
		else
		{
			//DEBUG_LOG_CATEGORY(InputController, "입력 조합을 만족하지 않음!");

			// 해당 입력값이 눌렸거나 눌리는 중이었을 때
			if ( (inputMappingState == EInputMappingState::DOWN) || 
				 (inputMappingState == EInputMappingState::PRESSING) )
			{
				inputMappingState = EInputMappingState::UP;
				DEBUG_LOG_CATEGORY(InputController, "이제는 입력 조합을 만족하지 않음!");				
			}
			// 해당 입력값이 눌리지 않은 상태에서 또 누르지 않았을 때 (누르지 않고 있다는 의미)
			else if (inputMappingState == EInputMappingState::UP)
			{
				inputMappingState = EInputMappingState::NONE;
				DEBUG_LOG_CATEGORY(InputController, "입력 조합을 계속 누르지 않고 있음!");
			}
		}

		// 입력 조합 상태 갱신
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
		DEBUG_LOG_CATEGORY(InputController, "%s 액션이 없어요!", szInputAction.data());
		return nullptr;
	}

	return iter->second;
}