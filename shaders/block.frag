#version 330 core

in vec4 pass_color;
in vec2 pass_uv;

out vec4 frag;

uniform sampler2D tex;

void main()
{
    //frag = pass_color;
    //frag = vec4(pass_color.x * pass_color.z, 0, 0, 1);
    //frag = vec4(1, pass_uv.x, pass_uv.y, 1);
    frag = texture(tex, pass_uv) * pass_color;
}
