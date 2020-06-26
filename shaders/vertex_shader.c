#version 330 core
uniform mat4 MVP;
attribute vec4 vCol;
attribute vec3 vPos;
varying vec4 color;
void main()
{
    gl_Position = MVP * vec4(vPos, 1.0);
    color = vCol;
}
