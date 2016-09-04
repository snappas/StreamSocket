//
// Created by ryan on 9/3/16.
//

#include "Epoll_If.hxx"
#include "ServerDescriptor.hxx"
#include "ClientDescriptor.hxx"
#include "FileDescriptor.hxx"
#include <sys/epoll.h>


void Epoll_If::event_loop() {
    epoll_event events[64]; /* concurrent events per iteration */

    int descriptors_count = epoll_wait(epollfd, events, 64, -1); /* block until any descriptors change */

    for (int i = 0; i < descriptors_count; ++i) {
        Descriptor* desc = reinterpret_cast<Descriptor*>(events[i].data.ptr);
        if(events[i].events & EPOLLOUT || events[i].events & EPOLLIN) {
            switch (desc->get_type()) {
                case Descriptor::SERVER:
                {
                    ServerDescriptor *sd = reinterpret_cast<ServerDescriptor *>(events[i].data.ptr);
                    int peer_fd = sd->accept_nonblocking();
                    if (peer_fd != -1) {
                        add_client_descriptor(peer_fd);
                    }
                    break;
                }

                case Descriptor::CLIENT:
                {
                    ClientDescriptor *cd = reinterpret_cast<ClientDescriptor *>(events[i].data.ptr);
                    set_fd(cd->do_io(events[i].events), cd);
                    break;
                }

                case Descriptor::FILE:
                {
                    FileDescriptor *fd = reinterpret_cast<FileDescriptor*>(events[i].data.ptr);
                    set_fd(fd->do_io(events[i].events), fd);
                    break;
                }

                default:
                    continue;
            }
        } else {
            perror("epoll_wait");
            continue;
        }
    }
}

void Epoll_If::init() {
    epollfd = epoll_create1(0);
}

void Epoll_If::add_server_descriptor(int fd) {
    epoll_event event;
    if (fd != -1) {
        event.data.ptr = new ServerDescriptor(fd);
        event.events = EPOLLIN | EPOLLET;
        if (epoll_ctl(epollfd, EPOLL_CTL_ADD, fd, &event) == -1) {
            perror("epoll_ctl");
        }
    }
}

void Epoll_If::add_client_descriptor(int fd) {
    epoll_event event;
    if (fd != -1) {
        event.data.ptr = new ClientDescriptor(fd, model);
        event.events = EPOLLIN | EPOLLET | EPOLLONESHOT;
        if (epoll_ctl(epollfd, EPOLL_CTL_ADD, fd, &event) == -1) {
            perror("epoll_ctl epolladd");
        }
    }
}

void Epoll_If::add_file_descriptor(int fd) {
    epoll_event event;
    if (fd != -1) {
        event.data.ptr = new FileDescriptor(fd, model);
        event.events = EPOLLIN | EPOLLET | EPOLLONESHOT;
        if (epoll_ctl(epollfd, EPOLL_CTL_ADD, fd, &event) == -1) {
            perror("epoll_ctl epolladd");
        }
    }
}

void Epoll_If::set_fd(int io, Descriptor* desc) {
    epoll_event event;
    event.data.ptr = desc;
    if(io == Descriptor::WRITABLE){
        event.events = EPOLLET | EPOLLOUT | EPOLLONESHOT;
        if (epoll_ctl(epollfd, EPOLL_CTL_MOD, desc->get_descriptor(), &event) != 0) {
            perror("epoll_ctl epollout");
        }
    }else if(io == Descriptor::READABLE){
        event.events = EPOLLET | EPOLLIN | EPOLLONESHOT;
        if (epoll_ctl(epollfd, EPOLL_CTL_MOD, desc->get_descriptor(), &event) != 0) {
            perror("epoll_ctl epollin");
        }
    } else {
        if (epoll_ctl(epollfd, EPOLL_CTL_DEL, desc->get_descriptor(), &event) != 0) {
            perror("epoll_ctl epolldel");
        }
        delete desc;
    }

}

Epoll_If::Epoll_If(DataModel *model) : model(model) {
    init();
}
