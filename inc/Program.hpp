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
     @func use
     @brief Sets the program to the current program being used
  */
  void use();

  /**
     @func vap
     @brief Set the  Vertex Attribute Pointer, i.e. the format of the read signal as acoording to the shaders
     @param std::string vname : name of variable in shader
            GLennum type : E.g. GL_FLOAT , depends on definition in shader
            unsigned int stride : Number of values in the array that pertain to said attribute, i.e. the offset between consecutive generic vertex attributes
            const void* pointer Specifies a offset of the first component of the first generic attribute in the array. (The initial value is 0)
  */
  void vap(std::string vname,
           int size,
           GLenum type,
           unsigned int stride,
           const void* pointer);

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
