
#include "main.h"

#include <graphics.h>
#include <log.h>
#include <vector_math.h>
#include <window.h>

#include "shaders.h"
#include <time.h>
#include <fbx_import.h>

window surface;
graphics context;

static float current_time = 0.0f;

char input[255];

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

int init()
{
	(void)current_time;
	
	fbx _fbx;
	if (fbx_load(&_fbx, "test.fbx"))
	{	
		LOG("load fbx successful");
		
		buffer out_buffer;
		
		int result = fbx_stringify(&_fbx, &out_buffer); 
		
		if (!result)
		{
			ERR("stringify has failed");
		}
		
		fbx_final(&_fbx);
		
		WRN("%s", (char*)out_buffer.data);
	}
	else
	{
		ERR("failed to load fbx");
	}
	
	return 1;
}

int final()
{	
	return 1;
}

int main()
{	
	int is_running = 0xFFFF;
	
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
		SYS("initialization succeeded");
	}
	
	
	SYS("finalizing graphics");
	
	final_graphics(&context);
	
	SYS("finalizing window");
	
	final_window(&surface);
	
	return 0;
}


