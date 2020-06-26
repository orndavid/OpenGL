#include "Program.hpp"

Program::Program()
{
  program_id = glCreateProgram();
}


Program::~Program()
{
}

void Program::add_shader(Shader& shdr)
{
  glAttachShader(program_id, shdr.id_);
}

void Program::Bind()
{
  glLinkProgram(program_id);
  glValidateProgram(program_id);
}

void Program::use()
{
  glUseProgram(program_id);
}


unsigned int Program::attrib_loc(const std::string name)
{
  const GLchar* glname = name.c_str();
  if(attribs.count(name))
    {
      return attribs[name];
    }
  else{
    int id = glGetAttribLocation(program_id, glname);
    attribs[name] = id;
    if(id == -1)
      {
        std::cerr << "Failed to find on GPU variable " << name << std::endl;
      }
    return id;
  }
}


void Program::vap(std::string vname,
                  int size,
                  GLenum type,
                  unsigned int stride,
                  const void* pointer)
{
  unsigned int id = attrib_loc(vname);
  glEnableVertexAttribArray(id);
  glVertexAttribPointer(id, size, type, GL_FALSE, stride, pointer);
}


unsigned int Program::uniform_loc(const std::string name)
{
  const GLchar* glname = name.c_str();
  if(uniforms.count(name))
    {
      return attribs[name];
    }
  else{
    int id = glGetUniformLocation(program_id, glname);
    uniforms[name] = id;
    if(id == -1)
      {
        std::cerr << "Failed to find on GPU variable " << name << std::endl;
      }
    return id;
  }
}
