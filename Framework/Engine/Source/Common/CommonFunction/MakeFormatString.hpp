// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// �� ���۹��� ũ������Ƽ�� Ŀ���� ������ǥ�� 4.0 ���� ���̼����� ���� �̿��� �� �ֽ��ϴ�.
// http://creativecommons.org/licenses/by/4.0/
//
// MakeFormatString()�� �����մϴ�.
// =====================================================================================
#pragma once

#include "Common/CommonBase.h"
#include "Common/CommonType.h"

/*
    std::string�� ���Ĺ��ڿ��� ȣȯ��Ű���� �ʿ��մϴ�.
*/
template <typename T>
T Argument(T value)
{
    return value;
}

/*
    std::string�� ���Ĺ��ڿ��� ȣȯ�ǰ� ���ݴϴ�.
    ���ø� �����ε��� �̿��Ϸ��� std::basic_string<T>�� �̿��ؾ� �ؿ�.
*/
template <typename T>
const char* Argument(const std::basic_string<T>& str)
{
    return str.c_str();
}

/*
    Char �迭�� ���Ĺ��ڿ��� ���ϴ�.
*/
template <typename... Args>
Int32 StringPrint(Char buffer[], size_t bufferCount, const Char* szFormat, Args&&... args)
{
    return snprintf(buffer, bufferCount, szFormat, Argument(std::forward<Args>(args))...);
}

/*
    ���Ĺ��ڿ��� std::string���� ����ϴ�.
*/
template <typename... Args>
std::string MakeFormatString(const Char* szFormat, Args&&... args)
{
    Int32 stringLength = StringPrint(nullptr, 0, szFormat, std::forward<Args>(args)...);

    std::string str;
    str.resize(stringLength);

    // snprintf()�� ���Ṯ�ڰ� ���ԵǾ��ٰ� �����ϹǷ� +1�� ����� �մϴ�.
    stringLength = StringPrint(str.data(), str.size() + 1, szFormat, std::forward<Args>(args)...);

    // ����ؾ� �� ���ڿ��� ���� ������ ���(���Ṯ�� ����)
    if (stringLength > static_cast<Int32>(str.size()))
    {
        str.resize(stringLength);
        StringPrint(str.data(), str.size() + 1, szFormat, std::forward<Args>(args)...);
    }
    // ����ؾ� �� ���ڿ� ���̺��� ���� ���(���Ṯ�� ����)
    else if (stringLength < static_cast<Int32>(str.size()))
    {
        str.resize(stringLength);
    }

    return str;
}