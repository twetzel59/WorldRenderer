#version 330 core

in vec4 pass_color;
in vec2 pass_uv;
in float visibility;

out vec4 frag;

uniform sampler2D tex;
uniform vec3 sky_color;
uniform float daylight;

void main()
{
    //frag = pass_color;
    //frag = vec4(pass_color.x * pass_color.z, 0, 0, 1);
    //frag = vec4(1, pass_uv.x, pass_uv.y, 1);
    frag = texture(tex, pass_uv) * pass_color;
    frag = mix(vec4(sky_color, 1.0), frag, visibility) * clamp(daylight, 0.2, 1.0);
}
