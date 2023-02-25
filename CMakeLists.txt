cmake_minimum_required(VERSION 3.0.0)
project(TestC VERSION 0.1.0)

include(CTest)
enable_testing()

include_directories(include)
add_executable(WebServer main_webserver.c webserver.c)
add_executable(Signal main_signal.c)
add_executable(Playground playground/playground_main.c)
add_executable(ClientServerTest Common.c main_client.c client.c server/server.c server/server_command.c server/data_section/msg_container/server_msg_container.c network_shot.c server/data_section/data_section_main.c)
add_library(clientlib SHARED clientlib/clientlib.c)
add_executable(TestClientLib main_testclientlib.c)
target_link_libraries(TestClientLib clientlib)


set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
