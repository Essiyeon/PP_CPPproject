// Server와 Client 간의 1:1 채팅코드
// 연속 채팅 안됨, 하번에 하나씩
// 메시지를 수신해야지만 송신할 수 있음

#include <winsock.h>
#include <stdio.h>
#include <string.h>

#define SERV_TCP_PORT 12345

int main(void) {
    int sockfd, newsock, ret;
    struct sockaddr_in serv_addr, cli_addr;
    int addrlen;
    char buffer[100];
    WSADATA wsa;

    if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0) {
        printf("Error");
        return -1;
    }

    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        printf("socket error");
        return -1;
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port = htons(SERV_TCP_PORT);

    ret = bind(sockfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr));
    if (ret == SOCKET_ERROR) {
        printf("BIND ERROR");
        return -1;
    }

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
    else
        printf("Connected\n");

    while (1) {
        recv(newsock, buffer, sizeof(buffer), 0);
        printf("Client: %s\n", buffer);

        printf("Server: ");
        gets_s(buffer);
        send(newsock, buffer, sizeof(buffer), 0);
    }

    return 0;
}
