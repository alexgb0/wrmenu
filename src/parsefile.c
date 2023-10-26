#include "parsefile.h"
#include <assert.h>
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>

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
			assert(str_len > 0);
			char* str_mem = malloc(str_len * sizeof(char));
			assert(str_mem != NULL);

			str_mem = memcpy(str_mem, ent->d_name, str_len);
			assert(str_mem != NULL);
			
			if (ent->d_name[0] == '.')
			{
				free(str_mem);
				continue;
			}

			names = reallocarray(names, size, sizeof(char*));
			assert(names != NULL);

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







void delete_files_list(struct files_list *file)
{
	for (int i = 0; i < file->filenm_len - 1; i++)
		free(file->filenm[i]);
	free(file->filenm);
}
