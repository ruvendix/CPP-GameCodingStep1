// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// 이 저작물은 크리에이티브 커먼즈 저작자표시 4.0 국제 라이선스에 따라 이용할 수 있습니다.
// http://creativecommons.org/licenses/by/4.0/
//
// 키보드와 마우스 입력을 제어합니다.
// 델타타임마다 폴링하므로 문자열 비교 대신 열거형으로 고정합니다.
// =====================================================================================

#ifndef INPUT_CONTROLLER__H__
#define INPUT_CONTROLLER__H__

#include "Common\CommonNecessary.h"
#include "Common\CommonMacro.h"

DECLARE_LOG_CATEGORY(InputController);

// 입력값 하나에 대한 상태가 아니라 입력 조합에 대한 상태에요!
enum class EInputMappingState : Int32
{
	NONE = 0, // 입력 조합을 누르지 않은 상태
	UP,       // 입력 조합을 뗀 상태
	PRESSING, // 입력 조합을 누르고 있는 상태
	DOWN,     // 입력 조합을 누른 상태
	MAX,
};

struct InputMappingInfo
{
	std::vector<TInput> vecInputTable; // 입력 매핑 테이블 (가상키는 0 ~ 255)
	std::list<TInput> listInputChecker; // 입력 매핑을 만족하는지 확인하기 위한 것 (이전 프레임도 확인해야 하므로...)
	EInputMappingState state = EInputMappingState::NONE; // 입력 매핑의 상태 (4가지)
};

class InputController final
{
	DECLARE_PHOENIX_SINGLETON(InputController);

public:
	using MapInputMappingInfo = std::unordered_map<std::string, InputMappingInfo*>;

	static const Int32 INPUT_DOWN_FLAG = 0x8000; // 입력값이 눌렸거나 눌려있는지 확인하는 용도
	static const Uint8 MAX_INPUT_RANGE = UINT8_MAX;

	void PollInput();
	void Finalize();
	bool CheckInputState(const std::string_view& szInputMappingName, EInputMappingState inputState) const;
	InputMappingInfo* FindInputMappingInfo(const std::string_view& szInputMappingName) const;

	// 가변 인자 템플릿에서의 Base Case에요!
	template <typename TInputVal>
	void InsertInputMappingInfo(const TInputVal& inputVal)
	{
		const std::string& strInputValType = typeid(TInputVal).name();
		if (strInputValType == "char")
		{
			if (std::isupper((Int32)inputVal) == 0)
			{
				ERROR_HANDLER(EErrorType::INPUT_MAPPING_VAL_IS_ONLY_UPPERCASE);
				return;
			}

			m_pInputMappingInfo->vecInputTable.push_back((Uint32)inputVal);
		}
		else if (strInputValType == "int") // 가상키를 의미해요!
		{
			m_pInputMappingInfo->vecInputTable.push_back((Uint32)inputVal);
		}

		return;
	}
	
	// 입력값을 추가할 때 자료형이 달라질 수 있으므로 가변 인자 템플릿을 사용할게요! (입력값은 char 아니면 int)
	// const로 인해 C++의 캐스팅은 사용할 수 없으니까 강제로 캐스팅해야 해요!
	template <typename TInputVal, typename ... types>
	void InsertInputMappingInfo(const TInputVal& inputVal, const types& ... args)
	{
		m_pInputMappingInfo = FindInputMappingInfo(inputVal);
		if (m_pInputMappingInfo != nullptr)
		{
			return; // 이미 자료구조에 있는 정보면 아무것도 하지 않아야 해요!
		}
		else
		{
			m_pInputMappingInfo = trace_new InputMappingInfo; // 해제는 자료구조에서!
		}

		const std::string& strInputValType = typeid(TInputVal).name();
		if (strInputValType == "char")
		{
			if (std::isupper((Int32)inputVal) == 0)
			{
				ERROR_HANDLER(EErrorType::INPUT_MAPPING_VAL_IS_ONLY_UPPERCASE);
				return;
			}

			m_pInputMappingInfo->vecInputTable.push_back((Uint32)inputVal);
		}
		else if (strInputValType == "int") // 가상키를 의미해요!
		{
			m_pInputMappingInfo->vecInputTable.push_back((Uint32)inputVal);
		}
		else // 첫 번째 인자만 여기에 들어와야 해요!
		{
			if (m_bInputMappingName == true)
			{
				ERROR_HANDLER(EErrorType::INPUT_MAPPING_SECOND_ARG_IS_NOT_AVAILABLE_STRING);
				return;
			}

			m_mapInputMappingInfo[reinterpret_cast<const char*>(inputVal)] = m_pInputMappingInfo;
			m_bInputMappingName = true;
		}

		InsertInputMappingInfo(args ...);

		m_pInputMappingInfo = nullptr;
		m_bInputMappingName = false;

		DEBUG_LOG_CATEGORY(InputController, "입력 매핑 정보 추가 완료! (%s)", inputVal);
	}

private:
	// InsertInputMappingInfo()에서만 사용되는 변수들
	bool m_bInputMappingName = false; // 두 번째 인자부터 걸러내기 위한 것!
	InputMappingInfo* m_pInputMappingInfo = nullptr; // 중복 할당을 막기 위한 것!
	
	MapInputMappingInfo m_mapInputMappingInfo;
};

#endif