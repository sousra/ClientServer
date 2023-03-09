#pragma comment(lib, "ws2_32.lib")
#include <iostream>
#include <cstdio>
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

	SOCKET connection = socket(AF_INET, SOCK_STREAM, NULL); // creates socket
	if (connect(connection, (SOCKADDR*)&addr, addrSize) != 0) { // connects client to server
		std::cout << "sever connecting error\n";
		return 1;
	}
	else {
		std::cout << "client is connected to sever\n";
		while (true) {
			char msg[1024];
			std::cout << "message: ";
			fgets(msg, 1024, stdin);
			msg[strlen(msg) - 1] = '\0'; // deletes \n symbol from msg
			send(connection, msg, strlen(msg) + 1, NULL);
		}
	}

	return 0;
}