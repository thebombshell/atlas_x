
#ifndef SMOL_WINDOW_H
#define SMOL_WINDOW_H

#include <windows.h>

/**
 *	@struct		window 
 *	@brief a struct containing window information
 *	@var		window::handle - a handle to the relevant window
 *	@var		window::is_running - if non-zero the window is open and running
 */
typedef struct {
	
	HWND handle;
	int is_running;
} window;

/** returns nonzero if the window is valid
 *	@memberof	window
 *	@param		t_window - the window the check for validity
 *	@returns	nonzero if the window is valid
 */
int window_is_valid(window* t_window);

/** initializes the given window
 *	@memberof	window
 *	@param		t_window - an invalid window to be initialized
 *	@param		t_proc - the windows procedure function for this window
 *	@returns	nonzero if initialized successfully
 */
int init_window(window* t_window, WNDPROC t_proc);

/** finalizes the given window
 *	@memberof	window
 *	@param		t_window - a valid window to be finalized
 */
void final_window(window* t_window);

unsigned int window_get_width(window* t_window);

unsigned int window_get_height(window* t_window);

#endif