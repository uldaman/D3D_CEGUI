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

    void initNear();      // ��ʼ����������
    std::list<NearObject> m_near_object;  // �����Ķ���
    void Interactive(int nID); // ����(�Ի�)

protected:
    void allotObject(int nKey);
    
};