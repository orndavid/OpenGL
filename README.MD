* OpenGL overview and configuration
- Currently we are not using googletest and the cmake config is disabled

** Dependencies
The extern folder contains three external libraries that are required
- glad       : git@github.com:Dav1dde/glad.git
- glfw       : git@github.com:glfw/glfw.git
- googletest : git@github.com:google/googletest.git

Clone those submodules into the extern file and build accordingly. 
Make sure to cp the glad.h file that gets created into inc/ since your file will probably be different.

** Build
After fetching and compiling the dependencies do the following from the top dir (OpenGL)
```shell
mkdir build && cd build
cmake .. -DCMAKE_BUILD_TYPE=Debug
cp ../bin/* .
./rrun
```
Here we set the make to run in debug mode and we move the shader files into the directory so we can run directly from there using ./rrun

** Sources
- The Cherno on youtube
  - https://www.youtube.com/watch?v=W3gAzLwfIP0&list=PLlrATfBNZ98foTJPJ_Ev03o2oq3-GGOS2
  
**** Topics
- Physically based rendering
- 2d rendering
- 3d render
- Lighting
- Rendering
- Post rendering
- Screenbased reflection
- 

*** What is it?
 It's a definition for interaction, via drivers,  to access our underlying hardware for rendering.

*** What isn't it?
 - It's not open source.
 - It's not a framework


