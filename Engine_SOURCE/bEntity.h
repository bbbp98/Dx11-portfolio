#pragma once
#include "bEngine.h"

namespace b
{
	class Entity
	{
	public:
		Entity();
		// 가상(virtual)함수는 기본 클래스 내에서 선언되어 파생 클래스에 의해 재정의되는 멤버 함수
		// 실행 시간에 함수의 다형성을 구현하는데 주로 사용
		// 가상 함수의 규칙
		// 1. 클래스의 public 섹션에 선언
		// 2. 가상 함수는 static일 수 없고, 다른 클래스의 friend가 될 수 없다.
		// 3. 실행 시간 다형성을 얻기 위해 기본 클래스의 포인터 또는 참조를 통해 접근(access)해야 한다.
		// 4. 가상 함수의 반환형과 매개변수는 기본 클래스와 파생 클래스에서 동일해야 한다.
		// 5. 클래스는 가상 소멸자를 가질 수 있지만 가상 생성자를 가질 수 없다.
		virtual ~Entity();

		void SetName(const std::wstring& name) { mName = name; }
		std::wstring& GetName() { return mName; }
		void SetID(UINT64 id) { mID = id; }
		UINT64 GetID() { return mID; }

	private:
		std::wstring mName;
		UINT64 mID;
	};
}

