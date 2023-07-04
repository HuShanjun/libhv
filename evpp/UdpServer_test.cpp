/*
 * UdpServer_test.cpp
 *
 * @build   make evpp
 * @server  bin/UdpServer_test 1234
 * @client  bin/UdpClient_test 1234
 *
 */

#include <iostream>

#include "UdpServer.h"

using namespace hv;

int main(int argc, char* argv[]) {
    int port = 1234;

    UdpServer srv;
    kcp_setting_t kcp_setting;
    srv.setKcp(&kcp_setting);
    int bindfd = srv.createsocket(port);
    if (bindfd < 0) {
        return -20;
    }
    printf("server bind on port %d, bindfd=%d ...\n", port, bindfd);
    srv.onMessage = [](const SocketChannelPtr& channel, Buffer* buf) {
        // echo
        printf("< %.*s\n", (int)buf->size(), (char*)buf->data());
        channel->write(buf);
    };
    srv.start();

    std::string str;
    while (std::getline(std::cin, str)) {
        if (str == "close") {
            srv.closesocket();
        } else if (str == "start") {
            srv.start();
        } else if (str == "stop") {
            srv.stop();
            break;
        } else {
            srv.sendto(str);
        }
    }

    return 0;
}
