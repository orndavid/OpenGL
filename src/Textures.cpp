#include "Textures.hpp"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include <iostream>

Textures::Textures(FIG_TYPE type, std::string filepath, GLenum target_texture):
                ftype(type)
                ,id_(0)
                ,slot_(0)
                ,filepath_(filepath)
                ,localBuffer(nullptr)
                ,width_(0)
                ,height_(0)
                ,BPP_(0)
                ,texture(target_texture)
{

  // Load the image
  stbi_set_flip_vertically_on_load(1);


  // Configure texture
  glGenTextures(1, &id_);
  glBindTexture(texture, id_);
  glTexParameteri(texture, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexParameteri(texture, GL_TEXTURE_MAG_FILTER, GL_TEXTURE_MIN_LOD);
  glTexParameteri(texture, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
  glTexParameteri(texture, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);

  if(ftype == FIG_TYPE::PNG)
    {
      localBuffer = stbi_load(filepath.c_str(), &width_, &height_, &BPP_, 4);
      glTexImage2D(texture, 0, GL_RGBA8, width_, height_, 0, GL_RGBA, GL_UNSIGNED_BYTE, localBuffer);
    }else if(ftype == FIG_TYPE::JPG)
    {
      localBuffer = stbi_load(filepath.c_str(), &width_, &height_, &BPP_, 0);
      glTexImage2D(texture, 0, GL_RGB, width_, height_, 0, GL_RGB, GL_UNSIGNED_BYTE, localBuffer);
    }
  glGenerateMipmap(texture);

  if(!localBuffer)
    std::cerr << "Failed to load texture buffer :" << filepath << std::endl;
}

Textures::Textures(FIG_TYPE type, std::string filepath):
  Textures(type, filepath, GL_TEXTURE_2D){}

Textures::~Textures()
{
  if(localBuffer)
    stbi_image_free(localBuffer);
  glDeleteTextures(1, &id_);
}

void Textures::Bind(unsigned int slot)
{
  slot_ = slot;
  glActiveTexture(GL_TEXTURE0+slot);
  glBindTexture(texture, id_);
}

void Textures::Unbind() const
{
  glBindTexture(texture, 0);
}

void Textures::freeLocal()
{
  if(localBuffer){
    stbi_image_free(localBuffer);
    localBuffer = nullptr;
  }
}
