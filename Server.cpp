#pragma comment(lib, "ws2_32.lib")
#include <iostream>
#include <cstring>
#include <WinSock2.h>

#pragma warning(disable: 4996) // removes inet_addr() warning

int main(int argc, char** argv) {
	/* Connect winsock2.h library to process */
	WSAData wsaData;
	WORD DLLversion = MAKEWORD(2, 1);
	if (WSAStartup(DLLversion, &wsaData)) {
		std::cout << "WSAStartup error\n";
		return -1;
	}

	SOCKADDR_IN addr; // create socket address
	int addrSize = sizeof(addr);
	addr.sin_addr.s_addr = inet_addr("127.0.0.1"); // put local address in the socket
	addr.sin_port = htons(1111);
	addr.sin_family = AF_INET;

	SOCKET sListen = socket(AF_INET, SOCK_STREAM, NULL); // create socket
	bind(sListen, (SOCKADDR*)&addr, addrSize); // bind address to socket
	listen(sListen, SOMAXCONN); // places a socket in a state in which it is listening for an incoming connection

	SOCKET newConnection;
	while (true) {
		newConnection = accept(sListen, (SOCKADDR*)&addr, &addrSize); // permits an incoming connection attempt on a socket
		if (newConnection == 0) {
			std::cout << "accept error\n";
		}
		else {
			char buf[1024];
			while (recv(newConnection, buf, 1024, NULL) != -1) {
				std::cout << buf << '\n';
			}
		}
	}

	return 0;
}