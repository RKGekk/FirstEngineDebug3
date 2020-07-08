#pragma once

#include <memory>

#include "tinyxml.h"
#include "IResourceLoader.h"
#include "ResHandle.h"

class XmlResourceLoader : public IResourceLoader {
public:
    virtual bool VUseRawFile() { return false; }
    virtual bool VDiscardRawBufferAfterLoad() { return true; }
    virtual unsigned int VGetLoadedResourceSize(char* rawBuffer, unsigned int rawSize) { return rawSize; }
    virtual bool VLoadResource(char* rawBuffer, unsigned int rawSize, std::shared_ptr<ResHandle> handle);
    virtual std::string VGetPattern() { return "*.xml"; }

    // convenience function
    static TiXmlElement* LoadAndReturnRootXmlElement(const char* resourceString, std::shared_ptr<ResCache> ResCacheHandle);
};