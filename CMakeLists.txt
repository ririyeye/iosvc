cmake_minimum_required(VERSION 3.0)



PROJECT(PROJECT_IOSVC)

add_executable(iosvc main.cpp)

target_link_libraries(iosvc boost_system)
#target_link_libraries(iosvc boost_thread)
target_link_libraries(iosvc pthread)

INSTALL(TARGETS iosvc
       RUNTIME DESTINATION .
)
