#include <cstring>
#include <iostream>
#include <WinSock2.h>
#include <Ws2tcpip.h>

#define DEFAULT_PORT 1600
#define ERROR_S "SERVER ERROR: "
#define CONNECTION_BREAK_SYMBOL '*'

bool is_connection_close(char* message)
{
    char* ptr = std::strchr(message, CONNECTION_BREAK_SYMBOL);
    if (ptr != nullptr) return true;
    return false;
}

int main(__attribute__((unused)) int argc, __attribute__((unused)) char const* argv[]) {
    int client;
    int server;

    struct sockaddr_in server_address;
    client = socket(AF_INET, SOCK_STREAM, 0);
    if (client == -1)
    {
        std::cerr << ERROR_S << "establishing socket error"<< std::endl; // Ошибка установки сокета
        perror("socket");
        exit(EXIT_FAILURE);
    }

    std::cout << "Server: Socket for server was successfully estalished" << std::endl;

    server_address.sin_port = htons(DEFAULT_PORT);
    server_address.sin_family = AF_INET; // Семейство портов IPV4
    server_address.sin_addr.s_addr = htons(INADDR_ANY);

    // sin_port Хранит номер порта структуры,
    // htons_ -эта функция преобразует 16-битные (2-байтовые) величины из порядка байтов хоста в порядок байтов сети.
    // sin_addr.s_addr - поле хранит в себе IP адрес в сетевом порядке байтов

    int ret = (bind(client, (sockaddr*) (&server_address),sizeof(server_address)));
    if (ret < 0)
    {
        std::cerr << ERROR_S << "Binding connection. Socket has been already established";
        return -1; // Окончание программы, сервер не был поднят
    }

    socklen_t size = sizeof(server_address);
    std::cout << "Server: " << "It is listening for clients... " << std::endl;
    int Listen = listen(client, 1);
    server = accept(client, (sockaddr*) &server_address, &size);
    if (server == 0)
    {
        std::cerr << ERROR_S << "Can't accepting a client \n";
        return -1;
    }
    char buffer[4096];
    bool isExit = false;
    while (server > 0) {
        strcpy(buffer, "=> Server connected\n");
        send(server,buffer, 4096,0);
        std::cerr << "=> Connected to the client" << std:: endl;
        std::cerr << "Enter " << CONNECTION_BREAK_SYMBOL << "to end the connection" << std:: endl;

        std::cerr << "Client :";
        recv(server, buffer, 4096, 0);
        std::cerr << buffer << std::endl;
        if(is_connection_close(buffer)) {
            isExit = true;
        }
        while (isExit) {
            std::cerr << "Server: ";
            std::cin.getline(buffer, 4096);
            send(server,buffer,4096,0);
            if(is_connection_close(buffer))
            {
                break;
            }
            std::cerr << "Client: ";
            recv(server,buffer, 4096, 0);
            std::cout << buffer << std::endl;
            if(is_connection_close(buffer))
            {
                break;
            }
        }
        std::cout << "Goodbye " << std::endl;
        isExit = false;
        exit(1);
    }
}