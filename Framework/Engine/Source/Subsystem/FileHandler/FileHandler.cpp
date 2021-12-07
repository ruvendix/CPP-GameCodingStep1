// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// �� ���۹��� ũ������Ƽ�� Ŀ���� ������ǥ�� 4.0 ���� ���̼����� ���� �̿��� �� �ֽ��ϴ�.
// http://creativecommons.org/licenses/by/4.0/
//
// ���� �ڵ鷯�Դϴ�.
// �ܺο��� ���� ������ ���ų� �ݴ� ����� �ֽ��ϴ�.
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
	// �ϴ� Win32 API �Լ� ��������� ����
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