#include "SocketClient.h"
#include "DefMessage.h"
#include "Martin.h"


CSocketClient::CSocketClient(HWND hGame, BYTE minorVer /*= 2*/, BYTE majorVer /*= 2*/)
    :CInitSock(minorVer, majorVer) {
    USHORT nPort = 12589;	// �˷����������Ķ˿ں�

    // ���������׽���
    SOCKET sListen = ::socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (sListen == INVALID_SOCKET) {
        martin->Debug("socket ���������׽���ʧ�� INVALID_SOCKET");
        ExitProcess(0);
    }
    martin->Debug("socket ���������׽��ֳɹ�");

    sockaddr_in sin;
    RtlZeroMemory(&sin, sizeof(sockaddr_in));
    sin.sin_family = AF_INET;
    sin.sin_port = htons(nPort);
    sin.sin_addr.S_un.S_addr = inet_addr("127.0.0.1"); // �򱾵�����, ע��, ���� INADDR_ANY, ���Ƿ������õ�.

    // ���׽�����Ϊ����֪ͨ��Ϣ����
    if (::WSAAsyncSelect(sListen, hGame, WM_SOCKET, FD_CONNECT | FD_CLOSE | FD_READ) == SOCKET_ERROR) {
        martin->Debug("WSAAsyncSelect �󶨴���ʧ��");
        ExitProcess(0);
    }
    martin->Debug("WSAAsyncSelect �󶨴��ڳɹ�");

    // ���ӷ�����, ��Ϊ������ WSAAsyncSelect, ���� connect �ķ���ֵ��û������
    ::connect(sListen, (struct sockaddr*)&sin, sizeof(sin));
}