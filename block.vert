#version 330 core

in vec3 pos;
in vec3 color;

out vec4 pass_color;

void main()
{
    gl_Position = vec4(pos, 1.0);
    pass_color = vec4(color, 1.0);
}
