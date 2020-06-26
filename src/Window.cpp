#include "Window.hpp"
#include <stdexcept>
#include <iostream>
#include <memory>

#define WHEIGHT 480
#define WWIDTH  640
#define WINNAME "Custom OpenGL Window"
static void key_callback(GLFWwindow* wwindow, int key, int scancode, int action, int mods);


Window::Window() :
  Window(WHEIGHT,WWIDTH, WINNAME){}

Window::Window(int height_, int width_):
  Window(height_, width_, WINNAME){}

Window::Window(const char* name):
  Window(WHEIGHT, WWIDTH, name){}


Window::Window(int _height, int _width, const char* name):
  height_(_height)
  , width_(_width)
  , window_name(name)
{
  if(!glfwInit())
    {
      throw std::runtime_error("Failed to initialize glfw");
    }else
    std::cout << "GLFW initialized\n";
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
  window = glfwCreateWindow(width_, height_, window_name, NULL, NULL);
  if(!window)
    {
      throw std::runtime_error("Failed to create window");
    }

  glfwMakeContextCurrent(window);
  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
      throw std::runtime_error("Failed to initialize GLAD");
    }
  // Set framerate
  glfwSwapInterval(1);
  // Bind the exit strategy
  glfwSetKeyCallback(window, key_callback);
}


Window::~Window()
{
  glfwDestroyWindow(window);
  glfwTerminate();
}

void Window::framerate(int fr)
{
  glfwMakeContextCurrent(window);
  glfwSwapInterval(fr);
}


void Window::windowSize(int* height, int* width)
{
  glfwGetFramebufferSize(window, width, height);
  width_ = *width;
  height_ = *height;
}

void Window::swapBuffers()
{
  glfwSwapBuffers(window);
}

void Window::pollEvents()
{
  glfwPollEvents();
}

void Window::wireframe()
{
  glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); //Enables wireframe mode
}

bool Window::close()
{
  return glfwWindowShouldClose(window);
}

void Window::clear()
{
  glClear(GL_COLOR_BUFFER_BIT);
}

void Window::constantViewport()
{
  glViewport(0, 0, width_, height_);
}

void Window::tDrawF(IndexBuffer& ibo)
{
  draw(GL_TRIANGLES, ibo.count(), ibo.type());
}

void Window::draw(GLenum mode, unsigned int count, GLenum type, const GLvoid* indicies)
{
  glDrawElements(mode, count, type, nullptr);
  glEnable(GL_BLEND);
}

void Window::blendOn()
{
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

}

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
  if(glfwGetKey(window, GLFW_KEY_ESCAPE))
    glfwSetWindowShouldClose(window, GLFW_TRUE);
  else if(glfwGetKey(window, GLFW_KEY_Q))
    glfwSetWindowShouldClose(window, GLFW_TRUE);
}
