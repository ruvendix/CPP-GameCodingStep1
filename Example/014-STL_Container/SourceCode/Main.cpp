// =====================================================================================
// Copyright(c) 2019, Ruvendix. All Rights Reserved.
// 
// �� ���۹��� ũ������Ƽ�� Ŀ���� ������ǥ�� 4.0 ���� ���̼����� ���� �̿��� �� �ֽ��ϴ�.
// http://creativecommons.org/licenses/by/4.0/
// =====================================================================================

#include <cstdio>
#include <string>

using int32  = signed __int32;
using real32 = float;

template <typename TContainer>
void ShowAllElement(const TContainer& container)
{
	printf("--------------------------------------------\n");
	for (const TContainer::value_type& iter : container)
	{
		printf("\"%s\"\n", iter.c_str());
	}
	printf("--------------------------------------------\n");
}

template <typename TMap>
void ShowAllElementOnlyMap(const TMap& container)
{
	printf("--------------------------------------------\n");
	for (const TMap::value_type& iter : container)
	{
		printf("\"%s\"\n", iter.second.c_str());
	}
	printf("--------------------------------------------\n");
}

int32 main()
{
#if 0
	///////////////////////////////////////////////////////////////////////////////////////////////////////
	// std::vector
	std::vector<std::string> vecJobName;

	// capcity�� �ø����� reserve()��,
	// size�� �ø����� resize()�� ȣ���ϼ���!
	// vecJobName.reserve(5);
	// vecJobName.resize(2); // capcity�� �� ������ capacity�� ����
	
	// �Ϲ����� ���� ����̿���!
	std::string strJobName = "�ǻ�";
	vecJobName.push_back(strJobName); // �����ڷ� �ް� ���ο��� ����
	ShowAllElement(vecJobName);

	// R-Value�� �̿��� ���� ����̿���!
	vecJobName.push_back("����");
	ShowAllElement(vecJobName);

	// �� �տ� �ִ� ��Ҹ� �����ҰԿ�.
	vecJobName.erase(vecJobName.begin()); // capacity ���� ����
	ShowAllElement(vecJobName);

	// ��� ��Ҹ� �����ҰԿ�.
	vecJobName.clear(); // capacity ���� ����

	// c++11 ���ĺ��ʹ� emplace_back()�� �̿��ϼ���!
	// emplace_back()�� push_back() ��ɿ� �ϳ��� �� �߰��� ���� �Լ�!
	// �� ����� Ŭ������ �˾ƺ� �� �˷��帱�Կ�!
	strJobName = "�ǻ�";
	vecJobName.emplace_back(strJobName);
	vecJobName.emplace_back("���");
	ShowAllElement(vecJobName);
#endif

#if 0
	///////////////////////////////////////////////////////////////////////////////////////////////////////
	// std::foward_list
	std::forward_list<std::string> listFoodName; // ���ӿ����� �ܹ��� ����Ʈ�� �ַ� ���!

	// �Ϲ����� ���� ����̿���!
	std::string strFoodName = "������";
	listFoodName.push_front(strFoodName); // �⺻ ������ �� �ո� ����!
	ShowAllElement(listFoodName);

	// R-Value�� �̿��� ���� ����̿���!
	listFoodName.push_front("���");
	ShowAllElement(listFoodName);

	// �߰��� �����ϴ� ����̿���!
	listFoodName.insert_after(listFoodName.begin(), "���");
	ShowAllElement(listFoodName);

	// �� �տ� �ִ� ��Ҹ� �����ҰԿ�.
	listFoodName.pop_front();
	ShowAllElement(listFoodName);

	// ��� ��Ҹ� �����ҰԿ�.
	listFoodName.clear();

	// ���⿡�� emplace�� �־��!
	listFoodName.emplace_front("�ұ���");
	listFoodName.emplace_after(listFoodName.begin(), "������ũ");
	ShowAllElement(listFoodName);
#endif

#if 0
	///////////////////////////////////////////////////////////////////////////////////////////////////////
	// std::unordered_map
	std::unordered_map<std::string, std::string> mapGameObject; // �ڿ� �ִ� �����͸� std::string���� ����!
	
	// �Ϲ����� ���� ����̿���!
	mapGameObject.insert(std::make_pair("���� Ű��", "����"));
	ShowAllElementOnlyMap(mapGameObject);

	// �� �� ���� ���� ����̿���! (C++11 ���� ����!)
	mapGameObject.insert( {"�� Ű��", "��"} );
	ShowAllElementOnlyMap(mapGameObject);

	// insert()�� ��ȯ���� Ȯ���ϴ� �� ���ƿ�!
	// �ʹ� �� Type Alias�� ����ҰԿ�.
	using MapGameObject = std::unordered_map<std::string, std::string>;
	std::pair<MapGameObject::iterator, bool> result = mapGameObject.insert( {"���� Ű��", "����"} );
	printf("first���� ������ ��! (\"%s\", \"%s\")\n", result.first->first.c_str(), result.first->second.c_str());
	(result.second == true) ? (printf("���� ����!\n")) : printf("���� ����!\n"); // second���� ���� ���� ����
	ShowAllElementOnlyMap(mapGameObject);

	// Ű���� �̿��ؼ� ���� ���� ���� ã�� �� �־��!
	MapGameObject::iterator iter = mapGameObject.find("�� Ű��");
	if (iter == mapGameObject.end())
	{
		printf("�ش�Ǵ� Ű���� �����!\n");
	}
	else
	{
		printf("Ű�� \"%s\"�� ���� \"%s\"����!\n", iter->first.c_str(), iter->second.c_str());
	}

	// ������ ã�� ��Ҹ� �����ҰԿ�!
	mapGameObject.erase(iter);
	ShowAllElementOnlyMap(mapGameObject);

	// ��� ��Ҹ� �����ҰԿ�.
	mapGameObject.clear();

	// ���⿡�� emplace�� �־��!
	mapGameObject.emplace("���� Ű��", "����");
	ShowAllElementOnlyMap(mapGameObject);
#endif

#if 0
	///////////////////////////////////////////////////////////////////////////////////////////////////////
	// std::tuple
	// �ʹ� ��ϱ� Type Alias�� �̿��ҰԿ�.
	using ObjectInfo = std::tuple<std::string, int32, real32>; // �� ��ҿ� Ư���� �ǹ̴� ����!
	
	// �Ϲ����� ���� ����̿���!
	ObjectInfo objectInfo = std::make_tuple("�� ������Ʈ", 100, 20.24f);
	
	// std::get�� �̿��ؼ� ���� �����;� �ؿ�!
	std::string strObjectName = std::get<0>(objectInfo);
	int32       intValue      = std::get<1>(objectInfo);
	real32      realValue     = std::get<2>(objectInfo);

	// ������ ������ ����غ��Կ�!
	printf("%s\t%d\t%f\n", strObjectName.c_str(), intValue, realValue);
#endif

	return EXIT_SUCCESS;
}