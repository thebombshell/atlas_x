
#include "main.h"

#include <graphics.h>
#include <log.h>
#include <vector_math.h>
#include <window.h>

#include "shaders.h"
#include <time.h>
#include <thread.h>
#include <json_import.h>

window surface;
graphics context;

thread update_thread;

int is_running = 0xFFFF;

static float current_time = 0.0f;
char input[255];

unsigned int json_read_succeeded = 0;
unsigned int json_stringify_complete = 0;
json_file json;

LRESULT CALLBACK window_proc(HWND t_handle, UINT t_message, WPARAM t_wparam, LPARAM t_lparam) 
{	
	switch (t_message)
	{		
		case WM_KEYDOWN:
		
			input[t_wparam] = 1;
		break;
		case WM_KEYUP:
			
			input[t_wparam] = 0;
		break;
		case WM_CLOSE:
			
			SYS("window received close request");
			
			PostQuitMessage(0); 
		return 0;
		case WM_QUIT:
			
			SYS("window received quit request");
			DestroyWindow(t_handle);
		return 0;
	}
	return DefWindowProc(t_handle, t_message, t_wparam, t_lparam);
}

char is_key_down(char t_key)
{	
	return input[(unsigned int)t_key];
}

void update()
{
	if (json_read_succeeded && !json_stringify_complete)
	{
		json_stringify_complete = 1;
		
		buffer string;
		
		if (json_stringify(&json, &string))
		{
			LOG("json stringify succeeded: %s", (const char*)string.data);
			
			buffer_final(&string);
		}
		else
		{
			ERR("failed to stringify json!");
		}
	}
}

void update_thread_func(void*)
{
	LOG("update thread starting");
	
	while (is_running)
	{
		update();
	}
	
	LOG("update thread ending");
}

int init()
{
	(void)current_time;
	
	int result = 0;
	
	if (json_load(&json, "test.gltf"))
	{
		json_read_succeeded = 1;
		LOG("load json successful");
	}
	else
	{
		ERR("load json failed");
	}
	
	result = thread_init(&update_thread, update_thread_func, 0);
	
	if (!result)
	{
		ERR("failed to init thread");
	}
	
	return 1;
}

int final()
{
	thread_join(&update_thread);
	
	thread_final(&update_thread);
	
	if (json_read_succeeded)
	{	
		json_final(&json);
	}
	
	return 1;
}

int main()
{
	
	SYS("initializing window");
	
	init_window(&surface, window_proc);
	
	SYS("initializing graphics");
	
	init_graphics(&context, &surface);
	
	glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	
	SYS("entering main loop");
	
	double delta;
	long long diff, start, length;
	MSG message;
	
	if (!init())
	{		
		SYS("initialization failed");
		is_running = 0;
	}
	
	SYS("initialization complete");
	
	start = clock();
	
	while (is_running)
	{		
		diff = clock() - start;
		delta = (double)diff / (double)CLOCKS_PER_SEC;
		current_time += delta;
		
		(void)delta;
		(void)current_time;
		
		start = clock();
		
		/* windows message handling */
		
		while (PeekMessage(&message, 0, 0, 0, PM_REMOVE))
		{			
			if (message.message == WM_QUIT || message.message == WM_CLOSE)
			{				
				SYS("setting running to false");
				
				is_running = 0;
				
				SYS("exiting main loop");
				
				break;
			}
			
			TranslateMessage(&message);
			DispatchMessage(&message);
		}
		
		graphics_swap_buffers(&context);
		
		/* timing */
		
		diff = clock() - start;
		length = diff * (1000 / CLOCKS_PER_SEC);
		if (length < 1000 / 60)
		{			
			Sleep(1000 / 60 - length);
		}
	}
	
	if (!final())
	{		
		SYS("finalization failed");
	}
	
	
	SYS("finalizing graphics");
	
	final_graphics(&context);
	
	SYS("finalizing window");
	
	final_window(&surface);
	
	return 0;
}


