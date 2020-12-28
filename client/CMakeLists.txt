
add_executable(ioclient main_client.cpp)
target_link_libraries(ioclient pthread)
target_link_libraries(ioclient boost_thread)

INSTALL(TARGETS ioclient
       RUNTIME DESTINATION .
)

