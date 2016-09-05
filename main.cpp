#include <iostream>
#include "ExternalProcess.hxx"
#include "Epoll_If.hxx"
#include "Server.hxx"

int main() {
    ExternalProcess telnet("telnet 192.168.1.13 30000");
    DataModel temperature;
    Epoll_If epoll(&temperature);
    Server server("127.0.0.1", 32001);
    epoll.add_descriptor(Descriptor::SERVER, server.get_descriptor());
    epoll.add_descriptor(Descriptor::FILE, telnet.start_process().get_descriptor());
    while(1){
        epoll.event_loop();
    }
}