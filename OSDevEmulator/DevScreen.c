#define SDL_MAIN_HANDLED
#include"DevScreen.h"
#include"glad.h"
#include"VRAM_TEST.h"
#include <string.h>
//TODO: Clean this file up. There's too much crap here
bool ShouldUseGL = false;
bool RenderLoop = true;
typedef enum DevVidMode {
	NONE,
	BITMAP_800x600_8BPP, //I'm aware that x can also be used as a var but we can't use * as that creates a syntax error. As the star gets treated as multipulication
	TEXT_MODE,
	TILE_MODE
}DevVidMode;
typedef struct DevScreenTileRegs {
	uint16_t Tile_Width;
	uint16_t Tile_Height;
	uint16_t Tile_OffX;
	uint16_t Tile_OffY;
	uint16_t Tile_Num;
}DevScreenTileRegs;
typedef struct DevScreenRegs {
	DevVidMode Screen_Mode;
	uint32_t Screen_TileSetDatSize;
	uint32_t Screen_VRAMSize;
	//unsigned char* TilesGFX_RAM;
//	unsigned char* GPU_VRAM;
	DevScreenTileRegs* Screen_TileRegs; //I'll likely use the Tile Registers for Text Mode as well. NOTE: VRAM will be used to store the tiles or the tilemap

}DevScreenRegs;
SDL_Window* SDLWindow;
SDL_Renderer* SDLRenderer;
SDL_Event SDLEvent;
SDL_GLContext* SDLContext;
SDL_Surface * SDLScrn;
SDL_Texture* SDLScrnTexture;
DevScreenRegs* GPU_Registers;
int SDLRenderComboVal;
extern unsigned long m68kClk;
unsigned int scr_tex_id;
//extern char ROM[512*1024];
unsigned char* TilesGFX_RAM;
unsigned char* VRAM;
//unsigned char* TilesRAM; //Memory region for storing the graphics for the tilemap
//unsigned char ScrPixels[800 * 600 * 8];

void* SDL_Pixels;
//DevVidMode Scr_Mode;
int pitch = 0;
//SDL_Texture* VRAM_Tex;
SDL_RWops* vram_in_file;
SDL_RWops* vram_out_file;
void DevScr_EventHook(void* userdata, SDL_Event* event) {
	if (event->type == SDL_KEYDOWN) {
		switch (event->key.keysym.sym) {
		case SDLK_p:
			vram_in_file = SDL_RWFromConstMem(VRAM_TEST, sizeof(VRAM_TEST));
			//SDL_AddTimer(20, DevScr_Timer,NULL);
			SDL_RWread(vram_in_file, VRAM, GPU_Registers->Screen_VRAMSize, 1);
			SDL_RWclose(vram_in_file);
			break;
		case SDLK_d:
			vram_out_file = SDL_RWFromFile("VRAM_OUT.data", "w");
			SDL_RWwrite(vram_out_file, VRAM, sizeof(VRAM), 1);
			SDL_RWclose(vram_out_file);
			break;
		case SDLK_s:
			//int** i = rand();
			//vram_in_file = SDL_RWFromConstMem(VRAM_TEST, sizeof(VRAM_TEST));
			//for (int i = 0; i < 2048*1024; i++) {
				//VRAM[i] = rand();
		//	}
			//SDL_memcpy(VRAM, &SDLRenderer, sizeof(VRAM));
			break;
		}
	}
}
void DevScr_Init(DevVidMode screen_mode) {
	GPU_Registers = malloc(sizeof(DevScreenRegs));
	if (GPU_Registers == NULL) {
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "DevScreen Fatal Error", strerror(errno), NULL);
		SDL_Quit();
	}
	else {
		GPU_Registers->Screen_Mode = screen_mode;
	}


	if (GPU_Registers->Screen_Mode != BITMAP_800x600_8BPP) {
		TilesGFX_RAM = malloc(sizeof(GPU_Registers->Screen_TileSetDatSize));
		//TilesRAM = malloc();
		//SDLScrn = SDL_CreateRGBSurfaceFrom(VRAM, )
			//SDL_CreateTextureFromSurface(SDLRenderer, )
	}else {


		if (ShouldUseGL) {
			//glGenTextures(1, &scr_tex_id);
		}
		else {
			//SDLScrn = SDL_CreateRGBSurfaceWithFormatFrom(VRAM, 800, 600, 8, 800 * 1, SDL_PIXELFORMAT_INDEX1LSB);
		//	SDLScrnTexture = SDL_CreateTexture(SDLRenderer, SDL_PIXELFORMAT_RGB444, SDL_TEXTUREACCESS_STREAMING, 800, 600);
			SDLScrnTexture = SDL_CreateTexture(SDLRenderer, SDL_PIXELFORMAT_RGBA32, SDL_TEXTUREACCESS_STREAMING, 800, 600);
			if (SDLScrnTexture == NULL) {
				SDL_Log("SDL_Error(Texture Creation):%s", SDL_GetError());
				GPU_Registers->Screen_Mode = NONE;
			}
			//VRAM = malloc(2048 * 1024);
			VRAM = calloc(4096 * 1024, 1);
			if (VRAM == NULL) {
				SDL_Log("Failed to allocate VRAM! Errno:%i\n", errno);
				exit(-3);
			}
			//printf("VRAM:%x\n", VRAM[1]);
			GPU_Registers->Screen_Mode = BITMAP_800x600_8BPP;
		}

	}


}


#ifdef USE_SCRIPT_FOR_DEV_EMU
const luaL_Reg DevScr_Lib[] = {
	"Init",DevScr_InitDeviceLua,
	"Write",DevScr_WriteToDeviceLua,
	"Read",DevScr_ReadFromDeviceLua,
	NULL,NULL
};
extern lua_State* Emu_LuaState;
int DevScr_InitDeviceLua(lua_State* L) {
	lua_setglobal(L, "DevEmu_MainLoop");

	DevScr_CreateDisplay(lua_tointeger(L,3), lua_tointeger(L,2));
	return 0;
}
int DevScr_ReadFromDeviceLua(lua_State* L) {
	unsigned int VRAM_index = lua_tointeger(L, 1);

	if (VRAM_index >= 2048 * 1024 ) {
		lua_pushstring(L, "VRAM_INDEX is invaild!");
		lua_error(L);
		return 0;
	}
	else {
		lua_pushinteger(L, VRAM[VRAM_index]);
		return 1;
	}
	
}
int DevScr_WriteToDeviceLua(lua_State* L) {
	unsigned int VRAM_index = lua_tointeger(L, 1);
	unsigned char VRAM_val = lua_tointeger(L, 2);
	if (VRAM_index >= 2048 * 1024) {
		lua_pushstring(L, "VRAM_INDEX is invaild!");
		lua_error(L);
		return 0;
	}
	else {
		lua_pushinteger(L, VRAM[VRAM_index]);
		return 1;
	}

}
#endif


void DevScr_GL_DrawVRAM() {
	glBindTexture(GL_TEXTURE_2D, scr_tex_id);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 800, 600, 0, GL_RGBA, GL_UNSIGNED_BYTE, VRAM);
	glGenerateMipmap(GL_TEXTURE_2D);
}
void DevScr_DrawVRAM() {
	float tex_w = 0;
	float tex_h = 0;
	
	if (GPU_Registers->Screen_Mode == BITMAP_800x600_8BPP) {

		if (ShouldUseGL) { //So this doesn't work as it's incomplete
			DevScr_GL_DrawVRAM();
		}
		else
		{
			if (SDL_LockTextureToSurface(SDLScrnTexture, NULL, &SDLScrn) != 0) {
				SDL_Log("SDL_Error:%s\n", SDL_GetError());
			}
			SDLScrn->pixels = VRAM;

			//So it turns if VRAM is written to after the texture is updated garbage is added to 
			SDL_UnlockTexture(SDLScrnTexture);
			if (SDL_UpdateTexture(SDLScrnTexture, NULL, SDLScrn->pixels, SDLScrn->pitch) != 0) {
				SDL_Log("Failed to update texture! SDL_Error:%s\n", SDL_GetError());
			}

			//
			if (SDL_RenderCopy(SDLRenderer, SDLScrnTexture, NULL, NULL) != 0) {
				SDL_Log("Failed to copy texture! SDL_Error:%s\n", SDL_GetError());
			}
		}
	}
	else { //Every other mode that isn't a bitmap mode will use the tile rendering code

	}
}
void DevScr_CreateDisplay(int width, int height) {
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "SDL Fatal Error", SDL_GetError(), NULL);
		RenderLoop = false;
		return;
	}
	if (ShouldUseGL == true) {
		SDLRenderComboVal = SDL_CreateWindowAndRenderer(width, height, SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE, &SDLWindow, &SDLRenderer);
	}
	else {
		SDLRenderComboVal = SDL_CreateWindowAndRenderer(width, height, SDL_WINDOW_RESIZABLE, &SDLWindow, &SDLRenderer);
	}
	
		
		if (SDLRenderComboVal == -1) {
			SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "SDL Fatal Error", SDL_GetError(), NULL);
			RenderLoop = false;
		}
		else {
			SDL_SetWindowTitle(SDLWindow, "DevScreen");
			if (ShouldUseGL) {
				SDLContext = SDL_GL_CreateContext(SDLWindow);
				if (SDLContext == NULL) {
					SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "SDL Fatal Error", SDL_GetError(), NULL);
					RenderLoop = false;
				}
				SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
				SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 6);
				SDL_SetHint(SDL_HINT_RENDER_DRIVER, "opengl");
				gladLoadGLLoader(SDL_GL_GetProcAddress);
			}

			else {
				
				//SDL_SetHint(SDL_HINT_RENDER_BATCHING, "1");
			}
			SDL_AddEventWatch(DevScr_EventHook, NULL);
		//	SDL_SetHint(SDL_HINT_RENDER_DRIVER, "direct3d11");
			DevScr_Init(BITMAP_800x600_8BPP);
	

			
		}
	
}
extern void DevEmu_Write8(void* ext, unsigned long addr, unsigned char val);
void DevScr_BeginRenderLoop() {

	if (ShouldUseGL) {
		DevScr_GLBeginRenderLoop();
	}
	else {

		while (RenderLoop == true) {
			SDL_PollEvent(&SDLEvent);
		
			SDL_RenderClear(SDLRenderer);
#ifdef USE_SCRIPT_FOR_DEV_EMU
			luaL_dostring(Emu_LuaState, "DevEmu_MainLoop()");
#endif
			DevScr_DrawVRAM();

			
			SDL_RenderPresent(SDLRenderer);
			//
	

			
			if (SDLEvent.type == SDL_QUIT) {
				RenderLoop = false;

			}
		}
	}

}

void DevScr_GLBeginRenderLoop() {
	while (RenderLoop == true) {
		
		glClear(GL_COLOR_BUFFER_BIT | GL_STENCIL_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		
		DevScr_DrawVRAM();
		SDL_GL_SwapWindow(SDLWindow);
		SDL_PollEvent(&SDLEvent);

		if (SDLEvent.type == SDL_WINDOWEVENT) {
			if (SDLEvent.window.event == SDL_WINDOWEVENT_SIZE_CHANGED) {

				glViewport(0, 0, SDLEvent.window.data1, SDLEvent.window.data2);

			}
		}
	}
}
