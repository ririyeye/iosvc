
add_executable(ioclient main.cpp iot_client_session.cpp)
target_link_libraries(ioclient pthread)
target_link_libraries(ioclient boost_thread)

INSTALL(TARGETS ioclient
       RUNTIME DESTINATION .
)

