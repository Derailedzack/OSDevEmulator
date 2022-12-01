#include"DevEmulator.h"
#include"DevScreen.h"
#include"e68000.h"
e68000_t* m68kCPU;
unsigned long m68kClk = LONG_MAX;
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
	/*if (addr < 0x40000) {
		 ROM[addr] = val;
	}*/
	if (addr < 0x100000) {
		RAM[addr] = val;
	}
	if (addr < 0x240000) {
		VRAM[addr] = val;
	}
}
void DevEmu_Write16(void* ext, unsigned long addr, unsigned short val) {
	/*if (addr < 0x40000) {
		ROM[addr] = val;
	}*/
	if (addr < 0x100000) {
		RAM[addr] = val;
	}
	if (addr < 0x240000) {
		VRAM[addr] = val;
	}
}
void DevEmu_Write32(void* ext, unsigned long addr, unsigned long val) {
	/*if (addr < 0x40000) {
		ROM[addr] = val;
	}*/
	if (addr < 0x100000) {
		RAM[addr] = val;
	}
	if (addr < 0x240000) {
		VRAM[addr] = val;
	}
}

void DevEmu_Reset(void* ext, unsigned val) {
	e68_set_pc_prefetch(m68kCPU, 0x0000000);
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
	m68kCPU = SDL_malloc(sizeof(e68000_t));
	e68_init(m68kCPU);
	e68_set_mem_fct(m68kCPU, NULL, DevEmu_Read8, DevEmu_Read16, DevEmu_Read32, DevEmu_Write8, DevEmu_Write16, DevEmu_Write32);
	
	if (m68k_type == M68000) {
		e68_set_68000(m68kCPU);
	}
	else if (m68k_type == M68010) {
		e68_set_68010(m68kCPU);
	}
	else {
		e68_set_68020(m68kCPU);
	}
	m68kCPU->reset = DevEmu_Reset;
	m68kCPU->hook = DevEmu_Hook;
	m68kCPU->inta = DevEmu_Intrrupt;
	m68kCPU->log_exception = DevEmu_LogException;
	
	DevScr_CreateDisplay(640, 480);
	DevScr_BeginRenderLoop();
}