//
// Created by erick on 12/17/18.
// 封装了一个服务器的类
//

#ifndef CLIONTEST_TCPSERVER_H
#define CLIONTEST_TCPSERVER_H

#include "TcpSocket.h"

class TcpServer {
public:

    TcpServer();

    bool listenOnPort(unsigned int port);  // 服务器监听

    bool isListening() const; // 是否正在监听

    TcpSocket *nextPendingConnection(); // 返回新建立连接的套接字指针

    unsigned int getServetPort() const { return m_serverPort; }

    inline void setMaxListnSocket(unsigned int num) { m_maxListenSocket = num; }

protected:
    void addPendingConnection(TcpSocket *socket); // 添加新来的Socket到队列中

    TcpSocket *m_serverSocket{nullptr};
    int m_serverPort{-1};  // 监听端口
    unsigned int m_maxListenSocket{5};  // 一次性最多监听的socket数量
    bool m_isListening{false};
};


#endif //CLIONTEST_TCPSERVER_H
