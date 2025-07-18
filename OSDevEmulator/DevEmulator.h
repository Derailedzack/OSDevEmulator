#pragma once

#include<lua.h>
#include "Config.h"
typedef enum CPU_TYPE {
	NONE,
	M68000,
	M68010,
	M68020,
	M68040,
	CUSTOM 
}CPU_TYPE;
typedef struct CPU_ModuleInfoRAW {
	const char* name;
	 void (*mod_init_func)();

}CPU_ModuleInfoRAW;
CPU_TYPE* CurrentCpuType;
typedef unsigned char (DevEmu_Read8_Func)(void* ext, unsigned long addr);
typedef unsigned short (DevEmu_Read16_Func)(void* ext, unsigned long addr);
typedef unsigned long (DevEmu_Read32_Func)(void* ext, unsigned long addr);
typedef void (DevEmu_Write8_Func)(void* ext, unsigned long addr,unsigned char val);
typedef void (DevEmu_Write16_Func)(void* ext, unsigned long addr, unsigned short val);
typedef void (DevEmu_Write32_Func)(void* ext, unsigned long addr, unsigned long val);
typedef void (DevEmu_Init_Func)(CPU_TYPE cpu_type,unsigned long vram_size);
typedef void (DevEmu_MainLoop_Func)();
int DevEmu_PrintLog(lua_State* L);
void DevEmu_MainLoop();
void DevEmu_Init(CPU_TYPE m68k_type,unsigned long vram_size, DevEmu_MainLoop_Func* custom_main_loop_func);
void DevEmu_InitLua(const char* script_path);
