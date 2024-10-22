#pragma once
#include "Singleton.h"
#include <unordered_map>

template<typename T>
class ResourceMgr : public Singleton<ResourceMgr<T>>
{
	friend Singleton<ResourceMgr<T>>();

protected:
	std::unordered_map<std::string, T*> resources;
	
	ResourceMgr() = default;
	~ResourceMgr() = default;
	
	ResourceMgr(const ResourceMgr&) = delete;
	ResourceMgr& operator=(const ResourceMgr&) = delete;

public:
	static T Empty;


	bool Load(const std::string& id)
	{
		if (resources.find(id) != resources.end())
			return false; // 로드 실패 했으니 false return
		
		T* resource = new T();
		bool succes = resource->loadFromFile(id);
		if (success)
		{
			resources.insert({id, resource }); 
		}
		else
		{
			delete resource;
		}

		return success;
	}

	bool Unload(const std::string& id)
	{
		auto it = resource.find(id);
		if (it == resources.end())
			return false;

		delete it->second;
		resources.erase(it);
		return true;
	}
	T& Get(const std::string& id)
	{
		auto it = resources.find(id);
		if (it == resources.end()
		{
			return Empty;
		}
		return *(it->second);
	}

};

template<typename T>
T ResourceMgr<T>::Empty;

