#version 330 core
in vec3 normal;
in vec2 tex_coord;

uniform float u_time;

out vec4 FragColor;

void main()
{
    float x = abs(sin(u_time));
    FragColor = vec4(x, x, x, 1.0f);
}