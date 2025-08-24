 # OSDevEmulator TODO List
  1. [ ] Add support for using lua for custom machines
  2. [ ] Port to the WiiU when this project is more complete
  3. [ ] Implement support for using a custom  scripting language
  4. [ ] Add CPU emulator specific code to main branch (As syncing branches sucks)
 5. [ ] Add support for using wasm, lua or a shared object to create/define an emulated system (Might use wasmer for the wasm part)
 6. [ ] Decide on whether to split wasm off as a separate project based on the OSDevEmulator's source
 7. [ ] Bitwise and addr in read and write callbacks with 0x00ffff to get offset from the address
# Lua TODO List
  1. [ ] Rewrite libraries in pure lua where possible and makes sense instead of C
  2. [ ] Rename Lua library name to just Lua51 for allowing for luajit to used instead of the plain old c implementation of Lua 5.1
# DevScreen TODO List
  1. [x]  Rewrite bitmap display to use a texture for rendering instead of glDrawpixel (1, 3, 4 and 5 have been done for sometime now)
  2. [ ]  Add premake support
  3. [x]  Add SDL2 rendering support 
  4. [x]  Commit working DevDisplay
  5. [x]  Readd OpenGL support into the DevDisplay
  6. [ ]  Implement various display modes (Text mode(s),Bitmap mode(s) at varrying color depths and resolutions and Tile mode(s)
  7. [ ]  Fix the Release config (Add C includes and libraries as well the library path for said libraries
  8. [ ]  Implement shader complication and linking into the DevScreen
  9. [x] Decouple main loop from the DevScreen
 10. [ ] Add text attribute registers to the DevScreen registers
 11. [ ] Add text FG and BG color to DevScreen 
 12. [x] Change Videomode check from a if statement to a switch case
 13. [ ] Add bank switching support to VRAM and TilesGFX RAM
 14. [ ] Add total number of tiles register to DevScreen or Number of tiles to indicate how many SDL Rects to allocate
 15. [ ] Remove Read and Write from the DevScr lua library (As well it doesn't really make sense to have this in lua
 16. [x] Rename 800x600 bitmap 8bpp to 800x600  bitmap 32bpp
 17. [ ] Add better way to enable and disable OpenGL for the DevScreen (Might use a config for this)
