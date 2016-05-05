#include "Network.h"

Network::Network() {
		if (WSAStartup(MAKEWORD(2, 2), &data) != 0)printf("WSAStartup Failed");

	
	}
Network::~Network() {
		WSACleanup();
	}




USocket::USocket() {
	iMode = 1;
	sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	if (sock == INVALID_SOCKET)printf("Error opening socket");
	iResult = ioctlsocket(sock, FIONBIO, &iMode);

}
USocket::~USocket() {
	closesocket(sock);
}

void USocket::SendTo(string& address, unsigned short port, const char* buffer, int len) {
	sockaddr_in add;
	add.sin_family = AF_INET;
	add.sin_addr.s_addr = inet_addr(address.c_str());
	add.sin_port = htons(port);
	int ret = sendto(sock, buffer, len, 0, reinterpret_cast<SOCKADDR *>(&add), sizeof(add));
	if (ret < 0)printf("sendto failed");
}
void USocket::SendTo(sockaddr_in& address, const char* buffer, int len) {
	iResult = sendto(sock, buffer, len, 0, reinterpret_cast<SOCKADDR *>(&address), sizeof(address));
	if (iResult < 0)
		throw std::system_error(WSAGetLastError(), std::system_category(), "sendto failed");
}
sockaddr_in USocket::RecvFrom(char* buffer, int len) {
	sockaddr_in from;
	int size = sizeof(from);
	iResult = recvfrom(sock, buffer, len, 0, reinterpret_cast<SOCKADDR *>(&from), &size);
	if (iResult < 0)printf("recvfrom failed");

	buffer[iResult] = 0;
	return from;
}
void USocket::Bind(unsigned short port) {
	sockaddr_in add;
	add.sin_family = AF_INET;
	add.sin_addr.s_addr = htonl(INADDR_ANY);
	add.sin_port = htons(port);

	iResult = bind(sock, reinterpret_cast<SOCKADDR *>(&add), sizeof(add));
	if (iResult < 0)printf("Bind failed");

}

