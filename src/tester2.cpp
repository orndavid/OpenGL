#include "gl_api.hpp"
#include <iostream>

#include "linmath.h" //Matrix computation in render()

// static struct _verticies
//   configuration  x, y, z, r, g, b;
float vertices[4][6] =
  {
   { -0.7f,  0.7f, 0.0f, 1.f, .0f, 0.f },//0
   { -0.7f, -0.7f, 0.0f, 0.f, 1.f, 0.f },//1
   {  0.7f, -0.7f,-0.0f, 0.f, 0.f, 1.f },//2
   {  0.7f,  0.7f, 0.0f, 0.f, 1.f, 0.f } //3
  };

unsigned int indicies[] =
  {
   0,1,2,
   2,3,0
  };




int main(void)
{
  Window nwin;

  FragmentShader fragment_shader("../shaders/fragment_shader.c");
  VertexShader vertex_shader("../shaders/vertex_shader.c");

  { /* This is because we mut ensure that the buffers destructors get called before the final window destructor */

    //VertexBuffer<float> vbo(data, 5);
  VertexBuffer vbo(vertices, 4*6*sizeof(float));
  IndexBuffer  ibo(indicies, 6);
  vbo.Bind();
  ibo.Bind();
  Program program;

  program.add_shader(fragment_shader);
  program.add_shader(vertex_shader);
  program.Bind();

  program.vap("vPos", 3, GL_FLOAT, 6*sizeof(float), (void*) 0);
  program.vap("vCol", 3, GL_FLOAT, 6*sizeof(float), (void*) (sizeof(float)*3));

  mat4x4 m, p, mvp;
  unsigned int mvp_location = program.uniform_loc("MVP");
  int height, width;
  float ratio;
  // Move all into main function

  while(!nwin.close())
    {
      nwin.windowSize(&height, &width);
      nwin.clear();

      ratio = width / (float)height;
      nwin.constantViewport();

      mat4x4_identity(m);
      mat4x4_rotate_Z(m, m, (float) glfwGetTime());
      mat4x4_ortho(p, -ratio, ratio, -1.f, 1.f, 1.f, -1.f);
      mat4x4_mul(mvp, p, m);

      program.use();
      // ???

      glUniformMatrix4fv(mvp_location, 1, GL_FALSE, (const GLfloat*) mvp);
      // Overwrite this in nwin
      //nwin.draw(GL_TRIANGLES, 6,);
      glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);

      // Overwrite in nwin
      nwin.swapBuffers();
      nwin.pollEvents();
    }

  } /*Ensuring buffers are called first*/

  return 0;
}
