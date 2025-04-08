#include "DevKeyboard.h"
#include <SDL.h>
#include<string.h>

unsigned char* KeyBuffer;
extern SDL_Window* SDLWindow;
int DevKeyboard_EventWatch(void* userdata,SDL_Event* event){

    if(event->type == SDL_KEYDOWN){
#if 0 
        if(event->key.keysym.sym == SDLK_c){
            if(SDL_GetWindowMouseGrab(SDLWindow) == SDL_FALSE){
                 SDL_SetWindowMouseGrab(SDLWindow,SDL_TRUE);
            }else{
             SDL_SetWindowMouseGrab(SDLWindow,SDL_FALSE);
            }
         }
#endif
        for (int i = 0; i < 512; i++)
        {
        
            KeyBuffer[i] = event->key.keysym.scancode;
            //SDL_Log("CurrentScancode:%x\n", event->key.keysym.scancode);
        }
        
    }

   
   
}
void DevKeyboard_Init(){
    //SDL_SetWindowMouseGrab(SDLWindow,SDL_TRUE);
    KeyBuffer = calloc(512, 1);
    if (KeyBuffer == NULL) {
        SDL_Log("Failed to allocate Keyboard KeyBuffer!\nstrerror:%s ERRNO:%i\n", strerror(errno), errno);
        SDL_Quit();
    }
    SDL_AddEventWatch(DevKeyboard_EventWatch,NULL);
}
unsigned char DevKeyboard_ReadKey(unsigned short addr){
    return KeyBuffer[addr];
}