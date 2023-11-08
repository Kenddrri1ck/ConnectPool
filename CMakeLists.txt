cmake_minimum_required(VERSION 3.20)
project(connectPool)
set(CMAKE_CXX_STANDARD 14)
include_directories(json)
include_directories(E:\\wamp64\\bin\\mysql\\mysql8.0.31\\include)
link_directories(E:\\wamp64\\bin\\mysql\\mysql8.0.31\\lib)

link_libraries(libmysql)

add_executable(connectPool mySQLConn.h mySQLConn.cpp  connectionPool.cpp connectionPool.h jsoncpp.cpp json/json.h json/json-forwards.h main.cpp)

target_link_libraries(connectPool libmysql)
