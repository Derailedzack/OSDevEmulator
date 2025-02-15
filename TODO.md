# OSDevEmulator TODO List
  1. [ ] Add support for using lua for custom machines
# Lua TODO List
  1. [ ] Rewrite libraries in pure lua where possible and makes sense instead of C
# DevScreen TODO List
  1. [x]  Rewrite bitmap display to use a texture for rendering instead of glDrawpixel (1, 3, 4 and 5 have been done for sometime now)
  2. [ ]  Add premake support
  3. [x]  Add SDL2 rendering support 
  4. [x]  Commit working DevDisplay
  5. [x]  Readd OpenGL support into the DevDisplay
  6. [ ]  Implement various display modes (Text mode(s),Bitmap mode(s) at varrying color depths and resolutions and Tile mode(s)
  7. [ ]  Fix the Release config (Add C includes and libraries as well the library path for said libraries
  8. [ ]  Implement shader complication and linking into the DevScreen
  9. [ ] Decouple main loop from the DevScreen
