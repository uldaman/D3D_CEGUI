#pragma once
#include <windows.h>
#include <string>
#include <list>

typedef struct NEAR_OBJECT {
    std::string strNpcName;
    int nNpcID;
    float fNpcPointX;
    float fNpcPointY;
} NearObject, *pNearObject;

class CNearObject {
public:
    CNearObject();
    ~CNearObject();
    static std::string GetObjectName(int nAddr);

    void initNear();      // 初始化附近对象
    std::list<NearObject> m_near_object;  // 附近的对象
    void Interactive(int nID); // 交互(对话)

protected:
    void allotObject(int nKey);
    
};