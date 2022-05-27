#include"DevScreen.h"
#undef main
int main() {
	DevScr_CreateDisplay(640, 480);
	DevScr_BeginRenderLoop();
}