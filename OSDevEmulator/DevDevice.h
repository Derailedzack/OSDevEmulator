#pragma once
//Set unused functions to NULL to disable them
typedef void (*Init_Func)();
typedef unsigned char (*Read_8_Func)(unsigned long addr); //ReadByte
typedef unsigned short (*Read_16_Func)(unsigned long addr); //ReadWord
typedef unsigned long (*Read_32_Func)(unsigned long addr); //ReadDoubleWord

typedef void (*Write_8_Func)(unsigned long addr, unsigned char val); //WriteByte
typedef void (*Write_16_Func)(unsigned long addr, unsigned short val); //WriteWord
typedef void (*Write_32_Func)(unsigned long addr, unsigned long val); //WriteDoubleWord
typedef struct DevDevice {
	const char* name;
	unsigned long base_addr;
	Init_Func* init;
	Read_8_Func* read_8;
	Read_16_Func* read_16;
	Read_32_Func* read_32;
	Write_8_Func* write_8;
	Write_16_Func* write_16;
	Write_32_Func* write_32;

	

}DevDevice;
DevDevice* CreateDevice(const char* name, unsigned long base_addr, Init_Func* init_func,Read_8_Func* read8_func,Read_16_Func* read16_func,Read_32_Func* read32_func,Write_8_Func* write_8_func,Write_16_Func* write_16_func,Write_32_Func* write_32_func);
//DevDevice* LoadDeviceFromSharedObject(const char* cfg_path);
/*
DevDevice* CreateDevice(const char* name, unsigned long base_addr, Init_Func* init_func, Read_8_Func* read8_func, Read_16_Func* read16_func, Write_8_Func* write8_func, Write_16_Func* write_16_func);
DevDevice* CreateDevice(const char* name, unsigned long base_addr, Init_Func* init_func, Read_8_Func* read8_func, Write_8_Func* write8_func);
DevDevice* CreateDevice(const char* name, unsigned long base_addr, Init_Func* init_func, Read_16_Func* read16_func, Write_16_Func* write16_func);
DevDevice* CreateDevice(const char* name, unsigned long base_addr, Init_Func* init_func, Read_32_Func* read32_func, Write_32_Func* write32_func);
*/