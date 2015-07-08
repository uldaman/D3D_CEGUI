#pragma once
#include <iostream>
#include <string>
#include "tinyxml.h"
//#pragma comment(lib,"tinyxml.lib")
#ifdef _DEBUG
#pragma comment(lib,"tinyxml_debug.lib")
#else
#pragma comment(lib,"tinyxml_release.lib")
#endif
#include <list>
#include <windows.h>
#include <vector>

struct _Xml {
    std::string KeyName;
    std::string Val;
};

class CXml {
public:
    CXml(void);
    ~CXml(void);
public:
    static BOOL FindXmlKeyFlag(std::vector<std::string> &arrFindXmlKeyName, TiXmlElement* Level);
    static void RecursiveTraversal(std::list<_Xml> &lAllVal, TiXmlElement* Level);
    static void RecursiveXml(std::list<_Xml> &lAllVal, std::vector<std::string> &arrFindXmlKeyName, TiXmlElement* Level);
    static int  DeadXml(std::list<_Xml> &lAllVal, std::vector<std::string> &arrFindXmlKeyName, std::string StrXmlPath);
};