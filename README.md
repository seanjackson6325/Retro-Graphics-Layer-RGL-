# RGL (Retro Graphics Layer)
RGL is a software layer on top of SDL2 written in C with the goal of easily creating convincing retro graphics.
I created this to simplify my rendering code, as well as to partially automate the task of creating pixel art.
Features include:
- Functions to convert 24-bit color bitmaps to retro resolution and color palettes (to make pixel art easy)
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
 - Returns NULL on failure


#### void SDL_DestroyRetroScreen(SDL_RetroScreen*)
 - Use this to free memory used by a SDL_RetroScreen
 - Keep in mind that the SDL_RetroPalette will also be freed


#### SDL_RetroPalette* SDL_CreateRetroPalette(...)

	SDL_RetroPalette* SDL_CreateRetroPalette
 	(
  		size_t num,                                 // desired # of colors in the palette (256 max)
    	Uint8 rmask,  Uint8 gmask,  Uint8 bmask,    // masks to isolate red, green, and blue bits
      	Uint8 rshift, Uint8 gshift, Uint8 bshift    // # of places masked bits should be shifted to be most significant
	)
 - Returns a pointer to a SDL_RetroPalette created in heap memory. Should be cleaned up using SDL_DestroyRetroPalette(...)
 - Keep in mind that SDL_DestroyRetroScreen(...) destroys it's associated SDL_RetroPalette
 - Returns NULL on failure


#### void SDL_DestroyRetroPalette(SDL_RetroPalette*)
 - Use this to free memory used by a SDL_RetroPalette
 - Keep in mind that SDL_DestroyRetroScreen(...) destroys it's associated SDL_RetroPalette


#### SDL_Surface* SDL_ConvertSurfaceToRetro(SDL_RetroScreen*, SDL_Surface*)
 - Use this to convert a 24-bit color SDL_Surface to the pixel format used by the SDL_RetroScreen
 - A pointer to a new SDL_Surface is returned, and the original is unaltered
 - Returns NULL on failure


#### SDL_Texture* SDL_CreateRetroTextureFromSurface(SDL_RetroScreen*, SDL_Surface*, int bcolor)
 - Use this to convert a 24-bit color SDL_Surface to a texture that can be blitted and scaled to a SDL_RetroScreen
 - A pointer to a new SDL_Texture is returned, and the source SDL_Surface is unaltered
 - Keep in mind that this functions calls SDL_ConvertSurfaceToRetro internally, so it would be redundant to use an already converted surface as the source
 - Returns NULL on failure


#### SDL_Color* SDL_RGBToRetroColor(SDL_RetroScreen*, Uint8 r, Uint8 g, Uint8 b)
 - Convert a 24-bit color to it's closest color in the color palette of the SDL_RetroScreen
 - This is useful if you need to convert specific colors for some reason (such as rendering geometry). Otherwise, it's much safer to convert Surfaces using SDL_ConvertSurfaceToRetro and SDL_CreateRetroTextureFromSurface


#### void SDL_SetRetroRenderDrawColor(SDL_RetroScreen*, Uint8 r, Uint8 g, Uint8 b)
 - Set the current draw color of a SDL_RetroScreen.
 - The 24-bit color value will be converted to it's closest color in the color palette of the SDL_RetroScreen using SDL_RGBToRetroColor



#### void SDL_SetRetroRenderTarget(SDL_RetroScreen*, SDL_Texture*)
 - Change the current rendering target of the SDL_RetroScreen to a different rendering target than that of the frame buffer of the SDL_RetroScreen. To switch back to the frame buffer, pass in NULL for the SDL_Texture*






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
