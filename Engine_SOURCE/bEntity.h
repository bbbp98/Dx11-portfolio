#pragma once
#include "bEngine.h"

namespace b
{
	class Entity
	{
	public:
		Entity();
		// ����(virtual)�Լ��� �⺻ Ŭ���� ������ ����Ǿ� �Ļ� Ŭ������ ���� �����ǵǴ� ��� �Լ�
		// ���� �ð��� �Լ��� �������� �����ϴµ� �ַ� ���
		// ���� �Լ��� ��Ģ
		// 1. Ŭ������ public ���ǿ� ����
		// 2. ���� �Լ��� static�� �� ����, �ٸ� Ŭ������ friend�� �� �� ����.
		// 3. ���� �ð� �������� ��� ���� �⺻ Ŭ������ ������ �Ǵ� ������ ���� ����(access)�ؾ� �Ѵ�.
		// 4. ���� �Լ��� ��ȯ���� �Ű������� �⺻ Ŭ������ �Ļ� Ŭ�������� �����ؾ� �Ѵ�.
		// 5. Ŭ������ ���� �Ҹ��ڸ� ���� �� ������ ���� �����ڸ� ���� �� ����.
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

