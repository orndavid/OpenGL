#ifndef _PROGRAM_H_
#define _PROGRAM_H_
#include "CONFIG.hpp"
#include "Shaders.hpp"
#include <map>

class Program
{
private:
  unsigned int program_id;
  std::map <const std::string, int> attribs;
  std::map <const std::string, int> uniforms;

public:
  Program();
  ~Program();

  /**
     @func add_shader
     @brief Add a shader object to the program. Takes in the base class
     @param Shader& shdr : reference to the created shader
  */
  void add_shader(Shader& shdr);
  /**
     @func  Bind
     @brief Binds the created program ids to the gpu using glLinkProgram, call add_shader first
  */
  void Bind();

  /**
     @func attrib_loc
     @brief Get a id to the shader variable on the gpu
     @param std::string name, name of the variable in the shader
  */
  unsigned int attrib_loc(const std::string name);
  unsigned int uniform_loc(const std::string name);

  unsigned int id() {return program_id;};

};

#endif //_PROGRAM_H_
