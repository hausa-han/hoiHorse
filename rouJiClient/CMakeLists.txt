cmake_minimum_required(VERSION 3.14)
project(rouJiClient)

set(CMAKE_CXX_STANDARD 17)

link_libraries(ws2_32 wsock32)

add_executable(rouJiClient main.cpp common/log/localLog.h common/log/localLog.cpp common/status/localStatus.h common/status/localStatus.cpp common/staticValues/localStaticValues.h service/parseCommands.h service/parseCommands.cpp)