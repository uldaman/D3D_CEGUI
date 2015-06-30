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

    void initNear();      // 初始化附近对象
    std::list<NearObject> m_near_object;  // 附近的对象
    void Interactive(int nID); // 交互(对话)
    void GetGlowingArticle(/*float& fPointX, float& fPointY, float& fPointZ*/);

    std::vector<GlowingArticle> GetGlowingArticleInfo() { //获取发包物品列表
        return m_glowingArticle_vector;
    }

protected:
    std::vector<GlowingArticle> m_glowingArticle_vector;
    void allotObject(int nKey);
    
};