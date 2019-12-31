// =====================================================================================
// Copyright(c) 2019, Ruvendix. All Rights Reserved.
// 
// 이 저작물은 크리에이티브 커먼즈 저작자표시 4.0 국제 라이선스에 따라 이용할 수 있습니다.
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

	// capcity만 늘리려면 reserve()를,
	// size도 늘리려면 resize()를 호출하세요!
	// vecJobName.reserve(5);
	// vecJobName.resize(2); // capcity가 더 많으면 capacity는 유지
	
	// 일반적인 삽입 방법이에요!
	std::string strJobName = "의사";
	vecJobName.push_back(strJobName); // 참조자로 받고 내부에서 복사
	ShowAllElement(vecJobName);

	// R-Value를 이용한 삽입 방법이에요!
	vecJobName.push_back("가수");
	ShowAllElement(vecJobName);

	// 맨 앞에 있는 요소를 삭제할게요.
	vecJobName.erase(vecJobName.begin()); // capacity 변경 없음
	ShowAllElement(vecJobName);

	// 모든 요소를 삭제할게요.
	vecJobName.clear(); // capacity 변경 없음

	// c++11 이후부터는 emplace_back()만 이용하세요!
	// emplace_back()은 push_back() 기능에 하나가 더 추가된 좋은 함수!
	// 그 기능은 클래스를 알아볼 때 알려드릴게요!
	strJobName = "판사";
	vecJobName.emplace_back(strJobName);
	vecJobName.emplace_back("농부");
	ShowAllElement(vecJobName);
#endif

#if 0
	///////////////////////////////////////////////////////////////////////////////////////////////////////
	// std::foward_list
	std::forward_list<std::string> listFoodName; // 게임에서는 단방향 리스트를 주로 사용!

	// 일반적인 삽입 방법이에요!
	std::string strFoodName = "볶음밥";
	listFoodName.push_front(strFoodName); // 기본 삽입은 맨 앞만 가능!
	ShowAllElement(listFoodName);

	// R-Value를 이용한 삽입 방법이에요!
	listFoodName.push_front("돈까스");
	ShowAllElement(listFoodName);

	// 중간에 삽입하는 방법이에요!
	listFoodName.insert_after(listFoodName.begin(), "라면");
	ShowAllElement(listFoodName);

	// 맨 앞에 있는 요소를 삭제할게요.
	listFoodName.pop_front();
	ShowAllElement(listFoodName);

	// 모든 요소를 삭제할게요.
	listFoodName.clear();

	// 여기에도 emplace가 있어요!
	listFoodName.emplace_front("쌀국수");
	listFoodName.emplace_after(listFoodName.begin(), "스테이크");
	ShowAllElement(listFoodName);
#endif

#if 0
	///////////////////////////////////////////////////////////////////////////////////////////////////////
	// std::unordered_map
	std::unordered_map<std::string, std::string> mapGameObject; // 뒤에 있는 데이터를 std::string으로 가정!
	
	// 일반적인 삽입 방법이에요!
	mapGameObject.insert(std::make_pair("나무 키값", "나무"));
	ShowAllElementOnlyMap(mapGameObject);

	// 좀 더 편한 삽입 방법이에요! (C++11 이후 가능!)
	mapGameObject.insert( {"집 키값", "집"} );
	ShowAllElementOnlyMap(mapGameObject);

	// insert()의 반환값을 확인하는 게 좋아요!
	// 너무 길어서 Type Alias를 사용할게요.
	using MapGameObject = std::unordered_map<std::string, std::string>;
	std::pair<MapGameObject::iterator, bool> result = mapGameObject.insert( {"동굴 키값", "동굴"} );
	printf("first에는 삽입한 값! (\"%s\", \"%s\")\n", result.first->first.c_str(), result.first->second.c_str());
	(result.second == true) ? (printf("삽입 성공!\n")) : printf("삽입 실패!\n"); // second에는 삽입 성공 여부
	ShowAllElementOnlyMap(mapGameObject);

	// 키값을 이용해서 실제 값을 쉽게 찾을 수 있어요!
	MapGameObject::iterator iter = mapGameObject.find("집 키값");
	if (iter == mapGameObject.end())
	{
		printf("해당되는 키값이 없어요!\n");
	}
	else
	{
		printf("키가 \"%s\"인 값은 \"%s\"에요!\n", iter->first.c_str(), iter->second.c_str());
	}

	// 위에서 찾은 요소를 삭제할게요!
	mapGameObject.erase(iter);
	ShowAllElementOnlyMap(mapGameObject);

	// 모든 요소를 삭제할게요.
	mapGameObject.clear();

	// 여기에도 emplace가 있어요!
	mapGameObject.emplace("상자 키값", "상자");
	ShowAllElementOnlyMap(mapGameObject);
#endif

#if 0
	///////////////////////////////////////////////////////////////////////////////////////////////////////
	// std::tuple
	// 너무 기니까 Type Alias를 이용할게요.
	using ObjectInfo = std::tuple<std::string, int32, real32>; // 각 요소에 특정한 의미는 없음!
	
	// 일반적인 대입 방법이에요!
	ObjectInfo objectInfo = std::make_tuple("빈 오브젝트", 100, 20.24f);
	
	// std::get을 이용해서 값을 가져와야 해요!
	std::string strObjectName = std::get<0>(objectInfo);
	int32       intValue      = std::get<1>(objectInfo);
	real32      realValue     = std::get<2>(objectInfo);

	// 가져온 값들을 출력해볼게요!
	printf("%s\t%d\t%f\n", strObjectName.c_str(), intValue, realValue);
#endif

	return EXIT_SUCCESS;
}