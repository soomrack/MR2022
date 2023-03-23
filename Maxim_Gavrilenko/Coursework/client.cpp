#include "chat_library_initialization.h"

#define DEFAULT_PORT 1600
#define ERROR_S "CLIENT ERROR: "
#define CONNECTION_BREAK_SYMBOL '*'
#define SERVER_IP "127.0.0.0"
#define BUFFER_SIZE 4096

bool connection_close(char* message)
{
    char* ptr = std::strchr(message, CONNECTION_BREAK_SYMBOL);
    if (ptr != nullptr) return true;
    return false;
}

int main(__attribute__((unused)) int argc, __attribute__((unused)) char const* argv[]) {
    int client;

    WSADATA data;
    if (0 != WSAStartup(MAKEWORD(2, 1), &data)) return 101;
    SOCKADDR_IN server_address;
    client = socket(AF_INET, SOCK_STREAM, 0);
    if (client == -1) {
        std::cerr << ERROR_S << "establishing socket error" << std::endl; // Ошибка установки сокета
        std::cerr << "Error " << strerror(errno) << std::endl;
        exit(EXIT_FAILURE);
    }
    server_address.sin_family = AF_INET;
    server_address.sin_port = ntohs(DEFAULT_PORT);
    inet_pton(AF_INET, SERVER_IP, &server_address.sin_addr);

    std:: cout << "=> Client socket created\n";
    int ret = connect(client, (sockaddr*) &server_address, sizeof(sockaddr));

    if(ret != 0) { std:: cerr << "=> Connection to " << inet_ntoa(server_address.sin_addr)
                              << " with port: " << DEFAULT_PORT << " FAILED" << std:: endl;
        return 101;
    }
    std:: cout << "=> Connection to" << inet_ntoa(server_address.sin_addr)
               << "with port: " << DEFAULT_PORT << std:: endl;
    char buffer[BUFFER_SIZE];
    std::cout << "Waiting for server confirmation...";
    recv(client, buffer, BUFFER_SIZE, 0);
    std::cout << "=> Connection established.\n" <<
        "Enter " << CONNECTION_BREAK_SYMBOL << " for disconnection\n";

    while(true) {
        std:: cout <<"Client: ";
        std::cin.getline(buffer, BUFFER_SIZE, 0);
        send(client, buffer, BUFFER_SIZE,0);
        if (connection_close(buffer)) {
            break;
        }
        std:: cout <<"Server: ";
        recv(client, buffer, BUFFER_SIZE, 0);
        std:: cout << buffer << std:: endl;
        if(connection_close(buffer)) {
            break;
        }
    }
    return 0;
}