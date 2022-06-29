#ifndef RGL_SCREEN_H
#define RGL_SCREEN_H

#pragma once
#include "SDL_include.h"
#include "RGL_Palette.h"

// ==================== RetroScreen structure ==================== //
typedef struct
{

	SDL_Window*   window;        // - SDL_Window used by screen
	SDL_Renderer* renderer;      // - SDL_Renderer used by screen
	SDL_Texture*  texture;       // - SDL_Texture that holds screen data

	SDL_PixelFormat* format;     // - pixel format of screen
	SDL_RetroPalette* palette;   // - retro palette used by screen

	Uint16 w, h;                 // - width and height of screen
}
SDL_RetroScreen;
// =============================================================== //




// ==================== Create Retro Screen ==================== //
// Returns NULL on failure                                       //
// ============================================================= //
SDL_RetroScreen* SDL_CreateRetroScreen
(
	const char* t,          // title that will appear on window
	Uint16 w, Uint16 h,     // width and height of screen
	SDL_RetroPalette* p,    // palette screen will use
	int window_flags,       // flags for SDL_Window
	int renderer_flags      // flags for SDL_Renderer
);
// ============================================================= //




// ==================== Destroy Retro Screen ==================== //
void SDL_DestroyRetroScreen
(
	SDL_RetroScreen* s      // pointer to screen to destroy
);
// ============================================================== //




// ============ Start Rendering & Prepare To Draw ============ //
void SDL_RenderRetroStart
(
	SDL_RetroScreen* s      // pointer to screen
);
// =========================================================== //




// ============ Stop Rendering & Swap Buffers ============ //
void SDL_RenderRetroFinish
(
	SDL_RetroScreen* s      // pointer to screen
);
// ======================================================= //




// ==================== Convert Surface To Retro Format ==================== //
SDL_Surface* SDL_ConvertSurfaceToRetro(SDL_RetroScreen*, SDL_Surface*);
// ========================================================================= //



// ==================== Create Retro Texture From Surface ==================== //
SDL_Texture* SDL_CreateRetroTextureFromSurface
(
	SDL_RetroScreen* scrn,    // pointer to screen
	SDL_Surface* surf,        // pointer to surface
	int bcolor                // index of color to be used as background
);
// =========================================================================== //


// ============================ Convert RGB To Retro Color ============================ //
SDL_Color SDL_RGBToRetroColor(SDL_RetroScreen* s, Uint8 r, Uint8 g, Uint8 b);
// ==================================================================================== //


// ============================ Set Draw Color (r,g,b) of SDL_RetroScreen (s) Renderer ============================ //
void SDL_SetRetroRenderDrawColor(SDL_RetroScreen* s, Uint8 r, Uint8 g, Uint8 b);
// ================================================================================================================ //

// ============== Set the Render Target of the SDL_RetroScreen (s) Renderer to Texture (t) ============== //
void SDL_SetRetroRenderTarget(SDL_RetroScreen* s, SDL_Texture* t);
// ====================================================================================================== //

#endif // RGL_SCREEN_H
