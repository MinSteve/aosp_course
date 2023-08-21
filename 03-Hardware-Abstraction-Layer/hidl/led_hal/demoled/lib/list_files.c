#include <stdio.h>
#include <dirent.h>
#include <sys/types.h>
#include <string.h>
#include <stdlib.h>

#include "list_files.h"

static void add_new_file(struct list_file **head, char *file_name)
{
	struct list_file *new_file = 
		(struct list_file*)malloc(sizeof(struct list_file));
	new_file->file_name = strdup(file_name);
	new_file->next = NULL;

	if (*head == NULL) {
		*head = new_file;
	} else {
		new_file->next = *head;
		*head = new_file;
	}
}

struct list_file *list_dir(const char *path) {
    struct dirent *entry;
    DIR *dir = opendir(path);
    struct list_file *head = NULL;

    if (dir == NULL) {
           return NULL;
    }

    while ((entry = readdir(dir)) != NULL) {
	if (!strstr(entry->d_name, ".") && !strstr(entry->d_name, "..")) {
        	add_new_file(&head, entry->d_name);
	}
    }

    closedir(dir);
    return head;
}

int number_of_files(struct list_file *list)
{
	int count = 0;
	
	while (list != NULL) {
		count++;
		list = list->next;
	}
	return count;
}
