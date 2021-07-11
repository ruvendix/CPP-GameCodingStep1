// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// 이 저작물은 크리에이티브 커먼즈 저작자표시 4.0 국제 라이선스에 따라 이용할 수 있습니다.
// http://creativecommons.org/licenses/by/4.0/
//
// 의도적으로 무시할 경고 모음입니다.
// =====================================================================================
#pragma once

#pragma warning(disable:4100) // 참조자를 사용하지 않았다는 경고(기본형은 참조자 사용하지 않을 거니까 무시)
#pragma warning(disable:6011) // nullptr을 역참조했다는 경고(nullptr은 다른 걸로 관리할 거니까 무시)
#pragma warning(disable:6031) // 반환값을 무시했다는 경고(반환값이 항상 필요한 게 아니므로 무시)
#pragma warning(disable:6054) // 문자열이 종료문자로 끝나지 않을 수도 있다는 경고(종료문자 없는 문자열도 많으니 무시)
#pragma warning(disable:6387) // nullptr이 전달될 수 있다는 경고(_Notnull_을 앞에 붙여주면 되는데 귀찮아서 무시)
#pragma warning(disable:26495) // 변수를 항상 초기화해야 한다는 경고(생성자로 초기화될 수도 있으므로 무시)
#pragma warning(disable:26812) // enum을 정수값으로 사용했다는 경고(enum class는 처리가 귀찮아서 무시)
#pragma warning(disable:28020) // 표현식이 true가 아니라는 경고(RX_ASSERT와 충돌나는 거니까 무시)