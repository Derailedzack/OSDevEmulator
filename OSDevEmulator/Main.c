
#include"DevEmulator.h"

int main() {
#ifdef USE_SCRIPT_FOR_DEV_EMU
	DevEmu_InitLua("init.lua");
#else

	DevEmu_Init(M68000,2048*1024);
#endif
}