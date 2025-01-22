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
int DevEmu_PrintLog(lua_State* L);
void DevEmu_Init(CPU_TYPE m68k_type);
void DevEmu_InitLua(const char* script_path);