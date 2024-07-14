#version 410

out vec4 out_color;
uniform float time_elapsed;

void main()
{
    out_color = vec4(vec3(1, 0.5, 0.5), 1.);
}