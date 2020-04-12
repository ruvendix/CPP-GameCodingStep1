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

#include "FrameController.h"

DEFINE_LOG_CATEGORY(InputController);
DEFINE_PHOENIX_SINGLETON(InputController);

/*
입력 매핑 정보를 기반으로 입력 상태를 계속 확인하며 갱신합니다.
*/
void InputController::PollInput()
{
	for (auto& iter : m_mapInputMappingInfo)
	{
		InputMappingInfo* pInputMappingInfo = iter.second;
		CHECK_NULLPTR_CONTINUE(pInputMappingInfo);

		// 입력 매핑표가 없으면 무시!
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

			// 리스트에 없는 값만 넣어야 함!
			if (common_func::IsOverlapValue(listInputChecker, inputValue) == false)
			{
				// 리스트에 없는 값에서만 입력값 추가!
				if (::GetAsyncKeyState(inputValue) & INPUT_DOWN_FLAG)
				{
					listInputChecker.push_back(inputValue);
					DEBUG_LOG_CATEGORY(InputController, "값 추가! (%d) (%s)", inputValue, iter.first.c_str());
				}
			}
			// 이미 리스트에 있는 값이면? 여전히 값이 눌려있는지 확인!
			else
			{
				if (IS_INPUT_DOWN(inputValue))
				{
					DEBUG_LOG_CATEGORY(InputController, "이미 누르고 있는 값! (%d) (%s)", inputValue, iter.first.c_str());
				}
				else
				{
					listInputChecker.pop_back();
					DEBUG_LOG_CATEGORY(InputController, "누르고 있던 값을 뗌! (%d) (%s)", inputValue, iter.first.c_str());
				}
			}
		}

		EInputMappingState inputMappingState = pInputMappingInfo->state;

		// 매핑된 정보를 만족하는 상태! (DOWN 아니면 PRESSING)
		if (std::equal(vecInputTable.cbegin(), vecInputTable.cend(), listInputChecker.cbegin(), listInputChecker.cend()) == true)
		{
			//DEBUG_LOG_CATEGORY(InputController, "입력 매핑을 만족했다!");

			// 해당 입력값이 눌리거나 누르는 상태가 아닐 때
			if ( (inputMappingState != EInputMappingState::DOWN) &&
				 (inputMappingState != EInputMappingState::PRESSING) )
			{
				inputMappingState = EInputMappingState::DOWN;
				DEBUG_LOG_CATEGORY(InputController, "입력 매핑을 최초로 만족했다!");
			}
			// 해당 입력값이 눌러진 상태에서 또 눌렀을 때 (누르는 중이라는 의미)
			else if (inputMappingState == EInputMappingState::DOWN)
			{
				inputMappingState = EInputMappingState::PRESSING;
				DEBUG_LOG_CATEGORY(InputController, "입력 매핑을 유지중!");
			}
		}
		// 매핑된 정보를 만족하지 못한 상태! (IDLE 아니면 UP)
		else
		{
			//DEBUG_LOG_CATEGORY(InputController, "입력 매핑을 만족하지 않음!");

			// 해당 입력값이 눌렸거나 눌리는 중이었을 때
			if ( (inputMappingState == EInputMappingState::DOWN) || 
				 (inputMappingState == EInputMappingState::PRESSING) )
			{
				inputMappingState = EInputMappingState::UP;
				DEBUG_LOG_CATEGORY(InputController, "이제는 입력 매핑을 만족하지 않음!");				
			}
			// 해당 입력값이 눌리지 않은 상태에서 또 누르지 않았을 때 (누르지 않고 있다는 의미)
			else if (inputMappingState == EInputMappingState::UP)
			{
				inputMappingState = EInputMappingState::IDLE;
				DEBUG_LOG_CATEGORY(InputController, "입력 매핑을 계속 만족하지 않음!");
			}
		}

		// 입력 매핑 상태 갱신
		pInputMappingInfo->state = inputMappingState;
	}
}

/*
모든 입력 매핑 정보를 제거합니다.
*/
void InputController::Finalize()
{
	for (auto& iter : m_mapInputMappingInfo)
	{
		SAFE_DELETE(iter.second);
	}
}

/*
매핑된 입력 정보를 제거합니다.
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
원하는 입력 매핑 이름에 해당되는 상태를 알려줍니다.
*/
bool InputController::CheckInputState(const std::string_view& szInputMappingName, EInputMappingState inputState) const
{
	InputMappingInfo* pInputMappingInfo = FindInputMappingInfo(szInputMappingName);
	CHECK_NULLPTR(pInputMappingInfo);
	return (pInputMappingInfo->state == inputState);
}

/*
원하는 입력 매핑 이름에 해당되는 정보를 알려줍니다.
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