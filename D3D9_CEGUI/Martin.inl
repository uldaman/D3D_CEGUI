//��ȡ�ڴ�
template<typename Type>
BOOL CMartin::ReadPtrData(DWORD beginAddr, std::string strFormat, OUT Type& outPut, int count, int second) {
    std::string strBuffer = "Debug: ";
    std::string strErr = " --> ���ִ���";

    int tmp_count = 0;
    while (tmp_count < count) {
        if (0 != IsBadReadPtr((CONST VOID*)beginAddr, sizeof(Type))) {
            tmp_count++;
        } else {
            outPut = *(Type*)beginAddr;
            return TRUE;
        }
        Sleep(second);
    }

    //��ʾ������Ϣ
    strBuffer += strFormat;
    strBuffer += strErr;
    OutputDebugString(strBuffer.c_str());

    return FALSE;
}