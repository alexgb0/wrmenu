#include <raylib.h>
#include <stdio.h>
#include <stdlib.h>

#include "parsefile.h"
#include "drawing.h"

int main()
{

	struct files_list files = list_files();

	static int screen_w = 800;
	static int screen_h = 100;

	SetTraceLogLevel(LOG_ERROR);
	InitWindow(screen_w, screen_h, "wrmenu");
	SetTargetFPS(60);

	char buff[128];
	struct input_buff buff_t = {
		.buff = buff,
		.input_buff_maxcap = 128,
		.input_buff_len = 0,
	};


	while (!WindowShouldClose())
	{
		draw_searchbox(&buff_t);
		

		BeginDrawing();
		ClearBackground(BLACK);
		DrawText(buff_t.buff, 5, 5, 15, WHITE);
		EndDrawing();
	}


	delete_files_list(&files);

	return 0;
}
