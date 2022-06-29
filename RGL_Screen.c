#include <stdio.h>
#include <stdlib.h>
#include "RGL_Screen.h"
#include "RGL_Palette.h"



// ==================== Create Retro Pixel Format ==================== //
// Returns NULL on failure                                             //
// =================================================================== //
SDL_PixelFormat* SDL_CreateRetroPixelFormat(SDL_Palette* p)
{
	// alloc memory for SDL_PixelFormat:
	SDL_PixelFormat* f = malloc(sizeof(SDL_PixelFormat));
	// check if pixel format allocation successful:
	if(f == NULL)    SDL_Log("RGL: Could not alloc memory for SDL_PixelFormat");
	else    // if successful:
	{
		// init pixel format:
		f->Rmask = f->Gmask = f->Bmask = f->Amask = 0;
		f->Rloss = f->Gloss = f->Bloss = f->Aloss = 8;
		f->Rshift= f->Gshift= f->Bshift= f->Ashift= 0;
		f->palette = p;    f->refcount = 0;
		f->format = SDL_PIXELFORMAT_INDEX8;
		f->BitsPerPixel = 8;    f->BytesPerPixel = 1;
	}
	return f;
}


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
)
{
	const char* initFail  = "RGL: Could not init";
	const char* allocFail = "RGL: Could not allocate memory for";

	// alloc memory for RGL_Screen:
	SDL_RetroScreen* screen = malloc(sizeof(SDL_RetroScreen));
	// check if memory could be allocated:
	if(screen == NULL) printf("%s new SDL_RetroScreen", allocFail);
	else    // if successful:
	{
		// init width and height of screen:
		screen->w = w;    screen->h = h;
		// init retro palette:
		screen->palette = p;
		// init SDL_Window:
		int pos = SDL_WINDOWPOS_CENTERED;
		screen->window = SDL_CreateWindow(t, pos, pos, w, h, window_flags);
		// check if window initialization was successful:
		if(screen->window == NULL) printf("RGL: %s", SDL_GetError());
		else    // if successful:
		{
			// init SDL_Renderer:
			screen->renderer = SDL_CreateRenderer(screen->window, -1, renderer_flags);
			SDL_RenderSetLogicalSize(screen->renderer, w, h);
			SDL_SetRenderDrawBlendMode(screen->renderer, SDL_BLENDMODE_BLEND);
			// check if renderer initialization successful:
			if(screen->renderer == NULL) printf("RGL: %s", SDL_GetError());
			else    // if successful:
			{
				// init screen pixel format:
				screen->format = SDL_CreateRetroPixelFormat(p->palette);
				// check if pixel format initialization successful:
				if(screen->format == NULL) printf("%s SDL_PixelFormat", allocFail);
				else    // if successful:
				{
					// init SDL_Texture:
					screen->texture = SDL_CreateTexture(screen->renderer,
							  SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, w, h);

					// check if texture initialization successful:
					if(screen->texture == NULL) printf("RGL: %s", SDL_GetError());
					else return screen;
				}
			}
		}
	}
	return NULL;
}




// ==================== Destroy Retro Screen ==================== //
void SDL_DestroyRetroScreen ( SDL_RetroScreen* s /* pointer to screen to destroy */ )
{
	SDL_DestroyWindow(s->window);
	SDL_DestroyTexture(s->texture);
	SDL_DestroyRenderer(s->renderer);
	SDL_DestroyRetroPalette(s->palette);
	free(s);
}




// ==================== Start Rendering & Prepare To Draw ==================== //
void SDL_RenderRetroStart ( SDL_RetroScreen* s /* pointer to screen */ )
{
	SDL_SetRenderTarget(s->renderer, s->texture);
}




// ==================== Stop Rendering & Swap Buffers ==================== //
void SDL_RenderRetroFinish ( SDL_RetroScreen* s /* pointer to screen */ )
{
	SDL_SetRenderTarget(s->renderer, NULL);
	SDL_RenderCopy(s->renderer, s->texture, NULL, NULL);
	SDL_RenderPresent(s->renderer);
}


// ==================== Convert Surface to Retro Format ==================== //
SDL_Surface* SDL_ConvertSurfaceToRetro(SDL_RetroScreen* SCRN, SDL_Surface* surf)
{
	return SDL_ConvertSurface(surf, SCRN->format, 0);
}


// ==================== Create Retro Texture From Surface ==================== //
SDL_Texture* SDL_CreateRetroTextureFromSurface
(
	SDL_RetroScreen* SCRN,    // pointer to screen
	SDL_Surface* surf,        // pointer to surface
	int bcol                  // index of color to be used as background
)
{
	// width and height of texture & surfaces in pixels:
	Uint32 w = surf->w, h = surf->h;
	// surfaces required for conversion:
	SDL_Surface *converted, *final;
	// pointers to surface pixel data:
	Uint8* convpxls;    Uint32* finalpxls;


	// convert surf to retro format and save as new surface:
	converted = SDL_ConvertSurface(surf, SCRN->format, 0);

	if(converted == NULL) SDL_Log("RGL: %s", SDL_GetError());
	else
	{
		// create new surface with RGBA8888 format:
		final = SDL_CreateRGBSurfaceWithFormat(0, w, h, 32, SDL_PIXELFORMAT_RGBA8888);

		if(final == NULL) SDL_Log("RGL: %s", SDL_GetError());
		else
		{
			// set pixel data of new final surface to retro converted surface:
			SDL_Color bkgndCol;     // color used as background (transparent)
			SDL_Color c;            // color of retro pixel
			Uint32 r, g, b, a;      // components of color
			Uint32 y, x;            // used for loop

			convpxls = converted->pixels;
			finalpxls = final->pixels;
			bkgndCol = SCRN->format->palette->colors[bcol];

			for(y = 0; y < h; y++)
				for(x = 0; x < w; x++)
				{
					c = SCRN->format->palette->colors[convpxls[x + y * w]];
					if(convpxls[x + y * w] != bcol)
					{
						r = c.r, g = c.g, b = c.b, a = c.a;
						finalpxls[x + y * w] = (r << 24) | (g << 16) | (b << 8) | a;
					}
					else finalpxls[x + y * w] = 0;
				}

			// print out he color
			//printf("%d\n", convpxls[0]);

			// create texture from converted surface:
			SDL_Texture* texture = SDL_CreateTextureFromSurface(SCRN->renderer, final);

			if(texture == NULL) SDL_Log("RGL: %s", SDL_GetError());
			else
			{
				// free surfaces:
				SDL_FreeSurface(converted);
				SDL_FreeSurface(final);
				// finally return texture:
				return texture;
			}
		}
	}
	return NULL;
}









// macro to make palette identifier shorter
#define P s->palette
// macro to convert color compontent (r, g, or b) to screen palette
#define CNV(s,c) (c & s->palette->c##mask) << s->palette->c##shift
// macro to init an SDL_Color with converted rgb values
#define CreateScreenColor(s, r, g, b) (SDL_Color) { CNV(s,r), CNV(s,g), CNV(s,b), 0 }

// ============================ Convert RGB To Retro Color ============================ //
SDL_Color SDL_RGBToRetroColor(SDL_RetroScreen* s, Uint8 r, Uint8 g, Uint8 b)
{
	return CreateScreenColor(s, r, g, b);
}

// ============================ Convert RGB To Retro Color & Set Draw Color ============================ //
void SDL_SetRetroRenderDrawColor(SDL_RetroScreen* s, Uint8 r, Uint8 g, Uint8 b)
{
	SDL_Color c = CreateScreenColor(s, r, g, b);
	SDL_SetRenderDrawColor(s->renderer, c.r, c.g, c.b, 255);
}

// ======== Set the Render Target of the SDL_RetroScreen (s) Renderer to Texture (t) ======== //
void SDL_SetRetroRenderTarget(SDL_RetroScreen* s, SDL_Texture* t)
{
	if (t == NULL) SDL_SetRenderTarget(s->renderer, s->texture);
	else SDL_SetRenderTarget(s->renderer, t);
}





#undef CreateScreenColor
#undef CNV
#undef P
