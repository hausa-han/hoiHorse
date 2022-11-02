#include <iostream>
#include <winsock2.h>
#include <afxres.h>
#include "common/log/localLog.h"
#include "common/status/localStatus.h"
#include "common/staticValues/localStaticValues.h"



using namespace std;


#ifndef SERVER_PORT
#define SERVER_PORT 11451
#endif

#pragma comment(lib, "ws2_32.lib")


int main() {

    // Init values
    char logString[511];

    // Init WSA
    WORD socketVersion = MAKEWORD(2, 2);
    WSADATA  wsaData;
    if (WSAStartup(socketVersion, &wsaData) != 0) {
        return INIT_SOCKET_ERROR;
    } else {
        logMessage("Finish Init WSA.");
    }

    // Create socket
    SOCKET sListen = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (sListen == INVALID_SOCKET) {
        logError("Create socket error.");
        return CREATE_SOCKET_ERROR;
    } else {
        logMessage("Finish create socket");
    }

    // Bind IP and PORT
    sockaddr_in socketAddressIn;
    socketAddressIn.sin_family = AF_INET;
    socketAddressIn.sin_port = htons(SERVER_PORT);
    socketAddressIn.sin_addr.S_un.S_addr = INADDR_ANY;
    if (bind(sListen, (LPSOCKADDR)&socketAddressIn, sizeof(socketAddressIn)) == SOCKET_ERROR) {
        logError("Bind socket error.");
        return BIND_SOCKET_ERROR;
    } else {
        logMessage("Finish bind ip:port");
    }

    // Start listen
    if (listen(sListen, 5) == SOCKET_ERROR) {
        logError("Start listen ERROR.");
        return SOCKET_START_LISTEN_ERROR;
    } else {
        sprintf(logString, "Server listening at %d", SERVER_PORT);
        logMessage(logString);
    }

    // Circle listen
    SOCKET sClient;
    sockaddr_in remoteAddress;
    int nAddressLen = sizeof(remoteAddress);
    char revData[MAX_SOCKET_DATA_LENGTH];
    while (true) {
        sClient = accept(sListen, (SOCKADDR *) &remoteAddress, &nAddressLen);
        if (sClient == INVALID_SOCKET) {
            logError("Accept error socket");
            continue;
        }
        logMessage("\n\nReceived a connection!!!");
        sprintf(logString, "Remote address: %d.%d.%d.%d",
                remoteAddress.sin_addr.S_un.S_un_b.s_b1,
                remoteAddress.sin_addr.S_un.S_un_b.s_b2,
                remoteAddress.sin_addr.S_un.S_un_b.s_b3,
                remoteAddress.sin_addr.S_un.S_un_b.s_b4);
        logMessage(logString);// inet_ntoa(remoteAddress.sin_addr)

        // Receive message
        int ret = recv(sClient, revData, MAX_SOCKET_DATA_LENGTH, 0);
        if (ret > 0) {
            revData[ret] = 0x00;
            cout << revData << endl;
            // If client send quit, quit
            if (strcmp(revData, "quit") == 0) {
                send(sClient, "quit", strlen("quit"), 0);
                closesocket(sClient);
                break;
            } else {
                send(sClient, "GOT", strlen("GOT"), 0);
            }
        }
    }
    closesocket(sListen);
    WSACleanup();
    return 0;
}