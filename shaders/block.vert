#version 330 core

in vec3 pos;
in vec3 color;
in vec2 uv;

out vec4 pass_color;
out vec2 pass_uv;
out float visibility;

uniform mat4 transform_mat; //Model
uniform mat4 view_mat; //View
uniform mat4 projection_mat; //Projection

const float fog_density = 0.007;
const float fog_gradient = 4.0;

void main()
{
    vec4 camera_coords = view_mat * transform_mat * vec4(pos, 1.0);
    gl_Position = projection_mat * camera_coords;
    pass_color = vec4(color, 1.0);
    pass_uv = uv;
    visibility = clamp(exp(-pow(length(camera_coords.xyz) * fog_density, fog_gradient)), 0.0, 1.0);
}
