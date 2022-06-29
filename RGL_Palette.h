#ifndef RGL_PALETTE_H
#define RGL_PALETTE_H

#include "SDL_include.h"

typedef struct
{
	SDL_Palette* palette;              // reference to SDL_Palette
	size_t num;                        // # of colors
	Uint8 rmask, gmask, bmask;         // masks to isolate red, green, and blue bits
	Uint8 rshift, gshift, bshift;      // # of bits masked bits should be shifted to be most significant
}
SDL_RetroPalette;

SDL_RetroPalette* SDL_CreateRetroPalette
(
	size_t num,                                  // # of colors in palette
	Uint8 rmask,  Uint8 gmask,  Uint8 bmask,     // masks to isolate red, green, and blue bits
	Uint8 rshift, Uint8 gshift, Uint8 bshift     // # of bits masked bits should be shifted to be most significant
);

void SDL_DestroyRetroPalette(SDL_RetroPalette* p);


// ==================== Return New Palettes ==================== //
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

#endif // RGL_PALETTE_H
