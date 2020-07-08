#pragma once

#include <memory>
#include <string>
#include <vector>
#include <list>
#include <map>

#include "Resource.h"
#include "IResourceFile.h"
#include "ResHandle.h"
#include "DefaultResourceLoader.h"
#include "stringUtility.h"
#include "ResHandle.h"

class IResourceLoader;

class ResCache {
	friend class ResHandle;

	std::list<std::shared_ptr<ResHandle>>				m_lru;				// lru list
	std::map<std::string, std::shared_ptr<ResHandle>>	m_resources;
	std::list<std::shared_ptr<IResourceLoader>>			m_resourceLoaders;

	IResourceFile* m_file;

	unsigned int			m_cacheSize;			// total memory size
	unsigned int			m_allocated;			// total memory allocated

protected:

	bool MakeRoom(unsigned int size);
	char* Allocate(unsigned int size);
	void Free(std::shared_ptr<ResHandle> gonner);

	std::shared_ptr<ResHandle> Load(Resource* r);
	std::shared_ptr<ResHandle> Find(Resource* r);
	void Update(std::shared_ptr<ResHandle> handle);

	void FreeOneResource();
	void MemoryHasBeenFreed(unsigned int size);

public:
	ResCache(const unsigned int sizeInMb, IResourceFile* file);
	virtual ~ResCache();

	bool Init();

	void RegisterLoader(std::shared_ptr<IResourceLoader> loader);

	std::shared_ptr<ResHandle> GetHandle(Resource* r);

	int Preload(const std::string pattern, void (*progressCallback)(int, bool&), std::shared_ptr<ResCache> resCacheHandle);
	std::vector<std::string> Match(const std::string pattern);

	void Flush(void);

	bool IsUsingDevelopmentDirectories(void) const;

};