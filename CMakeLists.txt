cmake_minimum_required(VERSION 3.17)

project(LINUX_WEB_BASED_PROGRAMMING)

include_directories(${CMAKE_SOURCE_DIR}/tcp)

file(GLOB PROJECT_SOURCE
     "src/*.c"
     "src/tcp/*.c"
)
# add_executable(
#     add
#     src/01_daxiaoduan.c
#     src/02_htonl.c
#     src/04ntohs.c
#     src/tcp/01tcp_client.c)

add_executable(add ${PROJECT_SOURCE})
