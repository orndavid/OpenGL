#ifndef _VERTEXBUFFER_H_
#define _VERTEXBUFFER_H_
#include "CONFIG.hpp"


class VertexBuffer
{
public:
  VertexBuffer(const void* data, unsigned int size);
  ~VertexBuffer();

  void Bind() const;
  void Unbind() const;
  unsigned int id() {return id_;};
private:
  unsigned int id_;
};
#endif //_VERTEXBUFFER_H_
