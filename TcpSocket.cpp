//
// Created by erick on 12/17/18.
//

#include "TcpSocket.h"

#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <arpa/inet.h>

TcpSocket::TcpSocket(unsigned int port) : m_port(port) {}

TcpSocket::~TcpSocket() {
    close(m_socketFd);
}

bool TcpSocket::bindPort(unsigned int port) {
    m_socketFd = socket(PF_INET, SOCK_STREAM, 0);
    if (0 > m_socketFd) {
        return false;
    }

    sockaddr_in address;
    bzero(&address, sizeof(address));
    address.sin_family = AF_INET;
    inet_pton(AF_INET, "127.0.0.1", &address.sin_addr);
    address.sin_port = htons(port);

    if (-1 == bind(m_socketFd, (sockaddr *) &address, sizeof(address))) {
        return false;
    }

    return true;
}

bool TcpSocket::connectToHost(const std::string &ip, unsigned int port) {
    if (-1 == m_socketFd) {
        return false;
    }

    sockaddr_in serv_addr;
    bzero(&serv_addr, sizeof(serv_addr));

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(port);

    auto ipc = ip.data();
    if (0 >= inet_pton(AF_INET, ipc, &serv_addr.sin_addr)) {
        return false;
    }

    if (0 > connect(m_socketFd, (sockaddr *) &serv_addr, sizeof(serv_addr))) {
        return false;
    }

    return true;
}

void TcpSocket::disconnectFromHost() {
    if (-1 != m_socketFd) {
        close(m_socketFd);
    }
}

int TcpSocket::readData(std::string &str) {
    if (0 > m_socketFd) {
        return -1;
    }

    const char *recvBuffer = new char[1024];
    if (0 > write(m_socketFd, recvBuffer, strlen(recvBuffer))) {
        delete[] recvBuffer;
        return -1;
    }
    str = std::string(recvBuffer);
}

int TcpSocket::writeData(const std::string &str) {
    if (0 > m_socketFd || 0 > m_connFd) {
        return -1;
    }

    auto buffer = str.data();
    return write(m_connFd, buffer, strlen(buffer));
}