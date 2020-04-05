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