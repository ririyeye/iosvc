
add_executable(ioclient main.cpp dummy_client.cpp client_dat.cpp mycrypto.cpp crc16.c)
target_link_libraries(ioclient pthread)
target_link_libraries(ioclient boost_thread)
target_link_libraries(ioclient boost_context)
target_link_libraries(ioclient boost_coroutine)

INSTALL(TARGETS ioclient
       RUNTIME DESTINATION .
)

