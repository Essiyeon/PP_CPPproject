// ������ ��� �޽����� �޾� �߰��ϸ� ������ Ŭ���̾�Ʈ���� ä�ð���
// Ŭ���̾�Ʈ �ڵ�� �������� N���� ���� �����Ͽ� N���� ä�ð���
// �޽��� �������۰��� (������ �۽Ű���)

#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <iostream>
#include <winsock2.h>
#include <thread>

SOCKET clientSocket;

void ReceiveMessages() {
    char buffer[1024];
    int bytesRead;

    while (true) {
        bytesRead = recv(clientSocket, buffer, sizeof(buffer), 0);
        if (bytesRead <= 0) {
            std::cout << "Server disconnected." << std::endl;
            break;
        }

        buffer[bytesRead] = '\0';
        std::cout << "Received: " << buffer << std::endl;
    }
}

int main() {
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        std::cerr << "WSAStartup failed." << std::endl;
        return 1;
    }

    clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (clientSocket == INVALID_SOCKET) {
        std::cerr << "Failed to create client socket." << std::endl;
        WSACleanup();
        return 1;
    }

    sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    serverAddr.sin_port = htons(12345);

    if (connect(clientSocket, (sockaddr*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR) {
        std::cerr << "Failed to connect to the server." << std::endl;
        closesocket(clientSocket);
        WSACleanup();
        return 1;
    }

    std::thread(ReceiveMessages).detach();

    char message[1024];
    while (true) {
        std::cin.getline(message, sizeof(message));
        send(clientSocket, message, strlen(message), 0);
    }

    closesocket(clientSocket);
    WSACleanup();
    return 0;
}
