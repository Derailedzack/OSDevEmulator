#pragma once
#include<stdbool.h>
#include<SDL.h>
extern bool RenderLoop;
extern SDL_Window* SDLWindow;
extern SDL_Renderer* SDLRenderer;
void DevScr_CreateDisplay(int width,int height);
void DevScr_BeginRenderLoop();