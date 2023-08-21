#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include <sys/epoll.h>
#include <sys/inotify.h>
#include <linux/input.h>

#define MAX_SIZE_OF_FILE_NAME		50
#define MAX_EVENTS 5
#define EVENT_SIZE (sizeof(struct inotify_event))
#define BUFFER_SIZE (MAX_EVENTS * (EVENT_SIZE + MAX_SIZE_OF_FILE_NAME))

#define FILE_EXIST(file_path)	(access(file_path, F_OK))
#define INPUT_DIR (!FILE_EXIST("/dev/input") ? "/dev/input/" : \
		"/home/tungnt/workspace/demo/")

void read_input_event(const char *file_path)
{
	char buff[sizeof(struct input_event)];
	ssize_t len;

	printf("file_path: %s\n", file_path);
	int fd = open(file_path, O_RDONLY);

	if (fd == -1) {
		perror("open\n");
	}
	len = read(fd, buff, sizeof(struct input_event));
	if (len < 0 ) {
		perror("read failed\n");
	} else {
		if (!FILE_EXIST("/dev/input")) {
			struct input_event *ievent = (struct input_event *)buff;
			printf("Key event - code: %u, value: %d\n", 
					ievent->code, ievent->value);
		} else
			printf("read: %s\n", buff);
	}
	close(fd);
}

int main() {
	int epoll_fd, inotify_fd, wd;
	struct epoll_event event, events[MAX_EVENTS];
	struct inotify_event* event_ptr;
	char buffer[BUFFER_SIZE];

	epoll_fd = epoll_create1(0);
	if (epoll_fd == -1) {
		perror("epoll_create1");
		return EXIT_FAILURE;
	}

	inotify_fd = inotify_init();
	if (inotify_fd == -1) {
		perror("inotify_init");
		return EXIT_FAILURE;
	}

	event.events = EPOLLIN;
	event.data.fd = inotify_fd;
	if (epoll_ctl(epoll_fd, EPOLL_CTL_ADD, inotify_fd, &event) == -1) {
		perror("epoll_ctl - inotify_fd");
		return EXIT_FAILURE;
	}

	wd = inotify_add_watch(inotify_fd, INPUT_DIR, IN_MODIFY);
	if (wd == -1) {
		perror("inotify_add_watch");
		return EXIT_FAILURE;
	}

	while (1) {
		int num_events = epoll_wait(epoll_fd, events, MAX_EVENTS, -1);
		if (num_events == -1) {
			perror("epoll_wait");
			return EXIT_FAILURE;
		}
	
		printf("have file modified\n");
		printf("inotify fd: %d\n", inotify_fd);
		for (int i = 0; i < num_events; i++) {
			if (events[i].data.fd == inotify_fd) {
			ssize_t len = read(inotify_fd, buffer, BUFFER_SIZE);
				if (len == -1) {
					perror("read - inotify_fd");
					return EXIT_FAILURE;
				}

				for (char* ptr = buffer; ptr < buffer + len;
					ptr += EVENT_SIZE + event_ptr->len) {
					event_ptr = (struct inotify_event*)ptr;
					if (event_ptr->mask & IN_MODIFY) {
						printf("File accessed: %s\n", 
							event_ptr->name);
						char *file_path = 
						(char *)malloc(strlen(INPUT_DIR)
							+ event_ptr->len);
						sprintf(file_path, "%s%s", 
						INPUT_DIR, event_ptr->name);
						read_input_event(file_path);
						free(file_path);
					}
				}
			}
		}
	}

    inotify_rm_watch(inotify_fd, wd);
    close(inotify_fd);
    close(epoll_fd);

    return EXIT_SUCCESS;
}
