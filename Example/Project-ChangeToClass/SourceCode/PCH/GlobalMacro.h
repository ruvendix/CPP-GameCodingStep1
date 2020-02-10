// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// �� ���۹��� ũ������Ƽ�� Ŀ���� ������ǥ�� 4.0 ���� ���̼����� ���� �̿��� �� �ֽ��ϴ�.
// http://creativecommons.org/licenses/by/4.0/
// =====================================================================================

#ifndef GLOBAL_MACRO__H__
#define GLOBAL_MACRO__H__

// VLD�� ��ü �������� Ȯ�� �ʿ�!
#ifdef _DEBUG
#define new new(_NORMAL_BLOCK, __FILE__, __LINE__ )                                            
#endif

#define SAFE_DELETE(ptr)\
	if (ptr != nullptr)\
	{\
		delete ptr;\
		ptr = nullptr;\
	}

// ���� �� �̵��� �����ϴ� ��ũ�ο���. (Copy Semantics, Move Semantics)
#define NON_COPYABLE_CLASS(TClass)\
public:\
	TClass(const TClass&) = delete;\
	TClass(const TClass&&) = delete;\
	TClass& operator=(const TClass&) = delete;\
	TClass&& operator=(const TClass&&) = delete;

// �ܺο����� ���� �� �Ҹ��� ���� ��ũ�ο���. (�⺻ �����ڸ� ����)
// ������ ��� ���迡���� ���� �����ϰ� ����� �ؿ�.
#define NON_EXTERNAL_CLASS(TClass)\
protected:\
	TClass() = default;\
	virtual ~TClass() = default;

// ��� ���迡���� ���� �Ұ����� �����Դϴ�.
#define ONLY_PRIVATE_CLASS(TClass)\
private:\
	TClass() = default;\
	virtual ~TClass() = default;

#endif