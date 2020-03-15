// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// �� ���۹��� ũ������Ƽ�� Ŀ���� ������ǥ�� 4.0 ���� ���̼����� ���� �̿��� �� �ֽ��ϴ�.
// http://creativecommons.org/licenses/by/4.0/
//
// Ű����� ���콺 �Է��� �����մϴ�.
// ��ŸŸ�Ӹ��� �����ϹǷ� ���ڿ� �� ��� ���������� �����մϴ�.
// =====================================================================================

#ifndef INPUT_CONTROLLER__H__
#define INPUT_CONTROLLER__H__

#include "Common\CommonNecessary.h"
#include "Common\CommonMacro.h"

DECLARE_LOG_CATEGORY(InputController);

// �Է°� �ϳ��� ���� ���°� �ƴ϶� �Է� ���տ� ���� ���¿���!
enum class EInputMappingState : Int32
{
	NONE = 0, // �Է� ������ ������ ���� ����
	UP,       // �Է� ������ �� ����
	PRESSING, // �Է� ������ ������ �ִ� ����
	DOWN,     // �Է� ������ ���� ����
	MAX,
};

struct InputMappingInfo
{
	std::vector<TInput> vecInputTable; // �Է� ���� ���̺� (����Ű�� 0 ~ 255)
	std::list<TInput> listInputChecker; // �Է� ������ �����ϴ��� Ȯ���ϱ� ���� �� (���� �����ӵ� Ȯ���ؾ� �ϹǷ�...)
	EInputMappingState state = EInputMappingState::NONE; // �Է� ������ ���� (4����)
};

class InputController final
{
	DECLARE_PHOENIX_SINGLETON(InputController);

public:
	using MapInputMappingInfo = std::unordered_map<std::string, InputMappingInfo*>;

	static const Int32 INPUT_DOWN_FLAG = 0x8000; // �Է°��� ���Ȱų� �����ִ��� Ȯ���ϴ� �뵵
	static const Uint8 MAX_INPUT_RANGE = UINT8_MAX;

	void PollInput();
	void Finalize();
	bool CheckInputState(const std::string_view& szInputMappingName, EInputMappingState inputState) const;
	InputMappingInfo* FindInputMappingInfo(const std::string_view& szInputMappingName) const;

	// ���� ���� ���ø������� Base Case����!
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
		else if (strInputValType == "int") // ����Ű�� �ǹ��ؿ�!
		{
			m_pInputMappingInfo->vecInputTable.push_back((Uint32)inputVal);
		}

		return;
	}
	
	// �Է°��� �߰��� �� �ڷ����� �޶��� �� �����Ƿ� ���� ���� ���ø��� ����ҰԿ�! (�Է°��� char �ƴϸ� int)
	// const�� ���� C++�� ĳ������ ����� �� �����ϱ� ������ ĳ�����ؾ� �ؿ�!
	template <typename TInputVal, typename ... types>
	void InsertInputMappingInfo(const TInputVal& inputVal, const types& ... args)
	{
		m_pInputMappingInfo = FindInputMappingInfo(inputVal);
		if (m_pInputMappingInfo != nullptr)
		{
			return; // �̹� �ڷᱸ���� �ִ� ������ �ƹ��͵� ���� �ʾƾ� �ؿ�!
		}
		else
		{
			m_pInputMappingInfo = trace_new InputMappingInfo; // ������ �ڷᱸ������!
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
		else if (strInputValType == "int") // ����Ű�� �ǹ��ؿ�!
		{
			m_pInputMappingInfo->vecInputTable.push_back((Uint32)inputVal);
		}
		else // ù ��° ���ڸ� ���⿡ ���;� �ؿ�!
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

		DEBUG_LOG_CATEGORY(InputController, "�Է� ���� ���� �߰� �Ϸ�! (%s)", inputVal);
	}

private:
	// InsertInputMappingInfo()������ ���Ǵ� ������
	bool m_bInputMappingName = false; // �� ��° ���ں��� �ɷ����� ���� ��!
	InputMappingInfo* m_pInputMappingInfo = nullptr; // �ߺ� �Ҵ��� ���� ���� ��!
	
	MapInputMappingInfo m_mapInputMappingInfo;
};

#endif