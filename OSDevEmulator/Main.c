
#include"DevEmulator.h"
#include<stdlib.h>
#include<stdio.h>
int main() {
#ifdef USE_SCRIPT_FOR_DEV_EMU
	DevEmu_InitLua("init.lua");
#else
	//void* test = calloc(23,4);
	//printf("test:%p\n", test);
	//DevEmu_Init(M68000, NULL);
	DevEmu_Init(M68000,2048*1024, DevEmu_MainLoop);
#endif
}