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
			// 리소스 맵에서 데이터 탐색
			// 데이터가 있다면 해당 데이터를 반환하고 없다면 end를 반환
			std::map<std::wstring, Resource*>::iterator iter = mResources.find(key);

			// 찾으려는 데이터가 존재한다면 해당 타입으로 형변환 후 반환
			if (iter != mResources.end())
			{
				return dynamic_cast<T*>(iter->second);
			}

			// 데이터가 없다면 null 반환
			return nullptr;
		}

		template<typename T>
		static T* Load(const std::wstring& key, const std::wstring& path)
		{
			// 키 값으로 검색
			T* resource = Resources::Find<T>(key);

			if (resource != nullptr)
				return resource;

			// 해당 리소스가 없다면 강제 종료
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

