#pragma once
#include "bEngine.h"

namespace b
{
	using namespace b::math;

	enum class eKeyCode
	{
		Q, W, E, R, T, Y, U, I, O, P,
		A, S, D, F, G, H, J, K, L,
		Z, X, C, V, B, N, M,

		UP, DOWN, LEFT, RIGHT, SPACE,
		LBUTTON, RBUTTON,
		END,
	};

	enum class eKeyState
	{
		Down,
		Pressed,
		Up,
		None,
	};

	class Input
	{
	public:
		struct Key
		{
			eKeyCode key;
			eKeyState state;
			bool bPressed;
		};

		static void Initialize();
		static void Update();
		static void Render(HDC hdc);

		// inline 함수는 하무가 여러 번 호출되어 발생하는 오버헤드를 줄이기 위해 사용
		// 함수를 호출하는 대신 함수가 호출되는 곳마다 함수의 코드를 복사해 넣어주는 방식
		// 컴파일러가 코드를 컴파일하면 모든 inline 함수가 in-place되어 확장됨
		// 단점으로 inline 함수가 길거나  inline 함수를 여러 번 호출하는 경우 컴파일된 코드르 약간 더 크게 만들 수 있다.
		// inline은 권장 사항으로 컴파일러가 inline을 무시할 수 있고, 반대로 inline화 시킬 수도 있다.
		inline static eKeyState GetKeyState(eKeyCode keyCode)
		{
			return mKeys[(UINT)keyCode].state;
		}

		// __forceinline은 컴파일러의 비용/이익 분석을 무시하고 프로그래머의 판단에 의존한다. 즉, 강제로 inline시키는 것
		static __forceinline bool GetKey(eKeyCode keyCode)
		{
			// 키를 누르는 시간만큼 true 반환
			return mKeys[static_cast<UINT>(keyCode)].state == eKeyState::Pressed;
		}

		static __forceinline bool GetKeyDown(eKeyCode keyCode)
		{
			// 키를 눌렀을 때 한 번 true 반환
			return mKeys[static_cast<UINT>(keyCode)].state == eKeyState::Down;
		}

		static __forceinline bool GetKeyUp(eKeyCode keyCode)
		{
			// 키를 뗐을 때 한 번 true 반환
			return mKeys[static_cast<UINT>(keyCode)].state == eKeyState::Up;
		}

		static __forceinline Vector2 GetMousePos() { return mMousePos; }

		static __forceinline Vector3 GetMousePosToWorld();

	private:
		static std::vector<Key> mKeys;
		static Vector2 mMousePos;
	};
}

