#define SDL_MAIN_HANDLED
#include"DevScreen.h"
#include"glad.h"
#include"VRAM_TEST.h"
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
SDL_Window* SDLWindow;
SDL_Renderer* SDLRenderer;
SDL_Event SDLEvent;
SDL_GLContext* SDLContext;
SDL_Surface * SDLScrn;
SDL_Texture* SDLScrnTexture;
int SDLRenderComboVal;
extern unsigned long m68kClk;
unsigned int scr_tex_id;
//extern char ROM[512*1024];
unsigned char VRAM[2048 * 1024];
//unsigned char ScrPixels[800 * 600 * 8];
float VRAM_x;
float VRAM_y;
float VRAM_Trans_x;
float VRAM_Trans_y;
void* SDL_Pixels;
DevVidMode Scr_Mode;
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
			SDL_RWread(vram_in_file, VRAM, sizeof(VRAM), 1);
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
void DevScr_Init() {

	
	if (ShouldUseGL) {
		//glGenTextures(1, &scr_tex_id);
	}
	else {
		//SDLScrn = SDL_CreateRGBSurfaceWithFormatFrom(VRAM, 800, 600, 8, 800 * 1, SDL_PIXELFORMAT_INDEX1LSB);
	//	SDLScrnTexture = SDL_CreateTexture(SDLRenderer, SDL_PIXELFORMAT_RGB444, SDL_TEXTUREACCESS_STREAMING, 800, 600);
		SDLScrnTexture = SDL_CreateTexture(SDLRenderer, SDL_PIXELFORMAT_RGBA32, SDL_TEXTUREACCESS_STREAMING, 800, 600);
		if (SDLScrnTexture == NULL) {
			SDL_Log("SDL_Error(Texture Creation):%s", SDL_GetError());
			Scr_Mode = NONE;
		}
		Scr_Mode = BITMAP_800x600_8BPP;
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



void DevScr_DrawVRAM() {
	float tex_w = 0;
	float tex_h = 0;


	if (ShouldUseGL) { //So this doesn't work as it's incomplete
		glBindTexture(GL_TEXTURE_2D, scr_tex_id);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 800, 600, 0, GL_RGBA, GL_UNSIGNED_BYTE, VRAM);
		glGenerateMipmap(GL_TEXTURE_2D); 
	}
	else
	{
		//SDL_ConvertPixels(800,600,)
		if (SDL_LockTextureToSurface(SDLScrnTexture, NULL, &SDLScrn) != 0) {
			SDL_Log("SDL_Error:%s\n", SDL_GetError());
		}
		SDLScrn->pixels = VRAM;
		//SDL_Delay(32);
		//So it turns if VRAM is written to after the texture is updated garbage is added to 
		SDL_UnlockTexture(SDLScrnTexture);
		//DevScr_UpdateVRAM();
	//	
		//SDL_SetRenderTarget(SDLRenderer, SDLScrnTexture);
		//SDL_SetRenderTarget(SDLRenderer, NULL);
		if (SDL_UpdateTexture(SDLScrnTexture, NULL, SDLScrn->pixels, SDLScrn->pitch) != 0) {
			SDL_Log("Failed to update texture! SDL_Error:%s\n", SDL_GetError());
		}

		//
		if (SDL_RenderCopy(SDLRenderer, SDLScrnTexture, NULL, NULL) != 0) {
			SDL_Log("Failed to copy texture! SDL_Error:%s\n", SDL_GetError());
		}
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
			DevScr_Init();
	

			
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

			if (SDLEvent.type == SDL_WINDOWEVENT) {
				if (SDLEvent.window.event == SDL_WINDOWEVENT_SIZE_CHANGED) {

					//glViewport(0, 0, SDLEvent.window.data1, SDLEvent.window.data2);

				}
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
		
		if (SDLEvent.type == SDL_KEYDOWN) {
			if (SDLEvent.key.keysym.sym == SDLK_d) {
				SDL_RWops* vram_out_file =  SDL_RWFromFile("VRAM_OUT.data", "w");
				//SDL_Log("VRAM_Ptr:%p", &VRAM);
				SDL_RWwrite(vram_out_file, VRAM, sizeof(VRAM), 1);
				SDL_RWclose(vram_out_file);
			}
			if (SDLEvent.key.keysym.sym == SDLK_p) {
				SDL_RWops* vram_in_file = SDL_RWFromFile("VRAM_IN.data", "r");
			
				SDL_RWread(vram_in_file, VRAM, sizeof(VRAM), 1);

				SDL_RWclose(vram_in_file);
			}
			if (SDLEvent.key.keysym.sym == SDLK_RIGHT) {
				VRAM_x += 0.005f;
			}
			if (SDLEvent.key.keysym.sym == SDLK_LEFT) {
				VRAM_x -= 0.005f;

			}
			if (SDLEvent.key.keysym.sym == SDLK_UP) {
				VRAM_y += 0.005f;

			}
			if (SDLEvent.key.keysym.sym == SDLK_DOWN) {
				VRAM_y -= 0.005f;

			}
			if (SDLEvent.key.keysym.sym == SDLK_0) {
				VRAM_Trans_x += 90.0f;

			}
			if (SDLEvent.key.keysym.sym == SDLK_1) {
				VRAM_Trans_x -= 90.0f;

			}

			if (SDLEvent.key.keysym.sym == SDLK_2) {
				VRAM_Trans_y += 0.005f;

			}
			if (SDLEvent.key.keysym.sym == SDLK_3) {
				VRAM_Trans_y -= 0.005f;

			}



			
		}

		
	}
}
