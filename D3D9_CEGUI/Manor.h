#pragma once
#include "Material.h"

/*-----------------------------------------------------------------------
 * ����: CManor
 * ˵��: ׯ԰��, ��������ׯ԰, ��ΪҪ�ɼ���Ʒ, ���Լ��� CMaterial ������
-----------------------------------------------------------------------*/
class CManor 
    : public CMaterial {
public:

    void intoMyManor(); // �����ҵ�ׯ԰
    void leaveManor(); // �뿪ׯ԰
    void UpgradeMushroom(); // ��������ľ��
};

