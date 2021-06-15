// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// 이 저작물은 크리에이티브 커먼즈 저작자표시 4.0 국제 라이선스에 따라 이용할 수 있습니다.
// http://creativecommons.org/licenses/by/4.0/
//
// 파일 핸들러입니다.
// 외부에서 받은 파일을 열거나 닫는 기능이 있습니다.
// =====================================================================================
#include "EnginePCH.h"
#include "FileHandler.h"

void FileHandler::SetUp()
{

}

void FileHandler::CleanUp()
{

}

Bool FileHandler::OpenFileStream(const std::string_view& strFilePath,
	EFileMode fileMode, EAccessMode accessMode, OUT FILE** ppFile) const
{
	// 일단 Win32 API 함수 적용까지는 보류
	//if (*ppFile != nullptr)
	//{
	//	CloseFileStream(*ppFile);
	//}

	std::string strMode;
	if (fileMode == EFileMode::TEXT)
	{
		if (accessMode == EAccessMode::READ)
		{
			strMode = "rt";
		}
		else if (accessMode == EAccessMode::WRITE)
		{
			strMode = "wt";
		}
		else if (accessMode == EAccessMode::APPEND)
		{
			strMode = "at";
		}
		else if (accessMode == EAccessMode::WRITE_PLUS)
		{
			strMode = "w+t";
		}
		else if (accessMode == EAccessMode::READ_PLUS)
		{
			strMode = "r+t";
		}
		else if (accessMode == EAccessMode::APPEND_PLUS)
		{
			strMode = "a+t";
		}
	}
	else if (fileMode == EFileMode::BINARY)
	{
		if (accessMode == EAccessMode::READ)
		{
			strMode = "rb";
		}
		else if (accessMode == EAccessMode::WRITE)
		{
			strMode = "wb";
		}
		else if (accessMode == EAccessMode::APPEND)
		{
			strMode = "ab";
		}
		else if (accessMode == EAccessMode::WRITE_PLUS)
		{
			strMode = "w+b";
		}
		else if (accessMode == EAccessMode::READ_PLUS)
		{
			strMode = "r+b";
		}
		else if (accessMode == EAccessMode::APPEND_PLUS)
		{
			strMode = "a+b";
		}
	}

	*ppFile = std::fopen(strFilePath.data(), strMode.c_str());
	RX_ASSERT(LogFileHandler, *ppFile != nullptr);

	return true;
}

void FileHandler::CloseFileStream(FILE* pFile) const
{
	if (std::fclose(pFile) != 0)
	{
		RX_ERROR(LogFileHandler, EErrorCode::CLOSE_FILE_STREAM_FAIL);
	}
}