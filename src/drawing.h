#pragma once

#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

#include <raylib.h>

#include "parsefile.h"

struct input_buff
{
	char *buff;
	int input_buff_len;
	int input_buff_maxcap;
};


void draw_searchbox(struct input_buff *buff_t);
void draw_program_list(struct program_list *list);
