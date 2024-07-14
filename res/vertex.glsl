#version 410


layout(location = 0) in vec2 in_position;
uniform float aspect_ratio;
uniform float time_elapsed;

void main()
{
    vec2 position = in_position;
    position.x = position.x / aspect_ratio;
    position.x = position.x + position.y*0.10 - 2.;
    position.x = position.x + time_elapsed * 1.;
    gl_Position = vec4(position, 0., 1.);
}