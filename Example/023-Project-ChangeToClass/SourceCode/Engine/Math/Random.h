// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// �� ���۹��� ũ������Ƽ�� Ŀ���� ������ǥ�� 4.0 ���� ���̼����� ���� �̿��� �� �ֽ��ϴ�.
// http://creativecommons.org/licenses/by/4.0/
//
// ���� ���� ��ƿ��Ƽ Ŭ�����Դϴ�.
// �õ尪�� �ʱ�ȭ�ؾ� ���������� ����� �� �ֽ��ϴ�.
// =====================================================================================

#ifndef MATH_UTILITY_RANDOM__H__
#define MATH_UTILITY_RANDOM__H__

#include "Common\CommonType.h"
#include "Common\CommonMacro.h"
#include "Common\CommonNecessary.h"

namespace math
{
	
	class RandomUtil
	{
		NON_COPYABLE_ONLY_PRIVATE_CLASS(RandomUtil);

	public:
		static void Initialize();
		
		static Int32 GenerateUniformDistribution(Int32 begin, Int32 end);
		static Int32 GenerateBinormalDistribution(Int32 eventCnt, Real32 probability);

		static Real32 GenerateUniformDistribution(Real32 begin, Real32 end);

	private:
		static std::default_random_engine m_defaultRandomEngine; // std::mt19937 (Mersenne Twister, �޸��� Ʈ������)
	};

} // namespace math end

#endif