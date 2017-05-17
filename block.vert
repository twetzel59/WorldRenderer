#version 330 core

in vec3 pos;

out vec4 pass_color;

void main()
{
    gl_Position = vec4(pos / 2, 1.0);
    pass_color = vec4(1.0, 0.0, 0.0, 1.0);
}
