#ifndef _WINDOW_H_
#define _WINDOW_H_

struct GLFWwindow;

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
     @func render
     @brief This function is overwritten by the user, it gets called in the start function
     @param
  */

  int height() {return height_;};
  int width() {return width_;};
  GLFWwindow* win() {return window;};

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
