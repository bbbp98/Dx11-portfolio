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

		// inline �Լ��� �Ϲ��� ���� �� ȣ��Ǿ� �߻��ϴ� ������带 ���̱� ���� ���
		// �Լ��� ȣ���ϴ� ��� �Լ��� ȣ��Ǵ� ������ �Լ��� �ڵ带 ������ �־��ִ� ���
		// �����Ϸ��� �ڵ带 �������ϸ� ��� inline �Լ��� in-place�Ǿ� Ȯ���
		// �������� inline �Լ��� ��ų�  inline �Լ��� ���� �� ȣ���ϴ� ��� �����ϵ� �ڵ帣 �ణ �� ũ�� ���� �� �ִ�.
		// inline�� ���� �������� �����Ϸ��� inline�� ������ �� �ְ�, �ݴ�� inlineȭ ��ų ���� �ִ�.
		inline static eKeyState GetKeyState(eKeyCode keyCode)
		{
			return mKeys[(UINT)keyCode].state;
		}

		// __forceinline�� �����Ϸ��� ���/���� �м��� �����ϰ� ���α׷����� �Ǵܿ� �����Ѵ�. ��, ������ inline��Ű�� ��
		static __forceinline bool GetKey(eKeyCode keyCode)
		{
			// Ű�� ������ �ð���ŭ true ��ȯ
			return mKeys[static_cast<UINT>(keyCode)].state == eKeyState::Pressed;
		}

		static __forceinline bool GetKeyDown(eKeyCode keyCode)
		{
			// Ű�� ������ �� �� �� true ��ȯ
			return mKeys[static_cast<UINT>(keyCode)].state == eKeyState::Down;
		}

		static __forceinline bool GetKeyUp(eKeyCode keyCode)
		{
			// Ű�� ���� �� �� �� true ��ȯ
			return mKeys[static_cast<UINT>(keyCode)].state == eKeyState::Up;
		}

		static __forceinline Vector2 GetMousePos() { return mMousePos; }

		static __forceinline Vector3 GetMousePosToWorld();

	private:
		static std::vector<Key> mKeys;
		static Vector2 mMousePos;
	};
}

