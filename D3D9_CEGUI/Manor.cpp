#include "Manor.h"
#include "Role.h"
#include "Martin.h"
#include "Base.h"


void CManor::intoMyManor() {
    int nTheFirstManorId, nTheSecondManorId;
    int nRoleAddr = CRole::GetRoleAddr();
    martin->ReadPtrData(nRoleAddr + OFFSET_ROLE_FARM + 0x8, "获取 []庄园 ID 1]", nTheFirstManorId);
    martin->ReadPtrData(nRoleAddr + OFFSET_ROLE_FARM + 0xC, "获取 []庄园 ID 2]", nTheSecondManorId);

    DWORD dwPackage[30];
    RtlZeroMemory(&dwPackage, sizeof(dwPackage));
    dwPackage[0] = 0x00000033;
    dwPackage[5] = nTheFirstManorId;
    dwPackage[6] = nTheSecondManorId;
    CRole::SendPackage((DWORD)&dwPackage);
}

void CManor::leaveManor() {
    DWORD dwPackage[30];
    RtlZeroMemory(&dwPackage, sizeof(dwPackage));
    dwPackage[0] = 0x0000000F;
    dwPackage[4] = 0x00000001;
    CRole::SendPackage((DWORD)&dwPackage);
}

void CManor::UpgradeMushroom() {
    DWORD dwPackage[30];
    RtlZeroMemory(&dwPackage, sizeof(dwPackage));
    dwPackage[0] = 0x000002F2;
    dwPackage[5] = 0x00000003;
    CRole::SendPackage((DWORD)&dwPackage);
}
