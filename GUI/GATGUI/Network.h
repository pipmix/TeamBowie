#pragma once
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <WinSock2.h>
#include <WS2tcpip.h>
#include <system_error>
#include <string>
#include <iostream>
#pragma comment (lib, "Ws2_32.lib")
using namespace std;

#define _WINSOCK_DEPRECATED_NO_WARNINGS


struct js_event {
	unsigned int    time;
	short           value;
	unsigned char   type;
	unsigned char   number;
};


class Network {

public:
	Network();
	~Network();
private:
	WSAData data;


};

class USocket {

public:
	USocket();
	~USocket();

	void SendTo(string& address, unsigned short port, const char* buffer, int len);
	void SendTo(sockaddr_in& address, const char* buffer, int len);
	sockaddr_in RecvFrom(char* buffer, int len);
	void Bind(unsigned short port);

private:

	SOCKET sock;
	int iResult;
	u_long iMode;
};