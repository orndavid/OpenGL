#ifndef _INDEXBUFFER_H_
#define _INDEXBUFFER_H_
#include "CONFIG.hpp"
class IndexBuffer
{
public:
  IndexBuffer(const unsigned int* data, const unsigned int count);
  ~IndexBuffer();

  void Bind() const;
  void Unbind() const;

  const unsigned int count() {return count_;};

  /**
     @func type
     @brief Get the GLenum type of the ibo buffer, by default this is GL_UNSIGNED_INT
     @returns The GLenum value of the buffer
  */
  GLenum type() {return type_;};

private:
  unsigned int id_;
  const unsigned int count_;
  GLenum type_;
};
#endif //_INDEXBUFFER_H_
