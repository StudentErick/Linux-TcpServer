//
// Created by erick on 12/17/18.
//

#include "TcpServer.h"

#include <sys/socket.h>

TcpServer::TcpServer() {

}

bool TcpServer::listenOnPort(unsigned int port) {
    if (nullptr != m_serverSocket) {
        delete m_serverSocket;
        m_isListening = false;
    }

    m_serverSocket = new TcpSocket(port);

    if (!m_serverSocket->bindPort(port)) {
        return false;
    }

    if (!listen(m_serverSocket->getSocketFD(), m_maxListenSocket)) {
        return false;
    }

    m_isListening = true;
    return true;
}