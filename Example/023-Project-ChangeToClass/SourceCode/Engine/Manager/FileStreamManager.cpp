// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// 이 저작물은 크리에이티브 커먼즈 저작자표시 4.0 국제 라이선스에 따라 이용할 수 있습니다.
// http://creativecommons.org/licenses/by/4.0/
//
// 파일 스트림을 관리합니다.
// 경로와 확장자까지 포함된 전체 경로가 키값이 되고 파일 스트림이 실제 데이터가 됩니다.
// 파일을 저장하거나 불러올 때는 GameElem에 있는 가상함수로 처리해야 합니다.
// =====================================================================================

#include "PCH.h"
#include "FileStreamManager.h"

DEFINE_PHOENIX_SINGLETON(FileStreamMgr);

FILE* FileStreamMgr::OpenFileStream(const std::string_view& szKey, const std::string_view& szFileFullPath, EFileStreamMode fileStreamMode)
{
	std::string strMode;
	
	switch (fileStreamMode)
	{
	case EFileStreamMode::WRITE_TEXT:
	{
		strMode = "wt";
		break;
	}

	case EFileStreamMode::READ_TEXT:
	{
		strMode = "rt";
		break;
	}

	case EFileStreamMode::WRITE_BINARY:
	{
		strMode = "wb";
		break;
	}

	case EFileStreamMode::READ_BINARY:
	{
		strMode = "rb";
		break;
	}

	default:
	{
		break;
	}
	}

	FILE* pFileStream = nullptr;
	fopen_s(&pFileStream, szFileFullPath.data(), strMode.c_str());

	if (pFileStream == nullptr)
	{
		ERROR_HANDLER(false, EErrorType::FILE_STREAM_OPEN_FAIL, szFileFullPath.data());
		return nullptr;
	}

	FileStreamData fileStreamData;
	fileStreamData.strFullPath = szFileFullPath;
	fileStreamData.pFileStream = pFileStream;

	auto ret = m_mapFileStream.insert(std::make_pair(szKey, FileStreamData()));
	if (ret.second == true)
	{
		ret.first->second = fileStreamData;
	}

	return pFileStream;
}

void FileStreamMgr::CloseFileStream(const std::string_view& szKey)
{
	FILE* pFileStream = FindFileStream(szKey);
	std::fclose(pFileStream);
}

FILE* FileStreamMgr::FindFileStream(const std::string_view& szKey)
{
	const auto& iter = m_mapFileStream.find(szKey.data());
	if (iter == m_mapFileStream.cend())
	{
		DEFAULT_ERROR_HANDLER(EErrorType::FILE_STREAM_OPEN_FAIL, szKey);
		return nullptr;
	}

	return iter->second.pFileStream;
}

Int32 FileStreamMgr::CalcFileSize(const std::string_view& szKey)
{
	FILE* pFileStream = FindFileStream(szKey);
    std::fseek(pFileStream, 0, SEEK_END);

	return std::ftell(pFileStream);
}

bool FileStreamMgr::CheckSameExt(const std::string_view& szFileFullPath, const std::string_view& srcExt) const
{
	// 아래에 있는 처리와 같음!
	// std::string_view szDestExt = szFileFullPath.substr(szFileFullPath.rfind(".")).data();

	char destExt[_MAX_EXT];
	_splitpath_s(szFileFullPath.data(), nullptr, 0, nullptr, 0, nullptr, 0, destExt, _countof(destExt));

	if (srcExt == destExt)
	{
		return true;
	}

	return false;
}
