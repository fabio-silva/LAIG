#pragma comment(lib, "ws2_32.lib")

#ifndef _WINDOWS_
#include <winsock.h>
#endif

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <iostream>

using namespace std;

class Client
{
protected:
	WORD versionRequested;
	WSADATA data;
	SOCKET sock;
	struct sockaddr_in server;
	struct hostent *hp;
	char buf[1024];


public:
	Client(int port, char *host);
	~Client();
	void sendData(char *data);
	char *receiveData();
};