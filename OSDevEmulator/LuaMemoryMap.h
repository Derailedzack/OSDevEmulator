#pragma once
//#include"lua.h"
#include"lauxlib.h"
#include"Config.h"
int Lua_InitMemoryMap(lua_State* L);
int Lua_GetDeviceByName(lua_State* L);
int Lua_GetDeviceByBaseAddr(lua_State* L);
int Lua_AddDeviceToMemoryMap(lua_State* L);
const luaL_Reg MemoryMapLib[] = {
	"Init",Lua_InitMemoryMap,
	"GetDeviceByName",Lua_GetDeviceByName,
	"GetDeviceByBaseAddr",Lua_GetDeviceByBaseAddr,
	"AddDevice",Lua_AddDeviceToMemoryMap,
	NULL,NULL
};
