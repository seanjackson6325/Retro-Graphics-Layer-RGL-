#include "RGL_Palette.h"
#include "RGL_Screen.h"
#include <stdio.h>

// ============================ Create Retro Palette ============================ //
SDL_RetroPalette* SDL_CreateRetroPalette
(
	const size_t num,                            // # of colors in palette
	Uint8 rmask,  Uint8 gmask,  Uint8 bmask,     // masks to isolate red, green, and blue bits
	Uint8 rshift, Uint8 gshift, Uint8 bshift     // # of bits masked bits should be shifted to be most significant
)
{
	// for printing alloc errors:
	const char* allocFail = "RGL: Could not alloc memory for ";
	// allocate new RetroPalette:
	SDL_RetroPalette* rpal = malloc(sizeof(SDL_RetroPalette));
	// check if RetroPalette allocation failed:
	if(rpal == NULL) 
		("%sSDL_RetroPalette", allocFail);
	else // if not...
	{
		// color array of palette:
		SDL_Color colors[256];
		// fill color array:
		for(Uint16 color = 0; color < num; color++)
		{
			// macro to convert color compontent (r, g, or b) to screen palette:
			#define CNV(c) (color & c##mask) << c##shift
			// init each color in color array:
			colors[color] = (SDL_Color) { CNV(r), CNV(g), CNV(b), 255 } ;
			// undefine:
			#undef CNV
		}
		// alloc palette memory:
		SDL_Palette* pal = SDL_AllocPalette(num);
		// check if palette allocation failed:
		if(pal == NULL)
		{
			SDL_DestroyRetroPalette(rpal);
			printf("%sSDL_RetroPalette", allocFail);
		}
		else // if not...
		{
			// init SDL_Palette:
			SDL_SetPaletteColors(pal, colors, 0, num);
			rpal->palette = pal;
			// init RetroPalette # of colors:
			rpal->num = num;
			// macro for initializing masks and shifts of r, g, and b components
			#define SET(c) rpal->c##mask = c##mask, rpal->c##shift = c##shift
			// init RetroPalette masks and shifts:
			SET(r);  SET(g); SET(b);
			#undef SET
			// and finally:
			return rpal;
		}
	}
	return NULL;
}




// ============================ Destroy Retro Palette ============================ //
void SDL_DestroyRetroPalette(SDL_RetroPalette* p)
{
	SDL_FreePalette(p->palette);
	free(p);
}


// ============================ Return New Premade Palettes ============================ //
#define INIT            SDL_CreateRetroPalette
#define CREATE_PAL(pal) SDL_CreateRetroPalette##pal

// 256 colors:
SDL_RetroPalette* CREATE_PAL(RGB233)() { return INIT( 256, 0b11000000, 0b00111000, 0b00000111, 0, 2, 5 ); }
SDL_RetroPalette* CREATE_PAL(RGB323)() { return INIT( 256, 0b11100000, 0b00011000, 0b00000111, 0, 3, 5 ); }
SDL_RetroPalette* CREATE_PAL(RGB332)() { return INIT( 256, 0b11100000, 0b00011100, 0b00000011, 0, 3, 6 ); }
// 128 colors:
SDL_RetroPalette* CREATE_PAL(RGB223)() { return INIT( 128, 0b01100000, 0b00011000, 0b00000111, 1, 3, 5 ); }
SDL_RetroPalette* CREATE_PAL(RGB232)() { return INIT( 128, 0b01100000, 0b00011100, 0b00000011, 1, 3, 6 ); }
SDL_RetroPalette* CREATE_PAL(RGB322)() { return INIT( 128, 0b01110000, 0b00001100, 0b00000011, 1, 4, 6 ); }
// 64  colors:
SDL_RetroPalette* CREATE_PAL(RGB123)() { return INIT( 64 , 0b00100000, 0b00011000, 0b00000111, 2, 3, 5 ); }
SDL_RetroPalette* CREATE_PAL(RGB132)() { return INIT( 64 , 0b00100000, 0b00011100, 0b00000011, 2, 3, 6 ); }
SDL_RetroPalette* CREATE_PAL(RGB231)() { return INIT( 64 , 0b00110000, 0b00001110, 0b00000001, 2, 4, 7 ); }
SDL_RetroPalette* CREATE_PAL(RGB321)() { return INIT( 64 , 0b00111000, 0b00000110, 0b00000001, 2, 5, 7 ); }
SDL_RetroPalette* CREATE_PAL(RGB222)() { return INIT( 64 , 0b00110000, 0b00001100, 0b00000011, 2, 4, 6 ); }
// 32  colors:
SDL_RetroPalette* CREATE_PAL(RGB122)() { return INIT( 32 , 0b00010000, 0b00001100, 0b00000011, 3, 4, 6 ); }
SDL_RetroPalette* CREATE_PAL(RGB212)() { return INIT( 32 , 0b00011000, 0b00000100, 0b00000011, 3, 5, 6 ); }
SDL_RetroPalette* CREATE_PAL(RGB221)() { return INIT( 32 , 0b00011000, 0b00000110, 0b00000001, 3, 5, 7 ); }
// 16  colors:
SDL_RetroPalette* CREATE_PAL(RGB112)() { return INIT( 16 , 0b00001000, 0b00000100, 0b00000011, 4, 5, 6 ); }
SDL_RetroPalette* CREATE_PAL(RGB121)() { return INIT( 16 , 0b00001000, 0b00000110, 0b00000001, 4, 5, 7 ); }
SDL_RetroPalette* CREATE_PAL(RGB211)() { return INIT( 16 , 0b00001100, 0b00000010, 0b00000001, 4, 6, 7 ); }
// 8   colors:
SDL_RetroPalette* CREATE_PAL(RGB111)() { return INIT( 8  , 0b00000100, 0b00000010, 0b00000001, 5, 6, 7 ); }

#undef INIT
#undef CREATE_PAL
