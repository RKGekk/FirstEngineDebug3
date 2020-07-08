#include "XmlResourceExtraData.h"

void XmlResourceExtraData::ParseXml(char* pRawBuffer) {
    m_xmlDocument.Parse(pRawBuffer);
}

std::string XmlResourceExtraData::VToString() {
    return "XmlResourceExtraData";
}

TiXmlElement* XmlResourceExtraData::GetRoot(void) {
    return m_xmlDocument.RootElement();
}