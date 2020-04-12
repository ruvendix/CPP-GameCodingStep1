// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// �� ���۹��� ũ������Ƽ�� Ŀ���� ������ǥ�� 4.0 ���� ���̼����� ���� �̿��� �� �ֽ��ϴ�.
// http://creativecommons.org/licenses/by/4.0/
//
// ���� ���� ��ƿ��Ƽ Ŭ�����Դϴ�.
// �õ尪�� �ʱ�ȭ�ؾ� ���������� ����� �� �ֽ��ϴ�.
// =====================================================================================

#include "PCH.h"
#include "Random.h"

namespace math
{

	std::default_random_engine RandomUtil::m_defaultRandomEngine;

	/*
	����Ʈ ���� ������ �õ尪 ����� �����ؼ� �ʱ�ȭ�մϴ�.
	*/
	void RandomUtil::Initialize()
	{
		std::array<Int32, std::default_random_engine::state_size> seeds; // �õ尪�� 624��
		std::generate_n(seeds.begin(), seeds.size(), std::ref(m_defaultRandomEngine)); // 624���� ���� �õ尪 ����
		std::seed_seq seedSeq(std::begin(seeds), std::end(seeds)); // ������ 624���� ���� �õ尪�� ���� ��ü�� ����
		m_defaultRandomEngine = std::default_random_engine(seedSeq); // �޸��� Ʈ�����Ϳ� �õ尪 ����
	}

	/*
	���� ���� ������ �������� �̽��ϴ�.
	�Ϲ����� ������ �����Դϴ�.
	*/
	Int32 RandomUtil::GenerateRandom(Int32 begin, Int32 end)
	{
		std::uniform_int_distribution<Int32> uniformIntDistribution(begin, end);
		return uniformIntDistribution(m_defaultRandomEngine);
	}

	/*
	�Ǽ� ���� ������ �������� �̽��ϴ�.
	�Ϲ����� ������ �����Դϴ�.
	*/
	Real32 RandomUtil::GenerateRandom(Real32 begin, Real32 end)
	{
		std::uniform_real_distribution<Real32> uniformRealDistribution(begin, end);
		return uniformRealDistribution(m_defaultRandomEngine);
	}

	/*
	��� ������ ����� �Ͼ Ȯ���� ���� ���� ���� ������ �������� �̽��ϴ�.
	*/
	Int32 RandomUtil::GenerateBinormalRandom(Int32 eventCnt, Real32 probability)
	{
		std::binomial_distribution<Int32> binomialDistribution(eventCnt, probability);
		return binomialDistribution(m_defaultRandomEngine);
	}

} // namespace math end