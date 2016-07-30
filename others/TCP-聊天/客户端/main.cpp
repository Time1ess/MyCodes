#include <stdio.h>
#include <stdlib.h>
#include <winsock.h>
#pragma comment(lib,"Ws2_32")
#pragma warning(disable:4996)
#define SERVER_PORT 6666 //侦听端口
#define LISTEN_PORT 6667
int main()
{
	char addr[20];
	printf("Please enter address:");
	scanf("%s",addr);
	WORD wVersionRequested;
	WSADATA wsaData;
	int ret;
	SOCKET sClient,sListen, sServer; //连接套接字
	struct sockaddr_in saServer,saClient; //地址信息
	char *ptr;
	BOOL fSuccess = TRUE;
	//WinSock初始化
	wVersionRequested = MAKEWORD(2, 2); //希望使用的WinSock DLL的版本
	ret = WSAStartup(wVersionRequested, &wsaData);
	if (ret != 0)
	{
		printf("WSAStartup() failed!\n");
		return -1;
	}
	//确认WinSock DLL支持版本2.2
	if (LOBYTE(wsaData.wVersion) != 2 || HIBYTE(wsaData.wVersion) != 2)
	{
		WSACleanup();
		printf("Invalid WinSock version!\n");
		return -1;
	}
	//创建Socket,使用TCP协议
	sListen = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	sClient = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (sClient == INVALID_SOCKET)
	{
		WSACleanup();
		printf("socket() failed!\n");
		return -1;
	}
	//构建服务器地址信息
	saServer.sin_family = AF_INET; //地址家族
	saServer.sin_port = htons(SERVER_PORT); //注意转化为网络节序
	saServer.sin_addr.S_un.S_addr = inet_addr(addr);

	saClient.sin_family = AF_INET; //地址家族
	saClient.sin_port = htons(LISTEN_PORT); //注意转化为网络字节序
	saClient.sin_addr.S_un.S_addr = htonl(INADDR_ANY); //使用INADDR_ANY 指示任意地址


	//连接服务器
	ret = connect(sClient, (struct sockaddr *)&saServer, sizeof(saServer));
	ret = bind(sListen, (struct sockaddr *)&saClient, sizeof(saClient));
	if (ret == SOCKET_ERROR)
	{
		printf("connect() failed!\n");
		closesocket(sClient); //关闭套接字
		WSACleanup();
		return -1;
	}
	if (ret == SOCKET_ERROR)
	{
		printf("bind() faild! code:%d\n", WSAGetLastError());
		closesocket(sListen); //关闭套接字
		WSACleanup();
		getchar();
				getchar();
		return -1;
	}
	ret = listen(sListen, 5);
	int length=sizeof(saClient);
	sServer = accept(sListen, (struct sockaddr *)&saClient, &length);

	char buf[255];
	do
	{
		gets(buf);
		ret = send(sClient, (char *)&buf, sizeof(buf), 0);
		if (ret == SOCKET_ERROR)
		{
			printf("send() failed!\n");
		}
		ret = recv(sServer,buf, sizeof(buf), 0);
		printf("%s\n",buf);
	} while (ret != SOCKET_ERROR);
	closesocket(sClient); //关闭套接字
	WSACleanup();
}