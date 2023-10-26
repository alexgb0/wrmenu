#pragma once

#include <stdlib.h>
#include <dirent.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h> 

#define DESKTOP_PATH "/usr/share/applications/"

struct program_list
{
	char *names;
	int names_len;

	char *execnm;
	int execnm_len;

	int selected;
};

struct files_list
{
	char **filenm;
	int filenm_len;
};

struct files_list list_files();

// Make sure to free the return string
char *get_exec(const char *filename);
char *parse_ini(const char *file, const char *key);

void delete_files_list(struct files_list *file);
