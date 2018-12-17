//
// Created by erick on 12/17/18.
// 封装Linux系统的Socket接口
//

#ifndef CLIONTEST_TCPSOCKET_H
#define CLIONTEST_TCPSOCKET_H

#include <string>

class TcpSocket {
public:

    explicit TcpSocket(unsigned int port = 8001);

    ~TcpSocket();

    bool bindPort(unsigned int port); // 绑定本地端口

    bool connectToHost(const std::string &ip, unsigned port); // 连接远程主机

    inline int getSocketFD() const { return m_socketFd; }

    void disconnectFromHost(); // 断开主机连接

    inline unsigned int localPort() const { m_port; }

    int readData(std::string& str); // 读取socket的数据

    int writeData(const std::string& str); // 写入数据，返回写入的字节数

private:
    int m_socketFd{-1}; // 自身的FD
    int m_port{-1};     // 绑定的端口
    int m_connFd{-1};   // 连接的端口
};


#endif //CLIONTEST_TCPSOCKET_H
