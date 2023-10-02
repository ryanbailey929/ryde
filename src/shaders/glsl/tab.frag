//author Ryan Bailey

#version 330 core
out vec4 frag_color;

uniform vec3 color;
uniform vec2 bottom_left;
uniform vec2 top_right;
uniform int height_diff;
uniform int border_radius;

void main()
{
    vec2 adj_fragcoord = vec2(gl_FragCoord.x, gl_FragCoord.y + height_diff);
    if(pow(abs(adj_fragcoord.x - (bottom_left.x + border_radius)), 2) +
       pow(abs(adj_fragcoord.y - (bottom_left.y + border_radius)), 2) <=
       pow(border_radius, 2) ||
       pow(abs(adj_fragcoord.x - (top_right.x - border_radius)), 2) +
       pow(abs(adj_fragcoord.y - (bottom_left.y + border_radius)), 2) <=
       pow(border_radius, 2) ||
       pow(abs(adj_fragcoord.x - (bottom_left.x + border_radius)), 2) +
       pow(abs(adj_fragcoord.y - (top_right.y - border_radius)), 2) <=
       pow(border_radius, 2) ||
       pow(abs(adj_fragcoord.x - (top_right.x - border_radius)), 2) +
       pow(abs(adj_fragcoord.y - (top_right.y - border_radius)), 2) <=
       pow(border_radius, 2) ||
       (adj_fragcoord.x > bottom_left.x + border_radius &&
        adj_fragcoord.x < top_right.x - border_radius) ||
       (adj_fragcoord.y > bottom_left.y + border_radius &&
        adj_fragcoord.y < top_right.y - border_radius))
    {
        frag_color = vec4(color, 1.0f);
    }
    else
    {
        frag_color = vec4(0.0f, 0.0f, 0.0f, 0.0f); //transparent
    }
}