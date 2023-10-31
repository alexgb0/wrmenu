#pragma once

#include <stdlib.h>
#include <dirent.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <spawn.h>

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
char *find_exec_ini(char *file, const char *section, const char *key);

// This function shoudn't be here but whatever
int exec_program(char *path);

void delete_files_list(struct files_list *file);
