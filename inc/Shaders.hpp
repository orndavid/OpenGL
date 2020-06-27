#ifndef _SHADERS_H_
#define _SHADERS_H_
#include <iostream>

/**
   @class Shader
   @brief Base shader type for the shader usecases
*/
class Shader
{
public:
  Shader(unsigned int type, std::string);
  ~Shader();
  unsigned int id_;
  void Bind() const;
  void Unbind() const;
};

class VertexShader : public Shader
{
public:
  VertexShader(std::string filename);
  unsigned int id(){return id_;};
};

class FragmentShader : public Shader
{
public:
  FragmentShader(std::string filename);
  unsigned int id(){return id_;};
};

/**
   @func load_shader_text
   @brief Loads the fragment and vertex shader from a string file and returns the file as a string.
   @param GLuint type : integer referring to vertex/fragment
          filename name of the files containing the actual files
*/
unsigned int load_shader_text(unsigned int type, const std::string& filename);

unsigned int CompileShader(unsigned int type, const std::string& source);

#endif //_SHADERS_H_
