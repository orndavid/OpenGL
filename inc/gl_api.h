#ifndef _GL_API_H
#define _GL_API_H
#include <glad/gl.h>
#include "GLFW/glfw3.h"

#include <memory>
#include "linmath.h"

#include <stdlib.h>
#include <stdio.h>

static struct _verticies
{
  float x, y, z;
  float r, g, b;
} vertices[] =
  {
   { -0.7f,  0.7f, 0.0f, 1.f, .0f, 0.f },//0
   { -0.7f, -0.7f, 0.0f, 0.f, 1.f, 0.f },//1
   {  0.7f, -0.7f,-0.0f, 0.f, 0.f, 1.f },//2
   {  0.7f,  0.7f, 0.0f, 0.f, 1.f, 0.f } //3
  };


class Window
{
 public:
  Window();
  ~Window();
  /**
     @func print
     @brief Print out information about the class object
  */
  void print();
 protected:
  /**
     @func update
     @brief The redraw function that is called each time
  */
  void update();

  /**
     @func load_shader_tesxt
     @brief
     @param GLuint type can be either GL_VERTEX_SHADER or GL_FRAGMENT_SHADER,
                   const std::string& filename set the shader filename
     @returns std::string containing the values from filename as a string
  */
  std::string load_shader_text(GLuint type, const std::string& filename);
 private:
  int width, height, count {0};
  float ratio;
  GLFWwindow* window;
  // ibo = index buffer object
  GLuint vertex_buffer, vertex_shader, fragment_shader, program, ibo;
  GLint mvp_location, vpos_location, vcol_location;
  mat4x4 m, p, mvp;
  std::string vertex_shader_txt, fragment_shader_txt;

  /**
     @func render
     @brief The function called in the object main loop.
  */
  void render();
  /**
     @func CompileShader
     @brief Create a integer value for a compile shader
     @param type   = unsigned integer for type
     source = string value, definition of the shader
     @returns GLuint value of shader glCreateShader
  */
  GLuint CompileShader(unsigned int type, const std::string& source);

  /**
     @func  ProgramSet
     @brief Sets the created shaders into a program and initializes it
     Should only be run after CompileShaders
  */
  void ProgramSet();

  /**
     @func  errcall
     @brief The fuction call for error handling
  */

  void errcall();
};


static void key_callback(GLFWwindow* wwindow, int key, int scancode, int action, int mods);

#endif // _GL_API_H
