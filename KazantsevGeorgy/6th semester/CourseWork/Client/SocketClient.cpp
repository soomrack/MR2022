//client
#define WIN32_LEAN_AND_MEAN
#include <iostream>
#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <config.h>
#include <stdlib.h>
#include <vector>
#include <string>
#include <thread>
//#define DEBUG

using namespace std;


class SocketClient {
public:
    void init();
    void run(ADDRINFO* addrresult, SOCKET connectsocket, SocketClient con);
    void close(ADDRINFO* addrresult, SOCKET connectsocket);
    void stop(ADDRINFO* addrresult, SOCKET connecttsocket);
    int send_message(SOCKET connectsocket, const char s_data[]);

    string str;
    WSADATA wsaData;
    ADDRINFO hints;
    ADDRINFO* addrResult = nullptr;
    SOCKET ConnectSocket = INVALID_SOCKET;
    char recvdata[512];
    int result;
};

void SocketClient::init()
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


    result = getaddrinfo(HOST, PORT, &hints, &addrResult);
    if (result != 0)
    {
#ifdef DEBUG
        cout << "getaddrinfo failed with error: " << result << endl;
#endif      
        WSACleanup();
        exit(2);
    }

    //addrResult->ai_next; ai_next = nullptr

    ConnectSocket = socket(addrResult->ai_family, addrResult->ai_socktype, addrResult->ai_protocol);
    if (ConnectSocket == INVALID_SOCKET)
    {
#ifdef DEBUG
        cout << "Socket creation failed" << endl;
#endif 
        freeaddrinfo(addrResult);
        WSACleanup();
        exit(3);
    }

    result = connect(ConnectSocket, addrResult->ai_addr, (int)addrResult->ai_addrlen);
    if (result == SOCKET_ERROR)
    {
#ifdef DEBUG
        cout << "Unable to connect to server";
#endif 
        closesocket(ConnectSocket);
        ConnectSocket = INVALID_SOCKET;
        freeaddrinfo(addrResult);
        WSACleanup();
        exit(4);
    }
    cout << "Connected to " << HOST << " " << endl;
}


void SocketClient::close(ADDRINFO* addrresult, SOCKET connectsocket)
{
    int result = shutdown(connectsocket, SD_SEND);
    if (result == SOCKET_ERROR)
    {
#ifdef DEBUG
        cout << "send failed, error: " << result << endl;
#endif 
        closesocket(connectsocket);
        freeaddrinfo(addrresult);
        WSACleanup();
        exit(6);
    }
}

void SocketClient::stop(ADDRINFO* addrresult, SOCKET connectsocket)
{
    closesocket(connectsocket);
    freeaddrinfo(addrresult);
    WSACleanup();
}



int SocketClient::send_message(SOCKET connectsocket, const char s_data[])
{
    return send(ConnectSocket, s_data, (int)strlen(s_data), 0);
}

void SocketClient::run(ADDRINFO* addrresult, SOCKET connectsocket, SocketClient con)
{
    bool _exit = 0;
    int result;
    do
    {
        cout <<endl << "Enter message";
        getline(cin, str);
        const char* s_data = new char[512];
        s_data = str.c_str();
        result = con.send_message(ConnectSocket, s_data);
        s_data = nullptr;
        delete[] s_data;

        result = recv(connectsocket, recvdata, 512, 0);
        if (result > 0)
        {
#ifdef DEBUG
            endl << "Received " << result << "bytes";
#endif 
            cout << "Recieved data: " << recvdata;

        }
        else if (result == 0)
        {
            cout << "Connected closed" << endl;
            _exit = 1;
        }
        else
        {
            cout << "recv failed with error " << endl;
            _exit = 1;
        }

    } while (_exit != 1);
}


int main(int argc, char const* argv[])
{
    SocketClient newcon;
    newcon.init();
    newcon.run(newcon.addrResult, newcon.ConnectSocket, newcon);
    newcon.close(newcon.addrResult, newcon.ConnectSocket);
    return 0;
}

