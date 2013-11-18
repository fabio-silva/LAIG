#include "Client.h"

Client::Client(int port, char *host)
{
	versionRequested = MAKEWORD(1,1);

	if(WSAStartup(versionRequested, &data) == 0)
	{
		LOBYTE(data.wHighVersion);
		HIBYTE(data.wHighVersion);
	}

	else 
	{
		cout << "Bad Version " << endl;
		WSACleanup();
		exit(1);
	}

	sock = socket(AF_INET, SOCK_STREAM, 0);

	if(sock == INVALID_SOCKET)
	{
		cout << "Error opening socket" << endl;
		exit(1);
	}

	setbuf(stdout, NULL);

	server.sin_family = AF_INET;

	hp = gethostbyname(host);

	if(hp == NULL)
	{
		cout << "Error getting host name" << endl;
		exit(1);
	}

	memcpy((char*)&server.sin_addr, (char*)hp->h_addr, hp->h_length);

	server.sin_port = htons((short)port);

	if(connect(sock, (struct sockaddr*)&server, sizeof(server)) == SOCKET_ERROR)
	{
		cout << "Error connecting stream socket" << endl;
		exit(1);
	}
}

Client::~Client()
{
	if(closesocket(sock) == SOCKET_ERROR) cout << "Error closing socket " << endl;
}

void Client::sendData(char *data)
{
	if(send(sock, data, strlen(data)+1, 0) == SOCKET_ERROR) cout << "Error writing on stream socket" << endl;
}

char *Client::receiveData()
{
	int n;

	memset((char*)buf, 0, sizeof(buf));

	while((n = recv(sock, buf, 1024, 0)) < 0);

	return buf;
}