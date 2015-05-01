#include <stdio.h>
#include <stdio.h>
#include <winsock.h>
#pragma comment(lib,"Ws2_32")
#pragma warning(disable:4996)
#define PORT 6666                         /* 客户机连接远程主机的端口 */ 
#define MAXDATASIZE 100                     /* 每次可以接收的最大字节 */ 
int main()
{
	int sockfd, numbytes;
	char buf[MAXDATASIZE];
	char msg[MAXDATASIZE];
	char *argv = "111.117.104.77";
	struct sockaddr_in their_addr;        /* 对方的地址端口信息 */

	WSADATA ws; 
	WSAStartup(MAKEWORD(2, 2), &ws);         //初始化Windows Socket Dll
	if ((sockfd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) == -1)
	{
		//如果建立socket失败，退出程序
		printf("socket error\n");
		exit(1);
	}

	//连接对方
	their_addr.sin_family = AF_INET;                         /* 协议类型是INET  */
	their_addr.sin_port = htons(PORT);                       /* 连接对方PORT端口 */
	their_addr.sin_addr.s_addr = inet_addr(argv);        /* 连接对方的IP */
	if (connect(sockfd, (struct sockaddr *)&their_addr, sizeof(struct sockaddr)) == -1)
	{
		//如果连接失败，退出程序
		printf("connet error\n");
		closesocket(sockfd);
		exit(1);
	}
	printf("connet succeed\n");
	//strcpy(msg,"hellodavid");
	while (1){
		scanf("%s", msg);
		//发送数据
			if (send(sockfd,msg,MAXDATASIZE,0) == -1)
			{
				printf("send error");
				closesocket(sockfd);
				getchar();
				exit(1);
			}

			//接收数据，并打印出来
			if ((numbytes = recv(sockfd, buf, MAXDATASIZE, 0)) == -1)
			{
				//接收数据失败，退出程序
				printf("recv error\n");
				closesocket(sockfd);
				getchar();
				exit(1);
			}
			//buf[numbytes] = '\0';
			printf("received: %s\n", buf);
	}
	closesocket(sockfd);
	return 0;
}