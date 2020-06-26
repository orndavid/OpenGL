#ifndef _WINDOW_H_
#define _WINDOW_H_
#include "CONFIG.hpp"
#include "IndexBuffer.hpp"

class Window{
public:
  Window(int height, int width, const char* name);
  Window(int height, int width);
  Window(const char* name);
  Window();
  ~Window();

  /**
     @func framerate
     @brief Sets the framerate for the opengl by using glfwSwapInterval
     @param int fr : value to set the framerate to
  */
  void framerate(int fr);
  /**
     @func  start
     @brief start function, after configuring the required values run the start
            program which starts the while loop, calls render, glfwSwapBuffers and polls
            for event
  */

  void wireframe();

  /**
     @func windowSize
     @brief Sets the values by reference of the window height and width
     @param int& height
            int& width
  */
  void windowSize(int* height, int* width);

  /**
     @func clear
     @brief Clears the current figure in the window
  */
  void clear();

  /**
     @func constantViewport()
     @brief Sets the viewport to represent the height and width of the window
  */
  void constantViewport();
  /**
     @func swapBuffers
     @brief Swaps the front and back buffers for window
  */
  void swapBuffers();
  /**
     @func pollEvents
     @brief Checks the window for event actions
  */
  void pollEvents();

 /**
    @func tDrawF
    @brief Triangle draw from an index buffer object where the input type is float
    @param IndexBuffer& ibo : Reference to a specific type
 */
  void tDrawF(IndexBuffer& ibo);
  /**
     @func  draw
     @brief Call the glDrawElements, which renders primatives from the array data
     @param GLenum mode : Defines what type of primatives to draw
            unsigned int count: Number of elements to be drawn
            GLenum type : specifies the type of value in indicies, e.g. GL_UNSIGNED_BYTE, GL_UNSIGNED_SHORT, GL_UNSIGNED_INT

  */
  void draw(GLenum mode, unsigned int count, GLenum type, const void* indicies=nullptr);

  int height() {return height_;};
  int width() {return width_;};
  GLFWwindow* win() {return window;};

  /**
     @func blendOn
     @brief Turns on blending allowing for the alpha value to be processed
  */
  void blendOn();

  bool close();

private:
  GLFWwindow* window;
  int height_;
  int width_;
  const char* window_name;
  //
  void* functionCall();
};




#endif //_WINDOW_H_
