#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <linux/input.h>
#include <sys/epoll.h>

#define INPUT_DEVICE "/dev/input/event0"

int main() {
    int fd = open(INPUT_DEVICE, O_RDONLY);
    if (fd < 0) {
        perror("Failed to open input device");
        exit(1);
    }

    int epoll_fd = epoll_create1(0);
    if (epoll_fd < 0) {
        perror("Failed to create epoll instance");
        exit(1);
    }

    struct epoll_event event;
    event.events = EPOLLIN;
    event.data.fd = fd;

    if (epoll_ctl(epoll_fd, EPOLL_CTL_ADD, fd, &event) < 0) {
        perror("Failed to add file descriptor to epoll");
        exit(1);
    }

    struct epoll_event events[1];

    while (1) {
        int num_events = epoll_wait(epoll_fd, events, 1, -1);
        if (num_events < 0) {
            perror("Failed to wait for events");
            exit(1);
        }

        if (events[0].data.fd == fd && (events[0].events & EPOLLIN)) {
            struct input_event ev;
            ssize_t bytes = read(fd, &ev, sizeof(struct input_event));
            if (bytes < sizeof(struct input_event)) {
                perror("Failed to read input event");
                exit(1);
            }
            printf("Key event - code: %u, value: %d\n", ev.code, ev.value);
        }
    }

    close(fd);
    close(epoll_fd);

    return 0;
}