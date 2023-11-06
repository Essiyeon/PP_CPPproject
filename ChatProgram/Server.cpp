// ����(Server.cpp)�� Ŭ���̾�Ʈ(Client.cpp)�� ����Ǹ�
// ������ connected �޽��� ���, Ŭ���̾�Ʈ���Լ� �޽����ް�
// bye�� ũ��� �Բ� �޾ƿ� �޽��� ���

#include   <winsock.h>
#include   <stdio.h>
#define SERV_TCP_PORT 12345

int main(void)
{
    int  sockfd, newsock, ret;
    struct sockaddr_in serv_addr, cli_addr;
    int addrlen;
    char buffer[100];
    WSADATA wsa;

    if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0) {
        printf("Error");
        return -1;
    }

    /* Open a TCP socket(an Internet stream socket). */
    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        printf("socket error");
    }
    //   bzero((char*)&serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port = htons(SERV_TCP_PORT);

    ret = bind(sockfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr));
    if (ret == SOCKET_ERROR) {
        printf("BIND ERROR");
        return -1;
    }

    /* Waiting... */
    ret = listen(sockfd, 5);
    if (ret == SOCKET_ERROR) {
        printf("error: listen");
        return -1;
    }

    printf("Server: ready...\n");

    addrlen = sizeof(cli_addr);
    newsock = accept(sockfd, (struct sockaddr*)&cli_addr, &addrlen);
    if (newsock == INVALID_SOCKET) {
        printf("accept error");
        return -1;
    }
    else printf("Connected \n");

    printf("%d", sizeof("bye"));
    recv(newsock, buffer, 100, 0);
    printf("%s \n", buffer);

    send(newsock, "bye", sizeof("bye"), 0);
    return 0;
}