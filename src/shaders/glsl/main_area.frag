//author Ryan Bailey

#version 330 core
out vec4 frag_color;

uniform vec3 main_area_background_color;
uniform vec3 separator_color;
uniform vec2 bottom_left;
uniform vec2 top_right;
uniform int height_diff;
uniform int separator_width;

void main()
{
    vec2 adj_fragcoord = vec2(gl_FragCoord.x, gl_FragCoord.y + height_diff);
    if((adj_fragcoord.x - bottom_left.x < separator_width) ||
       (adj_fragcoord.y > top_right.y - separator_width))
    {
        frag_color = vec4(separator_color, 1.0f);
    }
    else
    {
        frag_color = vec4(main_area_background_color, 1.0f);
    }
}