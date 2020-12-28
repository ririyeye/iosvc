cmake_minimum_required(VERSION 3.0)



PROJECT(PROJECT_IOSVC)
add_compile_options(-std=c++11)
add_executable(iosvc main.cpp udp_session.cpp)

target_link_libraries(iosvc pthread)
target_link_libraries(iosvc boost_thread)

add_subdirectory(client)


INSTALL(TARGETS iosvc
       RUNTIME DESTINATION .
)
