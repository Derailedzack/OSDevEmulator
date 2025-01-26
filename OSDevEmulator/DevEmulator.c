#include"DevEmulator.h"
#include"DevScreen.h"
#include"lualib.h"
#include "lauxlib.h"

#ifndef USE_SCRIPT_FOR_DEV_EMU
char ROM[256 * 1024];
char RAM[1024 * 1024];
extern char* VRAM;
#endif
bool RenderLoop = true;
DevEmu_MainLoop_Func* MainLoopPtr;
#ifdef USE_SCRIPT_FOR_DEV_EMU
lua_State* Emu_LuaState;
extern luaL_Reg MemoryMapLib[];
extern luaL_Reg DevScr_Lib[];
int DevEmu_PrintLog(lua_State* L) {
	SDL_Log(lua_tostring(L, 1));
}
void DevEmu_InitLua(const char* script_path) {
	Emu_LuaState = luaL_newstate();
	if (Emu_LuaState == NULL) {
		printf("Lua failed to allocate a lua state! ERRNO:%i\n", errno);
	}
	luaL_register(Emu_LuaState, "MemoryMap", MemoryMapLib);
	luaL_register(Emu_LuaState, "DevScreen",DevScr_Lib);
	luaL_openlibs(Emu_LuaState);
	if (luaL_dofile(Emu_LuaState, script_path) == 1) {
		printf("%s\n", lua_tostring(Emu_LuaState, -1));
		//return 0x02;
	}
	//lua_register(, "PrintTest", DevEmu_PrintLog);
	
	//luaopen_base(Emu_LuaState);


}
#else
void DevEmu_MainLoop() {
	while (RenderLoop) {
		if (MainLoopPtr != NULL) {
			(MainLoopPtr)();
		}
		DevScr_BeginRenderLoop();
	}
}
unsigned char DevEmu_Read8(void* ext, unsigned long addr) {
	if (addr < 0x40000) {
		return ROM[addr];
	}
	if (addr < 0x100000) {
		return RAM[addr];
	}
	if (addr < 0x240000) {
		return VRAM[addr];
	}
	return 0xff;
}
unsigned short DevEmu_Read16(void* ext, unsigned long addr) {
	if (addr < 0x40000) {
		return ROM[addr];
	}
	if (addr < 0x100000) {
		return RAM[addr];
	}
	if (addr < 0x240000) {
		return VRAM[addr];
	}
	return 0xff;
}
unsigned long DevEmu_Read32(void* ext, unsigned long addr) {
	if (addr < 0x40000) {
		return ROM[addr];
	}
	if (addr < 0x100000) {
		return RAM[addr];
	}
	if (addr < 0x240000) {
		return VRAM[addr];
	}
	return 0xff;
}
void DevEmu_Write8(void* ext, unsigned long addr, unsigned char val) {
	if (addr < 0x100000) {
		RAM[addr] = val;
	}
	if (addr < 0x240000) {
		VRAM[addr] = val;
	}
}
void DevEmu_Write16(void* ext, unsigned long addr, unsigned short val) {
	if (addr < 0x100000) {
		RAM[addr] = val;
	}
	if (addr < 0x240000) {
		VRAM[addr] = val;
	}
}
void DevEmu_Write32(void* ext, unsigned long addr, unsigned long val) {
	if (addr < 0x100000) {
		RAM[addr] = val;
	}
	if (addr < 0x240000) {
	 	VRAM[addr] = val;
	}
}

void DevEmu_Reset(void* ext, unsigned val) {
	
	SDL_LogVerbose(SDL_LOG_CATEGORY_APPLICATION, "val:%u\n", val);
}
int DevEmu_Hook(void* ext, unsigned val) {
	SDL_LogVerbose(SDL_LOG_CATEGORY_APPLICATION, "val:%u\n", val);
	return 0x00;
}
unsigned DevEmu_Intrrupt(void* ext, unsigned irq_level) {

}
void DevEmu_Trap(void* ext, unsigned n) {

}
void DevEmu_LogException(void* ext, unsigned tn) {
	SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "tn:%u", tn);
}
void DevEmu_Init(CPU_TYPE m68k_type, unsigned long vram_size, DevEmu_MainLoop_Func* main_loop_func) {
	//LoadDeviceFromSharedObject("",false);
	//DevEmu_InitLua("");
	if (vram_size == NULL) {
		printf("vram_size is NULL!\n");
		return;
	}
	if (main_loop_func != NULL) {
		MainLoopPtr = main_loop_func;
	}
	DevScr_CreateDisplay(800, 600, vram_size);
	DevEmu_MainLoop();
}
#endif
