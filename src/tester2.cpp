#includexg "gl_api.hpp"
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



void render(Window& window, Program& program)
{
  mat4x4 m, p, mvp;
  unsigned int mvp_location = program.uniform_loc("MVP");
  int height, width;
  float ratio;
  // Move all into main function
  while(!window.close())
    {
      height = window.height();
      width = window.width();
      //Overwrite this in window
      glfwGetFramebufferSize(window.win(), &width, &height);
      // Overwrite this in window
      glClear(GL_COLOR_BUFFER_BIT);

      ratio = width / (float)height;

      // Overwrite this in window
      glViewport(0, 0, width, height);

      mat4x4_identity(m);
      mat4x4_rotate_Z(m, m, (float) glfwGetTime());
      mat4x4_ortho(p, -ratio, ratio, -1.f, 1.f, 1.f, -1.f);
      mat4x4_mul(mvp, p, m);

      // Overwrite this in program
      glUseProgram(program.id());
      // ???
      glUniformMatrix4fv(mvp_location, 1, GL_FALSE, (const GLfloat*) mvp);
      // Overwrite this in window
      glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);

      // Overwrite in window
      glfwSwapBuffers(window.win());
      glfwPollEvents();
    }
}


int main(void)
{
  Window nwin;

  FragmentShader fragment_shader("../shaders/fragment_shader.c");
  VertexShader vertex_shader("../shaders/vertex_shader.c");
  //  unsigned int vertex_shader = load_shader_text(GL_VERTEX_SHADER, "../shaders/vertex_shader.c");
  //unsigned int fragment_shader = load_shader_text(GL_FRAGMENT_SHADER, "../shaders/fragment_shader.c");
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

  unsigned int vpos_location = program.attrib_loc("vPos");
  unsigned int vcol_location = program.attrib_loc("vCol");

  // TODO : abstract the openGL calls

  glEnableVertexAttribArray(vpos_location);
  glVertexAttribPointer(vpos_location, 3, GL_FLOAT, GL_FALSE,
                        sizeof(vertices[0]), (void*) 0);

  glEnableVertexAttribArray(vcol_location);
  glVertexAttribPointer(vcol_location, 3, GL_FLOAT, GL_FALSE,
                        sizeof(vertices[0]), (void*) (sizeof(float) * 3));


  render(nwin, program);
  } /*Ensuring buffers are called first*/

  return 0;
}
