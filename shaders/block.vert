#version 330 core

in vec3 pos;
in vec3 color;
in vec2 uv;

out vec4 pass_color;
out vec2 pass_uv;

uniform mat4 transform_mat; //Model
uniform mat4 view_mat; //View
uniform mat4 projection_mat; //Projection

void main()
{
    gl_Position = projection_mat * view_mat * transform_mat * vec4(pos, 1.0);
    pass_color = vec4(color, 1.0);
    pass_uv = uv;
}
