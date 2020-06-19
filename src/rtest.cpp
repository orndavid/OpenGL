#include "gl_api.h"
#include <iostream>
#include <exception>


int main(void)
{
  try{
    Window nwind;

  }catch(const std::runtime_error& e)
    {
      std::cerr << e.what() << std::endl;
      return -1;
    }

  std::cout << "Finshed\n";
    return 0;
}
