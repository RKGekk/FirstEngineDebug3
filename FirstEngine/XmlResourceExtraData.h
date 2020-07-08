#pragma once

#include "IResourceExtraData.h"
#include "tinyxml.h"

class XmlResourceExtraData : public IResourceExtraData {
    TiXmlDocument m_xmlDocument;

public:
    virtual std::string VToString();
    void ParseXml(char* pRawBuffer);
    TiXmlElement* GetRoot(void);
};