//server
#define WIN32_LEAN_AND_MEAN
#include <iostream>
#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <string>
#include <config.h>
#include <stdlib.h>
#include <vector>
//#define DEBUG
using namespace std;

class SocketServer {
public:
    void init();
    void run(ADDRINFO* addrresult, SOCKET clientsocket, SOCKET listensocket, SocketServer con);
    void close(ADDRINFO* addrresult, SOCKET clientsocket);
    void stop(ADDRINFO* addrresult, SOCKET clientsocket);
    int send_message(SOCKET clientsocket, const char s_data[]);
    string str;
    char recieved_data[512];
    WSADATA wsaData;
    ADDRINFO hints;
    ADDRINFO* addrResult = nullptr;
    SOCKET ClientSocket = INVALID_SOCKET;
    SOCKET ListenSocket = INVALID_SOCKET;
    int result;

};

void SocketServer::init()
{
    result = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (result != 0)
    {
#ifdef DEBUG
        cout << "WSAStartup failed, result = " << result << endl;
#endif        
        exit(1);
    }
    ZeroMemory(&hints, sizeof(hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;
    hints.ai_flags = AI_PASSIVE;
    result = getaddrinfo(HOST, PORT, &hints, &addrResult);
    if (result != 0)
    {
#ifdef DEBUG
        cout << "getaddrinfo failed with error: " << result << endl;
#endif     
        WSACleanup();
        exit(1);
    }

    //addrResult->ai_next; ai_next = nullptr

    ListenSocket = socket(addrResult->ai_family, addrResult->ai_socktype, addrResult->ai_protocol);
    if (ListenSocket == INVALID_SOCKET)
    {
#ifdef DEBUG
        cout << "Socket creation failed" << endl;
#endif     
        freeaddrinfo(addrResult);
        WSACleanup();
        exit(1);
    }
    cout << "+New server started from ipv4 address: " << HOST << " port: " << PORT << endl;

    result = bind(ListenSocket, addrResult->ai_addr, (int)addrResult->ai_addrlen);
    if (result == SOCKET_ERROR)
    {
#ifdef DEBUG
        cout << "Binding socket failed";
#endif   
        closesocket(ListenSocket);
        ListenSocket = INVALID_SOCKET;
        freeaddrinfo(addrResult);
        WSACleanup();
        exit(1);
    }

    result = listen(ListenSocket, SOMAXCONN);
    if (result == SOCKET_ERROR)
    {
#ifdef DEBUG
        cout << "Listening socket failed";
#endif   
        closesocket(ListenSocket);
        freeaddrinfo(addrResult);
        WSACleanup();
        exit(1);
    }

    ClientSocket = accept(ListenSocket, nullptr, nullptr);
    if (ClientSocket == SOCKET_ERROR)
    {
#ifdef DEBUG
        cout << "accept failed, error: " << result << endl;
#endif   
        closesocket(ListenSocket);
        freeaddrinfo(addrResult);
        WSACleanup();
        exit(1);
    }
    cout << "Connected has been established " << HOST << " " << PORT << endl;
}


void SocketServer::close(ADDRINFO* addrresult, SOCKET clientsocket)
{
    closesocket(clientsocket);
    freeaddrinfo(addrresult);
    WSACleanup();
    exit(1);
}

void SocketServer::stop(ADDRINFO* addrresult, SOCKET clientsocket)
{
    int result = shutdown(clientsocket, SD_SEND);
    if (result == SOCKET_ERROR)
    {
#ifdef DEBUG
        cout << "shutdown failed, error: " << result << endl;
#endif // DEBUG
        closesocket(clientsocket);
        freeaddrinfo(addrresult);
        WSACleanup();
        exit(1);
    }
}

int SocketServer::send_message(SOCKET clientsocket, const char s_data[])
{
    return send(clientsocket, s_data, (int)strlen(s_data), 0);
}

void SocketServer::run(ADDRINFO* addrresult, SOCKET clientsocket, SOCKET listensocket, SocketServer con)
{
    bool _exit = 0;
    int result;
    
    do   
    {
        result = recv(clientsocket, recieved_data, 512, 0);
        if (result > 0)
        {
#ifdef DEBUG
            cout << "Received " << result << "bytes" << endl;
#endif // DEBUG
            cout << "Recieved data: " << recieved_data << endl;
            cout << "Enter message";
            getline(cin, str);
            const char* s_data = new char[512];
            s_data = str.c_str();
            result = con.send_message(ClientSocket, s_data);
            s_data = nullptr;
            delete[] s_data;
        }
        else if (result == 0)
        {
#ifdef DEBUG
            cout << "Connected closing" << endl;
#endif // DEBUG
            _exit = 1;
        }
        else
        {
#ifdef DEBUG
            cout << "recv failed with error " << endl;
#endif // DEBUG
            _exit = 1;
        }
    }
    while (_exit != 1);
}


int main(int argc, char const* argv[])
{
    SocketServer newcon;
    newcon.init();
    newcon.run(newcon.addrResult, newcon.ClientSocket, newcon.ListenSocket, newcon);
    newcon.close(newcon.addrResult, newcon.ClientSocket);
    return 0;
}

