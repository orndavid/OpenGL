#ifndef _TEXTURES_H_
#define _TEXTURES_H_
#include "CONFIG.hpp"
#include <string>

// TODO add functionality for JPG, JPEG, GIF
enum FIG_TYPE{ PNG, JPG, JPEG, GIF};

class Textures
{
private:
  FIG_TYPE ftype;
  unsigned int id_, slot_;
  std::string filepath_;
  unsigned char* localBuffer;
  int width_, height_, BPP_; // BPP = bits per pixel
  GLenum texture;
public:
  Textures(FIG_TYPE type, std::string filepath, GLenum target_texture);
  /**
     @func Textures
     @brief 2D texture initialization function by default
     @param std::string filepath : Relative path, from the executable, to the texture file (currently .png file)
  */
  Textures(FIG_TYPE type, std::string filepath);
  ~Textures();

  void Bind(unsigned int slot=0);
  void Unbind() const;


  /**
     @func freeLocal
     @brief Call this if you don't need to store the copy on the cpu side during runtime, this clears up the data
  */
  void freeLocal();



  int width() const {return width_;};
  int height() const {return height_;};
  int bpp() const {return BPP_;};
  unsigned int slot() {return slot_;};

};

#endif //_TEXTURES_H_
