#ifndef DEVSCREEN_H
#define DEVSCREEN_H
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
typedef enum  {
	INVAILD,
	BITMAP_800x600_8BPP, //I'm aware that x can also be used as a var but we can't use * as that creates a syntax error. As the star gets treated as multipulication
	TEXT_MODE,
	TILE_MODE
}DevVidMode;
void DevScr_CreateDisplay(int width,int height, DevVidMode screen_mode,unsigned long vram_size, unsigned long tilegfx_mem_size);
void DevScr_GLBeginRenderLoop();
void DevScr_BeginRenderLoop();
#ifdef USE_SCRIPT_FOR_DEV_EMU
int DevScr_InitDeviceLua(lua_State* L);
int DevScr_ReadFromDeviceLua(lua_State* L);
int DevScr_WriteToDeviceLua(lua_State* L);
int DevScr_BeginRenderLoopLua(lua_State* L);
#endif
#endif