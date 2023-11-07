// client : implementation file
// 서버(Server.cpp)와 클라이언트(Client.cpp)가 연결되면
// 서버로 hello메시지 보내고 서버에서 메시지 받아 bye출력함

#include   <winsock.h>
#include   <stdio.h>
//#define   SERV_HOST_ADDR "1.247.67.186"
//#define   SERV_HOST_ADDR "192.168.0.6"
#define   SERV_HOST_ADDR "127.0.0.1"
#define SERV_TCP_PORT 12345

int main(void)
{
    int  sockfd;
    struct sockaddr_in serv_addr;
    char buffer[100];
    WSADATA wsa;

    if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0) return -1;

    /* Open a TCP socket(an Internet stream socket). */
    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
        printf("client :  can't open stream socket");

    //   bzero((char*)&serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = inet_addr(SERV_HOST_ADDR);
    serv_addr.sin_port = htons(SERV_TCP_PORT);

    /* Connect to the server */
    if (connect(sockfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0)
        printf("client: can't connect to server");

    //send(sockfd, buffer, sizeof(buffer), 0);
    send(sockfd, "hello", sizeof("hello"), 0);
    recv(sockfd, buffer, 100, 0);
    printf("%s \n", buffer);
    return 0;
}