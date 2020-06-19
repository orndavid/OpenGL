set(glfw_lib "/mnt/gaia/C++/OpenGL/extern/glfw/build/src/libglfw.so")
set(dllib "/lib/x86_64-linux-gnu/libdl.so.2")

add_library(glad_lib IMPORTED STATIC)
set_property(TARGET glad_lib PROPERTY
  IMPORTED_LOCATION "${PROJECT_SOURCE_DIR}/extern/glad/build/libglad.a")
add_library(dl IMPORTED STATIC)
set_property(TARGET dl PROPERTY
  IMPORTED_LOCATION "/lib/x86_64-linux-gnu/libdl.so.2")

# Configure threading
find_package(Threads REQUIRED)

set(NAME rrun)
add_executable(${NAME} rtest.cpp gl_api.cpp)
target_include_directories(${NAME} PUBLIC ${PROJECT_SOURCE_DIR}/inc
   ${PROJECT_SOURCE_DIR}/extern/glfw/include
   ${PROJECT_SOURCE_DIR}/extern/glfw/deps
  )
target_link_libraries(${NAME} PRIVATE glad_lib ${glfw_lib} dl "-pthread")
