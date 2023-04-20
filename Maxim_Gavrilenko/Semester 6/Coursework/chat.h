#pragma comment(lib, "Ws2_32.lib")

#include <cstring>
#include <iostream>
#include <ws2tcpip.h>
#include <winsock2.h>
#include <thread>
#include <windows.h>
#include "vector"
#include <chrono>


#define CONNECTION_BREAK_SYMBOL '*'
bool connection_close(char* message)
{
    char* ptr = strchr(message, CONNECTION_BREAK_SYMBOL);
    if (ptr != nullptr) return true;
    return false;
}

void SET_CONSOLE_GREEN()
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    // устанавливаем новые атрибуты для фона и текста
    SetConsoleTextAttribute(hConsole,FOREGROUND_GREEN);
}

void SET_CONSOLE_RED()
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    // устанавливаем новые атрибуты для фона и текста
    SetConsoleTextAttribute(hConsole,FOREGROUND_RED);
}
void GET_CONSOLE_NORMAL()
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
    WORD saved_attributes;

    // сохраняем текущие атрибуты консоли
    GetConsoleScreenBufferInfo(hConsole, &consoleInfo);
    saved_attributes = consoleInfo.wAttributes;
    SetConsoleTextAttribute(hConsole, saved_attributes);

}