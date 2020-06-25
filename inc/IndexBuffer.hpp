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

private:
  unsigned int id_;
  const unsigned int count_;
};
#endif //_INDEXBUFFER_H_
