//读取内存
template<typename Type>
BOOL CMartin::ReadPtrData(DWORD beginAddr, std::string strFormat, OUT Type& outPut, int count, int second) {
    std::string strBuffer = "Debug: ";
    std::string strErr = " --> 出现错误";

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

    //提示出错信息
    strBuffer += strFormat;
    strBuffer += strErr;
    OutputDebugString(strBuffer.c_str());

    return FALSE;
}