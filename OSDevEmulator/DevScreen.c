#include"DevScreen.h"
#include"glad.h"


bool RenderLoop = true;
SDL_Window* SDLWindow;
SDL_Renderer* SDLRenderer;
SDL_Event SDLEvent;
SDL_GLContext* SDLContext;
SDL_Surface* SDLScrn;
SDL_Texture* SDLScrnTexture;

extern unsigned long m68kClk;
extern char ROM[512*1024];
char VRAM[2048 * 1024];
void* SDL_Pixels;
void DevScr_Init() {
	SDL_RWops* RomFile = SDL_RWFromFile("test.bin", "r");
	if (RomFile == NULL) {
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Dev Emulator Init", SDL_GetError(), NULL);
		
	}
	else {
		if (SDL_RWread(RomFile, ROM, 1, 512*1024) == 0) {
			SDL_Log("SDL_RWread:%s", SDL_GetError());
		}

		
	}

	
}
void DevScr_DrawVRAM() {
	glDrawPixels(800, 600, GL_RGB, GL_UNSIGNED_BYTE, VRAM);
}
void DevScr_CreateDisplay(int width, int height){
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "SDL Fatal Error", SDL_GetError(), NULL);
		RenderLoop = false;
		return;
	}
		int SDLRenderComboVal = SDL_CreateWindowAndRenderer(width, height, SDL_WINDOW_OPENGL, &SDLWindow, &SDLRenderer);
		if (SDLRenderComboVal == -1) {
			SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "SDL Fatal Error", SDL_GetError(), NULL);
			RenderLoop = false;
		}
		else {
			SDLContext = SDL_GL_CreateContext(SDLWindow);
			if (SDLContext == NULL) {
				SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "SDL Fatal Error", SDL_GetError(), NULL);
				RenderLoop = false;
			}
			gladLoadGLLoader(SDL_GL_GetProcAddress);
			
			DevScr_Init();
			
			

			
		}
	
}
void DevScr_BeginRenderLoop() {
	while (RenderLoop == true) {
		
		glClear(GL_COLOR_BUFFER_BIT | GL_STENCIL_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		
		DevScr_DrawVRAM();
		SDL_GL_SwapWindow(SDLWindow);
		
	
		SDL_PollEvent(&SDLEvent);
		if (SDLEvent.type == SDL_QUIT) {
			RenderLoop = false;

		}
		if (SDLEvent.type == SDL_KEYDOWN) {
			if (SDLEvent.key.keysym.sym == SDLK_d) {
			
			}
		}
	}
}