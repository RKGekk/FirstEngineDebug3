#include "XmlResourceLoader.h"
#include "XmlResourceExtraData.h"
#include "ResCache.h"

bool XmlResourceLoader::VLoadResource(char* rawBuffer, unsigned int rawSize, std::shared_ptr<ResHandle> handle) {
    if (rawSize <= 0)
        return false;

    std::shared_ptr<XmlResourceExtraData> pExtraData = std::shared_ptr<XmlResourceExtraData>(new XmlResourceExtraData());
    pExtraData->ParseXml(rawBuffer);

    handle->SetExtra(std::shared_ptr<XmlResourceExtraData>(pExtraData));

    return true;
}

TiXmlElement* XmlResourceLoader::LoadAndReturnRootXmlElement(const char* resourceString, std::shared_ptr<ResCache> ResCacheHandle) {
    Resource resource(resourceString);
    std::shared_ptr<ResHandle> pResourceHandle = ResCacheHandle->GetHandle(&resource);  // this actually loads the XML file from the zip file
    std::shared_ptr<XmlResourceExtraData> pExtraData = std::static_pointer_cast<XmlResourceExtraData>(pResourceHandle->GetExtra());
    return pExtraData->GetRoot();
}