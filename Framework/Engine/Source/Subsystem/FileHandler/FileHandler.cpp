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

void FileHandler::StartUp()
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

	std::string_view strTextMode;
	if (fileMode == EFileMode::TEXT)
	{
		strTextMode = "t";
	}
	else if (fileMode == EFileMode::BINARY)
	{
		strTextMode = "b";
	}

	std::string_view strAccessMode;
	if (accessMode == EAccessMode::READ)
	{
		strAccessMode = "r";
	}
	else if (accessMode == EAccessMode::WRITE)
	{
		strAccessMode = "w";
	}
	else if (accessMode == EAccessMode::APPEND)
	{
		strAccessMode = "a";
	}
	else if (accessMode == EAccessMode::WRITE_PLUS)
	{
		strAccessMode = "w+";
	}
	else if (accessMode == EAccessMode::READ_PLUS)
	{
		strAccessMode = "r+";
	}
	else if (accessMode == EAccessMode::APPEND_PLUS)
	{
		strAccessMode = "a+";
	}

	std::string strMode;
	strMode += strAccessMode;
	strMode += strTextMode;

	*ppFile = std::fopen(strFilePath.data(), strMode.c_str());
	RX_ASSERT2(LogFileHandler, *ppFile != nullptr);

	return true;
}

void FileHandler::CloseFileStream(FILE* pFile) const
{
	if (std::fclose(pFile) != 0)
	{
		RX_ERROR2(LogFileHandler, EErrorCode::CLOSE_FILE_STREAM_FAIL);
	}
}