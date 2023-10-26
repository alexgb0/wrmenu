#include <raylib.h>
#include <stdio.h>
#include <stdlib.h>

#include "parsefile.h"
#include "drawing.h"

int main()
{

	struct files_list files = list_files();

	static int screen_w = 500;
	static int screen_h = 500;

	SetTraceLogLevel(LOG_ERROR);
	InitWindow(screen_w, screen_h, "wrmenu");
	SetTargetFPS(60);

	char buff[128];
	struct input_buff buff_t = {
		.buff = buff,
		.input_buff_maxcap = 128,
		.input_buff_len = 0,
	};

	const int font_heigh = 15;
	int selected_program = 0;

	while (!WindowShouldClose())
	{
		draw_searchbox(&buff_t);

		if (IsKeyPressed(KEY_DOWN) &&
				selected_program < files.filenm_len - 1)
		{
			selected_program++;
		}
		if (IsKeyPressed(KEY_UP) && selected_program > 0)
		{
			selected_program--;
		}

		BeginDrawing();
		ClearBackground(BLACK);

		DrawText(buff_t.buff, 5, 5, 15, WHITE);
		for (int i = 0; i < files.filenm_len - 1; ++i)
		{
			DrawText(files.filenm[i], 5, (font_heigh + 5) * (i + 1), 15, 
					(i == selected_program) ? PINK : GRAY);
		}

		EndDrawing();
	}


	delete_files_list(&files);

	return 0;
}
