#pragma once
#include "bResource.h"

namespace b
{
	class Resources
	{
	public:
		template<typename T>
		static T* Find(const std::wstring& key)
		{
			// ���ҽ� �ʿ��� ������ Ž��
			// �����Ͱ� �ִٸ� �ش� �����͸� ��ȯ�ϰ� ���ٸ� end�� ��ȯ
			std::map<std::wstring, Resource*>::iterator iter = mResources.find(key);

			// ã������ �����Ͱ� �����Ѵٸ� �ش� Ÿ������ ����ȯ �� ��ȯ
			if (iter != mResources.end())
			{
				return dynamic_cast<T*>(iter->second);
			}

			// �����Ͱ� ���ٸ� null ��ȯ
			return nullptr;
		}

		template<typename T>
		static T* Load(const std::wstring& key, const std::wstring& path)
		{
			// Ű ������ �˻�
			T* resource = Resources::Find<T>(key);

			if (resource != nullptr)
				return resource;

			// �ش� ���ҽ��� ���ٸ� ���� ����
			resource = new T();
			if (FAILED(resource->Load(path)))
			{
				assert(false);
				return nullptr;
			}

			resource->SetKey(key);
			resource->SetPath(path);
			mResources.insert(std::make_pair(key, resource));

			return dynamic_cast<T*>(resource);
		}

		template<typename T>
		static void Insert(const std::wstring& key, T* resource)
		{
			mResources.insert(std::make_pair(key, resource));
		}

		static void Release()
		{
			for (auto pair : mResources)
			{
				delete pair.second;
				pair.second = nullptr;
			}
		}

	private:
		static std::map<std::wstring, Resource*> mResources;
	};
}

