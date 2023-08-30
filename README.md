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
 - bcolor is the index of the color in the color palette of the SDL_RetroScreen to use as a background color. Pixels with color index of bcolor will not be rendered. This is similar to how 8-bit and 16-bit consoles dealt with removing backgrounds from bitmaps. Pass in -1 if there is no background color to be removed.
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


#### All function for pre-made color palettes
 - All functions below return a pointer to a SDL_RetroColorPalette
 - The last 3 digits at the end of each function name refer to how many bits are used for red, green, and blue. For example, "332" means 3 bits for red, 3 bits for green, and 2 bits for blue.
 - It's recommended to use these color palettes over creating your own (just because it's easier) but all of the functions above give you the tools to also generate your own custom color palette.
	
 		SDL_RetroPalette* SDL_CreateRetroPaletteRGB233();
		SDL_RetroPalette* SDL_CreateRetroPaletteRGB323();
		SDL_RetroPalette* SDL_CreateRetroPaletteRGB332();

		SDL_RetroPalette* SDL_CreateRetroPaletteRGB223();
		SDL_RetroPalette* SDL_CreateRetroPaletteRGB232();
		SDL_RetroPalette* SDL_CreateRetroPaletteRGB322();

		SDL_RetroPalette* SDL_CreateRetroPaletteRGB123();
		SDL_RetroPalette* SDL_CreateRetroPaletteRGB132();
		SDL_RetroPalette* SDL_CreateRetroPaletteRGB231();
		SDL_RetroPalette* SDL_CreateRetroPaletteRGB321();
		SDL_RetroPalette* SDL_CreateRetroPaletteRGB222();

		SDL_RetroPalette* SDL_CreateRetroPaletteRGB122();
		SDL_RetroPalette* SDL_CreateRetroPaletteRGB212();
		SDL_RetroPalette* SDL_CreateRetroPaletteRGB221();

		SDL_RetroPalette* SDL_CreateRetroPaletteRGB112();
		SDL_RetroPalette* SDL_CreateRetroPaletteRGB121();
		SDL_RetroPalette* SDL_CreateRetroPaletteRGB211();

		SDL_RetroPalette* SDL_CreateRetroPaletteRGB111();
	




## Examples:

#### Run a loop for five seconds


	#include <stdbool.h>
	#include "RGL.h"
	
	// A pointer for the SDL_RetroScreen
	SDL_RetroScreen* screen;
	// A pointer to the SDL_RetroPalette for the screen
	SDL_RetroPalette* palette;
	
	// A pointer to a test texture
	SDL_Texture* texture;
	
	// initialize screen and SDL
	void init()
	{
		SDL_Init(SDL_INIT_EVERYTHING);
	
		// Create a 256 color palette
		// 3 bits red, 2 bits green, 3 bits blue
		palette = SDL_CreateRetroPaletteRGB323();
	
		// create a new retro screen
		screen = SDL_CreateRetroScreen
		(
			"A 256 color landscape...",
			320, 240,
			palette,
			SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE,
			SDL_RENDERER_ACCELERATED
		);
	
		// create a surface and load a bitmap
		SDL_Surface* surf = SDL_LoadBMP("testbmp5.bmp");
		// create a retro, converted texture from the surface
		texture = SDL_CreateRetroTextureFromSurface(screen, surf, -1);
	}
	
	// just to clean up
	void close()
	{
		//destroy the texture
		SDL_DestroyTexture(texture);
	
		// destroy the retro screen
		// also destroys the palette!
		SDL_DestroyRetroScreen(screen);
	
		// free all SDL resources
		SDL_Quit();
	}
	
	// render the image
	void render()
	{
		// prepare screen for rendering...
		SDL_RenderRetroStart(screen);
	
		// draw the texture
		SDL_RenderCopy(screen->renderer, texture, NULL, NULL);
	
		// finish render, let SDL swap buffers etc.
		// this function calls SDL_RenderPresent
		SDL_RenderRetroFinish(screen);
	}
	
	// poll events for window and rendering
	void run()
	{
		init();
	
		bool running = true;
		SDL_Event event;
	
		while (running)
		{
			while (SDL_PollEvent(&event))
			{
				if (event.type == SDL_QUIT)
				{
					running = false;
				}
			}
			render();
		}
	}
	
	
	int main(int argc, char** argv)
	{
		run();
		return 0;
	}
