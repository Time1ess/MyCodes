#include <stdio.h>
#include <winsock.h>
#include <string.h>
#pragma comment(lib,"Ws2_32")
#pragma warning(disable:4996)
#define MAXDATASIZE 100 
#define MYPORT 6666  /*定义用户连接端口*/ 
#define SENDPORT 6667
#define BACKLOG 10  /*多少等待连接控制*/ 
int main()
{
	int sockfd, new_fd,socktt;                                  /*定义套接字*/
	struct sockaddr_in my_addr;          /*本地地址信息 */
	struct sockaddr_in their_addr;        /*连接者地址信息*/
	struct sockaddr_in terminal_addr;
	int sin_size, numbytes;   
	char msg[10], buf[MAXDATASIZE];
	char *PATHS = "255.255.255.255";

	
	WSADATA ws;
	WSAStartup(MAKEWORD(2, 2), &ws);           //初始化Windows Socket Dll
	//建立socket
	if ((sockfd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) == -1)
	{
		//如果建立socket失败，退出程序
		printf("socket error\n");
		getchar();
		exit(1);
	}

	if ((socktt = socket(AF_INET, SOCK_DGRAM, 0)) == -1)
	{
		//如果建立socket失败，退出程序
		printf("socket error\n");
		getchar();
		exit(1);
	}
	bool bbroadcast = true;
	setsockopt(socktt, SOL_SOCKET, SO_BROADCAST, (char*)&bbroadcast, sizeof(bool));

	//bind本机的MYPORT端口
	my_addr.sin_family = AF_INET;                     /* 协议类型是INET  */
	my_addr.sin_port = htons(MYPORT);            /* 绑定MYPORT端口*/
	my_addr.sin_addr.s_addr = htonl(INADDR_ANY);   /* 本机IP*/

	if (bind(sockfd, (struct sockaddr *)&my_addr, sizeof(struct sockaddr)) == -1)
	{
		//bind失败，退出程序
		printf("bind error\n");
		closesocket(sockfd);
		getchar();
		exit(1);
	}


	terminal_addr.sin_family = AF_INET;
	terminal_addr.sin_port = htons(SENDPORT);
	terminal_addr.sin_addr.s_addr = htonl(INADDR_BROADCAST);
	if (bind(socktt, (struct sockaddr *)&my_addr, sizeof(struct sockaddr)) == -1)
	{
		//bind失败，退出程序
		printf("terminal bind error\n");
		closesocket(sockfd);
		getchar();
		exit(1);
	}
     
	
	//listen，监听端口
	if (listen(sockfd, BACKLOG) == -1)
	{
		//listen失败，退出程序
		printf("listen error\n");
		closesocket(sockfd);
		getchar();
		exit(1);
	}
	printf("listen...\n");
	//等待客户端连接
	sin_size = sizeof(struct sockaddr_in);

	if ((new_fd = accept(sockfd, (sockaddr*)&their_addr, &sin_size)) == -1)
	{
		printf("accept error\n");
		closesocket(sockfd);
		getchar();
		exit(1);
	}

	while (1) 
	{
		if ((numbytes = recv(new_fd, buf, MAXDATASIZE, 0)) == -1)  continue;

		printf("%s", buf);
		printf("\n");
		sprintf(msg, "%d", strlen(buf));

		if (send(new_fd, msg, MAXDATASIZE, 0) == -1)
		{
			printf("send ERROR.\n");
			closesocket(sockfd);
			closesocket(new_fd);
			getchar();
			return 0;
		}


		if (sendto(socktt, buf, MAXDATASIZE, 0, (SOCKADDR*)&terminal_addr, sizeof(SOCKADDR)) == -1)
		{
			printf("send error.\n");
			closesocket(sockfd);
			GetLastError();
			getchar();
			exit(1);
		}
		else
			printf("send succeed.\n");

		if (!strcmp(buf, "bye"))
		{
			//成功，关闭套接字

			closesocket(sockfd);
			closesocket(new_fd);
			closesocket(socktt);
			getchar();
			return 0;
		}
	}

}