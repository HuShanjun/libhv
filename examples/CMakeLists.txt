list(APPEND EXAMPLES
    hloop_test
    htimer_test
    nc
    tinyhttpd
    tinyproxyd
    tcp_client_test
    tcp_echo_server
    tcp_chat_server
    tcp_proxy_server
    udp_echo_server
    udp_proxy_server
    socks5_proxy_server
    jsonrpc_client
    jsonrpc_server
)

include_directories(.. ../base ../ssl ../event ../util)

add_executable(hloop_test hloop_test.c)
target_link_libraries(hloop_test ${HV_LIBRARIES})
set_target_properties(hloop_test PROPERTIES FOLDER "Examples")

add_executable(htimer_test htimer_test.c)
target_link_libraries(htimer_test ${HV_LIBRARIES})
set_target_properties(htimer_test PROPERTIES FOLDER "Examples")

add_executable(nc nc.c)
target_link_libraries(nc ${HV_LIBRARIES})
set_target_properties(nc PROPERTIES FOLDER "Examples")

add_executable(tinyhttpd tinyhttpd.c)
target_link_libraries(tinyhttpd ${HV_LIBRARIES})
set_target_properties(tinyhttpd PROPERTIES FOLDER "Examples")

add_executable(tinyproxyd tinyproxyd.c)
target_link_libraries(tinyproxyd ${HV_LIBRARIES})
set_target_properties(tinyproxyd PROPERTIES FOLDER "Examples")

add_executable(tcp_client_test tcp_client_test.c)
target_link_libraries(tcp_client_test ${HV_LIBRARIES})
set_target_properties(tcp_client_test PROPERTIES FOLDER "Examples")

add_executable(tcp_echo_server tcp_echo_server.c)
target_link_libraries(tcp_echo_server ${HV_LIBRARIES})
set_target_properties(tcp_echo_server PROPERTIES FOLDER "Examples")

add_executable(tcp_chat_server tcp_chat_server.c)
target_link_libraries(tcp_chat_server ${HV_LIBRARIES})
set_target_properties(tcp_chat_server PROPERTIES FOLDER "Examples")

add_executable(tcp_proxy_server tcp_proxy_server.c)
target_link_libraries(tcp_proxy_server ${HV_LIBRARIES})
set_target_properties(tcp_proxy_server PROPERTIES FOLDER "Examples")

add_executable(udp_echo_server udp_echo_server.c)
target_link_libraries(udp_echo_server ${HV_LIBRARIES})
set_target_properties(udp_echo_server PROPERTIES FOLDER "Examples")

add_executable(udp_proxy_server udp_proxy_server.c)
target_link_libraries(udp_proxy_server ${HV_LIBRARIES})
set_target_properties(udp_proxy_server PROPERTIES FOLDER "Examples")

add_executable(socks5_proxy_server socks5_proxy_server.c)
target_link_libraries(socks5_proxy_server ${HV_LIBRARIES})
set_target_properties(socks5_proxy_server PROPERTIES FOLDER "Examples")

add_executable(jsonrpc_client jsonrpc/jsonrpc_client.c jsonrpc/cJSON.c)
target_compile_definitions(jsonrpc_client PRIVATE CJSON_HIDE_SYMBOLS)
target_link_libraries(jsonrpc_client ${HV_LIBRARIES})
set_target_properties(jsonrpc_client PROPERTIES FOLDER "Examples")

add_executable(jsonrpc_server jsonrpc/jsonrpc_server.c jsonrpc/cJSON.c)
target_compile_definitions(jsonrpc_server PRIVATE CJSON_HIDE_SYMBOLS)
target_link_libraries(jsonrpc_server ${HV_LIBRARIES})
set_target_properties(jsonrpc_server PROPERTIES FOLDER "Examples")

if(WITH_EVPP)
    include_directories(../cpputil ../evpp)

    # hmain_test
    add_executable(hmain_test hmain_test.cpp)
    target_link_libraries(hmain_test ${HV_LIBRARIES})
    set_target_properties(hmain_test PROPERTIES FOLDER "Examples")


    # nmap
    glob_headers_and_sources(NMAP_FILES nmap)
    add_executable(nmap ${NMAP_FILES})
    target_compile_definitions(nmap PRIVATE PRINT_DEBUG)
    target_link_libraries(nmap ${HV_LIBRARIES})
    set_target_properties(nmap PROPERTIES FOLDER "Examples")

    list(APPEND EXAMPLES hmain_test nmap)
if(WITH_HTTP)
    include_directories(../http)

    # wrk
    add_executable(wrk wrk.cpp)
    target_link_libraries(wrk ${HV_LIBRARIES})
    set_target_properties(wrk PROPERTIES FOLDER "Examples")

    list(APPEND EXAMPLES wrk)
if(WITH_HTTP_SERVER)
    include_directories(../http/server)

    # http_server_test
    add_executable(http_server_test http_server_test.cpp)
    target_link_libraries(http_server_test ${HV_LIBRARIES})
    set_target_properties(http_server_test PROPERTIES FOLDER "Examples")

    # websocket_server_test
    add_executable(websocket_server_test websocket_server_test.cpp)
    target_link_libraries(websocket_server_test ${HV_LIBRARIES})
    set_target_properties(websocket_server_test PROPERTIES FOLDER "Examples")

    list(APPEND EXAMPLES http_server_test websocket_server_test)
endif()

if(WITH_HTTP_CLIENT)
    include_directories(../http/client)

    # curl
    set(CURL_TARGET_NAME curl)
    if(WITH_CURL)
        set(CURL_TARGET_NAME hv_curl)
    endif()
    add_executable(${CURL_TARGET_NAME} curl.cpp)
    if(WITH_CURL)
        set_target_properties(${CURL_TARGET_NAME} PROPERTIES OUTPUT_NAME curl)
    endif()
    target_link_libraries(${CURL_TARGET_NAME} ${HV_LIBRARIES})
    set_target_properties(${CURL_TARGET_NAME} PROPERTIES FOLDER "Examples")

    # wget
    add_executable(wget wget.cpp)
    target_link_libraries(wget ${HV_LIBRARIES})
    set_target_properties(wget PROPERTIES FOLDER "Examples")

    # consul
    glob_headers_and_sources(CONSUL_FILES consul)
    add_executable(consul ${CONSUL_FILES})
    target_compile_definitions(consul PRIVATE PRINT_DEBUG)
    target_link_libraries(consul ${HV_LIBRARIES})
    set_target_properties(consul PROPERTIES FOLDER "Examples")

    # http_client_test
    add_executable(http_client_test http_client_test.cpp)
    target_link_libraries(http_client_test ${HV_LIBRARIES})
    set_target_properties(http_client_test PROPERTIES FOLDER "Examples")


    # websocket_client_test
    add_executable(websocket_client_test websocket_client_test.cpp)
    target_link_libraries(websocket_client_test ${HV_LIBRARIES})
    set_target_properties(websocket_client_test PROPERTIES FOLDER "Examples")

    list(APPEND EXAMPLES ${CURL_TARGET_NAME} wget consul http_client_test websocket_client_test)

    if(WITH_HTTP_SERVER)
        # httpd
        glob_headers_and_sources(HTTPD_FILES httpd)
        add_executable(httpd ${HTTPD_FILES})
        target_link_libraries(httpd ${HV_LIBRARIES})
        list(APPEND EXAMPLES httpd)
        set_target_properties(httpd PROPERTIES FOLDER "Examples")
    endif()
endif()

endif()
endif()

if(WITH_MQTT)
    include_directories(../mqtt)

    add_executable(mqtt_sub mqtt/mqtt_sub.c)
    target_link_libraries(mqtt_sub ${HV_LIBRARIES})
    set_target_properties(mqtt_sub PROPERTIES FOLDER "Examples")

    add_executable(mqtt_pub mqtt/mqtt_pub.c)
    target_link_libraries(mqtt_pub ${HV_LIBRARIES})
    set_target_properties(mqtt_pub PROPERTIES FOLDER "Examples")

    add_executable(mqtt_client_test mqtt/mqtt_client_test.cpp)
    target_link_libraries(mqtt_client_test ${HV_LIBRARIES})
    set_target_properties(mqtt_client_test PROPERTIES FOLDER "Examples")

    list(APPEND EXAMPLES mqtt_sub mqtt_pub mqtt_client_test)
endif()

add_custom_target(examples DEPENDS ${EXAMPLES})
