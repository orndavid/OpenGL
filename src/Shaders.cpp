#include "Shaders.hpp"
#include "CONFIG.hpp"
#include <fstream>


Shader::Shader(unsigned int type, std::string filename) :
  id_(load_shader_text(type, filename))
{}

Shader::~Shader()
{}


void Shader::Bind() const
{
  glUseProgram(id_);
}

void Shader::Unbind() const
{
  glUseProgram(0);
}


VertexShader::VertexShader(std::string filename):
  Shader(GL_VERTEX_SHADER, filename){}



FragmentShader::FragmentShader(std::string filename):
  Shader(GL_FRAGMENT_SHADER, filename){}


/**
   @func load_shader_text
   @brief Turns a textfile into a shader string object to send to GPU
   @param GLuint type : Type of shader GL_VERTEX_SHADER or GL_FRAGMET_SHADER,
          std::string filename = name of file with relative path from program call
   @return unsigned int id of shader
*/
unsigned int load_shader_text(GLuint type,
                              const std::string& filename)
{
  std::string data;
  std::fstream fin(filename, std::fstream::in);
  if(fin)
    {
      fin.seekg(0, std::ios::end);
      data.resize(fin.tellg());
      fin.seekg(0, std::ios::beg);
      fin.read(&data[0], data.size());
      fin.close();
    }
  else
    {
      std::string emsg = "Failed to open file: " + filename;
      throw std::runtime_error(emsg);
    }
  return CompileShader(type, data);
}

/**
   @func CompileShader
   @brief Compile a shader string and return the
   @param GLuint type : type of shader either GL_FRAGMENT_SHADER or GL_VERTEX_SHADER
          std::string& source : String representation of the input file
   @returns unsigned int shader id
*/
unsigned int CompileShader(GLuint type, const std::string& source)
{
  unsigned int id = glCreateShader(type);
  const char* src = source.c_str();
  glShaderSource(id, 1, &src, nullptr);
  glCompileShader(id);
  // Error handling
  GLint vertex_compiled;
  glGetShaderiv(id, GL_COMPILE_STATUS, &vertex_compiled);
  if(vertex_compiled != GL_TRUE)
    {
      int log_length = 0;
      char msg[1024];
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
