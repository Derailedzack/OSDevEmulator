#include"DevScreen.h"
bool RenderLoop = true;
SDL_Window* SDLWindow;
SDL_Renderer* SDLRenderer;
SDL_Event SDLEvent;
void DevScr_CreateDisplay(int width, int height){
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "SDL Fatal Error", SDL_GetError(), NULL);
		RenderLoop = false;
		return;
	}
		int SDLRenderComboVal = SDL_CreateWindowAndRenderer(width, height, SDL_WINDOW_RESIZABLE, &SDLWindow, &SDLRenderer);
		if (SDLRenderComboVal == -1) {
			SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "SDL Fatal Error", SDL_GetError(), NULL);
			RenderLoop = false;
		}
		else {

		}
	
}
void DevScr_BeginRenderLoop() {
	while (RenderLoop == true) {
		if (SDL_RenderClear(SDLRenderer) != 0) {
			SDL_LogError(SDL_LOG_CATEGORY_RENDER, "SDL 2 Failed to clear renderer! Error:%s\n", SDL_GetError());
		}
		SDL_RenderPresent(SDLRenderer);

		SDL_PollEvent(&SDLEvent);
		if (SDLEvent.type == SDL_QUIT) {
			RenderLoop = false;

		}
	}
}