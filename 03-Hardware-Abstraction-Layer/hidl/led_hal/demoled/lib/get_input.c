#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include <sys/epoll.h>
#include <linux/input.h>

#include "list_files.h"

#define MAX_EVENTS 5
#define FILE_EXIST(file_path)   (access(file_path, F_OK))
#define INPUT_DIR (!FILE_EXIST("/dev/input") ? "/dev/input/" : \
		"/home/tungnt/workspace/demo/")

int epoll_ctl_add_files(int epoll_fd, struct list_file *list, int *list_fd,
	       	struct epoll_event *ev)
{
	int fd;
	int i = 0;

	while (list != NULL) {
		printf("name: %s\n", list->file_name);
		char *file_path = (char*)malloc(strlen(INPUT_DIR) + strlen(list->file_name));
		memset(file_path, '\0', strlen(INPUT_DIR) + strlen(list->file_name));
		sprintf(file_path, "%s%s", INPUT_DIR, list->file_name);
		printf("file_path: %s\n", file_path);
		fd = open(file_path, O_RDWR);
		if (fd < 0) {
			perror("open failed\n");
			return -1;
		}
		list_fd[i] = fd;
		i++;

		ev->data.fd = fd;
		if (epoll_ctl(epoll_fd, EPOLL_CTL_ADD, fd, ev) == -1) {
			perror("Failed to add new file_fd to epoll\n");
			return -1;
		}
		list = list->next;
		free(file_path);
	}
	return 0;
}

void read_input_event(int fd)
{
	char buff[sizeof(struct input_event)];
	ssize_t len;

	len = read(fd, buff, sizeof(struct input_event));
	if (len < 0) {
		perror("read failed\n");
	} else {
		if (!FILE_EXIST("/dev/input")) {
			struct input_event *ievent = (struct input_event *)buff;
			printf("Key event - code: %u, value: %d\n",
					ievent->code, ievent->value);
		} else
			printf("read: %s\n", buff);
	}
}

int main()
{
	int ret;
	int epoll_fd;
	struct epoll_event event, events[MAX_EVENTS];
	struct list_file *list;
	int *list_fd;
	int num_files;

	list = list_dir(INPUT_DIR);
	num_files = number_of_files(list);
	list_fd = (int*)malloc(sizeof(int) * num_files);


	epoll_fd = epoll_create1(0);
	if (epoll_fd == -1) {
		perror("epoll_create1");
		return EXIT_FAILURE;
	}

	event.events = EPOLLIN;
	ret = epoll_ctl_add_files(epoll_fd, list, list_fd, &event);
	if (ret < 0) {
		return ret;
	}

	for (int i = 0; i < num_files; i++) {
		printf("file fd: %d\n", list_fd[i]);
	}
	while (1) {
		int num_events = epoll_wait(epoll_fd, events, MAX_EVENTS, -1);
		if (num_events == -1) {
			perror("Failed to wait for events\n");
			return -1;
		}
		printf("change: %d\n", num_events);

		for (int i = 0; i < num_events; i++) {
			printf("event fd: %d\n", events[i].data.fd);
			for (int j = 0; j < num_files; j++) {
				if (events[i].data.fd == list_fd[j]) {
					printf("Jump here\n");
					read_input_event(list_fd[i]);
				}
			}
		}
	}
	for (int i = 0; i < num_files; i++) {
		close(list_fd[i]);
	}
	close(epoll_fd);
}
