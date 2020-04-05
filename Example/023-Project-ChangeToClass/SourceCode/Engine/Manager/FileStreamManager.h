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

#ifndef FILE_STREAM_MGR__H__
#define FILE_STREAM_MGR__H__

#include "Common\CommonType.h"
#include "Common\CommonMacro.h"
#include "Element\NameTag.h"

enum class EFileStreamMode : Int32
{
	WRITE_TEXT = 0,
	WRITE_BINARY,
	READ_TEXT,
	READ_BINARY,
};

struct FileStreamData
{
	std::string strFullPath;
	FILE* pFileStream = nullptr;
};

DECLARE_LOG_CATEGORY(FileStreamMgr);

class FileStreamMgr final
{
	DECLARE_PHOENIX_SINGLETON(FileStreamMgr);

public:
	FILE* OpenFileStream(const std::string_view& szKey, const std::string_view& szFileFullPath, EFileStreamMode fileStreamMode);
	void CloseFileStream(const std::string_view& szKey);
	FILE* FindFileStream(const std::string_view& szKey);
	Int32 CalcFileSize(const std::string_view& szKey);
	bool CheckSameExt(const std::string_view& szFileFullPath, const std::string_view& szExt) const;

private:
	std::unordered_map<std::string, FileStreamData> m_mapFileStream;
};

#endif