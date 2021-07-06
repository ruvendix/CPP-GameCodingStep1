// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// 이 저작물은 크리에이티브 커먼즈 저작자표시 4.0 국제 라이선스에 따라 이용할 수 있습니다.
// http://creativecommons.org/licenses/by/4.0/
//
// 경로 관리자의 인터페이스입니다.
// =====================================================================================
#pragma once

#include "IPathManager.h"

// 전방 선언
class FrameworkPathfinder;

class PathManager final : public IPathManager
{
	ONLY_SUBSYSTEM(PathManager);

public:
	virtual void SetUp();
	virtual void CleanUp();

	virtual const std::string& FrameworkAbsolutePath() const override;
	virtual const std::string& FrameworkRelativePath() const override;
	virtual Uint32 FrameworkRelativePathStartPos() const override;

	virtual const std::string& ClientAbsolutePath() const override { return m_strClientAbsolutePath; }
	virtual const std::string& ClientRelativePath() const override { return m_strClientRelativePath; };
	virtual Uint32 ClientRelativePathStartPos() const override { return m_strClientRelativePath.length(); };

	virtual const Char* ExtractExtension(const std::string_view& strFilePath) const override;

private:
	// 내부에서만 사용하는 데이터는 내부 클래스를 이용하지만 FrameworkPathfinder는 예외입니다.
	// FrameworkPathfinder는 외부에서 생성 및 소멸을 막으려고 friend를 이용하는데
	// friend는 외부 클래스에만 사용하는 게 가독성이 좋아요.
	// 참고로 외부에서 생성 및 소멸이 막혀있으면 스마트 포인터를 사용하기가 매우 까다로워집니다.
	// 그래서 스마트 포인터를 포기하고 일반 포인터를 사용하는 걸 추천할게요.
	FrameworkPathfinder* m_pFrameworkPathFinder = nullptr;

	// 내부에서만 사용하는 데이터지만 최초 가공만 하고 변경되지 않는 데이터이므로 내부 클래스에 넣지 않을게요.
	std::string m_strClientAbsolutePath;
	std::string m_strClientRelativePath;
};