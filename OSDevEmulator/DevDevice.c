#include"DevDevice.h"
#include<stdlib.h>
#include<string.h>
#include<SDL_log.h>
DevDevice* CreateDevice(const char* name, unsigned long base_addr, Init_Func* init_func, Read_8_Func* read8_func, Read_16_Func* read16_func, Read_32_Func* read32_func, Write_8_Func* write_8_func, Write_16_Func* write_16_func, Write_32_Func* write_32_func) {
	DevDevice* new_device = malloc(sizeof(DevDevice));
	if (new_device == NULL) {
		SDL_Log("Failed to create new DevDevice Malloc ERRNO:%i strerror:%s", errno,strerror(errno));
		return NULL;
	}
	new_device->name = name;
	new_device->base_addr = base_addr;
	new_device->init = init_func;
	new_device->read_8 = read8_func;
	new_device->read_16 = read16_func;
	new_device->read_32 = read32_func;
	new_device->write_8 = write_8_func;
	new_device->write_16 = write_16_func;
	new_device->write_32 = write_32_func;
	return new_device;
}
/*
DevDevice* CreateDevice(const char* name, unsigned long base_addr, Init_Func* init_func, Read_8_Func* read8_func, Read_16_Func* read16_func, Write_8_Func* write8_func, Write_16_Func* write_16_func) {
	DevDevice* new_device = malloc(sizeof(DevDevice));
	if (new_device == NULL) {
		SDL_Log("Failed to create new DevDevice Malloc ERRNO:%i strerror:%s", errno, strerror(errno));
		return NULL;
	}
	new_device->name = name;
	new_device->base_addr = base_addr;
	new_device->init = init_func;
	new_device->read_8 = read8_func;
	new_device->read_16 = read16_func;
	new_device->read_32 = NULL;
	new_device->write_8 = write8_func;
	new_device->write_16 = write_16_func;
	new_device->write_32 = NULL;
	return new_device;
}
DevDevice* CreateDevice(const char* name, unsigned long base_addr, Init_Func* init_func, Read_8_Func* read8_func, Write_8_Func* write8_func) {
	DevDevice* new_device = malloc(sizeof(DevDevice));
	if (new_device == NULL) {
		SDL_Log("Failed to create new DevDevice Malloc ERRNO:%i strerror:%s", errno, strerror(errno));
		return NULL;
	}
	new_device->name = name;
	new_device->base_addr = base_addr;
	new_device->init = init_func;
	new_device->read_8 = read8_func;
	new_device->read_16 = NULL;
	new_device->read_32 = NULL;
	new_device->write_8 = write8_func;
	new_device->write_16 = NULL;
	new_device->write_32 = NULL;
	return new_device;
}
DevDevice* CreateDevice(const char* name, unsigned long base_addr, Init_Func* init_func, Read_16_Func* read16_func, Write_16_Func* write16_func) {
	DevDevice* new_device = malloc(sizeof(DevDevice));
	if (new_device == NULL) {
		SDL_Log("Failed to create new DevDevice Malloc ERRNO:%i strerror:%s", errno, strerror(errno));
		return NULL;
	}
	new_device->name = name;
	new_device->base_addr = base_addr;
	new_device->init = init_func;
	new_device->read_8 = NULL;
	new_device->read_16 = read16_func;
	new_device->read_32 = NULL;
	new_device->write_8 = NULL;
	new_device->write_16 = write16_func;
	new_device->write_32 = NULL;
	return new_device;
}
DevDevice* CreateDevice(const char* name, unsigned long base_addr, Init_Func* init_func, Read_32_Func* read32_func, Write_32_Func* write32_func) {
	DevDevice* new_device = malloc(sizeof(DevDevice));
	if (new_device == NULL) {
		SDL_Log("Failed to create new DevDevice Malloc ERRNO:%i strerror:%s", errno, strerror(errno));
		return NULL;
	}
	new_device->name = name;
	new_device->base_addr = base_addr;
	new_device->init = init_func;
	new_device->read_8 = NULL;
	new_device->read_16 = NULL;
	new_device->read_32 = read32_func;
	new_device->write_8 = NULL;
	new_device->write_16 = NULL;
	new_device->write_32 = write32_func;
	return new_device;
}
*/