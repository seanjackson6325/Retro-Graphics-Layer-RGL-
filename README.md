# RGL (Retro Graphics Layer)
RGL is a software layer on top of SDL2 written in C with the goal of easily creating convincing retro graphics. Features include:
- Functions to convert bitmaps to retro resolution and color palettes
- Choosing a specific color to use as a transparency color in textures
- The ability to create custom color palettes and apply them to textures
- Many pre-made retro color palletes in 4 bit, 6 bit and 8 bit color




## Data types:



#### SDL_RetroScreen

- A window and rendering structure for rendering retro graphics. The structure's variables are complex and should not be tampered with. Every rendering function goes back to this structure.


#### SDL_RetroPalette

- A structure that's used to create a custon retro color palette. This structure is complex and the variables should not be tampered with directly.



## Functions:


#### SDL_RetroScreen* SDL_CreateRetroScreen(...)

	SDL_RetroScreen* SDL_CreateRetroScreen
 	(
  		const char* t,         // title that will appear on window
    	Uint16 w, Uint16 h,    // width and height of screen buffer (not window)
      	SDL_RetroPalette* p,   // retro palette screen will use
		int window_flags,      // flags for SDL_Window
  		int render_flags       // flags for SDL_Renderer
	)
 - Returns a pointer to a SDL_RetroScreen created in heap memory. Should be cleaned up using SDL_DestroyRetroScreen(...)


#### SDL_RetroScreen* SDL_CreateRetroScreen(...)
 - Use this to free memory used by a SDL_RetroScreen


## Examples:

#### Run a loop for five seconds


	#include <stdio.h>
	#include "epoch.h"
	
	int main(int argc, char* argv[])
	{
	    // Initialize Epoch
	    Epoch__Init();
	
	    // Create a new timer
	    Epoch_t timer;
	
	    // Start the timer
	    Epoch__Start(&timer);
	    // Keep track of elapsed time
	    double elapsed;
	
	    // Print out elapsed time
	    // for five seconds
	    do
	    {
	        // Get change in time since the
	        // timer was started
	        elapsed = Epoch__QueryChange(&timer);
	        printf("%f\n", elapsed);
	    }
	    while (elapsed < 5.0);
	}

#### Get local time info

	#include <stdio.h>
	#include "epoch.h"
	
	int main(int argc, char* argv[])
	{
	    // Initialize Epoch
	    Epoch__Init();
	
	    // Used to hold system information
	    Epoch_SysInfo_t info;
	
	    // Get current system information (local time)
	    Epoch__QuerySysInfo(&info, EPOCH_LOCAL_TIME);
	
	    // Print some info
	    printf("Current Year: %d\n", info.year);
	    printf("Current Month: %d\n", info.month);
	    printf("Current Weekday: %d\n", info.weekday);
	    printf("Current Day: %d\n", info.day);
	    printf("Current Hour: %d\n", info.hour);
	    printf("Current Minute: %d\n", info.minute);
	    printf("Current Second: %d\n", info.second);
	}
