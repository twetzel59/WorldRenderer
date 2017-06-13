#version 330

in vec2 pass_uv;

out vec4 pixel;

uniform sampler2D cloud_tex;
uniform vec3 sky_color;

void main() {
    //pixel = vec4(pass_uv.x, 0.0, pass_uv.y, 1.0) + vec4(sky_color.r * 0.000001 + daylight * 0.000001, 0.0, 0.0, 0.0);
    vec4 sample = texture(cloud_tex, pass_uv);

    if(sample == vec4(1.0f, 0.0f, 1.0f, 1.0f)) {
        discard;
    }

    pixel = mix(sample, vec4(sky_color, 1.0), 0.7);
}
