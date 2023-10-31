#include <raylib.h>
#include <stdio.h>
#include <stdlib.h>

#include "config.h"
#include "parsefile.h"
#include "drawing.h"

int main(int argc, char **argv, char **envp)
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
	char *exec;

	Font font = LoadFont(FONT_PATH);

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

		if (IsKeyPressed(KEY_ENTER))
		{
			exec = get_exec(files.filenm[selected_program]);
			exec_program(exec);
			goto EXIT;
		}

		BeginDrawing();
		ClearBackground(BLACK);

		DrawTextEx(font, buff_t.buff, (Vector2){5, 5}, 15, 0.5f, WHITE);
		//DrawText(buff_t.buff, 5, 5, 15, WHITE);
		for (int i = 0; i < files.filenm_len - 1; ++i)
		{
			DrawTextEx(
					font, 
					files.filenm[i], 
					(Vector2){5, (font_heigh + 5) * (i + 1)},
					15, 
					0.5f,
					(i == selected_program) ? PINK : GRAY
			);
		}

		EndDrawing();
	}
EXIT:
	printf("closing the program...\n");

	UnloadFont(font);
	free(exec);
	delete_files_list(&files);

	return 0;
}
