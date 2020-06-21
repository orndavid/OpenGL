#include "gl_api.h"
#include <iostream>
#include <exception>
#include <thread>

void build_window()
{
  try{
    Window nwind;

  }catch(const std::runtime_error& e)
    {
      std::cerr << e.what() << std::endl;
    }
}

int main(void)
{
  /*std::thread thr_class(build_window);
  std::cout << "Continuing the main function \n";
  thr_class.join();*/
  Window nwind;
  std::cout << "Finishing function \n";
  return 0;
}
