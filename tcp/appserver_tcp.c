#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "transfer.h"
#include "utils.h"

void recvdata(int sockfd);
void print_socket(int sockfd);

int main(int argc, char *argv[])
{
    // 判断参数
    if (argc != 2)
    {
        perror("usage: appserver [server_port]\n");
        exit(1);
    }
    //  创建TCP套接字
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == 0)
    {
        perror("Can't allocate sockfd");
        exit(1);
    }

    // 配置服务器套接字地址
    struct sockaddr_in clientaddr, serveraddr;
    int port = atoi(argv[1]);
    memset(&serveraddr, 0, sizeof(serveraddr));
    serveraddr.sin_family = AF_INET;
    serveraddr.sin_addr.s_addr = htonl(INADDR_ANY);
    serveraddr.sin_port = htons(port);

    // 绑定套接字与地址
    if (bind(sockfd, (const struct sockaddr *)&serveraddr, sizeof(serveraddr)) == -1)
    {
        perror("Bind Error");
        exit(1);
    }

    // 开始监听
    if (listen(sockfd, 128) == -1)
    {
        perror("Listen Error");
        exit(1);
    }
    printf("%-10s\t%-10s\t%-10s\n", "Interval", "Transfer", "Bandwidth");
    while (1)
    {
        socklen_t addrlen = sizeof(clientaddr);
        int connfd = accept(sockfd, (struct sockaddr *)&clientaddr, &addrlen);
        if (connfd == -1)
        {
            perror("Connect Error");
            exit(1);
        }
        print_socket(connfd);
        recvdata(connfd);
        close(connfd);
    }

    close(sockfd);
    return 0;
}
void print_socket(int sockfd)
{
    struct sockaddr_in sa;
    socklen_t len = sizeof(sa);

    if (getsockname(sockfd, (struct sockaddr *)&sa, &len) != 0)
    {
        perror("Get local address error");
        exit(-1);
    }
    char *local_ip = inet_ntoa(sa.sin_addr);
    int local_port = htons(sa.sin_port);

    if (getpeername(sockfd, (struct sockaddr *)&sa, &len) != 0)
    {
        perror("Get peer address error");
        exit(-1);
    }
    char *peer_ip = inet_ntoa(sa.sin_addr);
    int peer_port = htons(sa.sin_port);

    printf("local %s port %d connected with %s port %d\n", local_ip, local_port, peer_ip, peer_port);
}
void recvdata(int sockfd)
{
    char data[DATA_SIZE] = {0};
    int rs;
    long long rsize = 0;
    double begin, end;
    begin = (double)timeInMilliseconds() / 1000;
    while ((rs = recv(sockfd, data, DATA_SIZE, 0)) > 0)
    {
        rsize += rs;
    }
    end = (double)timeInMilliseconds() / 1000;
    double interval = end - begin;
    char fmt_str[50];
    throughput(rsize, 0.0, interval, fmt_str);
    printf("%s\n", fmt_str);
}