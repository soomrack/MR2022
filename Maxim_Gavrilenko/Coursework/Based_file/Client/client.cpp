#pragma comment(lib, "Ws2_32.lib")

#include "C:\Users\El1x3r7714\CLionProjects\MR2022\Maxim_Gavrilenko\Coursework\SERVER_FOR_CLIENTS\chat.h"

#define DEFAULT_PORT 1600
#define ERROR_S "CLIENT ERROR: "
#define CONNECTION_BREAK_SYMBOL '*'
#define SERVER_IP "127.0.0.1"
#define BUFFER_SIZE 1024

/*int get_client_socket(int client)
{
    return client;
}
void exit_from_server() {
    char buf[0];
        buf[0] = '*';
    }
    send(get_client_socket(), stop, strlen(stop), 0);
    closesocket(client);
}*/
void write_messages(int client) {
    char buffer[BUFFER_SIZE];
    while (true) {
        std::this_thread::sleep_for(std::chrono::milliseconds(10000));
        std::cout << "Your message";
        std::cin.getline(buffer, BUFFER_SIZE);
        send(client, buffer, strlen(buffer), 0);
        if (connection_close(buffer))
            break;
    }
}

void receive_messages(int client_socket) {
    char buffer[BUFFER_SIZE];
    int read_size;
    std::this_thread::sleep_for(std::chrono::milliseconds(50));
    // Читаем данные от сервера и выводим их на экран
    while ((read_size = recv(client_socket, buffer, sizeof(buffer), 0)) > 0) {
        buffer[read_size] = '\0';
        std::cout << "\nReceived message: " << buffer << std::endl;
    }
}



int main(__attribute__((unused)) int argc, __attribute__((unused)) char const* argv[]) {
    int client;
    WSADATA data;
    SET_CONSOLE_NORMAL();
    SET_CONSOLE_GREEN();
    if (0 != WSAStartup(MAKEWORD(2, 1), &data)) return 101;
    SOCKADDR_IN server_address;
    client = socket(AF_INET, SOCK_STREAM, 0);
    if (client == -1) {
        SET_CONSOLE_RED();
        std::cerr << ERROR_S << "establishing socket error" << std::endl; // Ошибка установки сокета
        std::cerr << "Error " << strerror(errno) << std::endl;
        exit(EXIT_FAILURE);
    }
    server_address.sin_addr.s_addr = inet_addr(SERVER_IP);
    //InetPtonA(AF_INET, SERVER_IP, &server_address.sin_addr); НЕ КОМПИЛИТ MINGW
    server_address.sin_family = AF_INET;
    server_address.sin_port = ntohs(DEFAULT_PORT);

    std:: cout << "=> Client socket created\n";
    int ret = connect(client, (sockaddr*) &server_address, sizeof(sockaddr));
    if(ret != 0) {
        SET_CONSOLE_RED();
        std:: cerr << "=> Connection to " << inet_ntoa(server_address.sin_addr)
                              << " with port: " << DEFAULT_PORT << " FAILED" << std:: endl;
        return 101;
    }
    std:: cout << "=> Connection to " << inet_ntoa(server_address.sin_addr)
               << " with port: " << DEFAULT_PORT << std:: endl;
    char buffer[BUFFER_SIZE];
    std::cout << "Waiting for server confirmation...";
    recv(client, buffer, BUFFER_SIZE, 0);
    std::cout << "=> Connection established.\n" <<
        "Enter " << CONNECTION_BREAK_SYMBOL << " for disconnection\n";
    // Запускаем отдельный поток для чтения данных из сокета
    SET_CONSOLE_NORMAL();
    std::thread read(receive_messages, client);
    // Запускаем отдельный поток для посылки сообщения серверу
    std::thread write(write_messages, client);
    /*while (true) {
        std::this_thread::sleep_for(std::chrono::milliseconds(2000));
        std::cout << "Your message: ";
        std::cin.getline(buffer, BUFFER_SIZE);
        send(client, buffer, strlen(buffer), 0);
        if (connection_close(buffer))
            break;
    }*/

    /*atexit(exit_from_server);*/
    // Останавливаем поток и закрываем сокет
    read.join();
    closesocket(client);
    return 0;
}