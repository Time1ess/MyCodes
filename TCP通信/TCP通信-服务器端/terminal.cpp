#include <stdio.h>
#include <winsock.h>
#pragma comment(lib,"Ws2_32")
#pragma warning(disable:4996)
#define MAXDATASIZE 100 
#define MYPORT 7777  /*定义用户连接端口*/ 
#define BACKLOG 10  /*多少等待连接控制*/
bool onoff;
int mode;
bool cooling;
bool updown;
bool leftright;
int countdown;
int tempreture;

void resetall()
{
	mode = 0;
	onoff = false;
	cooling = true;
	updown = false;
	leftright = false;
	tempreture = 26;
	countdown = -1;
}

int main()
{
	resetall();
	int sockfd, new_fd;                                  /*定义套接字*/
	struct sockaddr_in my_addr;          /*本地地址信息 */
	struct sockaddr_in their_addr;        /*连接者地址信息*/
	int sin_size, numbytes;   char msg[10], buf[MAXDATASIZE];
	WSADATA ws;
	WSAStartup(MAKEWORD(2, 2), &ws);           //初始化Windows Socket Dll
	//建立socket
	if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
	{
		//如果建立socket失败，退出程序
		printf("socket error\n");
		exit(1);
	}
	//bind本机的MYPORT端口
	my_addr.sin_family = AF_INET;                     /* 协议类型是INET  */
	my_addr.sin_port = htons(MYPORT);            /* 绑定MYPORT端口*/
	my_addr.sin_addr.s_addr = INADDR_ANY;   /* 本机IP*/
	if (bind(sockfd, (struct sockaddr *)&my_addr, sizeof(struct sockaddr)) == -1)
	{
		//bind失败，退出程序
		printf("bind error\n");
		closesocket(sockfd);
		exit(1);
	}

	//listen，监听端口
	if (listen(sockfd, BACKLOG) == -1)
	{
		//listen失败，退出程序
		printf("listen error\n");
		closesocket(sockfd);
		exit(1);
	}
	printf("listen...");
	//等待客户端连接
	sin_size = sizeof(struct sockaddr_in);
	if ((new_fd = accept(sockfd, (struct sockaddr *)&their_addr, &sin_size)) == -1)
	{
		printf("accept error\n");
		closesocket(sockfd);
		exit(1);
	}
	printf("\naccept!\n");

	while (1) {
		if ((numbytes = recv(new_fd, buf, MAXDATASIZE, 0)) == -1)  continue;

		if (!strcmp(buf, "bye"))
		{
			//成功，关闭套接字

			closesocket(sockfd);
			closesocket(new_fd);
			return 0;
		}
		printf("%s %d", buf, strlen(buf));
		printf("\n");
	}
}