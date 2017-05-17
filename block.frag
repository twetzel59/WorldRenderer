#version 330 core

in vec4 pass_color;

out vec4 color;

void main()
{
    color = pass_color / 2;
}
