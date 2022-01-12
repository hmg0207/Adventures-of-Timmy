#version 430 core

in vec2 f_pos; 
in vec4 f_col;
in vec2 f_uv;

out vec4 colour;

uniform float timer;
uniform sampler2D tex;

void main()
{
    colour = vec4( f_col.r * ( cos( f_pos.x * 3.0 + timer ) + 1.0 ) * 0.5,
                   f_col.g * ( cos( f_pos.y * 9.0 + timer ) + 1.0 ) * 0.5,
                   f_col.b * ( cos( f_pos.x * 0.6 + timer ) + 1.0 ) * 0.5,
                   f_col.a ) * texture( tex, f_uv );             
}

