#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
// #include <time.h>

int main(int argc, char *argv[])
{
	int listenfd = 0
	int connfd = 0;
	struct sockaddr_in serverAddress;
	char sendBuffer[1025];

	listenfd = socket(AF_INET, SOCK_STREAM, 0);
	memset(&serverAddress, '0', sizeof(serverAddress));
	memset(sendBuffer, '0', sizeof(sendBuffer));

	serverAddress.sin_family = AF_INET;
	serverAddress.sin_addr.s_addr = htonl(INADDR_ANY);
	serverAddress.sin_port = htons(5000);

	bind(listenfd, (struct sockaddr*)&serverAddress, sizeof(serverAddress));
	listen(listenfd, 10);

	int x = 0;

	while(1)
	{
		connfd = accept(listenfd, (struct sockaddr*)NULL, NULL);

		x++;

		snprintf(sendBuffer, sizeof(sendBuffer), "Hello this is test send #%d\n", x);
		write(connfd, sendBuffer, strlen(sendBuffer));

		close(connfd);
		sleep(1);
	 }
}