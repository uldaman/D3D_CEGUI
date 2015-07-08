#include "Xml.h"

CXml::CXml(void) {
}


CXml::~CXml(void) {
}


BOOL CXml::FindXmlKeyFlag(std::vector<std::string> &arrFindXmlKeyName, TiXmlElement* Level) {
    if (arrFindXmlKeyName.empty()) {
        return FALSE;
    }
    for (auto& v : arrFindXmlKeyName) {
        if (v.find(Level->Value()) != std::string::npos) {
            return TRUE;
        }
    }
    return FALSE;
}

void CXml::RecursiveXml(std::list<_Xml> &lAllVal, std::vector<std::string> &arrFindXmlKeyName, TiXmlElement* Level) {
    if (Level != NULL) {
        if (FindXmlKeyFlag(arrFindXmlKeyName, Level))
            RecursiveTraversal(lAllVal, Level);
        RecursiveXml(lAllVal, arrFindXmlKeyName, Level->FirstChildElement());
        RecursiveXml(lAllVal, arrFindXmlKeyName, Level->NextSiblingElement());
    }
}

void CXml::RecursiveTraversal(std::list<_Xml> &lAllVal, TiXmlElement* Level) {
    _Xml _PushInfo;
    _PushInfo.KeyName = Level->Value();
    _PushInfo.Val = Level->GetText();
    lAllVal.push_back(_PushInfo);
}

int CXml::DeadXml(std::list<_Xml> &lAllVal, std::vector<std::string> &arrFindXmlKeyName, std::string StrXmlPath) {
    TiXmlDocument doc;
    doc.LoadFile(StrXmlPath.c_str());
    //    doc.Print();       
    TiXmlElement* firstLevel = doc.RootElement();

    /*
    某些情况会用注释的这些内容
    比如：
    <menu name="123" num="456">
    </menu>

    TiXmlAttribute *firstAtt=firstLevel->FirstAttribute();
    while (firstAtt!=NULL)
    {
    cout<<firstAtt->Name()<<":"<<firstAtt->Value();
    firstAtt=firstAtt->Next();
    }
    */
    //SCI("firstLevel:%s",firstLevel->Value());
    RecursiveXml(lAllVal, arrFindXmlKeyName, firstLevel->FirstChildElement());
    return lAllVal.size();
}