// 서버는 모든 메시지를 받아 중계하며 접속한 클라이언트끼리 채팅가능
// 클라이언트 코드는 수정없이 N개를 각각 실행하여 N명끼리 채팅가능
// 메시지 연속전송가능

#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <iostream>
#include <winsock2.h>
#include <thread>
#include <vector>
#include <sstream>

SOCKET serverSocket;
std::vector<SOCKET> clientSockets;
bool serverRunning = true;

template <typename T>
std::string to_string(const T& value) {
    std::ostringstream oss;
    oss << value;
    return oss.str();
}

void ClientHandler(SOCKET clientSocket) {
    char buffer[1024];
    int bytesRead;
    int clientID = -1;

    while (serverRunning) {
        bytesRead = recv(clientSocket, buffer, sizeof(buffer), 0);
        if (bytesRead <= 0) {
            std::cout << "Client " << clientID << " disconnected." << std::endl;
            closesocket(clientSocket);
            break;
        }

        std::string message(buffer, bytesRead);

        // 클라이언트에게 메시지 전달
        for (size_t i = 0; i < clientSockets.size(); i++) {
            if (clientSockets[i] == clientSocket) {
                clientID = i;
            }
        }

        std::cout << "Client" << clientID << ": " << message << std::endl;

        // 메시지에 클라이언트 식별 추가
        std::string labeledMessage = "Client" + to_string(clientID) + ": " + message;

        for (const SOCKET& client : clientSockets) {
            if (client != clientSocket) {
                send(client, labeledMessage.c_str(), labeledMessage.size(), 0);
            }
        }
    }
}

int main() {
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        std::cerr << "WSAStartup failed." << std::endl;
        return 1;
    }

    serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket == INVALID_SOCKET) {
        std::cerr << "Failed to create server socket." << std::endl;
        WSACleanup();
        return 1;
    }

    sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = INADDR_ANY;
    serverAddr.sin_port = htons(12345);

    if (bind(serverSocket, (sockaddr*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR) {
        std::cerr << "Bind failed." << std::endl;
        closesocket(serverSocket);
        WSACleanup();
        return 1;
    }


    if (listen(serverSocket, 5) == SOCKET_ERROR) {
        std::cerr << "Listen failed." << std::endl;
        closesocket(serverSocket);
        WSACleanup();
        return 1;
    }

    std::cout << "Server is listening on port 12345..." << std::endl;

    while (serverRunning) {
        SOCKET clientSocket = accept(serverSocket, nullptr, nullptr);
        if (clientSocket == INVALID_SOCKET) {
            std::cerr << "Accept failed." << std::endl;
            continue;
        }

        clientSockets.push_back(clientSocket);
        std::cout << "Client connected." << std::endl;
        std::thread(ClientHandler, clientSocket).detach();
    }

    for (SOCKET client : clientSockets) {
        closesocket(client);
    }

    closesocket(serverSocket);
    WSACleanup();
    return 0;
}