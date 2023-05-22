#include "chat.h"

#define DEFAULT_PORT 22222
#define ERROR_S "SERVER ERROR: "
#define CONNECTION_BREAK_SYMBOL '*'
#define BUFFER_SIZE 1024
#define MAX_CLIENTS 10


std::vector<int> clients;
void handle_client(int client_socket) {
    char buffer[BUFFER_SIZE];
    int read_size;

    // Добавляем клиента в список
    clients.push_back(client_socket);
    std::cout << "Client " << client_socket << " connected." << std::endl;
    send(client_socket,buffer, BUFFER_SIZE,0);
    // Читаем данные от клиента и отправляем их всем остальным клиентам
    while (((read_size = recv(client_socket, buffer, sizeof(buffer), 0)) > 0)) {
        buffer[read_size] = '\0';
        std::cout << "Received message from client " << client_socket << ": " << buffer << std::endl;

        if (connection_close(buffer)) {
            // Удаляем клиента из списка и закрываем сокет
            closesocket(client_socket);
            std::cout << "Client " << client_socket << " disconnected." << std::endl;
        }
        //for (int i : clients) { //range base
        for (int i = 0; i < clients.size(); i++) {
            if (clients[i] != client_socket) {
                send(clients[i], buffer, strlen(buffer), 0);
            }
        }
    }
}

int main() {
    int server_socket, client_socket;
    WSADATA data;
    if(0 != WSAStartup(MAKEWORD(2,1), &data)) return 101;
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    // устанавливаем новые атрибуты для фона и текста
    SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN);

    SOCKADDR_IN server_addr, client_addr;
    socklen_t addr_size;

    // Создаем сокет сервера
    server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket == -1) {
        std::cerr << ERROR_S << "Error creating server socket." << std::endl;
        return -1;
    }

    // Настраиваем адрес сервера
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(DEFAULT_PORT);
    server_addr.sin_addr.s_addr = INADDR_ANY;

    // Связываем сокет сервера с адресом
    if (bind(server_socket, (sockaddr*)&server_addr, sizeof(server_addr)) == -1) {
        std::cerr << ERROR_S << "Error binding server socket." << std::endl;
        return -1;
    }

    // Начинаем слушать входящие соединения
    if (listen(server_socket, MAX_CLIENTS) == -1) {
        std::cerr << ERROR_S << "Error listening on server socket." << std::endl;
        return -1;
    }

    std::cout << "Server started. Listening on port " << DEFAULT_PORT << "." << std::endl;

    // Принимаем соединения и обрабатываем их в отдельных потоках
    while (true) {
        addr_size = sizeof(client_addr);
        client_socket = accept(server_socket, (sockaddr*)&client_addr, &addr_size);

        if (client_socket == -1) {
            std::cerr << ERROR_S << "Error accepting client socket." << std::endl;
            continue;
        }
        std::thread A (handle_client, client_socket);
        A.detach();
    }
}
