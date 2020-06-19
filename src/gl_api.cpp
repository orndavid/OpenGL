#include "gl_api.h"
#include "glad/gl.h"
#include "GLFW/glfw3.h"

#include <iostream>
#include <exception>
#include <memory>
#include "linmath.h"
#include <string>
#include <fstream>

#include <stdlib.h>
#include <stdio.h>
#include <stdexcept>

#include <cstddef> // offsetof
#include <alloca.h> // alloca

Window::Window()
{
  if(!glfwInit())
    {
      std::cerr << "Failed to initialize glfw\n";
    }else
    std::cout << "GLFW initialized\n";
  // Enable the window
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
  window = glfwCreateWindow(640, 480, "My Title", NULL, NULL);
  if (!window)
    {
      throw std::runtime_error("Failed to create window");
    }

  if (!glfwInit())
    exit(EXIT_FAILURE);

  glfwMakeContextCurrent(window);
  // Connecting the callback to the window
  glfwSetKeyCallback(window, key_callback);
  gladLoadGL(glfwGetProcAddress);
  glfwSwapInterval(1);

  glGenBuffers(1, &vertex_buffer);
  glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  // TODO move this into a function call from the outside
  // Load the shader text
  vertex_shader_txt   = load_shader_text(GL_VERTEX_SHADER, "vertex_shader.c");
  fragment_shader_txt = load_shader_text(GL_FRAGMENT_SHADER, "fragment_shader.c");

  // Add here -> CompileShader, but first we need to figure out how to configure the string src
  vertex_shader   = CompileShader(GL_VERTEX_SHADER, vertex_shader_txt);
  fragment_shader = CompileShader(GL_FRAGMENT_SHADER, fragment_shader_txt);

  // Attaches the programs to the
  ProgramSet();

  mvp_location = glGetUniformLocation(program, "MVP");
  vpos_location = glGetAttribLocation(program, "vPos");
  vcol_location = glGetAttribLocation(program, "vCol");

  glEnableVertexAttribArray(vpos_location);
  glVertexAttribPointer(vpos_location, 3, GL_FLOAT, GL_FALSE,
                        sizeof(vertices[0]), (void*) 0);
  glEnableVertexAttribArray(vcol_location);
  glVertexAttribPointer(vcol_location, 3, GL_FLOAT, GL_FALSE,
                        sizeof(vertices[0]), (void*) (sizeof(float) * 2));

  //std::cout << "offs (vces, y) " << offsetof(vces, y) << std::endl;

  while(!glfwWindowShouldClose(window))
    {
      //std::cout << glfwWindowShouldClose(window) << std::endl;
      render();
      glfwSwapBuffers(window);
      glfwPollEvents();
    }
}


Window::~Window()
{
  glDeleteProgram(program);
  glDeleteShader(vertex_shader);
  glDeleteShader(fragment_shader);
  glfwDestroyWindow(window);
  glfwTerminate();
}


void Window::render()
{
  glfwGetFramebufferSize(window, &width, &height);
  ratio = width / (float) height;

  glViewport(0, 0, width, height);
  glClear(GL_COLOR_BUFFER_BIT);

  mat4x4_identity(m);
  mat4x4_rotate_Z(m, m, (float) glfwGetTime()*2);
  mat4x4_ortho(p, -ratio, ratio, -1.f, 1.f, 1.f, -1.f);
  mat4x4_mul(mvp, p, m);
  mat4x4_scale(mvp, mvp, 1.0/(10*glfwGetTime()));

  glUseProgram(program);
  glUniformMatrix4fv(mvp_location, 1, GL_FALSE, (const GLfloat*) mvp);
  glDrawArrays(GL_TRIANGLES, 0, 3);
  update();
}


void Window::update()
{
  if(count%1000==0)
    {
      float p = 0.95;
      vertices[0].x = vertices[0].x*p;
      vertices[1].r = vertices[1].r*p;
    }

  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_DYNAMIC_DRAW);
  count++;
}


GLuint Window::CompileShader(unsigned int type, const std::string& source)
{
  GLuint id = glCreateShader(type);
  const char* src = source.c_str();
  glShaderSource(id, 1, &src, nullptr);
  glCompileShader(id);
  // Error handling
  GLint vertex_compiled;
  glGetShaderiv(id, GL_COMPILE_STATUS, &vertex_compiled);
  if(vertex_compiled != GL_TRUE)
    {
      int log_length = 0;
      GLchar msg[1024];
      glGetShaderInfoLog(id, 1024, &log_length, msg);
      //Create an output message
      std::string _type = (type == GL_VERTEX_SHADER ? "vertex" : "fragment");
      std::string emsg = "Failed to compile shader " + _type + " -- \n";
      std::cout << msg << std::endl;
      glDeleteShader(id);
      throw std::runtime_error(emsg);
    }
  return id;
}


void Window::ProgramSet()
{
  program = glCreateProgram();
  glAttachShader(program, vertex_shader);
  glAttachShader(program, fragment_shader);
  glLinkProgram(program);
  glValidateProgram(program);
}


std::string Window::load_shader_text(GLuint type, const std::string& filename)
{
  std::fstream fin(filename, std::fstream::in);
  if(fin)
    {
      std::string data;
      fin.seekg(0, std::ios::end);
      data.resize(fin.tellg());
      fin.seekg(0, std::ios::beg);
      fin.read(&data[0], data.size());
      fin.close();
      return data;
    }
  std::string emsg = "Failed to open file: " + filename;
  throw std::runtime_error(emsg);
}


void Window::print()
{
  std::cout << "Printing info about window\n";
}


static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{

  if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    {
      glfwSetWindowShouldClose(window, GLFW_TRUE);
    }
  else if(key == GLFW_KEY_Q && GLFW_PRESS)
    {
      glfwSetWindowShouldClose(window, GLFW_TRUE);
    }
}
