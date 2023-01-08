cmake_minimum_required(VERSION 3.0.0)
project(TestC VERSION 0.1.0)

include(CTest)
enable_testing()

add_executable(TestC main.c server.c client.c Common.c server_command.c file.c)
add_executable(Client main_client.c client.c)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
