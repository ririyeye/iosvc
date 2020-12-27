cmake_minimum_required(VERSION 3.0)



PROJECT(PROJECT_IOSVC)

add_executable(iosvc main.cpp udp_session.cpp )

target_link_libraries(iosvc pthread)
target_link_libraries(iosvc boost_thread)

INSTALL(TARGETS iosvc
       RUNTIME DESTINATION .
)
