cmake_minimum_required(VERSION 3.13)
project(Server)

set(CMAKE_CXX_STANDARD 14)

add_executable(ClionTest main.cpp TcpSocket.cpp TcpSocket.h TcpServer.cpp TcpServer.h)
