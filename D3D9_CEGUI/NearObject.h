#pragma once
#include <windows.h>
#include <string>
#include <vector>
#include <list>

typedef struct NEAR_OBJECT {
    std::string strNpcName;
    int nNpcID;
    float fNpcPointX;
    float fNpcPointY;
} NearObject, *pNearObject;

typedef struct GLOWING_ARTICLE {
    float fNpcPointX;
    float fNpcPointY;
    float fNpcPointZ;
} GlowingArticle, *PGlowingArticle;

class CNearObject {
public:
    CNearObject();
    ~CNearObject();
    static std::string GetObjectName(int nAddr);

    void initNear();      // ��ʼ����������
    std::list<NearObject> m_near_object;  // �����Ķ���
    void Interactive(int nID); // ����(�Ի�)
    void GetGlowingArticle(/*float& fPointX, float& fPointY, float& fPointZ*/);

    std::vector<GlowingArticle> GetGlowingArticleInfo() { //��ȡ������Ʒ�б�
        return m_glowingArticle_vector;
    }

protected:
    std::vector<GlowingArticle> m_glowingArticle_vector;
    void allotObject(int nKey);
    
};