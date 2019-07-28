#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#define ERR_EXIT(m) \
    do { \
        perror(m);\
        exit(EXIT_FAILURE);\
    }while(0)

void do_service(int sockfd);
typedef struct {
    int datalen;
    char buf[1000];
}train_t;
int main(int argc, const char *argv[])
{
    if(argc != 3)
    {
        printf("error args\n");
        return -1;
    }
    int peerfd = socket(PF_INET, SOCK_STREAM, 0);
    if(peerfd == -1)
        ERR_EXIT("socket");

    struct sockaddr_in addr;
    memset(&addr, 0, sizeof addr);
    addr.sin_family = AF_INET;
    //addr.sin_addr.s_addr = inet_addr("192.168.4.169"); //localhost
    addr.sin_addr.s_addr = inet_addr(argv[1]); //localhost
    addr.sin_port = htons(atoi(argv[2]));
    socklen_t len = sizeof addr;
    if(connect(peerfd, (struct sockaddr*)&addr, len) == -1)
        ERR_EXIT("Connect");

	char buff[1024] = {0};
	read(peerfd, buff, sizeof(buff));
	printf("%s\n", buff);

    do_service(peerfd);
    return 0;
}



void do_service(int sockfd)
{
    char recvbuf[1000] = {0};
    char sendbuf[1024] = {0};
    while(1)
    {
        fgets(sendbuf, sizeof sendbuf,stdin);
        printf("sendbuf : %s\n", sendbuf);
        write(sockfd, sendbuf, strlen(sendbuf));

        //read
        //小火车接收数据
        //train_t train;
        int datalen;

        int nread = read(sockfd, &datalen, 4);

        if(nread == -1)
        {
            if(errno == EINTR)
                continue;
            ERR_EXIT("read");
        }
        else if(nread == 0)
        {
            printf("server close!\n");
            close(sockfd);
            exit(EXIT_SUCCESS);
        }
        read(sockfd, recvbuf, datalen);
        printf("receive msg : %s",recvbuf);

        memset(recvbuf, 0, sizeof recvbuf);
        memset(sendbuf, 0, sizeof sendbuf);
    }
}




