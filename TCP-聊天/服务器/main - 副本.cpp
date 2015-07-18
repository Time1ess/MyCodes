#include <stdio.h>
#include <winsock.h>
#pragma comment(lib,"Ws2_32")
#pragma warning(disable:4996)
#define SERVER_PORT 6666 //侦听端口
#define SEND_PORT 6667
int main()
{
	char addr[20];
	printf("Please enter address:");
	scanf("%s",addr);
	WORD wVersionRequested;
	WSADATA wsaData;
	int ret, nLeft, length;
	SOCKET sListen, sServer,sClient; //侦听套接字，连接套接字
	struct sockaddr_in saServer, saClient,saSend; //地址信息   
	char *ptr;//用于遍历信息的指针   
	//WinSock初始化
	wVersionRequested = MAKEWORD(2, 2); //希望使用的WinSock DLL 的版本
	ret = WSAStartup(wVersionRequested, &wsaData);
	if (ret != 0)
	{
		printf("WSAStartup() failed!\n");
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
	if (sListen == INVALID_SOCKET)
	{
		WSACleanup();
		printf("socket() faild!\n");
		return -1;
	}
	//构建本地地址信息
	saServer.sin_family = AF_INET; //地址家族
	saServer.sin_port = htons(SERVER_PORT); //注意转化为网络字节序
	saServer.sin_addr.S_un.S_addr = htonl(INADDR_ANY); //使用INADDR_ANY 指示任意地址

	saSend.sin_family = AF_INET; //地址家族
	saSend.sin_port = htons(SEND_PORT); //注意转化为网络节序
	saSend.sin_addr.S_un.S_addr = inet_addr(addr);


	//绑定
	ret = bind(sListen, (struct sockaddr *)&saServer, sizeof(saServer));
	if (ret == SOCKET_ERROR)
	{
		printf("bind() faild! code:%d\n", WSAGetLastError());
		closesocket(sListen); //关闭套接字
		WSACleanup();
		return -1;
	}

	//侦听连接请求
	ret = listen(sListen, 5);
	if (ret == SOCKET_ERROR)
	{
		printf("listen() faild! code:%d\n", WSAGetLastError());
		closesocket(sListen); //关闭套接字
		return -1;
	}

	printf("Waiting for client connecting!\n");
	printf("Tips: Ctrl+c to quit!\n");
	length = sizeof(saClient);
	sServer = accept(sListen, (struct sockaddr *)&saClient, &length);
	if (sServer == INVALID_SOCKET)
	{
		printf("accept() faild! code:%d\n", WSAGetLastError());
		closesocket(sListen); //关闭套接字
		WSACleanup();
		return -1;
	}



	ret = connect(sClient, (struct sockaddr *)&saSend, sizeof(saClient));
	if (ret == SOCKET_ERROR)
	{
		printf("connect() failed!\n");
		closesocket(sClient); //关闭套接字
		WSACleanup();
		return -1;
	}

	//阻塞等待接受客户端连接
	while (1)//循环监听客户端，永远不停止，所以，在本项目中，我们没有心跳包。
	{


		char receiveMessage[255];
			//接收数据
		ret = recv(sServer,receiveMessage, sizeof(receiveMessage), 0);
		if (ret == SOCKET_ERROR)
		{
			printf("recv() failed!\n");
			return -1;
		}
		printf("%s\n", receiveMessage);
		gets(receiveMessage);
		ret = send(sClient,receiveMessage, sizeof(receiveMessage), 0);
		if(ret==SOCKET_ERROR)
			printf("send error");
	}
	closesocket(sListen);
	closesocket(sServer);
	WSACleanup();
	return 0;
}