#pragma once
#include<stdbool.h>
#include<SDL.h>
#include"Config.h"
#ifdef USE_SCRIPT_FOR_DEV_EMU
#include<lua.h>
#endif
#include <lauxlib.h>
extern bool RenderLoop;
extern SDL_Window* SDLWindow;
extern SDL_Renderer* SDLRenderer;

void DevScr_CreateDisplay(int width,int height,unsigned long vram_size);
void DevScr_GLBeginRenderLoop();
void DevScr_BeginRenderLoop();
#ifdef USE_SCRIPT_FOR_DEV_EMU
int DevScr_InitDeviceLua(lua_State* L);
int DevScr_ReadFromDeviceLua(lua_State* L);
int DevScr_WriteToDeviceLua(lua_State* L);
int DevScr_BeginRenderLoopLua(lua_State* L);
#endif