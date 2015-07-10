#include "SocketClient.h"
#include "DefMessage.h"
#include "Martin.h"
#include "DataType.h"


CSocketClient::CSocketClient(HWND hGame, BYTE minorVer /*= 2*/, BYTE majorVer /*= 2*/)
    :CInitSock(minorVer, majorVer) {
    USHORT nPort = 12589;	// 此服务器监听的端口号

    // 创建监听套节字
    m_sListen = ::socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (m_sListen == INVALID_SOCKET) {
        martin->Debug("socket 创建监听套节字失败 INVALID_SOCKET");
        ExitProcess(0);
    }
    martin->Debug("socket 创建监听套节字成功");

    sockaddr_in sin;
    RtlZeroMemory(&sin, sizeof(sockaddr_in));
    sin.sin_family = AF_INET;
    sin.sin_port = htons(nPort);
    sin.sin_addr.S_un.S_addr = inet_addr("127.0.0.1"); // 向本地连接, 注意, 不是 INADDR_ANY, 这是服务器用的.

    // 将套接字设为窗口通知消息类型
    if (::WSAAsyncSelect(m_sListen, hGame, WM_SOCKET, FD_CONNECT | FD_CLOSE | FD_READ) == SOCKET_ERROR) {
        martin->Debug("WSAAsyncSelect 绑定窗口失败");
        ExitProcess(0);
    }
    martin->Debug("WSAAsyncSelect 绑定窗口成功");

    // 连接服务器, 因为调用了 WSAAsyncSelect, 所以 connect 的返回值将没有意义
    ::connect(m_sListen, (struct sockaddr*)&sin, sizeof(sin));
}

void CSocketClient::SendGameInfo(const char* szBuffer) {
    int nSize = sizeof(SOCKET_INFO);
    send(m_sListen, szBuffer, nSize, 0);
}