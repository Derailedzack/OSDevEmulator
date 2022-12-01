#pragma once
typedef enum CPU_TYPE {
	NONE,
	M68000,
	M68010,
	M68020
}CPU_TYPE;
CPU_TYPE* CurrentCpuType;
void DevEmu_Init(CPU_TYPE m68k_type);