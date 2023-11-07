// Server와 Client 간의 1:1 채팅코드
// 연속 채팅 안됨, 한 번에 하나씩
// 메시지를 수신해야지만 송신할 수 있음

#include <winsock.h>
#include <stdio.h>
#include <string.h>

#define SERV_HOST_ADDR "127.0.0.1"
#define SERV_TCP_PORT 12345

int main(void) {
    int sockfd;
    struct sockaddr_in serv_addr;
    char buffer[100];
    WSADATA wsa;

    if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
        return -1;

    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
        printf("client: can't open stream socket");

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = inet_addr(SERV_HOST_ADDR);
    serv_addr.sin_port = htons(SERV_TCP_PORT);

    if (connect(sockfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0)
        printf("client: can't connect to server");

    while (1) {
        printf("Client: ");
        gets_s(buffer);
        send(sockfd, buffer, sizeof(buffer), 0);

        recv(sockfd, buffer, sizeof(buffer), 0);
        printf("Server: %s\n", buffer);
    }

    return 0;
}
