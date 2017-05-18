#version 330 core

in vec4 pass_color;

out vec4 frag;

void main()
{
    frag = pass_color;
    //frag = vec4(pass_color.x * pass_color.z, 0, 0, 1);
}
