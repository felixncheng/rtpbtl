#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>
#include <signal.h>
#include "transfer.h"
#include "utils.h"

void *monitor(void *ssize);

long total = 0;
long long begin = 0;

/* Signal Handler for SIGINT */
void sigintHandler(int sig_num)
{
    double end = (double)timeInMilliseconds() / 1000;
    int interval = end - begin;
    char fmt_str[50];
    throughput(total, 0.0, interval, fmt_str);
    printf("%s\n", fmt_str);
    exit(0);
}

int main(int argc, char *argv[])
{
    // 判断参数
    if (argc != 4)
    {
        perror("usage: appclient server_ip server_port time\n");
        exit(1);
    }
    printf("%-10s\t%-10s\t%-10s\n", "Interval", "Transfer", "Bandwidth");
    begin = (double)timeInMilliseconds() / 1000;
    signal(SIGINT, sigintHandler);
    //  创建TCP套接字
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == 0)
    {
        perror("Can't allocate sockfd");
        exit(1);
    }
    // 配置服务器套接字地址
    struct sockaddr_in serveraddr;
    int port = atoi(argv[2]);
    memset(&serveraddr, 0, sizeof(serveraddr));
    serveraddr.sin_family = AF_INET;
    serveraddr.sin_port = htons(port);
    if (inet_pton(AF_INET, argv[1], &serveraddr.sin_addr) < 0)
    {
        perror("IPaddress Convert Error");
        exit(1);
    }
    // 建立连接
    if (connect(sockfd, (const struct sockaddr *)&serveraddr, sizeof(serveraddr)) < 0)
    {
        perror("Connect Error");
        exit(1);
    }

    // 发送数据
    char data[DATA_SIZE] = {0};
    pthread_t t1;
    pthread_create(&t1, NULL, monitor, NULL);
    time_t begin;
    time(&begin);
    long until = (long)begin + atoi(argv[3]);
    int ss;
    long long s = 0;
    while (until > (long)time(NULL))
    {
        if ((ss = send(sockfd, data, DATA_SIZE, 0)) == -1)
        {
            perror("Send error");
            exit(-1);
        }
        total += ss;
        s += ss;
    }
    close(sockfd);
    char fmt_str[50];
    double end = (double)timeInMilliseconds() / 1000;
    double interval = end - begin;
    throughput(total, 0, interval, fmt_str);
    printf("%s\n", fmt_str);
    return 0;
}

void *monitor(void *ssize)
{
    char fmt_str[50];
    double t = 0;
    long ss = 0;
    long long tt = 0;
    while (1)
    {
        sleep(1);
        t++;
        ss = total - tt;
        tt += ss;
        throughput(ss, t - 1, t, fmt_str);
        printf("%s\n", fmt_str);
    }
}