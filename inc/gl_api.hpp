#ifndef _GL_API_H_
#define _GL_API_H_
// Open up the window configuration
/**
   @incl  Window
   @brief Create a new window
   @param Possible initializers
       Window(int height, int width, const char* name);
       Window(int height, int width);
       Window(const char* name);
       Window();


  What is missing for the code to be complete is the definition of a render function
             void Window::render();
  This function is called in the while loop in the window


*/
#include "Window.hpp"

/**
   @incl  Shader control
   @brief Control flow for the shader
   @func std::string load_shader_text(GLuint type, const std::string& filename)
*/
#include "Shaders.hpp"

/**
   @incl  Vertex buffer handling, a simple call
   @brief
   @param
*/
#include "VertexBuffer.hpp"

/**
   @incl   Index buffer handling, simple class
   @brief
   @param
*/
#include "IndexBuffer.hpp"

/**
   @incl   Creates a program object that handles erros and creations
   @brief
   @param
*/
#include "Program.hpp"



#endif //_GL_API_H_
