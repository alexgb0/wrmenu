#include "parsefile.h"
#include <assert.h>
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>

extern char **environ;

struct files_list FILE_ERROR = {NULL, -1};

struct files_list list_files()
{
	DIR *dir;
	struct dirent *ent;

	char **names = malloc(sizeof(char*));
	int size = 1;

	if ((dir = opendir(DESKTOP_PATH)) != NULL)
	{
		while ((ent = readdir(dir)) != NULL)
		{

			int str_len = strlen(ent->d_name) + 1;
			if (str_len <= 0)
			{
				free(names);
				return FILE_ERROR;
			}

			char* str_mem = malloc(str_len * sizeof(char));
			if (str_mem == NULL)
			{
				free(names);
				return FILE_ERROR;
			}

			str_mem = memcpy(str_mem, ent->d_name, str_len);
			if (str_mem == NULL)
			{
				free(names);
				free(str_mem);
				return FILE_ERROR;
			}
			
			if (ent->d_name[0] == '.')
			{
				free(str_mem);
				continue;
			}

			names = reallocarray(names, size, sizeof(char*));
			if (names == NULL)
			{
				free(names);
			}

			names[size-1] = str_mem;

			size++;
		}

		closedir(dir);
	}
	else 
	{
		perror("can't open the file");
	}


	return (struct files_list){
		.filenm = names,
		.filenm_len = size
	};
}



char *get_exec(const char *filename)
{
	int fname_size = strlen(filename) + 1;
	int dsknm = strlen(DESKTOP_PATH) + 1;
	if (fname_size <= 0)
		return NULL;
	char *fcpy = malloc((fname_size + dsknm) * sizeof(char));
	if (fcpy == NULL)
		return NULL;
	
	fcpy = strcpy(fcpy, DESKTOP_PATH);
	assert(fcpy != NULL);
	fcpy = strcat(fcpy, filename);
	assert(fcpy != NULL);

	struct stat st;
	int st_success = stat(fcpy, &st);

	if (st_success == 0)
	{

		FILE *fp;
		fp = fopen(fcpy, "r");
		assert(fp != NULL); // Is impossible to not find the folder
		
		free(fcpy);

		char *file = malloc(st.st_size);
		int err = fread(file, 1, st.st_size, fp);

		if (err != st.st_size)
		{
			free(file);
			return NULL;
		}

		char *exec = find_exec_ini(file, "[Desktop Entry]", "Exec");
		assert(("Exec file not found!", exec != NULL)); // Again for being able to do anything we have to find this entry
		if (exec != NULL)
			free(file);

		return exec;
	}

	return NULL;
}

// 27/10/2023: This function explodes if it can't find the exec.
// By default **should** be able to find it.
char *find_exec_ini(char *file, const char *section, const char *key)
{
	int in_section = 0;
	char *ptr = NULL;

	for (char *line = strtok(file, "\n"); line != NULL; line = strtok(NULL, "\n"))
	{
		if (line == NULL)
			continue;

		if (line[0] == '[')
		{
			if (strcmp(line, section) == 0)
				in_section = 1;
			else
				in_section = 0;

			continue;
		}

		if (in_section)
		{
			char buff_key[128];
			char buff_value[128];
			int n = sscanf(line, "%4s=%s", buff_key, buff_value);
			if (n != 2)
				continue;

			if (strcmp(buff_key, key) == 0)
			{
				int len = strlen(buff_value) + 1;
				assert(len > 0);
				ptr = malloc(len * sizeof(char));
				if (ptr == NULL)
					return NULL;
				ptr = strcpy(ptr, buff_value);
				assert(ptr != NULL);
				ptr[len] = '\0';

				printf("path: %s\n", buff_value);

				break;
			}
		}

	}

	return ptr;
}

int exec_program(char *path)
{
	assert(path != NULL);
	pid_t pid;
	char **env = environ;
	char *argv[] = {"sh", "-c", path, NULL};

	int status = posix_spawn(&pid, "/bin/sh", NULL, NULL, argv, env);
	
	return status;
}

void delete_files_list(struct files_list *file)
{
	for (int i = 0; i < file->filenm_len - 1; i++)
		free(file->filenm[i]);
	free(file->filenm);
}
