#include"DevEmulator.h"
#include"DevScreen.h"

char ROM[256 * 1024];
char RAM[1024 * 1024];
extern char VRAM[2048 * 1024];

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
void DevEmu_Init(CPU_TYPE m68k_type) {

	
	DevScr_CreateDisplay(640, 480);
	DevScr_BeginRenderLoop();
}