#pragma once

#include <stdlib.h>
#include <dirent.h>
#include <stdio.h>
#include <string.h>


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


void delete_files_list(struct files_list *file);
