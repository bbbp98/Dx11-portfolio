#pragma once
#include "bResource.h"

namespace b
{
	class Resources
	{
	public:
		template<typename T>
		static std::shared_ptr<T> Find(const std::wstring& key)
		{
			// ���ҽ� �ʿ��� ������ Ž��
			// �����Ͱ� �ִٸ� �ش� �����͸� ��ȯ�ϰ� ���ٸ� end�� ��ȯ
			std::map<std::wstring, std::shared_ptr<Resource>>::iterator iter = mResources.find(key);

			// ã������ �����Ͱ� �����Ѵٸ� �ش� Ÿ������ ����ȯ �� ��ȯ
			if (iter != mResources.end())
			{
				return std::dynamic_pointer_cast<T>(iter->second);
			}

			// �����Ͱ� ���ٸ� null ��ȯ
			return nullptr;
		}

		template<typename T>
		static std::shared_ptr<T> Load(const std::wstring& key, const std::wstring& path)
		{
			// Ű ������ �˻�
			std::shared_ptr<T> resource = Resources::Find<T>(key);

			if (resource != nullptr)
				return resource;

			// �ش� ���ҽ��� ���ٸ� ���� ����
			resource = std::make_shared<T>();
			if (FAILED(resource->Load(path)))
			{
				assert(false);
				return nullptr;
			}

			resource->SetKey(key);
			resource->SetPath(path);
			mResources.insert(std::make_pair(key, resource));

			return std::dynamic_pointer_cast<T>(resource);
		}

		template<typename T>
		static void Insert(const std::wstring& key, std::shared_ptr<T> resource)
		{
			mResources.insert(std::make_pair(key, resource));
		}


	private:
		static std::map<std::wstring, std::shared_ptr<Resource>> mResources;
	};
}

