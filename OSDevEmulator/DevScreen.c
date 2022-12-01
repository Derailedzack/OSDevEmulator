#include"DevScreen.h"
#include"glad.h"
#include "e68000.h"

bool RenderLoop = true;
SDL_Window* SDLWindow;
SDL_Renderer* SDLRenderer;
SDL_Event SDLEvent;
SDL_GLContext* SDLContext;
SDL_Surface* SDLScrn;
SDL_Texture* SDLScrnTexture;
e68_dasm_t* m68kDasm;
extern e68000_t* m68kCPU;
extern unsigned long m68kClk;
extern char ROM[512*1024];
char VRAM[2048 * 1024];
void* SDL_Pixels;
void DevScr_Init() {
	/*SDLScrn = SDL_CreateRGBSurfaceWithFormat(0, 640, 480, 8, SDL_PIXELFORMAT_RGB888);
	if (SDLScrn == NULL) {
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "DevScreen Error(SDL Screen Surface)", SDL_GetError(), SDLWindow);
	}
	
	SDLScrnTexture = SDL_CreateTexture(SDLRenderer, SDL_PIXELFORMAT_RGB888, SDL_TEXTUREACCESS_STREAMING, 640, 480);
	if (SDLScrnTexture == NULL) {
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "DevScreen Error(SDL Screen Texture)", SDL_GetError(), SDLWindow);
	}*/
	/*if (SDL_LockSurface(SDLScrn) != 0) {
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "DevScreen Error(SDL Screen Surface Lock)", SDL_GetError(), SDLWindow);
	}*/
	//for (int i = 0; i < 512 * 1024; i++) {
		//DL_Pixels[i] = 0x00;

	//}
	//SDL_assert(&SDL_Pixels == NULL);
	//SDL_assert(*SDL_Pixels == NULL);
	//SDL_Pixels = malloc(sizeof(char*));
	//printf("&SDL_Pixels:%x", SDL_Pixels);

	/*if (SDL_LockSurface(SDLScrn) != 0) {
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "DevScreen Error(SDL Screen Surface Lock)", SDL_GetError(), SDLWindow);
	}*/
	/*if (SDL_LockTexture(SDLScrnTexture, NULL, &SDL_Pixels, 0) != 0) {
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "DevScreen Error(SDL Screen Texture Lock)", SDL_GetError(), SDLWindow);
	}*/
	SDL_RWops* RomFile = SDL_RWFromFile("test.bin", "r");
	if (RomFile == NULL) {
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Dev Emulator Init", SDL_GetError(), NULL);
		//return;
	}
	else {
		if (SDL_RWread(RomFile, ROM, 1, 512*1024) == 0) {
			SDL_Log("SDL_RWread:%s", SDL_GetError());
		}

		//fread(ROM, 1, 512 * 1024, RomFile);
	}
	m68kDasm = SDL_malloc(sizeof(e68_dasm_t));
	
}
void DevScr_DrawVRAM() {
	/*SDL_Pixels = VRAM;
	if (SDL_UpdateTexture(SDLScrnTexture, NULL, SDL_Pixels, 2) != 0) {
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "DevScreen Error(SDL Screen Texture Update)", SDL_GetError(), SDLWindow);
	}
	
	SDL_UnlockSurface(SDLScrn);
	SDL_RenderCopy(SDLRenderer, SDLScrnTexture, NULL, NULL);*/
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
			//SDL_assert(VRAM != NULL);
			

			
		}
	
}
void DevScr_BeginRenderLoop() {
	while (RenderLoop == true) {
		/*if (SDL_RenderClear(SDLRenderer) != 0) {
			SDL_LogError(SDL_LOG_CATEGORY_RENDER, "SDL 2 Failed to clear renderer! Error:%s\n", SDL_GetError());
		}*/
		glClear(GL_COLOR_BUFFER_BIT | GL_STENCIL_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		/*if (m68kCPU->halt != 1) {
		
		}*/
	//e68_execute(m68kCPU);
		/*m68kCPU->clkcnt += m68kCPU->delay;
		m68kCPU->delay = 0;*/

		//e68_execute(m68kCPU);
		//e68_dasm_cur(m68kCPU, m68kDasm);
				//DevScr_DrawVRAM();
		//DevScr_UpdateVRAM();

		DevScr_DrawVRAM();
		SDL_GL_SwapWindow(SDLWindow);
		
		//SDLScrn = SDL_CreateRGBSurfaceWithFormatFrom(VRAM, 640, 480, 8, 1, SDL_PIXELFORMAT_RGB888);
		SDL_PollEvent(&SDLEvent);
		if (SDLEvent.type == SDL_QUIT) {
			RenderLoop = false;

		}
		if (SDLEvent.type == SDL_KEYDOWN) {
			if (SDLEvent.key.keysym.sym == SDLK_d) {
				
				SDL_Log("%s %s %s\n", m68kDasm->op, m68kDasm->arg1, m68kDasm->arg2);
				SDL_Log("PC:%i D0:%u A0:%u", m68kCPU->pc, m68kCPU->dreg, m68kCPU->areg);
			}
		}
	}
}