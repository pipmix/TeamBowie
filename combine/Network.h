#ifndef NETWORK_H
#define NETWORK_H








#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <fcntl.h>

#include <stdlib.h>
#include <stdio.h>
#include <sys/ioctl.h>

#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <netdb.h>



#include <string>
#include <iostream>

using namespace std;




class USocket {

public:
	USocket() {
		sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
		if (sock == 0)printf("Error opening socket");

	}
	~USocket() {
		close(sock);
	}

	void SendTo(const std::string& address, unsigned short port, const char* buffer, int len, int flags = 0) {
		sockaddr_in add;
		add.sin_family = AF_INET;
		add.sin_addr.s_addr = inet_addr(address.c_str());
		add.sin_port = htons(port);
		int ret = sendto(sock, buffer, len, flags, reinterpret_cast<sockaddr *>(&add), sizeof(add));
		if (ret < 0)printf("sendto failed");
	}
	void SendTo(sockaddr_in& address, const char* buffer, int len, int flags = 0) {
		iResult = sendto(sock, buffer, len, flags, (sockaddr*)&address, sizeof(address));
		if (iResult < 0)printf("sendto failed");
			
	}
	sockaddr_in RecvFrom(char* buffer, int len) {
		sockaddr_in from;
		socklen_t size = sizeof(from);
		iResult = recvfrom(sock, (char*)buffer, len, 0, (sockaddr*)&from, &size);
		if (iResult < 0)printf("recvfrom failed");

		buffer[iResult] = 0;
		return from;
	}
	void Bind(unsigned short port) {
		sockaddr_in add;
		add.sin_family = AF_INET;
		add.sin_addr.s_addr = htonl(INADDR_ANY);
		add.sin_port = htons(port);

		iResult = bind(sock, reinterpret_cast<sockaddr *>(&add), sizeof(add));
		if (iResult < 0)printf("Bind failed");

	}

private:

	socklen_t sock;
	socklen_t iResult;
};



#endif
