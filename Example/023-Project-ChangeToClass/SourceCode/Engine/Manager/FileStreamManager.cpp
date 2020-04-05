// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// �� ���۹��� ũ������Ƽ�� Ŀ���� ������ǥ�� 4.0 ���� ���̼����� ���� �̿��� �� �ֽ��ϴ�.
// http://creativecommons.org/licenses/by/4.0/
//
// ���� ��Ʈ���� �����մϴ�.
// ��ο� Ȯ���ڱ��� ���Ե� ��ü ��ΰ� Ű���� �ǰ� ���� ��Ʈ���� ���� �����Ͱ� �˴ϴ�.
// ������ �����ϰų� �ҷ��� ���� GameElem�� �ִ� �����Լ��� ó���ؾ� �մϴ�.
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
	// �Ʒ��� �ִ� ó���� ����!
	// std::string_view szDestExt = szFileFullPath.substr(szFileFullPath.rfind(".")).data();

	char destExt[_MAX_EXT];
	_splitpath_s(szFileFullPath.data(), nullptr, 0, nullptr, 0, nullptr, 0, destExt, _countof(destExt));

	if (srcExt == destExt)
	{
		return true;
	}

	return false;
}
