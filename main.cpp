#include <iostream>
#include "ExternalProcess.hxx"
#include "Epoll_If.hxx"
#include "Server.hxx"

int main() {
    ExternalProcess telnet("telnet 192.168.1.13 30000");
    DataModel temperature;
    Epoll_If epoll(&temperature);
    Server server("127.0.0.1", 32001);
    epoll.add_server_descriptor(server.get_server_file_descriptor());
    epoll.add_file_descriptor(telnet.get_file_descriptor());
    while(1){
        epoll.event_loop();
    }
}