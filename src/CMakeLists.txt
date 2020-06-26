set(glfw_lib "/mnt/gaia/C++/OpenGL/extern/glfw/build/src/libglfw.so")

add_library(glad_lib IMPORTED STATIC)
set_property(TARGET glad_lib PROPERTY
  IMPORTED_LOCATION "${PROJECT_SOURCE_DIR}/extern/glad/build/libglad.a")
add_library(dl IMPORTED STATIC)
set_property(TARGET dl PROPERTY
  IMPORTED_LOCATION "/lib/x86_64-linux-gnu/libdl.so.2")


message("Project source dir " ${PROJECT_SOURCE_DIR})
set(lib_name "gl_custom_lib")
add_library(${lib_name}
  ${PROJECT_SOURCE_DIR}/src/gl_api.cpp
  ${PROJECT_SOURCE_DIR}/src/Window.cpp
  ${PROJECT_SOURCE_DIR}/src/Shaders.cpp
  ${PROJECT_SOURCE_DIR}/src/VertexBuffer.cpp
  ${PROJECT_SOURCE_DIR}/src/IndexBuffer.cpp
  ${PROJECT_SOURCE_DIR}/src/Program.cpp
  ${PROJECT_SOURCE_DIR}/src/Textures.cpp

  )

target_include_directories(
  ${lib_name} PUBLIC
  ${PROJECT_SOURCE_DIR}/inc
  ${PROJECT_SOURCE_DIR}/extern/glad/build/include
  ${PROJECT_SOURCE_DIR}/extern/glfw/include
  ${PROJECT_SOURCE_DIR}/extern/glfw/deps
  ${PROJECT_SOURCE_DIR}/extern/stb_image
  )

target_link_libraries(
  ${lib_name} PRIVATE
  glad_lib ${glfw_lib} dl
  )

# Configure threading
#find_package(Threads REQUIRED)

set(NAME rrun)
#add_executable(${NAME} rtest.cpp gl_api.cpp error_handling.cpp)
#target_include_directories(${NAME} PUBLIC ${PROJECT_SOURCE_DIR}/inc
#   ${PROJECT_SOURCE_DIR}/extern/glfw/include
#   ${PROJECT_SOURCE_DIR}/extern/glfw/deps ${PROJECT_SOURCE_DIR}/extern/glad/build/include
#
#  )
#target_link_libraries(${NAME} PRIVATE glad_lib ${glfw_lib} dl)

add_executable(test2 tester2.cpp ${PROJECT_SOURCE_DIR}/inc/gl_api.hpp)
target_link_libraries(test2 ${lib_name})
