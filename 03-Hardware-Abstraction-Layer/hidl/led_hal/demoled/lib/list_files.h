#ifndef __LIST_FILE_H__
#define __LIST_FILE_H__

struct list_file {
	const char *file_name;
	struct list_file *next;
};

struct list_file *list_dir(const char *path);
int number_of_files(struct list_file *list);

#endif
