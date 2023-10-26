#include "drawing.h"
#include <raylib.h>


void draw_searchbox(struct input_buff *buff_t)
{
	int key = GetCharPressed();

	while (key > 0)
	{

                if ((key >= 32) && (key <= 125) && 
				(buff_t->input_buff_len < buff_t->input_buff_maxcap))
		{
			buff_t->buff[buff_t->input_buff_len] = (char)key;
			buff_t->buff[buff_t->input_buff_len+1] = '\0';
			buff_t->input_buff_len++;
		}

		key = GetCharPressed();
	}

	if (IsKeyPressed(KEY_BACKSPACE))
	{
		buff_t->input_buff_len -= 1;
		if (buff_t->input_buff_len < 0) buff_t->input_buff_len = 0;
		buff_t->buff[buff_t->input_buff_len] = '\0';
	}
}


