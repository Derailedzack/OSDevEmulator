#include"LuaMemoryMap.h"

int Lua_InitMemoryMap(lua_State* L) {

	lua_newtable(L);
	//lua_pushstring(L, "MemoryMap.DEVICES");
	lua_setglobal(L, "MemoryMap.Devices");
	return 1;
}
int Lua_GetDeviceByName(lua_State* L) {
	return 0;
}
int Lua_GetDeviceByBaseAddr(lua_State* L) {
	return 0;
}
int Lua_AddDeviceToMemoryMap(lua_State* L) {
	lua_getglobal(L, "MemoryMap.Devices");
	lua_touserdata(L, 1);
	//printf("Stack index %i type: %s", 1, lua_typename(L, lua_type(L, -1002)));

	
	if (lua_isnil(L, -1)) {
		lua_pushstring(L, "MemoryMap.Devices is nil!\n");
		lua_error(L);
		return 1;
	}
	else {
		//lua_gettable(L, 1);
	}
	return 0;
}